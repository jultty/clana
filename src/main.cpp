#include <fstream>
#include "file.hpp"
#include "header.hpp"

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

  //print mapped contents
  file.print("");

  cout << "Chuva 22 is at column";
  cout << get_column("Chuva22", file.headers) << endl;

  return 0;
}
