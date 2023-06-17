#include <iostream>
#include <fstream>
#include <string>
#include "file.h"

using namespace std;

int main () {

  // set up I/O stream
  ifstream infile;
  ofstream outfile;
  infile.open("in.txt");

  // iterate over each input line
  string line;
  while (getline (infile, line)) {
    cout << line << endl;
  }

  infile.close();

  // write output to a file
  outfile.open ("out.log");
  outfile << "File I/O scaffold\n";
  outfile.close();

  // for make testing 
  cout << "4 + 6 is " << add(4,6) << endl;

  cout << "Exiting";
  return 0;
}
