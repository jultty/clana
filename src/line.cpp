#include "file.hpp"
#include "line.hpp"
#include "field.hpp"

// checks if line has gaps
// if not, moves to the next line
// returns the first found line's row number
Line* range_gap_scan(Line* start, Line* end) {

  Line* line = start;

  while (line != end) {
    Field* gap = line_gap_scan(line);

    if (gap->column != line->first_field->column)
      return line;

    line = line->next;  
  }

  if (line == end) {
    Field* gap = line_gap_scan(line);

    if (gap->column != line->first_field->column)
      return line;
  }

  // no gap found
  return NULL;
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


