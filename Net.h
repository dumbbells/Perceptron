#ifndef NET_H_
#define NET_H_

#include <list>
#include <iostream>
#include <math.h>
#include <cstdlib>

using namespace std;
struct Sample{
  double *field;
  double classification;
};

struct inputNode{
  double weight;
  double currentValue;
};

class Net{
  list <Sample> samples;
  list <Sample>::iterator lit;
  inputNode* input;
  inputNode dummy;
  int numInputs, output;
  double accumulator, swing;

  void initInput(int);
  void adjustWeight(Sample);

public:
  int outputMatch(Sample);
  void applySample(Sample);
  double errorRate();
  void trainNet(int);
  Net(list<Sample>, int);
};




#endif
