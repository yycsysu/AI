#include "DecisionTree.h"

string attributs[16] = {
  "handicapped-infants",
  "water-project-cost-sharing",
  "adoption-of-the-budget-resolution",
  "physician-fee-freeze",
  "el-salvador-aid",
  "religious-groups-in-schools",
  "anti-satellite-test-ban",
  "aid-to-nicaraguan-contras",
  "mx-missile",
  "immigration",
  "synfuels-corporation-cutback",
  "education-spending",
  "superfund-right-to-sue",
  "crime",
  "duty-free-exports",
  "export-administration-act-south-africa"
};
string v[3] = { "y", "n", "?" };

bool used[16];
int usedValueNum;

DecisionTree * makeDecisionTree(vector<Vote> votes) {
  Vote vote;
  DecisionTree* decisionTree;
  char ch = 0;

  usedValueNum = 0;
  memset(used, false, sizeof(bool) * 16);
  DecisionTree* def = new DecisionTree();

  decisionTree = decisionTreeLearning(votes, used, def);

  return decisionTree;
}


DecisionTree * decisionTreeLearning(vector<Vote> votes, bool attribs[], DecisionTree * def) {
  DecisionTree * classification = new DecisionTree();
  if (votes.empty()) {
    return def;
  } else if (checkSameClassification(votes, classification)) {
    return classification;
  } else if (usedValueNum == 16) {
    return majorityValue(votes);
  } else {
    int best = chooseAttribute(attribs, votes);
    if (best == -1)
      return majorityValue(votes);
    attribs[best] = true;
    usedValueNum++;

    DecisionTree * tree = new DecisionTree(attributs[best], best, votes);
    DecisionTree * m = majorityValue(votes);

    for (int i = 0; i < 3; i++) {
      vector<Vote>::iterator it;
      vector<Vote> tmp;
      for (it = votes.begin(); it != votes.end(); it++) {
        if (it->values[best] == v[i]) {
          tmp.push_back(*it);
        }
      }
      DecisionTree * subtree = decisionTreeLearning(tmp, attribs, m);
      tree->next[i] = subtree;
    }

    attribs[best] = false;
    usedValueNum--;
    return tree;
  }

}

int chooseAttribute(bool attribs[], vector<Vote> votes) {
  vector<Vote>::iterator it;
  double maxGain = 0;
  double maxD = 0;
  int bestValue = -1;
  for (int i = 0; i < 16; i++) {
    if (attribs[i] == true) continue;
    int all = 0, p = 0, n = 0;
    int pi[3] = { 0, 0, 0 };
    int ni[3] = { 0, 0, 0 };
    double epi[3] = { 0, 0, 0 };
    double eni[3] = { 0, 0, 0 };
    int vCount[3] = { 0, 0, 0 };
    //string v[3] = { "y", "n", "?" };

    // p + n : all, p : d, n : r
    all = votes.size();
    for (it = votes.begin(); it != votes.end(); it++) {
      for (int j = 0; j < 3; j++)
        if (it->values[i] == v[j]) {
          vCount[j]++;
          if (it->className == "republican") {
            ni[j]++;
            n++;
          } else if (it->className == "democrat") {
            pi[j]++;
            p++;
          }
          break;
        }
    }

    double D = 0;
    for (int j = 0; j < 3; j++) {
      epi[j] = p * (double)(pi[j] + ni[j]) / (p + n);
      eni[j] = n * (double)(pi[j] + ni[j]) / (p + n);
      D += (((pi[j] - epi[j]) * (pi[j] - epi[j])) / epi[j]
        + ((ni[j] - eni[j]) * (ni[j] - eni[j])) / eni[j]);
    }
    if (D < 4.61) continue;

    double gain = I(p / (p + n), n / (p + n));
    for (int j = 0; j < 3; j++) {
      if ((pi[j] + ni[j]) != 0) {
        gain -= ((double)(pi[j] + ni[j]) / (p + n)) * I(((double)pi[j] / (pi[j] + ni[j])), ((double)ni[j] / (pi[j] + ni[j])));
      }
    }
    if (bestValue == -1 || gain > maxGain) {
      maxGain = gain;
      bestValue = i;
    }
  }
  return bestValue;
}

DecisionTree * majorityValue(vector<Vote> votes) {
  vector<Vote>::iterator it;
  int rCount = 0, dCount = 0;
  for (it = votes.begin(); it != votes.end(); it++) {
    if (it->className == "republican")
      rCount++;
    else if (it->className == "democrat")
      dCount++;
  }
  if (dCount > rCount)
    return new DecisionTree("democrat", -2,votes);
  else return new DecisionTree("republican", -1, votes);
}

bool checkSameClassification(vector<Vote> votes, DecisionTree * classification) {
  vector<Vote>::iterator it;
  it = votes.begin();
  string className = it->className;
  while (++it != votes.end()) {
    if (it->className != className)
      return false;
  }
  classification->attributeName = className;
  classification->index = -2;
  classification->votes = votes;
  return true;
}

void readFile(FILE* fp, vector<Vote> & votes) {
  char ch;
  Vote vote;
  while (1) {
    string className = "";
    while ((ch = fgetc(fp)) && (ch != ',')) {
      className += ch;
    }
    vote.className = className;
    int count = 0;
    while ((ch = fgetc(fp)) && (ch != '\n') && (ch != EOF)) {
      if (ch == 'y' || ch == 'n' || ch == '?') vote.values[count++] = ch;
    }
    votes.push_back(vote);
    if (ch == EOF) break;
  }
}


double I(double a, double b) {
  double result = 0;
  if (a != 0)
    result -= a * log2(a);
  if (b != 0)
    result -= b * log2(b);
  return result;
}


void testTreeDepth(DecisionTree *decisionTree, int depth) {
  if (decisionTree->attributeName == "republican" || decisionTree->attributeName == "democrat") printf("%d ", depth);

  depth++;
  for (int i = 0; i < 3; i++)
    if (decisionTree->next[i] != NULL)testTreeDepth(decisionTree->next[i], depth);

}
