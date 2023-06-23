#ifndef CLANA_HEADER_H
#define CLANA_HEADER_H
#include <string>
#include <iostream>

using namespace std;
using Header = struct Header;
using Line = struct Line;
using Field = struct Field;

struct Header {
  int column = -1;
  Field* field = nullptr;
  Header* next = nullptr;
  Header* previous = nullptr;
  Field* first_field = nullptr;
  Field* last_field = nullptr;
  double total = 0;
  double average = -1;
};

bool detect_headers(string);
Header* get_header(int, Line*);
Header* traverse_headers(Line*, int, int);
int get_column(string, Line*);
int count_headers(string);
double parse_double(string);

#endif
