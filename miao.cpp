#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct Student {
  std::string name;
  std::string surname;
  int badge_number;
};

struct Node {
  Student student;
  Node* next;
};

Node* head = nullptr;
size_t size = 0;

void add(const Student& student) {
  Node* new_node = new Node{student, head};
  head = new_node;
  size++;
}

Student get(size_t index) {
  Node* current = head;
  for (size_t i = 0; i < index; i++) {
    current = current->next;
  }
  return current->student;
}

void remove(size_t index) {
  if (index == 0) {
    Node* to_delete = head;
    head = head->next;
    delete to_delete;
  } else {
    Node* current = head;
    for (size_t i = 0; i < index - 1; i++) {
      current = current->next;
    }
    Node* to_delete = current->next;
    current->next = current->next->next;
    delete to_delete;
  }
  size--;
}

void clear() {
  Node* current = head;
  while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;
  }
  head = nullptr;
  size = 0;
}

void save(const std::string& filename) {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file\n";
    return;
  }

  Node* current = head;
  while (current != nullptr) {
    file << current->student.name << "," << current->student.surname << "," << current->student.badge_number << "\n";
    current = current->next;
  }
}

void load(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file\n";
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream linestream(line);
    std::string name, surname;
    int badge_number;
    std::getline(linestream, name, ',');
    std::getline(linestream, surname, ',');
    linestream >> badge_number;

    Student student = {name, surname, badge_number};
    add(student);
  }
}

int main() {
  bool quit = false;
  while (!quit) {
    std::cout << "Menu:\n";
    std::cout << "1. Add student\n";
    std::cout << "2. Delete student\n";
    std::cout << "3. Print students\n";
    std::cout << "4. Save students\n";
    std::cout << "5. Load students\n";
    std::cout << "6. Quit\n";
    std::cout << "Enter your choice: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1) {
      std::cout << "Enter name: ";
      std::string name;
      std::getline(std::cin, name);

      std::cout << "Enter surname: ";
      std::string surname;
      std::getline(std::cin, surname);

      std::cout << "Enter badge number: ";
      int badge_number;
      std::cin >> badge_number;
      std::cin.ignore();

      Student student = {name, surname, badge_number};
      add(student);
    } else if (choice == 2) {
      std::cout << "Enter index of student to delete: ";
      size_t index;
      std::cin >> index;
      std::cin.ignore();
      remove(index);
    } else if (choice == 3) {
      for (size_t i = 0; i < size; i++) {
        Student s = get(i);
        std::cout << s.name << " " << s.surname << " " << s.badge_number << "\n";
      }
    } else if (choice == 4) {
      std::cout << "Enter filename: ";
      std::string filename;
      std::getline(std::cin, filename);
      save(filename);
    } else if (choice == 5) {
      std::cout << "Enter filename: ";
      std::string filename;
      std::getline(std::cin, filename);
      load(filename);
    } else if (choice == 6) {
      quit = true;
    }
  }

  clear();

  return 0;
}

