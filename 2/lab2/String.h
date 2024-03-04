#include <iostream>
#include <algorithm>
#include "MyString.h"
using namespace std;

class String{
   using string = emcpp::MyString;
//    using string = std::string;

/// Store a pointer to dynamically allocated string!

public:
    String();     /// creates an empty string
    String(const char * str);           /// copy C-string
    String(const String & );            /// no copy
    String operator=(const String & s); /// no copy
    /// makes a copy of a string if it has more than one reference.
    void set(int index, char ch);
    /// no copy
    char get(int index) const;
    /// creates a new string only if both strings are non empty
    friend String operator+(String a, String b);
    friend std::ostream & operator<< (std::ostream & out, String s);
};
