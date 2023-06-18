#ifndef CLANA_FIELD_H
#define CLANA_FIELD_H
#include <string>
#include <sstream>
#include "file.h"

using namespace std;

struct Field {
  int column = -1;
  Line *line = nullptr;
  string header = "";
  string content = "";
  Field *next = nullptr;
  Field *previous = nullptr;
};

#endif
