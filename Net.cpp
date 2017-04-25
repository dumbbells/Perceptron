#include "Net.h"
using namespace std;

double Net::applySample(Sample sample){
  for (int i = 0; i < numInputs; i++){
    input[i].currentValue = sample.field[i];
  }
}

bool Net::outputMatch(){
  return false;
}

void Net::trainNet(int rounds){
  cout << "begin training session \n";
  for (int i = 0; i < rounds; i++){
    lit = samples.begin();
    while (lit != samples.end()){
      applySample(*lit);
      if (!outputMatch()){
        //adjust weight
        cout << "weight adjustment\n";
      }
      else cout << "output matches!\n";
      lit++;
    }
  }
}

void Net::initInput(int size){
  cout << "initializing the nodes\n";
  input = new inputNode[size];
  for (int i = 0; i < size; i++){
    input[i].weight = 0;
  }
}

Net::Net(list<Sample> samples, int complexity){
  cout << "net created" << endl;
  numInputs = complexity;
  this->samples = samples;
  initInput(samples.size());
  accumulator = 0;
  swing = 1 / samples.size();
}
