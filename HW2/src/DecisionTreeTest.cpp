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
  if ((fp = fopen(argv[1], "w")) == NULL) {
    printf("cannot open file: testOutput.txt\n");
    exit(0);
  }
    double sum = 0;
  for (it1 = votes.begin() + 50; it1 != votes.end() - 50; it1++) {
    vector<Vote> inputVotes(it1, votes.end());
    vector<Vote> testVotes(votes.begin(), it1);
    DecisionTree * tree = makeDecisionTree(inputVotes);
    cnt = 0;
    ycnt = 0;
    ncnt = 0;
    for (it2 = testVotes.begin(); it2 != testVotes.end(); it2++)
      testDecisionTree(tree, it2);

    printf("training size: %lu\t", inputVotes.size());
    fprintf(fp,"%lu ", inputVotes.size());
    //printf("yes no.:\t%d, no no.:\t%d ", ycnt, ncnt);
    sum += (double)ycnt / cnt;
    printf("hit rate: %lf\n", (double)ycnt / (cnt));
    fprintf(fp, "%lf\n", (double)ycnt / (cnt));
  }
  printf("%lf\n", sum / 335);
  fprintf(fp, "%lf\n", sum / 335);
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
