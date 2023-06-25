#include "file.hpp"
#include "header.hpp"
#include <cmath>
#include <tuple>

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

// finds gaps in columns, returns first match
// returns the header field if all fields are gaps
Field* column_gap_scan(Header* header, Line* start, Line* end) {

  Field* current = header->first_field;

  Field* first_match = nullptr;
  bool has_values = false;

  // check all fields for gaps
  while (current != nullptr) {
    int field_row = current->line->row;

    // if field is a gap, first match and within range
    if (current->content == "") {
      if (first_match == nullptr && 
          field_row >= start->row && field_row <= end->row) {
        first_match = current;
      } 
      // field is not a gap
    } else {
      has_values = true;
    }

    // if there is a field below, move to it
    if (current->below != nullptr) {
      current = current->below;
      // if there is no field below, exit loop
    } else {
      break;
    }
  }

  // column is not all gaps and there is a gap within range 
  if (has_values) {
    if (first_match != nullptr) {
      return first_match;
    }
  // column is all gaps
  } else {
    return header->field;
  }
  // column has no gaps
  return first_match;
}

void gap_average_solver(Header* header, Line* start, Line* end) {

  Field* current = header->first_field;

  // check whole column for gaps
  while (current != nullptr) {
    int field_row = current->line->row;

    // if field is a gap and within range, set content to the column average
    if (current->content == "") {
      if (field_row >= start->row && field_row <= end->row) {
        current->content = to_string(current->header->average);
      }
    }

    // move to field below if it exists
    if (current->below != nullptr)
      current = current->below;
    else
      break;
  }
}

void gap_regression_solver(Header* header, Line* start, Line* end, tuple<double, double> model) {

  Field* current = header->first_field;

  // check whole column for gaps
  while (current != nullptr) {
    int field_row = current->line->row;

    // if field is a gap and within range, set content to a predicted value
    if (current->content == "") {
      if (field_row >= start->row && field_row <= end->row) {
        double predicted_value =
          predict(current->header->average, model);
        current->content = to_string(predicted_value);
      }
    }

    // move to field below if it exists
    if (current->below != nullptr)
      current = current->below;
    else
      break;
  }
}

void range_average_solver(Header* start, Header* end) {
  Header* current = start;

  while (current != nullptr) {

    gap_average_solver(current, current->first_field->line,
        current->last_field->line);

    current = current->next;
  }
}

void range_regression_solver(Header* start, Header* end, tuple<double, double> model) {
  Header* current = start;

  while (current != nullptr) {

    gap_regression_solver(current, current->first_field->line,
        current->last_field->line, model);

    current = current->next;
  }
}

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

double sqr(double x) {
  return x * x;
};

// arguments: header for the column and number of lines
double sqrd_sum(Header* header, int n) {

  double total = 0;
  Field* current = header->first_field;

  for (int i = 1; i <= n; i++) {
    total += sqr(parse_double(current->content));
    if (current->below != nullptr) {
      current = current->below;
    } else {
      break;
    }
  }

  return total;
};

double multiplied_sum(Header* x, Header* y, int n) {
  double total = 0;
  Field* current_x = x->first_field;
  Field* current_y = y->first_field;

  for (int i = 1; i <= n; i++) {
    total += parse_double(current_x->content) * parse_double(current_y->content);
    if (current_x->below != nullptr && current_y->below != nullptr) {
      current_x = current_x->below;
      current_y = current_y->below;
    } else {
      break;
    }
  }

  return total;
}

double get_correlation(Header*x, Header* y, int n) {
  double x_sum = x->total;
  double x_sqrd_sum = sqrd_sum(x, n);
  double y_sum = y->total;
  double y_sqrd_sum = sqrd_sum(y, n);
  double xy_sum = multiplied_sum(x, y, n);

  double numerator = (n * xy_sum) - (x_sum * y_sum);
  double x_root = sqrt((n * x_sqrd_sum) - sqr(x_sum));
  double y_root = sqrt((n * y_sqrd_sum) - sqr(y_sum));
  double denominator = x_root * y_root;

  return numerator / denominator;
};

tuple<double, double> regression(Header* x, Header* y, int n) {
  double x_sum = x->total;
  double x_sqrd_sum = sqrd_sum(x, n);
  double y_sum = y->total;
  double xy_sum = multiplied_sum(x, y, n);

  double numerator = (n * xy_sum) - (x_sum * y_sum);
  double denominator = (n * x_sqrd_sum) - sqr(x_sum);

  double m = numerator / denominator;
  double b = y->average - (m * x->average);

  return make_tuple(m, b);
}

double predict(double x, tuple<double, double> model) {
  double m = get<0>(model);
  double b = get<1>(model);
  return (m * x) + b;
}
