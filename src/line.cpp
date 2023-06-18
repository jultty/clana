#include "line.h"

using namespace std;

using Line = struct;

Line {
  int number = -1;
  string content = "";
  Line *next = nullptr;
  Line *previous = nullptr;
};

