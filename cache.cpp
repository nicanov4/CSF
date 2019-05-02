#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>
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
vector<unsigned long long int> cacheASS;

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
  if (find(cacheASS.begin(), cacheASS.end(), address) != cacheASS.end()) {
    cacheASS.erase(curr);
    cacheASS.insert(cacheASS.begin(), address);
    hitsASS++;
  } else {
    if (counterASS >= 8192) {
      cacheASS.pop_back();
      cacheASS.insert(cacheASS.begin(), address);
      counterASS++;
    }
    missesASS++;
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
