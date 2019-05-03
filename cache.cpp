#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include<algorithm>
#include<vector>
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
map<unsigned long long, list<unsigned long long>> luaSET;
map<unsigned long long, map<unsigned long long, int>> cacheSET;

unsigned long long hitsBLK;
unsigned long long missesBLK;
unsigned long long cacheBLK[256][4][8];
vector<int> luaBLK[256];

unsigned long long hitsNWA;
unsigned long long missesNWA;
unsigned long long cacheNWA[256][4][8];
vector<int> luaNWA[256];

unsigned long long hitsPRF;
unsigned long long missesPRF;
unsigned long long cachePRF[256][4][8];
vector<int> luaPRF[256];

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
    sluaSET.push_front(address);
  }
  luaSET[index] = sluaSET;
  cacheSET[index] = scSET;
}

int blk() {
  int firstIndex = address >> 3 & 255;
  int secondIndex = address & 7;
  bool hit = false;
  for (int j = 0; j < 4; j++) {
    if (cacheBLK[firstIndex][j][secondIndex] == address) {
      luaBLK[firstIndex].erase(find(luaBLK[firstIndex].begin(), luaBLK[firstIndex].end(), j));
      luaBLK[firstIndex].insert(luaBLK[firstIndex].begin(), j);
      hitsBLK++;
      hit = true;
      break;
    }
  }
  if (!hit) {
    int index = 0;
    if (luaBLK[firstIndex].size() < 4) {
      index = luaBLK[firstIndex].size();
    } else {
      index = luaBLK[firstIndex].back();
      luaBLK[firstIndex].pop_back();
    }
    for (int i = 0; i < 8; i++) {
      cacheBLK[firstIndex][index][i] = address - secondIndex + i;
    }
    luaBLK[firstIndex].insert(luaBLK[firstIndex].begin(), index);
    missesBLK++;
  }
}

int nwa() {
  int firstIndex = address >> 3 & 255;
  int secondIndex = address & 7;
  bool  hit = false;
  for (int j = 0; j < 4; j++) {
    if (cacheNWA[firstIndex][j][secondIndex] == address) {
      luaNWA[firstIndex].erase(find(luaNWA[firstIndex].begin(), luaNWA[firstIndex].end(), j));
      luaNWA[firstIndex].insert(luaNWA[firstIndex].begin(), j);
      hitsNWA++;
      hit = true;
      break;
    }
  }
  if (!hit) {
    if (flag == 'L') {
      int index = 0;
      if (luaNWA[firstIndex].size() < 4) {
        index= luaNWA[firstIndex].size();
      } else {
        index = luaNWA[firstIndex].back();
        luaNWA[firstIndex].pop_back();
      }
      for (int i = 0; i < 8; i++) {
        cacheNWA[firstIndex][index][i] = address - secondIndex + i;
      }
      luaNWA[firstIndex].insert(luaNWA[firstIndex].begin(), index);
    }
    missesNWA++;
  }
}

int prf() {
  bool hit = false;
  int firstIndex = address >> 3 & 255;
  int secondIndex = address & 7;

  for (int j = 0; j < 4; j++) {
    if (cachePRF[firstIndex][j][secondIndex] == address) {
      luaPRF[firstIndex].erase(find(luaPRF[firstIndex].begin(), luaPRF[firstIndex].end(), j));
      luaPRF[firstIndex].insert(luaPRF[firstIndex].begin(), j);
      hitsPRF++;
      hit = true;
      break;
    }
  }
  if (!hit) {
    if (flag == 'L') {
      int index = 0;
      if (luaPRF[firstIndex].size() < 4) {
        index = luaPRF[firstIndex].size();
      } else {
        index = luaPRF[firstIndex].back();
        luaPRF[firstIndex].pop_back();
      }
      for (int i = 0; i < 8; i++) {
        cachePRF[firstIndex][index][i] = address - secondIndex + i;
      }
      luaPRF[firstIndex].insert(luaPRF[firstIndex].begin(), index);
    }
    missesPRF++;
  }
  if (!hit && flag == 'L') {
    bool hit2 = false;
    address += 8;
    firstIndex = address >> 3 & 255;
    secondIndex = address & 7;

    for (int k = 0; k < 4; k++) {
      if (cachePRF[firstIndex][k][secondIndex] == address) {
        luaPRF[firstIndex].erase(find(luaPRF[firstIndex].begin(), luaPRF[firstIndex].end(), k));
        luaPRF[firstIndex].insert(luaPRF[firstIndex].begin(), k);
        hit2 = true;
        break;
      }
    }
    if (!hit2) {
      int index = 0;
      if (luaPRF[firstIndex].size() < 4) {
        index = luaPRF[firstIndex].size();
      } else {
        index = luaPRF[firstIndex].back();
        luaPRF[firstIndex].pop_back();
      }
      for (int o = 0; o < 8; o++) {
        cachePRF[firstIndex][index][o] = address - secondIndex + o;
      }
      luaPRF[firstIndex].insert(luaPRF[firstIndex].begin(), index);
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
    set();
    blk();
    nwa();
    prf();
  }

  printf("DIR: %20llu %20llu\n",hitsDIR, missesDIR);
  printf("ASS: %20llu %20llu\n",hitsASS, missesASS);
  printf("SET: %20llu %20llu\n",hitsSET, missesSET);
  printf("BLK: %20llu %20llu\n",hitsBLK, missesBLK);
  printf("NWA: %20llu %20llu\n",hitsNWA, missesNWA);
  printf("PRF: %20llu %20llu\n",hitsPRF, missesPRF);
}
