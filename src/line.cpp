#include "file.hpp"
#include "line.hpp"
#include "field.hpp"

// finds gaps in lines, returns first match
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
  return nullptr;
};

// traverses a linked list of fields
Line* traverse_lines(Line* start, int distance) {

  Line* current_position = start;

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


