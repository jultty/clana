#include <iostream>
#include <fstream>

using namespace std;

string line;

int main () {
  ofstream outfile;
  ifstream infile;

  infile.open("in.txt");

    while (getline (infile, line)) {
      cout << line;
    }

  infile.close();

  outfile.open ("out.txt");
  outfile << "File I/O scaffold\n";
  outfile.close();
  return 0;
}
