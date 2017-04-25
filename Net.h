#ifndef NET_H_
#define NET_H_

#include <list>
#include <iostream>

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
  int numInputs;
  double accumulator, swing, dummyWeight;

  void initInput(int);
  bool outputMatch();
  double applySample(Sample);

public:
  void trainNet(int);
  Net(list<Sample>, int);
};




#endif
