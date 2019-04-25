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

int sta() {
  if ((target_adress < branch_adress && flag == 'T') || (target_adress > branch_adress && flag == 'N')) {
    correctSTA++;
  } else {
    incorrectSTA++;
  }
}

int bah() {
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
  
  while (scanf("%llx %llx %c", &branch_adress, &target_adress, &flag)) {
    sta();
    printf("STA: %20llu %20llu %20llu\n", correctSTA, incorrectSTA, collisionSTA);
    
    bah();
    printf("BAH: %20llu %20llu %20llu\n", correctBAH, incorrectBAH, collisionBAH);
  }  
}
