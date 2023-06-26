#include <fstream>
#include <iomanip>
#include "file.hpp"
#include "header.hpp"

using namespace std;

int main () {

  // set up I/O stream
  ifstream infile;
  infile.open("in.csv");

  // populate data structures with file contents
  File file;
  string line_content;

  while (getline (infile, line_content))
    file.add(line_content);
  infile.close();

  // set number notation and precision
  cout << fixed << setprecision(4);

  /* int choice = file.menu(); */
  int choice = 6;

  switch (choice) {
    case 1:
      file.print("all");
      break;
    case 2:
      file.print_interactively("all");
      break;
    case 3:
      file.write();
      break;
    case 4:
      file.find_gaps();
      break;
    case 5:
      file.show_correlation();
      break;
    case 6:
      break;
  }

  return 0;
}
