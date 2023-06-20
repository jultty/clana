#include <fstream>
#include "file.h"

using namespace std;

int main () {

  // set up I/O stream
  ifstream infile;
  ofstream outfile;
  infile.open("in.csv");

  // iterate over each input line
  File file;
  string line_content;

  while (getline (infile, line_content))
    file.add(line_content);

  infile.close();

  // write output to a file
  outfile.open ("out.log");
  outfile << "File I/O OK\n";
  outfile.close();

  // print file contents
  // file.print("");

  return 0;
}
