#ifndef CLANA_HEADER_H
#define CLANA_HEADER_H
#include <string>
#include <iostream>

using namespace std;

bool detect_headers(string);
string get_header(int, Line* headers);
int count_headers(string);
void wait();

#endif
