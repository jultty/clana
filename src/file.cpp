#include <fstream>
#include <iostream>
#include <string>
#include "file.hpp"
#include "header.hpp"

using namespace std;

File::File() : first(nullptr), last(nullptr) {}

void File::add(string content) {

  Line* new_line = new Line;
  new_line->content = content;
  int field_counter = 1;

  // check if this line is the header
  if (detect_headers(content)) {
    headers = new_line;
    new_line->is_header = true;
    max_fields = count_headers(headers->content) + 1;
  }

  // if headers are set, map each observed value to a field 
  if (headers) {

    stringstream ss(content);
    string observation;

    while (getline(ss, observation, ';') && field_counter <= max_fields) {
      Field* new_field = new Field;

      new_field->line = new_line;
      new_field->content = observation;

      // set first, last, previous and next
      if (new_line->first_field == nullptr) {
        new_field->column = 1;
        new_line->first_field = new_field;
        new_line->last_field = new_field;
      }
      else {
        new_field->column = new_line->last_field->column + 1;
        new_field->previous = new_line->last_field;
        new_line->last_field->next = new_field;
        new_line->last_field = new_field;
      }

      if (new_line->is_header) {
        Header* new_header = new Header;

        new_header->column = new_field->column;
        new_header->field = new_field;

        if (first_header == nullptr) {
          first_header = new_header;
          last_header = new_header;
        } else {
          new_header->previous = last_header;
          last_header->next = new_header;
          last_header = new_header;
        };
        new_field->header = new_header;
      } else {
        // set header name
        new_field->header = get_header(new_field->column, headers);

        // set vertical links
        if (new_field->header->first_field == nullptr) {
          new_field->header->first_field = new_field;
          new_field->header->last_field = new_field;
        } else {
          new_field->above = new_field->header->last_field;
          new_field->header->last_field->below = new_field;
          new_field->header->last_field = new_field;
        }

        // calculate header total and average
        new_field->header->total = new_field->header->total 
          + parse_double(observation);
        int observation_rows = (last->row - headers->row);
        new_field->header->average =
          new_field->header->total / observation_rows;
      }

      field_counter++;
    }
  }

  // set first, last, previous and next
  if (first == nullptr) {
    first = new_line;
    last = new_line;
    new_line->row = 1;
  }
  else {
    new_line->row = last->row + 1;
    new_line->previous = last;
    new_line->previous->is_last = false;
    last->next = new_line;
    last = new_line;
    new_line->is_last = true;
  }
}

void wait_dialog() {
  string back_dialog;
  cout << "\nTask completed. Press return to go back: ";
  cin.get();
  cin.ignore(32767, '\n');
  cin.clear();
}

// print all lines
void File::print(string option) {
  Line* current = first;
  if (option != "all")
    current = headers->next;
  while (current != nullptr) {
    cout << "Line " << current->row << ": " << current->content << endl;
    current = current->next;
  }
  wait_dialog();
  cin.clear();
}

void File::print_interactively(string option) {
  Line* current = first;
  if (option != "all")
    current = headers->next;
  while (current != nullptr) {
    cout << "Line " << current->row << ": " << current->content << endl;

    cout << "\n n: next line \n p: previous line \n e: exit\n";
    cout << " line number: go to line\n > ";
    string input;
    cin >> input;
    cout << "\n";

    if (input == "e") {
      break;
    } else if (input == "n") {
      current = current->next;
    } else if (input == "p" && current->previous != nullptr) {
      current = current->previous;
    } else if (current->previous == nullptr) {
      cout << " [!] Invalid position \n";
    } else {
      current = traverse_lines(first, stoi(input) - 1);
    }
  }
}

void File::write() {
  ofstream outfile;
  outfile.open("out.csv");
  Line* current = headers;
  Field* current_field = current->first_field;

  while (current != nullptr) {
    while (current_field != nullptr) {
      outfile << current_field->content;
      if (current_field != current->last_field) {
        outfile << ";";
      }
      if (current_field->next != nullptr) {
        current_field = current_field->next;
      } else {
        break;
      }
    }
    if (current->next != nullptr) {
      outfile << "\n";
      current = current->next;
      current_field = current->first_field;
    } else {
      break;
    }
  }
  outfile.close();
  wait_dialog();
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif
}

int File::menu() {
  int option = 0;
  while (option == 0) {
    clear_screen();
    cout << ".---------------------------------------." << endl;
    cout << "|                                       |" << endl;
    cout << "|             clana 0.1.0               |" << endl;
    cout << "|                                       |" << endl;
    cout << "|  1. Print all data                    |" << endl;
    cout << "|  2. Print data interactively          |" << endl;
    cout << "|  3. Write current data to file        |" << endl;
    cout << "|  4. Find gaps                         |" << endl;
    cout << "|  5. Show correlation                  |" << endl;
    cout << "|  6. Solve gaps with average           |" << endl;
    cout << "|  7. Solve gaps with regression        |" << endl;
    cout << "|  8. Exit                              |" << endl;
    cout << "|                                       |" << endl;
    cout << "|  Enter your choice below and press    |" << endl;
    cout << "|  return to continue:                  |" << endl;
    cout << "'---------------------------------------'" << endl;
    cout << "  > ";
    if(!(cin >> option)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      option = 0;
    } else if (option < 1 || option > 8) {
      option = 0;
    }
  }
  return option;
}

