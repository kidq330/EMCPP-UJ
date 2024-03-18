#ifndef STATIC_VECTOR_H
#define STATIC_VECTOR_H

#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <ranges>
#include <vector>

template <typename T, size_t N>
class Vector;

template <typename T, size_t N>
void swap(Vector<T, N> &u, Vector<T, N> &v);

template <typename T, size_t N>
Vector<T, N> operator+(const Vector<T, N> &u, const Vector<T, N> &v);

template <typename T, size_t N>
std::ostream &operator<<(std::ostream &out, const Vector<T, N> &v);

template <typename T, size_t N>
Vector<T, N> operator+(const Vector<T, N> &u, const Vector<T, 0> &v);

template <typename T, size_t N>
Vector<T, N> operator+(const Vector<T, 0> &u, const Vector<T, N> &v);

template <typename T, size_t N>
class Vector {
  T data[N];

 public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef T *pointer;
  typedef T &reference;
  typedef const T &const_reference;

  Vector();
  Vector(const Vector &);
  Vector(Vector &&);
  Vector(const std::initializer_list<T> &list);
  Vector &operator=(Vector);

  void set(size_type index, const_reference value);

  constexpr size_type size() const;
  const_reference get(size_type index) const;
  reference operator[](size_type index);
  const_reference operator[](size_type index) const;

  friend void swap<>(Vector &u, Vector &v);
  friend Vector operator+ <>(const Vector &u, const Vector &v);
  friend std::ostream &operator<< <>(std::ostream &out, const Vector &v);

  friend Vector operator+ <>(const Vector &u, const Vector<T, 0> &v);
  friend Vector operator+ <>(const Vector<T, 0> &u, const Vector &v);

  friend Vector<T, 0>;
  explicit operator Vector<T, 0>() const;
};

#include "staticVector.tcc"

#endif  // STATIC_VECTOR_H