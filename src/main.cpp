#include <fstream>
#include <iomanip>
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

  // set number notation and precision
  cout << fixed << setprecision(4);

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

    cout << "Line gap scan started at row " << mock_line->row;
    cout << ", first gap found on line " << gap_line->row;
    cout << ", column " << gap_field->column << " (";
    cout << gap_field->header->field->content << ")" << endl;

  cout << "Chuva 22 is at column";
  cout << get_column("Chuva22", file.headers) << endl;

  Header* Maxima = traverse_headers(file.headers, 1, 4);
  double n = file.last->row - file.headers->row - 1;
  double sum_of_squared_values = sqrd_sum(Maxima, n);
   
  Header* Total = traverse_headers(file.headers, 1, 5);
  sum_of_squared_values = sqrd_sum(Total, n);
  double correlation = get_correlation(Maxima, Total, n);

  cout << "Column " << Maxima->column << " (";
  cout << Maxima->field->content << ") and column ";
  cout << Total->column << " (" << Total->field->content;
  cout << ") have a correlation coefficient of " << correlation << endl;

  return 0;
}
