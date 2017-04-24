#ifndef NET_H_
#define NET_H_

#include <list>

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
  inputNode *input;
  double accumulator;

public:
  Net(list<Sample>);
};




#endif
