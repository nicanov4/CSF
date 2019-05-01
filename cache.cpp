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

unsigned long long int hitsSET;
unsigned long long int missesSET;

unsigned long long int hitsBLK;
unsigned long long int missesBLK;

unsigned long long int hitsNWA;
unsigned long long int missesNWA;

unsigned long long int hitsPRF;
unsigned long long int missesPRF;

int dir() {
  auto in = make_tuple(address, flag);
  int index = address & 8192;
  if (get<0>(cacheDIR[index]) == address) {
    if (get<1>(cacheDIR[index]) == flag) {
      hitsDIR++;
      cacheDIR[index] = in;
    }
  } else {
    missesDIR++;
    cacheDIR[index] = in;
  }
}

int main (int argc, char* argv[]) {
  if (argc > 4) {
    return 1;
  }

  int count = 0;
  while (scanf("%llx %c", &address, &flag) != EOF) {
    dir();
    count++;
    if (count > 127) {
      return 1;
    }
  }

  printf("DIR: %20llu %20llu\n",hitsDIR, missesDIR);
  printf("ASS: %20llu %20llu\n",hitsASS, missesASS);
  printf("SET: %20llu %20llu\n",hitsSET, missesSET);
  printf("BLK: %20llu %20llu\n",hitsBLK, missesBLK);
  printf("NWA: %20llu %20llu\n",hitsNWA, missesNWA);
  printf("PRF: %20llu %20llu\n",hitsPRF, missesPRF);
}
