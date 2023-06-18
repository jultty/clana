#ifndef CLANA_FILE_H
#define CLANA_FILE_H
#include <string>
#include "line.h"

using namespace std;

class File {
private:
  Line *first = nullptr;
  Line *last = nullptr;
  Line *header = nullptr;

public:
  File();
  void add(string content);
  void print(string option);
};

#endif
