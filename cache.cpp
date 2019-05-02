#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <list>
#include <tuple>
#include <map>
using namespace std;

unsigned long long address;
char flag;

unsigned long long hitsDIR;
unsigned long long missesDIR;
map<int, tuple<unsigned long long, char>> cacheDIR;

unsigned long long hitsASS;
unsigned long long missesASS;
int counterASS;
map<unsigned long long, char> cacheASS;

unsigned long long hitsSET;
unsigned long long missesSET;

unsigned long long hitsBLK;
unsigned long long missesBLK;

unsigned long long hitsNWA;
unsigned long long missesNWA;

unsigned long long hitsPRF;
unsigned long long missesPRF;

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
  list<unsigned long long>::iterator it;
  it = find(cacheASS.begin(), cacheASS.end(), address);
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
