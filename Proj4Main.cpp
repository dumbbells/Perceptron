

#include <iostream>
#include <list>
#include <fstream>
#include <string>

using namespace std;

int main(){
  Net *net;
  net = new Net(new list<Samples>);

  delete net;

  return 0;
}
