#ifndef DYNAMIC_VECTOR_H
#define DYNAMIC_VECTOR_H

#include <memory>
#include <ranges>

#include "staticVector.h"

struct VectorException : std::runtime_error {
  using std::runtime_error::runtime_error;
};

template <typename T>
void swap(Vector<T, 0> &u, Vector<T, 0> &v);

template <typename T>
Vector<T, 0> operator+(const Vector<T, 0> &u, const Vector<T, 0> &v);

template <typename T>
std::ostream &operator<<(std::ostream &out, const Vector<T, 0> &v);

template <typename T>
class Vector<T, 0> {
  size_t m_size = 0;
  std::shared_ptr<T[]> p_data = nullptr;

 public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef T *pointer;
  typedef T &reference;
  typedef const T &const_reference;

  Vector();
  Vector(size_t size);
  Vector(const Vector &);
  Vector(Vector &&);
  Vector(const std::initializer_list<T> &list);
  Vector &operator=(Vector m);

  void resize(size_t newSize);

  void set(size_type index, const_reference value);
  constexpr size_type size() const;
  const_reference get(size_type index) const;
  reference operator[](size_type index);
  const_reference operator[](size_type index) const;

  friend void swap<>(Vector &u, Vector &v);
  friend Vector operator+ <>(const Vector &u, const Vector &v);
  friend std::ostream &operator<< <>(std::ostream &out, const Vector &v);

  template <typename, size_t>
  friend class Vector;

  template <size_t N>
  explicit operator Vector<T, N>() const;
};

#include "dynamicVector.tcc"

#endif

// Exercise 4. Mixed operators
// Add explicit conversions between a static Vector and a dynamic Vector and
// vice versa. Add explicit conversion from Vector<T,N> to Vector<S,M>.
// Implement addition between static and dynamic vectors:
// • sum of static and dynamic vector should be a static vector.