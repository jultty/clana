#include <fstream>
#include "file.hpp"
#include "header.hpp"

using namespace std;

int main () {

  // set up I/O stream
  ifstream infile;
  ifstream mock_infile;
  ofstream outfile;
  infile.open("in.csv");
  mock_infile.open("mock.csv");

  // iterate over each input line
  File file;
  File mock_file;
  string line_content;

  while (getline (infile, line_content))
    file.add(line_content);
  infile.close();

  while (getline (mock_infile, line_content))
    mock_file.add(line_content);
  mock_infile.close();

  //print mapped contents
  /* file.print(""); */
  /* mock_file.print(""); */

  // find the first field with a gap
  Field* empty = field_gap_scan(file.last);
  cout << "Found empty field: " << empty->header->field->content;
  cout << " at row " << file.last->row;
  cout << " column " << empty->column << endl;

  // find the first line with a gap
  Line* mock_line = traverse_lines(mock_file.first, 45);
  Line* gap_line = line_gap_scan(mock_line);
  Field* gap_field = field_gap_scan(gap_line);

  if (gap_field  -1) {
    cout << "Line gap scan started at " << mock_line->row;
    cout << ", first gap found on line " << gap_line->row;
    cout << ", column " << gap_field->column << " (";
    cout << gap_field->header->field->content << ")" << endl;
  }

  cout << "Chuva 22 is at column";
  cout << get_column("Chuva22", file.headers) << endl;

  Header* total_example = traverse_headers(file.headers, 1, 7);
  cout << "Total for variable at column " << total_example->column;
  cout << " (" << total_example->field->content << "): ";
  cout << total_example->total << endl;
  return 0;
}
