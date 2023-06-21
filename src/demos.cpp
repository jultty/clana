#include <fstream>
#include "file.h"
#include "header.h"

using namespace std;

int demo() {

  // set up I/O stream
  ifstream infile;
  ifstream fake_infile;
  ofstream outfile;
  infile.open("in.csv");
  fake_infile.open("fake.csv");

  // iterate over each input line
  File file;
  File fake_file;
  string line_content;

  while (getline (infile, line_content))
    file.add(line_content);
  infile.close();
 
  while (getline (fake_infile, line_content))
    fake_file.add(line_content);
  fake_infile.close();

  // demos

  // find the first field with a gap
  Field* empty = field_gap_scan(file.last);
  cout << "Found empty field: " << empty->header;
  cout << " at row " << file.last->row;
  cout << " column " << empty->column << endl;

  // find the first line with a gap
  Line* fake_line = traverse_lines(fake_file.first, 45);
  Line* gap_line = line_gap_scan(fake_line);
  Field* gap_field = field_gap_scan(gap_line);

  if (gap_field  -1) {
    cout << "Line gap scan started at " << fake_line->row;
    cout << ", first gap found on line " << gap_line->row;
    cout << ", column " << gap_field->column << " (";
    cout << gap_field->header << ")" << endl;
  }

  return 0;
}
