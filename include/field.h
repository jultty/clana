#ifndef CLANA_FIELD_H
#define CLANA_FIELD_H
#include <string>
#include <sstream>
#include "file.h"

using namespace std;

struct Field {
  int column = -1;
  string content = "";
  string header = "";
  Line* line = nullptr;
  Field* next = nullptr;
  Field* previous = nullptr;
};

#endif
