#include <iostream>
#include "file.hpp"
#include "field.hpp"
#include <algorithm>
#include <string>

// traverses a linked list of fields
Field* traverse_fields(Line* line, int start, int distance) {

  Field* current_position = line->first_field;

  distance += start - 1; // traversing will start at position 1

  while (distance != 0) {
    if (distance > 0) {
      distance--;
      current_position = current_position->next;
    } else {
      current_position = current_position->previous;
      distance++;
    }
  }
  return current_position;
}

// finds gaps in lines
// returns the first field if none found
Field* line_gap_scan(Line* line) {

  Field* field = line->first_field;
  int limit = line->last_field->column;

  while (field->column < limit) {
    if (field->content == "")  {
      return field;
    } else {
      field = field->next;
    }
  }
  // no gap found
  return line->first_field;
};

