#include <iostream>
#include <fstream>
#include <string>
#include "file.h"
#include "utils.h"

using namespace std;

int main () {

  // set up I/O stream
  ifstream infile;
  ofstream outfile;
  infile.open("in.txt");

  // iterate over each input line
  string line;
  while (getline (infile, line)) {
    if (detect_headers(line))
      cout << line;
  }

  infile.close();

  // write output to a file
  outfile.open ("out.log");
  outfile << "File I/O scaffold\n";
  outfile.close();

  cout << "Exiting" << endl;
  return 0;
}
