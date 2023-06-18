#ifndef CLANA_LINE_H
#define CLANA_LINE_H
#include <string>

using namespace std;

struct Line {
  int row = -1;
  std::string content = "";
  Line *next = nullptr;
  Line *previous = nullptr;
};

#endif
