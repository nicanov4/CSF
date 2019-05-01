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

int main (int argc, char* argv[]) {

  if (argc > 4) {
    return 1;
  }

  int count = 0;
  while (scanf("%llx %c", &address, &flag) != EOF) {


    count++;
    if (count > 127) {
      return 1;
    }
  }

  printf("DIR: %20llu %20llu\n",hits,misses);
  printf("ASS: %20llu %20llu\n",hits,misses);
  printf("SET: %20llu %20llu\n",hits,misses);
  printf("BLK: %20llu %20llu\n",hits,misses);
  printf("NWA: %20llu %20llu\n",hits,misses);
  printf("PRF: %20llu %20llu\n",hits,misses);
}
