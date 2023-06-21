#include <iostream>
#include "file.h"
#include "field.h"

// finds gaps in lines
// returns the first field if none found
Field* field_gap_scan(Line* line) {

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
