#include <iostream>
#include <fstream>
#include<stdio.h>
#include<string.h>
#include<array>

using namespace std;


int main (int argc, char* argv[]) {
  string x = "pendeho";
  int temp = x.size();
  int temp2 = 0;
  cout << temp/2;
  for (int i = 0; i < (x.size()/2); i++) {
    temp2 = x[temp];
    x[temp] = x[i];
    x[i] = temp2;
  }
  cout << x;

}
