#include <iostream>

#include "Box.h"

using namespace std;

// Exercise: modify code so that appropriate constructor and operators are
// called.
class Container : public Box {
 public:
  static bool verbose;

 public:
  Container(int content) : Box(content) {}
  Container(const Container &container) : Box(container) {
    if (verbose) cout << "Container: copy constructor.\n";
    // __jm__ TODO
  }
  Container &operator=(const Container &container) {
    if (verbose) cout << "Container: copy assignment.\n";
    Box::operator=(container);
    return *this;
  }
  Container(Container &&container) : Box(std::move(container)) {
    if (verbose) cout << "Container: move constructor.\n";
  }
  Container &operator=(Container &&container) {
    if (verbose) cout << "Container: move assignment.\n";
    Box::operator=(std::move(container));
    return *this;
  }
  ~Container() {
    if (verbose) cout << "Container destructor. \n";
  }

  friend Container operator+(const Container &p1, const Container &p2);
  friend ostream &operator<<(ostream &out, const Container &p) {
    return (cout << " [" << p.getContent() << "] ");
  }
};
bool Container::verbose = false;

inline Container operator+(const Container &p1, const Container &p2) {
  Container suma(p1.getContent() + p2.getContent());
  return suma;
}