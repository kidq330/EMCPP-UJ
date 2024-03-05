#include <algorithm>
#include <iostream>
#include <memory>

#include "MyString.h"
using namespace std;

class String {
  using string = emcpp::MyString;
  //    using string = std::string;

  /// Store a pointer to dynamically allocated string!
  std::shared_ptr<string> mp_s = nullptr;

 public:
  String();                           /// creates an empty string
  String(const char* str);            /// copy C-string
  String(const String&);              /// no copy
  String operator=(const String& s);  /// no copy
  /// makes a copy of a string if it has more than one reference.
  void set(int index, char ch);
  /// no copy
  char get(int index) const;
  /// creates a new string only if both strings are non empty
  friend String operator+(String a, String b);
  friend std::ostream& operator<<(std::ostream& out, String s);
};

String::String() : mp_s(std::make_shared<String::string>()) {}
String::String(const char* str) : mp_s(std::make_shared<String::string>(str)) {}
String::String(const String& str) : mp_s(str.mp_s) {}

String String::operator=(const String& s) {
  mp_s = s.mp_s;
  return *this;
}

void String::set(int index, char ch) {
  switch (mp_s.use_count()) {
    case 0:
      throw std::invalid_argument("Container does not own a string");
      break;
    case 1:
      break;
    default:
      mp_s = std::make_shared<String::string>(*mp_s);
      break;
  }
  (*mp_s)[index] = ch;
}

char String::get(int index) const { return mp_s->operator[](index); }

String operator+(String a, String b) {
  return a.mp_s->empty()   ? a = b
         : b.mp_s->empty() ? b = a
                           : String((*a.mp_s + *b.mp_s).c_str());
}

std::ostream& operator<<(std::ostream& out, String s) { return out << *s.mp_s; }