#include "Network.h"

Network::Network(int p = 25, int t = 4000, double a = 0.8) {
  this->numOfLayers = 3;
  this->numOfUnits[0] = 64;
  this->numOfUnits[1] = p;
  this->numOfUnits[2] = 10;
  this->times = t;
  this->alpha = a;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < V_SIZE; j++)
      for (int k = 0; k < V_SIZE; k++)
        this->weight[i][j][k] = (double)rand()/RAND_MAX;
}

double Network::g(double x) {
  return (1.0 / (1.0 + exp(-x)));
}

double Network::g_(double x) {
  return (exp(-x) / ((1 + exp(-x)) * (1 + exp(-x))));
}

void readFile(FILE *fp, vector<Example> * examles) {
  while (!feof(fp)) {
    double x[V_SIZE];
    int o;
    for (int i = 0; i < V_SIZE; i++)
      fscanf(fp, "%lf,", &x[i]);
    fscanf(fp, "%d\n", &o);
    examles->push_back(Example(x, o));
  }
}

void Network::backPropLearning(vector<Example> * examples, vector<Example> * test) {
  int count = 0;
  vector<Example> * tmp = new vector<Example>(*examples);
  double lastExErr = 30;
  double lastTestErr = 30;
  double exErr = 30;
  double testErr = 30;
  while (1) {
    count++;
    vector<Example>::iterator e;
    random_shuffle(tmp->begin(), tmp->end());
    for (e = tmp->begin(); e != tmp->end(); e++) {
      // Get Output
      double a[3][V_SIZE];
      double delta[3][V_SIZE];
      double in[3][V_SIZE];
      for (int j = 0; j < V_SIZE; j++) a[0][j] = e->values[j];
      for (int l = 1; l < this->numOfLayers; l++) {
        for (int i = 0; i < this->numOfUnits[l]; i++) {
          in[l][i] = 0;
          for (int j = 0; j < this->numOfUnits[l]; j++)
            in[l][i] += weight[l - 1][j][i] * a[l - 1][j];
          a[l][i] = this->g(in[l][i]);
        }
      }
      // Get Error
      for (int i = 0; i < numOfUnits[2]; i++) {
        delta[2][i] = this->g_(in[2][i]) * (e->output[i] - a[2][i]);
      }
      //

      // updata weight
      for (int l = this->numOfLayers - 2; l >= 0; l--) {
        for (int j = 0; j < this->numOfUnits[l]; j++) {
          double sum = 0;
          for (int i = 0; i < this->numOfUnits[l + 1]; i++) {
            sum += weight[l][j][i] * delta[l + 1][i];
          }
          delta[l][j] = this->g_(in[l][j]) * sum;
          for (int i = 0; i < this->numOfUnits[l + 1]; i++) {
            weight[l][j][i] = weight[l][j][i] + this->alpha * a[l][j] * delta[l + 1][i];
          }
        }
      }
      // updata weight end
    }
    /*    
    exErr = this->getError(examples); 
    testErr = this->getError(test);
    cout << exErr << " " << testErr << endl;
    if (exErr < lastExErr && testErr > lastTestErr)
      cout << "bestTime: " << count - 1 << endl;
    lastExErr = exErr;
    lastTestErr = testErr;
    */ 
      if (count == this->times) return;;
  }
}


int Network::getOutput(Example e) {
  // Get Output
  double a[3][V_SIZE];
  double in[3][V_SIZE];
  for (int j = 0; j < V_SIZE; j++) a[0][j] = e.values[j];
  for (int l = 1; l < this->numOfLayers; l++) {
    for (int i = 0; i < this->numOfUnits[l]; i++) {
      in[l][i] = 0;
      for (int j = 0; j < this->numOfUnits[l]; j++)
        in[l][i] += this->weight[l - 1][j][i] * a[l - 1][j];
      a[l][i] = this->g(in[l][i]);
    }
  }
  int o = 0;
  for (int i = 1; i < 10; i++) {
    if (a[this->numOfLayers - 1][o] < a[this->numOfLayers - 1][i])
      o = i;
  }
  return o;
}

int Network::t(int output[10]) {
  for (int i = 0; i < 10; i++) {
    if (output[i] == 1) return i;
  }
  return 0;
}

double Network::testNetwork(vector<Example> * examples) {
  vector<Example>::iterator e;
  int hit = 0;
  for (e = examples->begin(); e != examples->end(); e++) {
    if (getOutput(*e) == t(e->output)) hit++;
  }
  cout << "hit: " << hit << ", test size:" <<  examples->size() << endl;
  cout << "hit rate: " << (double)hit / examples->size() << endl;
  return (double)hit / examples->size();
}

double Network::getError(vector<Example> * es) {
  vector<Example>::iterator e;
  int err = 0;
  for (e = es->begin(); e != es->end(); e++) {
    int a = getOutput(*e);
    int b = t(e->output);
    if (a != b) err++;
  }
  return (double)err/es->size();
}


void Network::Normalization(vector<Example> * examples) {
  vector<Example>::iterator e;
  for (e = examples->begin(); e != examples->end(); e++) {
    for (int i = 0; i < V_SIZE; i++) {
      e->values[i] = e->values[i] / 16;
    }
  }
}
