#include <iostream>
#include <fstream>
#include <string>
#include "file.h"
#include "line.h"
#include "utils.h"

using namespace std;

int main () {

  // set up I/O stream
  ifstream infile;
  ofstream outfile;
  infile.open("in.txt");

  // iterate over each input line
  string line_content;
  while (getline (infile, line_content)) {
    if (detect_headers(line_content))
      cout << line_content;
  }

  infile.close();

  // write output to a file
  outfile.open ("out.log");
  outfile << "File I/O scaffold\n";
  outfile.close();

  // testing
  File file;
  file.addLine("Line 1");
  file.addLine("Line 2");
  file.addLine("Line 3");
  file.print();

  cout << "Exiting" << endl;
  return 0;
}
