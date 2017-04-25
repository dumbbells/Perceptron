

#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include "Net.h"

using namespace std;

int main(){
  int complexity, population;
  list <Sample> samples;
  Sample* single;

  ifstream in;
  in.open("Sample.txt");

  in >> complexity;
  cout << "complexity is: " << complexity << endl;
  in >> population;
  cout << "population is: " << population << endl;

  for (int i = 0; i < population; i++){
    single = new Sample;
    single->field = new double[complexity];
    for (int k = 0; k < complexity; k++){
      in >> single->field[k];
    }
    in >> single->classification;
    samples.push_back(*single);
  }

  Net *net = new Net(samples, complexity);

  int trainTime;
  cout << "Please enter the amount of training rounds: ";
  cin >> trainTime;

  net->trainNet(trainTime);
  cout << "error rate is " << net->errorRate() << endl;

  delete net;
  return 0;
}
