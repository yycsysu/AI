#ifndef _DECISIONTREE_H
#define _DECISIONTREE_H

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

struct Vote {
  string className;
  string values[16];
};

struct DecisionTree {
  string attributeName;
  int index;
  vector<Vote> votes;
  DecisionTree *next[3];
  DecisionTree(string attr = string("republican"), int i = -1, vector<Vote> vs = vector<Vote>()) {
    attributeName = attr;
    index = i;
    votes = vs;
    next[0] = NULL;
    next[1] = NULL;
    next[2] = NULL;
  }
};


DecisionTree * makeDecisionTree(vector<Vote> votes);
void readFile(FILE*, vector<Vote> & votes);
DecisionTree* decisionTreeLearning(vector<Vote> votes, bool attribs[], DecisionTree * def);
bool checkSameClassification(vector<Vote> votes, DecisionTree * classification);
int chooseAttribute(bool attribs[], vector<Vote> votes);
DecisionTree* majorityValue(vector<Vote> votes);
double I(double a, double b);
void testTreeDepth(DecisionTree *decisionTree, int depth);

#endif // !_DECISIONTREE_H
