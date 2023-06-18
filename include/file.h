#ifndef CLANA_FILE_H
#define CLANA_FILE_H
#include <string>
#include "line.h"
#include "field.h"

using namespace std;
using File = struct File;

class File {
private:
  Line *header = nullptr;
  Line *first = nullptr;
  Line *last = nullptr;

public:
  File();
  void add(string content);
  void print(string option);
};

#endif
