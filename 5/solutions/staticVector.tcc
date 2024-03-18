#include "staticVector.h"

template <typename T, size_t N>
Vector<T, N>::Vector() = default;

template <typename T, size_t N>
Vector<T, N>::Vector(const Vector<T, N> &m) {
  std::copy(std::begin(m.data), std::end(m.data), std::begin(this->data));
}

template <typename T, size_t N>
Vector<T, N>::Vector(Vector<T, N> &&m) = default;

template <typename T, size_t N>
Vector<T, N>::Vector(const std::initializer_list<T> &list) {
  std::copy(std::begin(list), std::end(list), std::begin(data));
}

template <typename T, size_t N>
Vector<T, N> &Vector<T, N>::operator=(Vector<T, N> m) {
  swap(*this, m);
  return *this;
}

template <typename T, size_t N>
constexpr Vector<T, N>::size_type Vector<T, N>::size() const {
  return N;
}

template <typename T, size_t N>
Vector<T, N>::const_reference Vector<T, N>::get(size_type index) const {
  return data[index];
}

template <typename T, size_t N>
void Vector<T, N>::set(size_type index, const_reference value) {
  data[index] = value;
}

template <typename T, size_t N>
Vector<T, N>::reference Vector<T, N>::operator[](size_type index) {
  return data[index];
}

template <typename T, size_t N>
Vector<T, N>::const_reference Vector<T, N>::operator[](size_type index) const {
  return data[index];
}

template <typename T, size_t N>
std::ostream &operator<<(std::ostream &out, const Vector<T, N> &v) {
  std::for_each(std::begin(v.data), std::end(v.data),
                [&out](auto elem) { out << elem << " "; });
  return out;
}

template <typename T, size_t N>
Vector<T, N> operator+(const Vector<T, N> &u, const Vector<T, N> &v) {
  Vector<T, N> res;
  std::transform(std::begin(u.data), std::end(u.data), std::begin(v.data),
                 std::begin(res.data), std::plus{});
  return res;
}

template <typename T, size_t N>
void swap(Vector<T, N> &u, Vector<T, N> &v) {
  using std::swap;
  std::swap(u.data, v.data);
}
