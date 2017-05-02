#include "Net.h"
using namespace std;

/*Function to train the net based on the amount of rounds
specified by the user. Selects a sample at random
as many times as there are samples per round.
some samples may not be selected each round
as a result of this method.*/
void Net::trainNet(int rounds){
  for (int i = 0; i < rounds; i++){
    for (int l = 0; l < samples.size(); l++){
      lit = samples.begin();
      advance(lit, rand() % samples.size());
      applySample(*lit);
      outputMatch(*lit);
      adjustWeight(*lit);
    }
    if (errorRate() == 0) return;
  }
}

/*Function to split up each element of the sample data
among the neurons. Each value is multiplied by the weight
and added to accumulator. Accumulator is the element that
ultimately determines the classifaction, or in case of
training whether the weights need to be tweaked.*/
void Net::applySample(Sample sample){
  accumulator = 0;
  for (int i = 0; i < numInputs; i++){
    input[i].currentValue = sample.field[i];
    accumulator += input[i].currentValue * input[i].weight;
  }
  accumulator += dummy.currentValue * dummy.weight;
}

/*This function returns the classification to
the user function (1 or -1) and assigns the output
for the neural net in terms of binary representation*/
int Net::outputMatch(Sample sample){
  if (accumulator > 0){
    output = 1;
    return output;
  }
  else output = 0;
  return -1;
}

/*This algorithm adjusts the weights in accordance
with the feedback attained from training sessions*/
void Net::adjustWeight(Sample sample){
  for (int i = 0; i < numInputs; i++){
    input[i].weight += swing * (sample.classification - output) * input[i].currentValue;
  }
  dummy.weight += swing * (sample.classification - output)
              * dummy.currentValue;
}

/*This function tallies how many wrong classifications
according to the sample data the network produces*/
double Net::errorRate(){
  double tally = 0;
  lit = samples.begin();
  while (lit != samples.end()){
    applySample(*lit);
    outputMatch(*lit);
    if (output != lit->classification) tally++;
    lit++;
  }
  return tally / samples.size();
}

/*initializes all of the values of the
net including the weight and value of the
dummy weight*/
void Net::initInput(int size){
  input = new inputNode[size];
  for (int i = 0; i < size; i++){
    input[i].weight = 0;
  }
  dummy.weight = 0;
  dummy.currentValue = 1;
}

//function to print the weights of all edges
void Net::printNet(){
  for (int i = 0; i < numInputs; i++){
    cout << "w" << i << " = " << input[i].weight << endl;
  }
  cout << "dummy = " << dummy.weight << endl;
}

//constructor for neural net. sets the L value (swing)
Net::Net(list<Sample> samples, int complexity){
  numInputs = complexity;
  this->samples = samples;
  initInput(samples.size());
  accumulator = 0;
  swing = (double).5 / samples.size();
  cout << "swing is " << swing << endl;
}
