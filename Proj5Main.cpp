

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
  string fileName = "Sample.txt";

  //Gathers the file name to read sample data from and opens it for reading
  ifstream in;
  cout << "Please enter a file to read sample data from: ";
  cin >> fileName;
  in.open(fileName);

  //Reads in complexity or number of binary elements and population
  //which is the size of the sample set.
  in >> complexity;
  cout << "complexity is: " << complexity << endl;
  in >> population;
  cout << "population is: " << population << endl;

  //Reads in each piece of data, creates a new struct and pushes it
  //onto the list to be sent for training
  for (int i = 0; i < population; i++){
    single = new Sample;
    single->field = new double[complexity];
    for (int k = 0; k < complexity; k++){
      in >> single->field[k];
    }
    in >> single->classification;
    samples.push_back(*single);
  }

  //Creates the neural net with the samples collected
  Net *net = new Net(samples, complexity);

  //request amount of training rounds to select random samples from
  int trainTime;
  cout << "Please enter the amount of epochs: ";
  cin >> trainTime;

  //trains net and prints the results
  net->trainNet(trainTime);
  net->printNet();
  cout << "error rate is " << net->errorRate() << endl;

  //loop to take user input to test the net that's created.
  loop:
  while (true) {
    cout << "Please enter binary sequence of " << complexity << " elements\n"
    << "Enter '2' to quit, or '3' to print the weights.\n";
    for (int i = 0; i < complexity; i++){
      cin >> single->field[i];
      if (single->field[i] == 2) goto end;
      if (single->field[i] == 3){
        net->printNet();
        goto loop;
      }
    }
    net->applySample(*single);
    cout << "Classification is: " << net->outputMatch(*single) << endl;
  }
  end:
  delete net;
  return 0;
}
