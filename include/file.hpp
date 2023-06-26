#ifndef CLANA_FILE_H
#define CLANA_FILE_H
#include <string>
#include <limits>
#include "line.hpp"
#include "field.hpp"
#include "header.hpp"

using namespace std;
using File = struct File;

class File {
  private:
    int max_fields;

  public:
    Line* first = nullptr;
    Line* last = nullptr;
    Line* headers = nullptr;
    Header* first_header = nullptr;
    Header* last_header = nullptr;
    File();
    void add(string content);
    void print(string option);
    void print_interactively(string option);
    void write();
    int menu();
    void find_gaps();
    void show_correlation();
    void average_solve();
    void regression_solve();
};

#endif
