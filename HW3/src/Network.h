#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#define ALPHA 0.5
#define V_SIZE 64

using namespace std;

struct Example{
  double values[V_SIZE];
  int output[10];
  Example(double v[], int o = 0) {
    for (int i = 0; i < 10; i++) output[i] = 0;
    output[o] = 1;
    for (int i = 0; i < V_SIZE; i++) {
      values[i] = v[i];
    }
  }
};

class Network {
 private:
  double alpha;
  int times;
  int numOfLayers;
  int numOfUnits[3];
  double weight[2][V_SIZE][V_SIZE];
 public:
  Network(int p, int t, double a);
  double g(double in);
  double g_(double in);
  int t(int output[]);
  void backPropLearning(vector<Example> * examples, vector<Example> * test);
  int getOutput(Example e);
  double testNetwork(vector<Example> * examples);
  double getError(vector<Example> * es);
  void Normalization(vector<Example> * examples);
};

void readFile(FILE * fp, vector<Example> * examles);
