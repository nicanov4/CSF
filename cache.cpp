#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include<algorithm>
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
list<unsigned long long> luaASS;
map<unsigned long long, int> cacheASS;

unsigned long long hitsSET;
unsigned long long missesSET;
map<unsigned long long, list<unsigned long long> luaSET;
map<unsigned long long, map<unsigned long long, int>> cacheSET;

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
  if (cacheASS[address] == 0) {
    if (counterASS >= 8192) {
      cacheASS[luaASS.back()] = 0;
      luaASS.pop_back();
      luaASS.push_front(address);
    } else {
      luaASS.push_front(address);
      counterASS++;
    }
    cacheASS[address] = 1;
    missesASS++;
  } else {
    hitsASS++;
    luaASS.remove(address);
    luaASS.push_front(address);
  }
}

int set() {
  int index = address & 2047;
  map<unsigned long long, int> scSET = cacheSET[index];
  list<unsigned long long> sluaSET = luaSET[index];
  if(scSET[address] == 0) {
    if (sluaSET.size() >= 4) {
      scSET[sluaSET.back()] = 0;
      sluaSET.pop_back();
      sluaSET.push_front(address);
    } else {
      sluaSET.push_front(address);
    }
    scSET[address] = 1;
    missesSET++;
  } else {
    hitsSET++;
    sluaSET.remove(address);
    luaASS.push_front(address);
  }
  luaSET[index] = sluaSET;
  cacheSET[index] = scSET;
}

int main (int argc, char* argv[]) {
  if (argc > 4) {
    return 1;
  }

  counterASS = 0;
  while (scanf("%llx %c", &address, &flag) != EOF) {
    //dir();
    //ass();
    set();
  }

  printf("DIR: %20llu %20llu\n",hitsDIR, missesDIR);
  printf("ASS: %20llu %20llu\n",hitsASS, missesASS);
  printf("SET: %20llu %20llu\n",hitsSET, missesSET);
  printf("BLK: %20llu %20llu\n",hitsBLK, missesBLK);
  printf("NWA: %20llu %20llu\n",hitsNWA, missesNWA);
  printf("PRF: %20llu %20llu\n",hitsPRF, missesPRF);
}
