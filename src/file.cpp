#include <string>
#include "file.h"

using namespace std;

typedef struct Line {
  int number = 1;
  string content;
  Line *next;
  Line *previous;
} Line;

class File {
  private:
    Line *first;
    Line *last;

  public:
    File() : first(nullptr), last(nullptr) {}
};
