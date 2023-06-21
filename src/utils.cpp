#include "file.h"
#include "utils.h"

using namespace std;

const string HEADER_PATTERN = "EstacaoCodigo;NivelConsistencia;";

bool detect_headers(string line)
{
  return line.substr(0, HEADER_PATTERN.size()) == HEADER_PATTERN;
}

void wait() {
  cout << " [utils.wait] Hit return to continue";
  cout.flush();
  while (getchar() != '\n');
}

Field* field_traverser(Line* headers, int start, int distance) {

  Field* at = headers->first_field;

  distance += start - 1; // traversing will start at position 1

  while (distance != 0) {
    if (distance > 0) {
      distance--;
      at = at->next;
    } else {
      at = at->previous;
      distance++;
    }
  }
  return at; 
}

string search_header(Line* headers, int target, int first, int last) {

  int pivot = (first + last) / 2;
  int distance = target-pivot;
  Field* traversed_field = field_traverser(headers, pivot, distance);
  string target_header = traversed_field->content;

  if (target > pivot) {
    search_header(headers, target, pivot + 1, last);
  } else if (target < pivot) {
    search_header(headers, target, first, pivot - 1);
  } else {
    return target_header;
  }
}

// search for a header by its column
// set the field's header property
string get_header(int column, Line* headers) {

  int first = headers->first_field->column;
  int last = headers->last_field->column;

  string result = search_header(headers, column, first, last);

  return result;
};

int count_headers(string content) {

  int count = 0;
  char target = ';';

  for (char c : content) {
    if (c == target)
      count++;
  }

  return count;
};
