#ifndef NET_H_
#define NET_H_

#include <list>
#include <iostream>
#include <math.h>
#include <cstdlib>

//struct for the sample data
using namespace std;
struct Sample{
  double *field;
  double classification;
};

//struct for each input node
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
  /*accumulator sums the values of the
  nodes multiplied by their weights,
  swing determines how much a weight
  can change if there is a bad
  classification during training*/
  double accumulator, swing;

  void initInput(int);
  void adjustWeight(Sample);

public:
  void printNet();
  int outputMatch(Sample);
  void applySample(Sample);
  double errorRate();
  void trainNet(int);
  Net(list<Sample>, int);
};

#endif
