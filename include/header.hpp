#ifndef CLANA_HEADER_H
#define CLANA_HEADER_H
#include <iostream>
#include <string>
#include <tuple>

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
Field* column_gap_scan(Header*, Line*, Line*);
void gap_average_solver(Header*, Line*, Line*);
void range_average_solver(Header*, Header*);
int count_headers(string);
double parse_double(string);
double sqrd_sum(Header*, int);
double get_correlation(Header*, Header*, int);
tuple<double, double> regression(Header*, Header*, int);
double predict(double, tuple<double, double>);


#endif
