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
  Line* line = nullptr;
  Header* header = nullptr;
  Field* next = nullptr;
  Field* previous = nullptr;
  Field* above = nullptr;
  Field* below = nullptr;
};

Field* traverse_fields(Line*, int, int);
Field* get_field(Line*, int, int);
Field* range_gap_scan(Line*,  Line*);

#endif
