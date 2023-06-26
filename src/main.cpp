#include <fstream>
#include <iomanip>
#include <cstring>
#include "file.hpp"
#include "header.hpp"

using namespace std;

int main (int argc, char* argv[]) {

  // interactive control for CI
  bool is_interactive = true;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--non-interactive") == 0) {
      is_interactive = false;
      break;
    }
  }

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

  if (is_interactive) {
    int choice = 0;
    while (choice != 8) {
      choice = file.menu();

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
          file.average_solve();
          break;
        case 7:
          file.regression_solve();
          break;
        case 8:
          break;
      }
    }
  }

  return 0;
}
