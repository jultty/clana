#ifndef CLANA_FILE_H
#define CLANA_FILE_H
#include <string>
#include "line.hpp"
#include "field.hpp"

using namespace std;
using File = struct File;

class File {
  private:
    int max_fields;

  public:
    Line* first = nullptr;
    Line* last = nullptr;
    Line* headers = nullptr;
    File();
    void add(string content);
    void print(string option);
    void print_interactively(string option);
};

#endif
