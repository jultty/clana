#include <fstream>
#include <iomanip>
#include "file.hpp"
#include "header.hpp"

using namespace std;

int main () {

  // set up I/O stream
  ifstream infile;
  ofstream outfile;
  infile.open("in.csv");

  // populate data structures with file contents
  File file;
  string line_content;

  while (getline (infile, line_content))
    file.add(line_content);
  infile.close();

  // set number notation and precision
  cout << fixed << setprecision(4);

  // print mapped contents (prints all lines)
  /* file.print("all"); */

  // search columns by content
  cout << "Maxima is at column " << get_column("Maxima", file.headers);
  cout << " and Total at " << get_column("Total", file.headers) << endl;

  // get the correlation coefficient
  Header* Maxima = traverse_headers(file.headers, 1, 4);
  Header* Total = traverse_headers(file.headers, 1, 5);
  double n = file.last->row - file.headers->row - 1;
  double correlation = get_correlation(Maxima, Total, n);

  cout << "Column " << Maxima->column << " (";
  cout << Maxima->field->content << ") and ";
  cout << Total->column << " (" << Total->field->content;
  cout << ") have a correlation of " << correlation << endl;

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

  // find the first gap
  Line* range_start = traverse_lines(file.first, 44);
  Line* range_end = traverse_lines(file.first, 85);
  Field* gap = range_gap_scan(range_start, range_end);

  cout << "Gap scan from row " << range_start->row;
  cout << " found a gap on row " << gap->line->row << ", column ";
  cout << gap->column << " (" << gap->header->field->content << ")\n";

  // solve gaps with column average
  range_average_solver(gap->header, file.last_header);

  // re-scan
  Field* average_solved_gap = range_gap_scan(range_start, range_end);
  cout << "After average solving, scan found the first gap on row "; 
  cout << average_solved_gap->line->row << ", column ";
  cout << average_solved_gap->column << endl;

  Field* previous_gap = get_field(file.headers, 72, 42);
  cout << "Previous first gap now has value " << previous_gap->content;
  cout << " while its header has average " << previous_gap->header->average;

  cout << endl;

  return 0;
}
