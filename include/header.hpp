#ifndef CLANA_HEADER_H
#define CLANA_HEADER_H
#include <string>
#include <iostream>

using namespace std;
using Header = struct Header;

struct Header {
  int column = -1;
  string content = "";
  int total = -1;
  float average = -1;
  Line* line = nullptr;
  Field* next = nullptr;
  Field* previous = nullptr;
};

bool detect_headers(string);
string get_header(int, Line*);
int get_column(string, Line*);
int count_headers(string);
void wait();

#endif
