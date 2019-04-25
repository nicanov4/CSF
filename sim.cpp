#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <tuple>
#include <map>
using namespace std;

unsigned long long int branch_adress;
unsigned long long int target_adress;
char flag;

unsigned long long int correctSTA;
unsigned long long int incorrectSTA;
unsigned long long int collisionSTA;

unsigned long long int correctBAH;
unsigned long long int incorrectBAH;
unsigned long long int collisionBAH;
map<int, tuple<bool, unsigned long long int>> tableBAH;

unsigned long long int correctTAH;
unsigned long long int incorrectTAH;
unsigned long long int collisionTAH;
map<int, tuple<bool, unsigned long long int>> tableTAH;


unsigned long long int correctBTA;
unsigned long long int incorrectBTA;
unsigned long long int collisionBTA;
map<int, tuple<bool, unsigned long long int>> tableBTA;


unsigned long long int correctCOL;
unsigned long long int incorrectCOL;
unsigned long long int collisionCOL;

unsigned long long int correctSAT;
unsigned long long int incorrectSAT;
unsigned long long int collisionSAT;

unsigned long long int correctTWO;
unsigned long long int incorrectTWO;
unsigned long long int collisionTWO;

int sta() {
  if ((target_adress < branch_adress && flag == 'T') || (target_adress > branch_adress && flag == 'N')) {
    correctSTA++;
  } else {
    incorrectSTA++;
  }
}

int bah() {
  auto in = make_tuple(branch_adress, target_adress, flag);

  if (get<1>(tableBAH[get<0>(in) & 1023]) != get<0>(in)) {
    collisionBAH++;
    get<1>(tableBAH[get<0>(in) & 1023]) = get<0>(in);
    if (get<2>(in) == 'T') {
      get<0>(tableBAH[get<0>(in) & 1023]) = 1;
    } else {
      get<0>(tableBAH[get<0>(in) & 1023]) = 0;
    }
  } else if ((get<0>(tableBAH[get<0>(in) & 1023]) && get<2>(in) == 'T') || (!get<0>(tableBAH[get<0>(in) & 1023]) && get<2>(in) == 'N')) {
    correctBAH++;
  } else {
    incorrectBAH++;
    if (get<2>(in) == 'T') {
      get<0>(tableBAH[get<0>(in) & 1023]) = 1;
    } else {
      get<0>(tableBAH[get<0>(in) & 1023]) = 0;
    }
  }
}

int tah() {
  auto in = make_tuple(branch_adress, target_adress, flag);

  if (get<1>(tableBAH[get<1>(in) & 1023]) != get<1>(in)) {
    collisionTAH++;
    get<1>(tableTAH[get<1>(in) & 1023]) = get<1>(in);
    if (get<2>(in) == 'T') {
      get<0>(tableTAH[get<1>(in) & 1023]) = 1;
    } else {
      get<0>(tableTAH[get<1>(in) & 1023]) = 0;
    }
  } else if ((get<0>(tableTAH[get<1>(in) & 1023]) && get<2>(in) == 'T') || (!get<0>(tableTAH[get<1>(in) & 1023]) && get<2>(in) == 'N')) {
    correctTAH++;
  } else {
    incorrectTAH++;
    if (get<2>(in) == 'T') {
      get<0>(tableTAH[get<1>(in) & 1023]) = 1;
    } else {
      get<0>(tableTAH[get<1>(in) & 1023]) = 0;
    }
  }
}

int bta() {
  return 1;
}

int col() {
  return 1;
}

int sat() {
  return 1;
}

int two() {
  return 1;
}

int main (int argc, char* argv[]) {
  if (argc > 4) {
    return 1;
  }

  correctSTA = 0;
  incorrectSTA = 0;
  collisionSTA = 0;

  correctBAH = 0;
  incorrectBAH = 0;
  collisionBAH = 0;

  correctTAH = 0;
  incorrectTAH = 0;
  collisionTAH = 0;

  correctBTA = 0;
  incorrectBTA = 0;
  collisionBTA = 0;

  correctCOL = 0;
  incorrectCOL = 0;
  collisionCOL = 0;

  correctSAT = 0;
  incorrectSAT = 0;
  collisionSAT = 0;

  correctTWO = 0;
  incorrectTWO = 0;
  collisionTWO = 0;

  while (scanf("%llx %llx %c", &branch_adress, &target_adress, &flag) != EOF) {
    sta();
    bah();
    tah();
    bta();
    col();
    sat();
    two();
  }
  printf("STA: %20llu %20llu %20llu\n", correctSTA, incorrectSTA, collisionSTA);
  printf("BAH: %20llu %20llu %20llu\n", correctBAH, incorrectBAH, collisionBAH);
  printf("TAH: %20llu %20llu %20llu\n", correctTAH, incorrectTAH, collisionTAH);
  printf("BTA: %20llu %20llu %20llu\n", correctBTA, incorrectBTA, collisionBTA);
  printf("COL: %20llu %20llu %20llu\n", correctCOL, incorrectCOL, collisionCOL);
  printf("SAT: %20llu %20llu %20llu\n", correctSAT, incorrectSAT, collisionSAT);
  printf("TWO: %20llu %20llu %20llu\n", correctTWO, incorrectTWO, collisionTWO);
}