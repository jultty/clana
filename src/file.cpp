#include <string>
#include <iostream>
#include "file.h"
#include "line.h"

using namespace std;

File::File() : first(nullptr), last(nullptr) {}

void File::addLine(string content) {

  Line *new_line = new Line;
  new_line->content = content;

  if (first == nullptr) {
    first = new_line;
    last = new_line;
    new_line->number = 1;
  }
  else {
    new_line->number = last->number + 1;
    new_line->previous = last;
    last->next = new_line;
    last = new_line;
    cout << new_line->number << endl;
  }
}

void File::print() {
  Line *current = first;
  while (current != nullptr) {
    cout << current->number << ": ";
    cout << current->content << endl;
    current = current->next;
  }
}
