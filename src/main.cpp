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

  Field* Maxima_gap = column_gap_scan(Maxima, file.headers, file.last);
  Field* Total_gap = column_gap_scan(Total, file.headers, file.last);

  cout << "Scan on column " << Maxima->field->content;
  cout << " found a gap on row " << Maxima_gap->line->row << endl;

  cout << "Scan on column " << Total->field->content;
  cout << " found a gap on row " << Total_gap->line->row << endl;

  Field* solved_Maxima_gap = get_field(file.headers, 109, 5);
  cout << "\nSolving gap on " << Maxima->field->content << " with the average solver\n";

  range_average_solver(Maxima, Maxima);
  Maxima_gap = column_gap_scan(Maxima, file.headers, file.last);
  solved_Maxima_gap = get_field(file.headers, 109, 5);
  if (Maxima_gap == nullptr)
    cout << "Gap now has value " << solved_Maxima_gap->content;

  cout << "\nSolving gap on " << Total->field->content << " with the regression solver\n";
  Field* solved_Total_gap = get_field(file.headers, 109, 6);

  range_regression_solver(Total, Total, model, Maxima);
  Total_gap = column_gap_scan(Total, file.headers, file.last);
  solved_Total_gap = get_field(file.headers, 109, 6);

  if (Total_gap == nullptr)
    cout << "Gap now has value " << solved_Total_gap->content;

  cout << endl;

  return 0;
}
