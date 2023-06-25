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

  // populate data structures with file contents
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

  // print mapped contents (prints all lines)
  /* file.print("all"); */
  /* mock_file.print("all"); */

  // find the first field with a gap
  Field* empty = line_gap_scan(file.last);
  cout << "Found empty field: " << empty->header->field->content;
  cout << " at row " << file.last->row;
  cout << " column " << empty->column << endl;

  // find the first line with a gap
  Line* mock_range_start = traverse_lines(mock_file.first, 45);
  Line* mock_range_end = traverse_lines(mock_file.first, 85);
  Line* gap_line = range_gap_scan(mock_range_start, mock_range_end);
  Field* gap_field = line_gap_scan(gap_line);

  cout << "Line gap scan started at row " << mock_range_start->row;
  cout << ", first gap found on line " << gap_line->row;
  cout << ", column " << gap_field->column << " (";
  cout << gap_field->header->field->content << ")" << endl;

  // search columns by content
  cout << "Chuva 22 is at column";
  cout << get_column("Chuva22", file.headers) << endl;

  // get the correlation coefficient
  Header* Maxima = traverse_headers(file.headers, 1, 4);
  Header* Total = traverse_headers(file.headers, 1, 5);
  double n = file.last->row - file.headers->row - 1;
  double correlation = get_correlation(Maxima, Total, n);

  cout << "Column " << Maxima->column << " (";
  cout << Maxima->field->content << ") and column ";
  cout << Total->column << " (" << Total->field->content;
  cout << ") have a correlation coefficient of " << correlation << endl;

  // build a regression model
  tuple<double, double> model  = regression(Maxima, Total, n);
  double m = get<0>(model);
  double b = get<1>(model);

  cout << "Regression model for " << Maxima->field->content;
  cout << " and " << Total->field->content;
  cout << ": y = " << m << "x + " << b << endl;

  // predict a value
  cout << "ŷ for x = 51.9 is " << predict(51.9, model) << endl;
  cout << "ŷ for x = 140.2 is " << predict(140.2, model) << endl;

  return 0;
}
