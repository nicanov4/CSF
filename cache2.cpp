#include <iostream>
#include <fstream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<map>
#include<vector>
#include<bitset>
using namespace std;

// Helper function to return a hashed value
int hasher(unsigned long long input, int numBits) {
  int maxValue[14] = {0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191};
  return (input & maxValue[numBits]);
}

int main (int argc, char* argv[]) {
  // Standard variables to track every line
  unsigned long long address = 0;
  char flag;
  unsigned long long hitsDIR = 0, missesDIR = 0, hitsASS = 0, missesASS = 0, hitsSET = 0, missesSET = 0;
  unsigned long long hitsBLK = 0, missesBLK = 0, hitsNWA = 0, missesNWA = 0, hitsPRF = 0, missesPRF = 0;


  map<int, unsigned long long> cacheDIR;
  vector<unsigned long long> cacheASS;
  int numASS = 0;
  map<int, vector<unsigned long long> > cacheSET;


  // Switching over to an array system for the more complicated ones
  unsigned long long cacheBLK[256][4][8];
  vector<int> freqBLK[256];

  unsigned long long cacheNWA[256][4][8];
  vector<int> freqNWA[256];

  unsigned long long cachePRF[256][4][8];
  vector<int> freqPRF[256];

  // Loading up the time tracking variables and the caches
  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 8; k++) {
	cacheNWA[i][j][k] = 0;
	cacheBLK[i][j][k] = 0;
	cachePRF[i][j][k] = 0;
      }
    }
  }
  for (int i = 0; i < 256; i++) {
    vector<int> temp;
    freqNWA[i] = temp;
    vector<int> temp2;
    freqBLK[i] = temp2;
    vector<int> temp3;
    freqPRF[i] = temp3;
  }

  // Scan throughout the entire file
  while (scanf("%llx %c",&address,&flag) != EOF) {
    // DIR
    // Using a map, we first hash a key, then see if that key exists
    map<int, unsigned long long>::iterator itDIR = cacheDIR.find(hasher(address, 13));
    if (itDIR != cacheDIR.end()) {
      // If it does exist, then check to see if the address matches, and update accordingly
      if (itDIR->second == address) {
	hitsDIR += 1;
      } else {
	missesDIR++;
	itDIR->second = address;
      }
      // Otherwise, insert a new pair
    } else {
      missesDIR++;
      cacheDIR.insert(make_pair(hasher(address, 13), address));
    }

    // ASS
    // Similar to the DIR above, but this time we have a vector containing the most recent
    vector<unsigned long long>::iterator itASS = find(cacheASS.begin(), cacheASS.end(), address);
    if (itASS != cacheASS.end()) {
      // Check if its in there, and if so, put it back in the front
      hitsASS += 1;
      cacheASS.erase(itASS);
      cacheASS.insert(cacheASS.begin(), address);
    } else {
      // Check if its full, and place it in the front
      if (numASS >= 8192) {
	cacheASS.pop_back();
	cacheASS.insert(cacheASS.begin(), address);
      } else {
	cacheASS.insert(cacheASS.begin(), address);
	numASS += 1;
      }
      missesASS++;
    }

    // SET
    // A combination of the two above, which led to a map of ints and vectors
    map<int, vector<unsigned long long> >::iterator itSET = cacheSET.find(hasher(address, 11));
    if (itSET != cacheSET.end()){
      // Find the value in the map, then in the vector
      vector<unsigned long long>::iterator itSETvec = find(itSET->second.begin(), itSET->second.end(), address);
      if (itSETvec != itSET->second.end()) {
	hitsSET += 1;
	itSET->second.erase(itSETvec);
	// Update misses and hits accordingly
      } else {
	missesSET += 1;
	if (itSET->second.size() >= 4)
	  itSET->second.pop_back();
      }
      // Place the address in the vector at the hash location
      itSET->second.insert(itSET->second.begin(), address);
    } else {
      // If it hasn't been found yet, then its a miss and must be added
      missesSET += 1;
      vector<unsigned long long> temp;
      temp.insert(temp.begin(), address);
      cacheSET.insert(make_pair(hasher(address, 11), temp));
    }


    // BLK
    // Now using a more comprehensive method
    int firstIndex = hasher(address >> 3, 8);
    int secondIndex = hasher(address, 3);
    bool hit = false;
    // Loop through the 4 possible positions
    for (int i = 0; i < 4; i++) {
      if (cacheBLK[firstIndex][i][secondIndex] == address) {
	hitsBLK += 1;
	// If we find it, increment and put in the front of the queue
	freqBLK[firstIndex].erase(find(freqBLK[firstIndex].begin(), freqBLK[firstIndex].end(), i));
	freqBLK[firstIndex].insert(freqBLK[firstIndex].begin(), i);
	hit = true;
	break;
      }
    }
    // If we haven't found it, increment misses, and place it in the queue/cache
    if (!hit) {
      missesBLK += 1;
      int indexValue = 0;
      if (freqBLK[firstIndex].size() >= 4) {
	indexValue = freqBLK[firstIndex].back();
	freqBLK[firstIndex].pop_back();
      } else {
	indexValue = freqBLK[firstIndex].size();
      }
      for (int j = 0; j < 8; j++) {
	cacheBLK[firstIndex][indexValue][j] = address - secondIndex + j;
      }
      freqBLK[firstIndex].insert(freqBLK[firstIndex].begin(), indexValue);
    }

    // NWA
    // Very similar to the one above, but check on misses if we should change anything
    firstIndex = hasher(address >> 3, 8);
    secondIndex = hasher(address, 3);
    hit = false;
    for (int i = 0; i < 4; i++) {
      if (cacheNWA[firstIndex][i][secondIndex] == address) {
	hitsNWA += 1;
	freqNWA[firstIndex].erase(find(freqNWA[firstIndex].begin(), freqNWA[firstIndex].end(), i));
	freqNWA[firstIndex].insert(freqNWA[firstIndex].begin(), i);
	hit = true;
	break;
      }
    }
    if (!hit) {
      missesNWA += 1;
      if (flag != 'S') {
	int indexValue = 0;
	if (freqNWA[firstIndex].size() >= 4) {
	  indexValue = freqNWA[firstIndex].back();
	  freqNWA[firstIndex].pop_back();
	} else {
	  indexValue = freqNWA[firstIndex].size();
	}
	for (int j = 0; j < 8; j++) {
	  cacheNWA[firstIndex][indexValue][j] = address - secondIndex + j;
	}
	freqNWA[firstIndex].insert(freqNWA[firstIndex].begin(), indexValue);
      }
    }

    // PRF
    // Similar to the one above, but add an extra step with an incremented address
    // if the cache misses.
    firstIndex = hasher(address >> 3, 8);
    secondIndex = hasher(address, 3);
    hit = false;
    for (int i = 0; i < 4; i++) {
      if (cachePRF[firstIndex][i][secondIndex] == address) {
	hitsPRF += 1;
	freqPRF[firstIndex].erase(find(freqPRF[firstIndex].begin(), freqPRF[firstIndex].end(), i));
	freqPRF[firstIndex].insert(freqPRF[firstIndex].begin(), i);
	hit = true;
	break;
      }
    }
    // First check the 'n' value, as we have done in the past
    if (!hit) {
      missesPRF += 1;
      if (flag != 'S') {
	int indexValue = 0;
	if (freqPRF[firstIndex].size() >= 4) {
	  indexValue = freqPRF[firstIndex].back();
	  freqPRF[firstIndex].pop_back();
	} else {
	  indexValue = freqPRF[firstIndex].size();
	}
	for (int j = 0; j < 8; j++) {
	  cachePRF[firstIndex][indexValue][j] = address - secondIndex + j;
	}
	freqPRF[firstIndex].insert(freqPRF[firstIndex].begin(), indexValue);
      }
    }
    // This is for the 'n+1' value, which happens on misses that have L
    if (!hit && flag != 'S') {
      address = address + 8;
      firstIndex = hasher(address >> 3, 8);
      secondIndex = hasher(address, 3);
      bool hit2 = false;
      for (int i = 0; i < 4; i++) {
	if (cachePRF[firstIndex][i][secondIndex] == address) {
	  freqPRF[firstIndex].erase(find(freqPRF[firstIndex].begin(), freqPRF[firstIndex].end(), i));
	  freqPRF[firstIndex].insert(freqPRF[firstIndex].begin(), i);
	  hit2 = true;
	  break;
	}
      }
      // Very similar to the base, but just don't increment the counters
      if (!hit2) {
	int indexValue = 0;
	if (freqPRF[firstIndex].size() >= 4) {
	  indexValue = freqPRF[firstIndex].back();
	  freqPRF[firstIndex].pop_back();
	} else {
	  indexValue = freqPRF[firstIndex].size();
	}
	for (int j = 0; j < 8; j++) {
	  cachePRF[firstIndex][indexValue][j] = address - secondIndex + j;
	}
	freqPRF[firstIndex].insert(freqPRF[firstIndex].begin(), indexValue);
      }
    }
  }



  // Print out the counters
  printf("DIR: %20llu %20llu\n",hitsDIR,missesDIR);
  printf("ASS: %20llu %20llu\n",hitsASS,missesASS);
  printf("SET: %20llu %20llu\n",hitsSET,missesSET);
  printf("BLK: %20llu %20llu\n",hitsBLK,missesBLK);
  printf("NWA: %20llu %20llu\n",hitsNWA,missesNWA);
  printf("PRF: %20llu %20llu\n",hitsPRF,missesPRF);
}
