#include "file.h"
#include "utils.h"

using namespace std;

const string HEADER_PATTERN = "EstacaoCodigo;NivelConsistencia;";

bool detect_headers(string line)
{
  return line.substr(0, HEADER_PATTERN.size()) == HEADER_PATTERN;
}

void map_headers() {
  // use sorted headers to search for each field position and set
};

void wait() {
    string null;
    getline(cin, null);
}

Field* field_traverser(Line* headers, int start, int distance) {
  cout << " [utils.field_traverser] traversing from " << start << " for " << distance << " positions" << endl;

  Field* at = headers->first_field;

  distance += start - 1; // traversing will start at position 1

  while (distance != 0) {
    cout << " [utils.field_traverser] at position " << start;
    if (distance > 0) {
       cout << " moving forward at distance " << distance - 1;
       distance--;
       at = at->next;
       cout << " now at" << at->content << endl;
    } else {
       cout << " moving backward at distance " << distance + 1;
       at = at->previous;
       cout << " now at" << at->content << endl;
       distance++;
    }
    cout << " [utils.field_traverser] distance traversed" << endl;
  }
  cout << " [utils.field_traverser] returning" << endl;
  return headers->first_field; // TODO
}

string search_header(Line* headers, int target, int first, int last) {

  cout << " [utils.search_header] got request for column " << target << endl;

  int pivot = (first + last) / 2;

  cout << " [utils.search_header]  target = " << target  << " | first = " << first << " | last = " << last << " | pivot = " << pivot << endl;

  if (target > pivot) {
    int distance = target-pivot;

    cout << " [utils.search_header] distance between target and pivot is " << distance << endl;
    cout << " [utils.search_header] requesting traversal to target position" << endl;
    field_traverser(headers, pivot, distance);

    cout << " [utils.search_header] target > pivot -> " << target << " > " << pivot << endl;
    cout << " [utils.search_header] recursing " << "\n\n";
    search_header(headers, target, pivot + 1, last);
  } else if (target < pivot) {
    cout << " [utils.search_header] target < pivot -> " << target << " < " << pivot << endl;
    cout << " [utils.search_header] recursing " << "\n\n";
    search_header(headers, target, first, pivot - 1);
  } else {
    cout << " [utils.search_header] " "<< found match: " << " target = " << target  << " | first = " << first << " | last = " << last << " | pivot = " << pivot << endl;
    return "not implemented yet"; // todo return header
  }

  cout << " [utils.get_header] returning" << endl;
  return "not implemented yet"; // TODO
}

// search for a header by its column
// set the field's header property
string get_header(int column, Line* headers) {
  cout << " [utils.get_header] got request for column " << column << endl;

  int first = headers->first_field->column;
  int last = headers->last_field->column;

  cout << " [utils.get_header] first column is " << first << ", last is " << last << endl;

  cout << " [utils.get_header] now calling a recursion for header at column " << column << endl;
  string result = search_header(headers, column, first, last);
  cout << " [utils.get_header] got result " << result << " from binary search" << endl;

  cout << " [utils.get_header] returning" << endl;
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
