#include "file.h"
#include "utils.h"

using namespace std;

File::File() : first(nullptr), last(nullptr) {}

void File::add(string content) {

  cout << " [file] add responding to call" << endl;
  cout << " [file] instantiating line" << endl;
  Line* new_line = new Line;
  new_line->content = content;
  cout << " [file] content set to " << content << endl;
  int field_counter = 1;
  cout << " [file] field_counter set to " << field_counter << endl;

  cout << " [file] checking if this line is the header" << endl;
  // check if this line is the header
  if (detect_headers(content)) {
    cout << " [file] header found "  << endl;
    headers = new_line;
    cout << " [file] file's headers property set to this line" << endl;
    cout << " [file] will now pass this line's content to count_headers to set a max_fields value" << endl;
    max_fields = count_headers(headers->content) + 1;
    cout << " [file] max_fields set to " << max_fields << endl;
  }

  // map each observed value to a field 
  if (headers) {
    cout << " [file] headers are already set" << endl;

    stringstream ss(content);
    string observation;

    cout << " [file] will now loop over all fields on this line" << endl;
    while (getline(ss, observation, ';') && field_counter <= max_fields) {
      Field* new_field = new Field;

      new_field->content = observation;
      new_field->line = new_line;

      cout << " [file] max_fields control is currently " << max_fields << endl;
      cout << " [file] instantiated a field with content " << new_field->content << endl;

      // set first, last, previous and next
      cout << " [file] now setting first, last, previous and next for field" << endl;
      if (new_line->first_field == nullptr) {
        cout << " [file] this is the first field" << endl;
        new_field->column = 1;
        new_line->first_field = new_field;
        new_line->last_field = new_field;
        cout << " [file] first field set with column " << new_field->column << endl;
        cout << " [file] line first field set to field on column " << new_line->first_field->column << endl;
        cout << " [file] line last field set to field on column " << new_line->last_field->column << endl;
      }
      else {
        cout << " [file] this is not the first field" << endl;
        new_field->column = new_line->last_field->column + 1;
        cout << " [file] field set with column " << new_field->column << endl;
        new_field->previous = new_line->last_field;
        cout << " [file] this field's previous field set to line's last field on column " << new_field->previous->column << endl;
        new_line->last_field->next = new_field;
        cout << " [file] this line's last field's next field set to this field on column " << new_line->last_field->next->column << endl;
        new_line->last_field = new_field;
        cout << " [file] line last field set to this field on column " << new_line->last_field->column << endl;
      }
      cout << " [file] done setting first, last, previous and next" << "\n\n";

      cout << " [file] the current first header field is " << headers->first_field->content << endl;
      cout << " [file] the current last header field is " << headers->last_field->content << endl;

      cout << " [file] now asking for the header" << endl; 
      new_field->header = get_header(new_field->column, headers);
      cout << " [file] got response " <<  new_field->header << " from get_header " << endl;
      cout << " [file] field " << new_field->column << " now has header set to " << new_field->header << endl;

      field_counter++;
      cout << " [file] field_counter incremented to " << field_counter << endl;
      cout << " [file] max_fields is " << max_fields << endl;
      
      if (new_field->header != "")
      {
        cout << " [file] field headers set to " << new_field->header << endl;
      }

      cout << " [file] done with field " << new_field->header << ", now looping for next field" << "\n\n";
    }
  } else {
  cout << " [file] field mapping skipped: file headers are not set yet" << "\n\n";
  }

  // set first, last, previous and next
  cout << " [file] now setting first, last, previous and next for line" << endl;
  if (first == nullptr) {
    cout << " [file] this is the first line" << endl;
    first = new_line;
    last = new_line;
    new_line->row = 1;
    cout << " [file] first and last lines set to this line" << endl;
    cout << " [file] this line's row set to 1" << endl;
    cout << " [file] the following should read 111: " << first->row << last->row << new_line->row << endl;
  }
  else {
    cout << " [file] this is not the first line" << endl;
    new_line->row = last->row + 1;
    cout << " [file] this new line's row set to last row + 1, at row number "  << new_line->row << endl;
    new_line->previous = last;
    cout << " [file] this line's previous row set to the current last row. this new line's previous row is now "  << new_line->previous->row << endl;
    last->next = new_line;
    cout << " [file] file's last line's next line set to this one. last line is row " << last->row << " and its next row is " << last->next->row  << endl;
    last = new_line;
    cout << " [file] file's last line set to this line. the file's last line's row is now " << last->row << endl;
  }
  cout << " [file] this line is done for, add() is exiting" << "\n\n\n";
}

void File::print(string option) {
  Line* current = first;
  if (option != "all")
    current = headers->next;
  while (current != nullptr) {
    cout << current->row << ": ";
    cout << current->content << endl;
    current = current->next;
  }
}
