#include "Network.h"

int main(int argc, char** argv) {
  FILE *fp;
  vector<Example> * es = new vector<Example>();
  vector<Example> * test = new vector<Example>();
  int size = 0;
  if ((fp = fopen("digitstra.txt", "r")) == NULL) {
    printf("cannot open file: dataset.txt\n");
    exit(0);
  }
  readFile(fp, es);
  fclose(fp);
  if ((fp = fopen("digitstest.txt", "r")) == NULL) {
    printf("cannot open file: dataset.txt\n");
    exit(0);
  }
  readFile(fp, test);
  fclose(fp);

  Network *network = new Network(25, 20000, 1.8);
  network->Normalization(es);
  network->Normalization(test);
  int bestP = 10;
  double bestHit = 0;
  //29 + 25
  //11 + 45
  for (int i = 1; i <= 64; i++) {
    network = new Network(i, 90,1.4); 
    network->backPropLearning(es, test);
    double hit = network->testNetwork(test);
    if (hit > bestHit) {
      bestP = i;
      bestHit = hit;
    }
  }
  cout << "best: " << bestP << ", " << bestHit << endl;
  return 0;
}
