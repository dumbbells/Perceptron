#include "Net.h"
using namespace std;

void Net::applySample(Sample sample){
  accumulator = 0;
  for (int i = 0; i < numInputs; i++){
    input[i].currentValue = sample.field[i];
    accumulator += input[i].currentValue * input[i].weight;
    //cout << i << " is " << input[i].currentValue * input[i].weight << endl;
  }
  accumulator += dummy.currentValue * dummy.weight;
  //cout << "dummy is " << dummy.currentValue * dummy.weight << endl;
//  cout << "accumulator is: " << accumulator << endl;
}

int Net::outputMatch(Sample sample){
  if (accumulator > 0) output = 1;
  else output = -1;
  return output;
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

double Net::errorRate(){
  double tally = 0;
  lit = samples.begin();
  while (lit != samples.end()){
    applySample(*lit);
    if (outputMatch(*lit) != lit->classification) tally++;
    lit++;
  }
  return tally / samples.size();
}

void Net::trainNet(int rounds){
  cout << "begin training session \n";
  for (int i = 0; i < rounds; i++){
    cout << "round " << i << endl;
    for (int l = 0; l < samples.size(); l++){
      lit = samples.begin();
      advance(lit, rand() % samples.size());
      applySample(*lit);
      if (outputMatch(*lit) != lit->classification){
        cout << "no match...\n";
        adjustWeight(*lit);
      }
      else cout << "match!\n";
      cout << endl;
    }
    if (errorRate() == 0) return;
  }
}

void Net::initInput(int size){
  input = new inputNode[size];
  for (int i = 0; i < size; i++){
    input[i].weight = 0;
  }
  dummy.weight = 0;
  dummy.currentValue = 1;
}

Net::Net(list<Sample> samples, int complexity){
  numInputs = complexity;
  this->samples = samples;
  initInput(samples.size());
  accumulator = 0;
  swing = (double).5 / samples.size();
  cout << "swing is " << swing << endl;
}
