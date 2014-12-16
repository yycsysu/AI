#include <cstdio>
#include "DecisionTree.h"

int cnt;
int ycnt;
int ncnt;
string vt[3] = { "y", "n", "?" };

void testDecisionTree(DecisionTree *decisionTree, vector<Vote>::iterator it);

int main(int argc, char** argv) {

  vector<Vote> votes;
  vector<Vote>::iterator it1;
  vector<Vote>::iterator it2;
  FILE *fp;
  if ((fp = fopen("dataset.txt", "r")) == NULL) {
    printf("cannot open file: dataset.txt\n");
    exit(0);
  }
  readFile(fp, votes);
  fclose(fp);
  if ((fp = fopen("testOutput.txt", "w")) == NULL) {
    printf("cannot open file: testOutput.txt\n");
    exit(0);
  }
  for (it1 = votes.begin() + 10; it1 != votes.end() - 10; it1++) {
    vector<Vote> testVotes(it1, votes.end());
    vector<Vote> inputVotes(votes.begin(), it1);
    DecisionTree * tree = makeDecisionTree(inputVotes);
    cnt = 0;
    ycnt = 0;
    ncnt = 0;
    for (it2 = testVotes.begin(); it2 != testVotes.end(); it2++)
      testDecisionTree(tree, it2);

    printf("training size: %lu\t", inputVotes.size());
    fprintf(fp,"%lu ", inputVotes.size());
    //printf("yes no.:\t%d, no no.:\t%d ", ycnt, ncnt);

    printf("hit rate: %lf\n", (double)ycnt / (cnt));
    fprintf(fp, "%lf\n", (double)ycnt / (cnt));
  }
  fclose(fp);

  return 0;
}

void testDecisionTree(DecisionTree *decisionTree, vector<Vote>::iterator it) {
  if (decisionTree->attributeName == "republican" || decisionTree->attributeName == "democrat") {
    cnt++;
    if (it->className == decisionTree->attributeName) {
      ycnt++;
      return;
    } else {
      ncnt++;
      return;
    }
  }
  for (int i = 0; i < 3; i++) {
    if (it->values[decisionTree->index] == vt[i])
      testDecisionTree(decisionTree->next[i], it);
  }
}
