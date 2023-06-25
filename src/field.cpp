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

// finds gaps between two lines, returns first match
Field* range_gap_scan(Line* start, Line* end) {

  Line* line = start;
  Field* gap = nullptr;

  // iterate over line range
  while (line != end->next) {
    // find the first gap in the line
    gap = line_gap_scan(line);

    // if a gap is found
    if (gap != nullptr) {

      // iterate over all line columns 
      while (gap->column <= line->last_field->column) {
        // check if column is all gaps
        Field* column_scan = column_gap_scan(gap->header, start, end);

        // column is not all gaps and has at least one gap
        if (column_scan != gap->header->field && column_scan != nullptr) {
          // found gap is within range
          if (column_scan->line->row >= start->row && column_scan->line->row <= end->row) {
            return column_scan;
          } 
        } 

          // if there are still fields to scan
          if (gap->next != nullptr) {
            gap = gap->next;
          }
          else {
            break;
          }
        }
      }

      // move to next line
      if (line->next != nullptr) {
        line = line->next;
      }
    }

    return gap;
  };

