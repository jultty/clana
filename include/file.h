#ifndef CLANA_FILE_H
#define CLANA_FILE_H
#include <string>
#include "line.h"

using namespace std;

class File {
private:
  Line *first = nullptr;
  Line *last = nullptr;

public:
  File();
  void addLine(string content);
  void print();
  void print_neighbors();
};

#endif
