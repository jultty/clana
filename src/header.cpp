#include "file.hpp"
#include "header.hpp"

using namespace std;

const string HEADER_PATTERN = "EstacaoCodigo;NivelConsistencia;";

bool detect_headers(string line)
{
  return line.substr(0, HEADER_PATTERN.size()) == HEADER_PATTERN;
}

// traverses a linked list of headers
Header* traverse_headers(Line* headers, int start, int distance) {

  Header* current_position = headers->first_field->header;

  distance += start - 1; // traversing will start at position 1

  while (distance != 0) {
    if (distance > 0) {
      distance--;
      current_position = current_position->next;
    } else {
      current_position = current_position->previous;
      distance++;
    }
  }
  return current_position;
}

// binary search for a column's header
Header* search_header(Line* headers, int target, int first, int last) {

  int pivot = (first + last) / 2;
  int distance = target - pivot;
  Field* traversed_field = traverse_fields(headers, pivot, distance);
  Header* target_header = traversed_field->header;

  if (target > pivot) {
    search_header(headers, target, pivot + 1, last);
  } else if (target < pivot) {
    search_header(headers, target, first, pivot - 1);
  }
  return target_header;
}

// search for a header by its column
Header* get_header(int column, Line* headers) {

  int first = headers->first_field->column;
  int last = headers->last_field->column;

  Header* result = search_header(headers, column, first, last);
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

// search for a column by its header
int get_column(string header, Line* headers) {
  Field* start = traverse_fields(headers, 1, 1);

  while (header != start->content) {
    start = start->next;
  }
  return start->column;
};

double parse_double(string observation) {
  string parsed_observation = "";
  for (char character : observation) {
        if (character == ',') {
          parsed_observation.push_back('.');
        }
          else if (isdigit(character)) {
          parsed_observation.push_back(character);
        } else {
          parsed_observation = "0";
        }
    }

  if (parsed_observation == "") {
    parsed_observation = "0";
  }
  double parsed_double = stod(parsed_observation);
  return parsed_double;
};
