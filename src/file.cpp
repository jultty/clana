#include "file.hpp"
#include "header.hpp"

using namespace std;

File::File() : first(nullptr), last(nullptr) {}

void File::add(string content) {

  Line* new_line = new Line;
  new_line->content = content;
  int field_counter = 1;

  // check if this line is the header
  if (detect_headers(content)) {
    headers = new_line;
    new_line->is_header = true;
    max_fields = count_headers(headers->content) + 1;
  }

  // if headers are set, map each observed value to a field 
  if (headers) {

    stringstream ss(content);
    string observation;

    while (getline(ss, observation, ';') && field_counter <= max_fields) {
      Field* new_field = new Field;

      new_field->line = new_line;
      new_field->content = observation;

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

      if (new_line->is_header) {
        Header* new_header = new Header;

        new_header->column = new_field->column;
        new_header->field = new_field;

        if (first_header == nullptr) {
          first_header = new_header;
          last_header = new_header;
        } else {
          new_header->previous = last_header;
          last_header->next = new_header;
          last_header = new_header;
        };
        new_field->header = new_header;
      } else {
        // set header name
        new_field->header = get_header(new_field->column, headers);

        // set vertical links
        if (new_field->header->first_field == nullptr) {
          new_field->header->first_field = new_field;
          new_field->header->last_field = new_field;
        } else {
          new_field->above = new_field->header->last_field;
          new_field->header->last_field->below = new_field;
          new_field->header->last_field = new_field;
        }

        // calculate header total and average
        new_field->header->total = new_field->header->total 
          + parse_double(observation);
        int observation_rows = (last->row - headers->row) +  1;
        new_field->header->average =
          new_field->header->total / observation_rows;
      }

      field_counter++;
    }
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
    new_line->previous->is_last = false;
    last->next = new_line;
    last = new_line;
    new_line->is_last = true;
  }
}

// print all lines
void File::print(string option) {
  Line* current = first;
  if (option != "all")
    current = headers->next;
  while (current != nullptr) {
    cout << "Line " << current->row << ": " << current->content << endl;
    current = current->next;
  }
}

void File::print_interactively(string option) {
  Line* current = first;
  if (option != "all")
    current = headers->next;
  while (current != nullptr) {
    cout << "Line " << current->row << ": " << current->content << endl;

    cout << "\n n: next line \n p: previous line \n any other key: exit\n > ";
    char input;
    cin >> input;
    cout << "\n";

    if (input == 'n') {
      current = current->next;
    } else if (input == 'p' && current->previous != nullptr) {
      current = current->previous;
    } else if (current->previous == nullptr) {
      cout << " [!] Invalid position \n";
    } else {
      cout << " Exiting\n";
      break;
    }
  }
}
