#include "Net.h"
using namespace std;

void Net::applySample(Sample sample){
  for (int i = 0; i < numInputs; i++){
    input[i].currentValue = sample.field[i];
    accumulator += input[i].currentValue * input[i].weight;
  }
}

bool Net::outputMatch(Sample sample){
  if (accumulator > 0) output = 1;
  else output = -1;
  if (output == sample.classification) return true;
  else return false;
}

void Net::adjustWeight(Sample sample){
  cout << output << " and we wanted " << sample.classification << endl;
  for (int i = 0; i < numInputs; i++){
    input[i].weight += swing * (sample.classification - output) * input[i].currentValue;
    cout << "new weight " << i << " = " << input[i].weight << endl;
  }
  dummy.weight += swing * (sample.classification - output) * dummy.currentValue;
  cout << "dummy weight = " << dummy.weight << endl;
}

void Net::trainNet(int rounds){
  cout << "begin training session \n";
  for (int i = 0; i < rounds; i++){
    cout << "round " << i << endl;
    lit = samples.begin();
    while (lit != samples.end()){
      applySample(*lit);
      if (!outputMatch(*lit)){
        cout << "no match...\n";
        adjustWeight(*lit);
      }
      else cout << "match!\n";
      lit++;
      accumulator = 0;
      cout << endl;
    }
  }
}

void Net::initInput(int size){
  input = new inputNode[size];
  for (int i = 0; i < size; i++){
    input[i].weight = 0;
  }
  dummy.weight = 0;
  dummy.currentValue = -1;
}

Net::Net(list<Sample> samples, int complexity){
  numInputs = complexity;
  this->samples = samples;
  initInput(samples.size());
  accumulator = 0;
  swing = (double)1 / samples.size();
  cout << "swing is " << swing << endl;
}
