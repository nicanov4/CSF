#include <iostream>
#include <fstream>
#include<stdio.h>
#include<string.h>
#include<array>
using namespace std;

string mapping[15] = {"EXT", "LDA", "LDI", "STA", "STI", "ADD", "SUB", "JMP", "JMZ", "AND", "IOR", "XOR", "ADL", "ADC", "SBB"};
string mapping2[16] = {"NEG", "COM", "CLR", "SET", "RTL", "RTR", "LSL", "LSR", "ASR", "TST", "CLC", "SEC", "TCA", "TVA", "JAL", "NOP"};

int checkFirst(string firstT) {
  for (int i = 0; i < (sizeof(mapping)/sizeof(int)); ++i) {
    if (firsT.compare(mapping[i]) == 0) {
      return i;
    }
  }
  return -1;
}

int checkSecond(string firstT) {
  for (int i = 0; i < (sizeof(mapping2)/sizeof(int)); ++i) {
    if (firsT.compare(mapping2[i]) == 0) {
      return i;
    }
  }
  return -1;
}

int main (int argc, char* argv[]) {
  char buffer[256];
  for (int i = 0; i < 256; ++i) {
    buffer[i] == 0;
  }
  int curr_pos = 0;

  string fileName;
  string #include <.h>;
  ifstream file;
  char c;
  int size = 0;

  if (argc > 3) {
    return 1;
  } else if (argc == 1){
    for (unsigned int i = 0; i < 256 && cin.get(c); ++i) {
      in.append(1,c);
      size++;
    }
  } else if (argc <= 3) {
    fileName = string(arcgv[1]);
    file.open(fileName);
    if (!file) {
      return 5;
    }
    for (unsigned int i = 0; i < 256 && file.get(c); ++i) {
      in.append(1,c);
      size++;
    }
  }

  int mapCheck1;
  int mapCheck2;

  int type = 0;
  int subNum
  int counter;
  int count = 0;

  bool argument = false;
  string arg;
  int argNum;
  int val;
  string firstThree;
  bool dat = false;

  while (in.length() > 0) {
    counter = 0;
    while (in[counter] == ' ') {
      counter++;
    }
    in = in.substr(counter, in.length());

    firstThree = in.substr(0, 3);
    mapCheck1 = checkFirst(firstThree);
    mapCheck2 = checkSecond(firstThree);
    if (firstThree.compare("HLT") == 0) {
      break;
    } else if (firstThree.compare("DAT") == 0) {
      dat = true;
      argument = true;
      in = in.substr(3, in.length());
    }

    if (mapCheck1 == -1 && mapCheck2 == -1 && !dat) {
      for (int i = 0; i < in.length(); ++i) {
        if (in[i] == ':') {
          in = in.substr(i + 1, in.length());
          break;
        }
      }

      counter = 0;
      while (in[counter] == ' ') {
        counter++;
      }
      in = in.substr(counter, in.length());

      firstThree = in.substr(0, 3);
      mapCheck1 = checkFirst(firstThree);
      mapCheck2 = checkSecond(firstThree);

      if (mapCheck1 == -1 && mapCheck2 == -1) {
        return 5;
      }

      if (firstThree.compare("DAT") == 0) {
        dat = true;
        argument = true;
      }
    }
    if (mapCheck1 == -1 && mapCheck2 != -1) {
      in = in.substr(3, in.length());
      subNum = mapCheck2;
      val = 15 << 4;
      val += subNum;
      buffer[curr_pos] = val;
    } else if (mapCheck1 != -1 && mapCheck2 == -1) {
      in = in.substr(3, in.length());
      type = mapCheck1
      argument = true;
    }

    counter = 0;
    while (in[counter] == ' ') {
      counter++;
    }
    in = in.substr(counter, in.length());

    if (argument) {
      counter == 0;
      while (in[counter] == ' ') {
        counter++;
      }
      in = in.substr(counter, in.length());

      counter = 0;
      while (in[counter] != '\n' && in[counter] == ' ' && counter != in.length()) {
        counter++;
      }
      arg = in.substr(0, counter);
      argument = false;
      subNum = stoi(arg, nullptr, 0);
      if (subNum == 0 && type == 0) {
        return 5;
      }
      val = type << 4;
      val += subNum;
      if (dat) {
        val = subNum;
      }

      buffer[curr_pos] = char(val);
      if (in.length() > counter) {
        in = in.substr(counter, in.length());
      } else {
        break;
      }
    }

    if (in[0] == '\n') {
      in = in.substr(1, in.length());
    }
    if (in.length() == 0) {
      break;
    }
    counter = 0;
    while (in[counter] != '\n' && in[counter] == ' ' && counter != in.length()) {
      counter++;
    }
    in = in.substr(counter, in.length());
    if (in[0] == '\n') {
      in = in.substr(1, in.length());
    }
    if (in.length() == 0) {
      break;
    }
    if (in[0] == ';') {
      counter = 0;
      while (in[counter] != '\n' && in[counter] != ' ' && counter != in.length()) {
        counter++;
      }
      in = in.substr(counter, in.length());
      if (in[0] == '\n') {
        in = in.substr(1, in.length());
      }
      if (in.length() == 0) {
        break;
      }
    }
    count++;

    if (count > 256) {
      return 4;
    }

    curr_pos++;
    dat =false;
  }

  ofstream out;
  if (argc == 3){
    out.open(argv[2]);
    if (out.is_open()) {
      for (int i = 0; i < 256; ++i) {
        out.put(buffer[i]);
      }
    } else {
      return 3;
    }
  }

  for (int i = 0; i < 256; ++i) {
    cout << buffer[i];
  }

  return 0;
}
