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

// print all lines
void File::print(string option) {
  Line* current = first;
  if (option != "all")
    current = headers->next;
  while (current != nullptr) {
    cout << "Line " << current->row << ": " << current->content << endl;
    current = current->next;
  }
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
  outfile.open ("out.csv");
  Line* current = first;
    current = headers->next;
  while (current != nullptr) {
    outfile << current->content << endl;
    current = current->next;
  }
  outfile.close();
}

int File::menu() {
  int option = 0;
  while (option == 0) {
    cout << ".---------------------------------------." << endl;
    cout << "|                                       |" << endl;
    cout << "|             clana 0.1.0               |" << endl;
    cout << "|                                       |" << endl;
    cout << "|  1. Print all data                    |" << endl;
    cout << "|  2. Print data interactively          |" << endl;
    cout << "|  3. Write current data to file        |" << endl;
    cout << "|  4. Find gaps                         |" << endl;
    cout << "|  5. Get correlation                   |" << endl;
    cout << "|  6. Exit                              |" << endl;
    cout << "|                                       |" << endl;
    cout << "|  Enter your choice below and press    |" << endl;
    cout << "|  return to continue:                  |" << endl;
    cout << "'---------------------------------------'" << endl;
    cout << "  > ";
    if(!(cin >> option)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      option = 0;
    } else if (option < 1 || option > 7) {
      option = 0;
    }
  }
  return option;
}

void File::find_gaps() {
  cout << "Type the title of the column to search:" << endl;
  string title = "";
  getline(cin, title);
  cin.clear();
  int column = get_column(title, headers);
  Header* header = traverse_headers(headers, 1, column);
  Field* found_gap = column_gap_scan(header, first, last);
  cout << "Gap found at row " << found_gap->line->row << endl;
}

void File::show_correlation() {
  cout << "Type the title of two columns to correlate:" << endl;
  string a_title = "";
  string b_title = "";

  getline(cin, a_title);
  cin.clear();
  getline(cin, b_title);
  cin.clear();
  int a_column = get_column(a_title, headers);
  int b_column = get_column(b_title, headers);
  
  Header* a_header = traverse_headers(headers, 1, a_column);
  Header* b_header = traverse_headers(headers, 1, b_column);
  double n = last->row - headers->row - 1;

  double correlation = get_correlation(a_header, b_header, n);

  cout << "Correlation is " << correlation << endl;
}


