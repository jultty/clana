#ifndef CLANA_LINE_H
#define CLANA_LINE_H
#include "file.hpp"

using namespace std;
using Field = struct Field;

struct Line {
  int row = -1;
  string content = "";
  bool is_header = false;
  bool is_last = false;
  Line* next = nullptr;
  Line* previous = nullptr;
  Field* first_field = nullptr;
  Field* last_field = nullptr;
};

Line* line_gap_scan(Line*);
Line* traverse_lines(Line*, int);

#endif
