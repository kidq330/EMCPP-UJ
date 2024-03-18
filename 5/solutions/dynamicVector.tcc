#include "dynamicVector.h"

template <typename T>
Vector<T, 0>::Vector() = default;

template <typename T>
Vector<T, 0>::Vector(size_t size)
    : m_size(size), p_data(std::make_shared<T[]>(m_size)) {}

template <typename T>
Vector<T, 0>::Vector(const Vector &v) : Vector(v.size()) {
  std::copy_n(v.p_data.get(), m_size, this->p_data.get());
}

template <typename T>
Vector<T, 0>::Vector(Vector &&v) = default;

template <typename T>
Vector<T, 0> &Vector<T, 0>::operator=(Vector<T, 0> m) {
  swap(*this, m);
  return *this;
}

template <typename T>
Vector<T, 0>::Vector(const std::initializer_list<T> &list) {
  resize(list.size());
  std::copy(std::begin(list), std::end(list), p_data.get());
}

template <typename T>
void Vector<T, 0>::resize(size_t newSize) {
  auto tmp = Vector(newSize);
  std::copy_n(p_data.get(), std::min(m_size, tmp.m_size), tmp.p_data.get());
  *this = std::move(tmp);
}

template <typename T>
constexpr Vector<T, 0>::size_type Vector<T, 0>::size() const {
  return m_size;
}

template <typename T>
Vector<T, 0>::const_reference Vector<T, 0>::get(size_type index) const {
  return p_data[index];
}

template <typename T>
void Vector<T, 0>::set(size_type index, const_reference value) {
  p_data[index] = value;
}

template <typename T>
Vector<T, 0>::reference Vector<T, 0>::operator[](size_type index) {
  return p_data[index];
}

template <typename T>
Vector<T, 0>::const_reference Vector<T, 0>::operator[](size_type index) const {
  return p_data[index];
}

template <typename T>
Vector<T, 0> operator+(const Vector<T, 0> &u, const Vector<T, 0> &v) {
  const auto n = u.size();
  if (n != v.size()) {
    throw VectorException("incompatible sizes in Vector::operator+");
  }
  Vector<T, 0> res(n);
  std::transform(u.p_data.get(), u.p_data.get() + n, v.p_data.get(),
                 res.p_data.get(), std::plus{});
  return res;
}

template <typename T>
void swap(Vector<T, 0> &a, Vector<T, 0> &b) {
  using std::swap;
  std::swap(a.m_size, b.m_size);
  std::swap(a.p_data, b.p_data);
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Vector<T, 0> &v) {
  std::for_each_n(v.p_data.get(), v.size(),
                  [&out](auto elem) { out << elem << " "; });
  return out;
}

template <typename T>
template <size_t N>
Vector<T, 0>::operator Vector<T, N>() const {
  if (m_size != N) {
    throw VectorException("");
  }
  Vector<T, N> res;

  std::copy_n(p_data.get(), N, std::begin(res.data));
  return res;
}

template <typename T, size_t N>
Vector<T, N>::operator Vector<T, 0>() const {
  Vector<T, 0> res(N);
  std::copy(std::begin(this->data), std::end(this->data), res.p_data.get());
  return res;
}

template <typename T, size_t N>
Vector<T, N> operator+(const Vector<T, N> &u, const Vector<T, 0> &v) {
  return u + static_cast<Vector<T, N>>(v);
}

template <typename T, size_t N>
Vector<T, N> operator+(const Vector<T, 0> &u, const Vector<T, N> &v) {
  return operator+(v, u);
}