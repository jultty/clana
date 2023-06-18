#ifndef CLANA_LINE_H
#define CLANA_LINE_H
#include <string>
#include "file.h"

using namespace std;
using Field = struct Field;

struct Line {
    int row = -1;
    string content = "";
    Line *next = nullptr;
    Line *previous = nullptr;
    Field *first_field = nullptr;
    Field *last_field = nullptr;

};

#endif
