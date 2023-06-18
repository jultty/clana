#include <string>
#include <iostream>
#include "file.h"
#include "line.h"
#include "utils.h"

using namespace std;

File::File() : first(nullptr), last(nullptr) {}

void File::add(string content) {

  Line *new_line = new Line;
  new_line->content = content;

  if (detect_headers(content))
    header = new_line;

  if (first == nullptr) {
    first = new_line;
    last = new_line;
    new_line->row = 1;
  }
  else {
    new_line->row = last->row + 1;
    new_line->previous = last;
    last->next = new_line;
    last = new_line;
  }
}

void File::print(string option) {
  Line *current = first;
  if (option != "all")
    current = header->next;
  while (current != nullptr) {
    cout << current->row << ": ";
    cout << current->content << endl;
    current = current->next;
  }
}
