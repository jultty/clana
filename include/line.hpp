#ifndef CLANA_LINE_H
#define CLANA_LINE_H
#include "file.hpp"
#include "header.hpp"

using namespace std;

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

Line* range_gap_scan(Line*,  Line*);
Line* traverse_lines(Line*, int);

#endif
