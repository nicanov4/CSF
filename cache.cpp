#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <list>
#include <tuple>
#include <map>
#include<algorithm>
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
int counterSET;
map<int, list<unsigned long long>> cacheSET;

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
  auto in = make_tuple(address, flag);
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
  map<int, vector<unsigned long long>>::iterator iteratorSET1
    = cacheSET.find(index));
    if (itSET != cacheSET.end()){
      vector<unsigned long long>::iterator iteratorSET2
        = find(iteratorSET1->second.begin(), iteratorSET1->second.end(), address);
      if (iteratorSET2 != iteratorSET1->second.end()) {
        hitsSET += 1;
        itSET->second.erase(itSETvec);
      } else {
        missesSET += 1;
        if (itSET->second.size() >= 4)
          itSET->second.pop_back();
      }
      iteratorSET1->second.insert(iteratorSET->second.begin(), address);
    } else {
      missesSET += 1;
      vector<unsigned long long> temp;
      temp.insert(temp.begin(), address);
      cacheSET.insert(make_pair(hasher(address, 11), temp));
    }

}

int main (int argc, char* argv[]) {
  if (argc > 4) {
    return 1;
  }

  counterASS = 0;
  counterSET = 0;
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