void File::find_gaps() {
  cout << "Type the title of the column to search:" << endl;
  string title = "";
  cin >> title;
  cin.clear();
  int column = get_column(title, headers);
  Header* header = traverse_headers(headers, 0, column);
  Field* found_gap = column_gap_scan(header, first, last);
  if (found_gap != nullptr) {
    cout << "Gap found at row " << found_gap->line->row;
    cout << " of column " << found_gap->column << " (";
    cout << found_gap->header->field->content << ")\n";
  } else {
    cout << "No gap found\n";
  }
  wait_dialog();
  
}

void File::show_correlation() {
  cout << "Provide the headers for the two columns and press return:" << endl;
  string a_title = "";
  string b_title = "";

  cout << "First column: ";
  cin >> a_title;
  cin.clear();
  cout << "Second column: ";
  cin >> b_title;
  cin.clear();
  int a_column = get_column(a_title, headers);
  int b_column = get_column(b_title, headers);
  
  Header* a_header = traverse_headers(headers, 0, a_column);
  Header* b_header = traverse_headers(headers, 0, b_column);
  double n = last->row - headers->row - 1;

  double correlation = get_correlation(a_header, b_header, n);

  cout << "Correlation is " << correlation << endl;
  wait_dialog();
}

void File::average_solve() {
  cout << "Provide two headers for the beginning and end of the range\n";
  cout << "To modify a single column, provide its header twice\n";
  string a_title = "";
  string b_title = "";

  cout << "First column: ";
  cin >> a_title;
  cin.clear();
  cout << "Second column: ";
  cin >> b_title;
  cin.clear();

  int a_column = get_column(a_title, headers);
  int b_column = get_column(b_title, headers);
  
  Header* a_header = traverse_headers(headers, 0, a_column);
  Header* b_header = traverse_headers(headers, 0, b_column);

  range_average_solver(a_header, b_header);

  cout << "Done. Now running a gap scan on this range\n";
  Field* a_gap = column_gap_scan(a_header, headers, last);
  Field* b_gap = column_gap_scan(b_header, headers, last);
  if (a_gap == nullptr && b_gap == nullptr)
    cout << "Success: No gaps found\n";

  wait_dialog();
}

void File::regression_solve() {
  
  cout << "Provide two headers for the beginning and end of the range\n";
  cout << "To modify a single column, provide its header twice\n";
  string a_title = "";
  string b_title = "";

  cout << "First column: ";
  cin >> a_title;
  cin.clear();
  cout << "Second column: ";
  cin >> b_title;
  cin.clear();

  int a_column = get_column(a_title, headers);
  int b_column = get_column(b_title, headers);
  
  Header* a_header = traverse_headers(headers, 0, a_column);
  Header* b_header = traverse_headers(headers, 0, b_column);

  cout << "Provide two headers to build the regression model\n";

  string a_model_title, b_model_title;

  cout << "First column: ";
  cin >> a_model_title;
  cin.clear();
  cout << "Second column: ";
  cin >> b_model_title;
  cin.clear();

  int a_model_column = get_column(a_model_title, headers);
  int b_model_column = get_column(b_model_title, headers);
  
  Header* a_model_header = traverse_headers(headers, 0, a_model_column);
  Header* b_model_header = traverse_headers(headers, 0, b_model_column);
  double n = last->row - headers->row - 1;

  double correlation = get_correlation(a_model_header, b_model_header, n);
  tuple<double, double> model  = regression(a_model_header, b_model_header, n);
  double m = get<0>(model);
  double b = get<1>(model);

  cout << "Model is ready with correlation coefficient of " << correlation;
  cout << "\nThe equation for " << a_model_header->field->content << " and ";
  cout << b_model_header->field->content << " is: y = " << m << "x + ";
  cout << b << endl;

  string correlated_title;

  cout << "Enter the header for the column to use for your X value: ";

  cin >> correlated_title;
  cin.clear();

  int correlated_column = get_column(correlated_title, headers);
  Header* correlated_header = traverse_headers(headers, 0, correlated_column);

  range_regression_solver(a_model_header, b_model_header, model, correlated_header);

  cout << "Done. Now running a gap scan on this range\n";
  Field* a_gap = column_gap_scan(a_header, headers, last);
  Field* b_gap = column_gap_scan(b_header, headers, last);
  if (a_gap == nullptr && b_gap == nullptr)
    cout << "Success: No gaps found\n";

  wait_dialog();
}
