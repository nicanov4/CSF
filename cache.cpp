#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <list>
#include <tuple>
#include <map>
using namespace std;

unsigned long long int address;
char flag;

unsigned long long int hitsDIR;
unsigned long long int missesDIR;
map<int, tuple<unsigned long long int, char>> cacheDIR;

unsigned long long int hitsASS;
unsigned long long int missesASS;
int counterASS;
list<int> stackASS;
map<unsigned long long int, int> countASS;

unsigned long long int hitsSET;
unsigned long long int missesSET;

unsigned long long int hitsBLK;
unsigned long long int missesBLK;

unsigned long long int hitsNWA;
unsigned long long int missesNWA;

unsigned long long int hitsPRF;
unsigned long long int missesPRF;

int dir() {
  int index = address & 8191;
  auto in = make_tuple(address, flag);
  if (get<0>(cacheDIR[index]) != address) {
    missesDIR++;
    cacheDIR[index] = in;
  } else {
    hitsDIR++;
    cacheDIR[index] = in;
  }
}

int ass() {
  auto in = make_tuple(address, flag);
  if (counterASS < 8191) {
    if (countASS[address] == 0) {
      missesASS++;
      countASS[address] += 1;
      stackASS.remove(address);
      stackASS.push_back(address);
      counterASS++;
    } else {
      stackASS.remove(address);
      stackASS.push_back(address);
      hitsASS++;
    }
  } else {
    if (countASS[address] == 0) {
      int temp = stackASS.front();
      stackASS.remove(temp);
      countASS[temp] == 0;
      stackASS.push_back(address);
      countASS[address] += 1;
      missesASS++;
      counterASS++;
    } else {
      stackASS.remove(address);
      stackASS.push_back(address);
      hitsASS++;
    }
  }
}

int main (int argc, char* argv[]) {
  if (argc > 4) {
    return 1;
  }

  counterASS = 0;
  while (scanf("%llx %c", &address, &flag) != EOF) {
    dir();
    ass();
  }

  printf("DIR: %20llu %20llu\n",hitsDIR, missesDIR);
  printf("ASS: %20llu %20llu\n",hitsASS, missesASS);
  printf("SET: %20llu %20llu\n",hitsSET, missesSET);
  printf("BLK: %20llu %20llu\n",hitsBLK, missesBLK);
  printf("NWA: %20llu %20llu\n",hitsNWA, missesNWA);
  printf("PRF: %20llu %20llu\n",hitsPRF, missesPRF);
}
