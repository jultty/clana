#ifndef CLANA_FIELD_H
#define CLANA_FIELD_H
#include <string>
#include <sstream>
#include "file.hpp"
#include "field.hpp"

using namespace std;

struct Field {
  int column = -1;
  string content = "";
  string header = "";
  int total = -1;
  float average = -1;
  Line* line = nullptr;
  Field* next = nullptr;
  Field* previous = nullptr;
};

Field* field_gap_scan(Line*);

#endif
