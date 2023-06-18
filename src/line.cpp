#include "line.h"

using namespace std;

using Line = struct;

Line {
  int row = -1;
  string content = "";
  Line *next = nullptr;
  Line *previous = nullptr;
};

