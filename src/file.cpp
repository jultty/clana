#include <string>
#include <iostream>
#include "file.h"
#include "utils.h"

using namespace std;

File::File() : first(nullptr), last(nullptr) {}

void File::add(string content) {

  Line *new_line = new Line;
  new_line->content = content;

  // check if this line is the header
  if (detect_headers(content))
    header = new_line;

  // map each observed value to a column
  stringstream ss(content);
  string observation;

  while (getline(ss, observation, ';')) {
    Field *new_field = new Field;

    new_field->content = observation;
    new_field->line = new_line;

    // set first, last, previous and next
    if (new_line->first_field == nullptr) {
      new_field->column = 1;
      new_line->first_field = new_field;
      new_line->last_field = new_field;
    }
    else {
      new_field->column = new_line->last_field->column + 1;
      new_field->previous = new_line->last_field;
      new_line->last_field->next = new_field;
      new_line->last_field = new_field;
    }

    new_field->header = ""; // TODO
  }

  // set first, last, previous and next
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
