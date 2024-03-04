#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>

class Matrix {
  using T = double;
  size_t R = 0, C = 0;
  T *data = nullptr;

 public:
  const T &operator()(size_t i, size_t j) const;
  T &operator()(size_t i, size_t j);
  Matrix operator-() const;
  friend std::ostream &operator<<(std::ostream &, const Matrix &);

  friend void swap(Matrix &, Matrix &);

  Matrix &operator=(Matrix m);
  Matrix();
  Matrix(size_t R, size_t C);
  Matrix(std::initializer_list<std::initializer_list<T>>);
  Matrix(const Matrix &);
  Matrix(Matrix &&);
  ~Matrix();
};

const Matrix::T &Matrix::operator()(size_t i, size_t j) const {
  return *(data + i * C + j);
}
Matrix::T &Matrix::operator()(size_t i, size_t j) {
  return *(data + i * C + j);
}

Matrix Matrix::operator-() const {
  auto m = *this;
  for (size_t i = 0; i < m.R; ++i) {
    for (size_t j = 0; j < m.C; ++j) {
      m(i, j) *= -1;
    }
  }
  return m;
}

std::ostream &operator<<(std::ostream &out, const Matrix &m) {
  for (size_t i = 0; i < m.R; ++i) {
    for (size_t j = 0; j < m.C; ++j) {
      out << m(i, j) << ' ';
    }
    out << '\n';
  }
  return out;
}

void swap(Matrix &m1, Matrix &m2) {
  using std::swap;
  std::swap(m1.C, m2.C);
  std::swap(m1.R, m2.R);
  std::swap(m1.data, m2.data);
}

Matrix &Matrix::operator=(Matrix m) {
  swap(*this, m);
  return *this;
}

Matrix::Matrix() = default;

Matrix::Matrix(size_t R, size_t C) : R(R), C(C) {
  data = new Matrix::T[R * C];
  std::fill(data, data + R * C, 0);
}

Matrix::Matrix(std::initializer_list<std::initializer_list<Matrix::T>> list) {
  this->C = std::ranges::max(
      list | std::views::transform(&std::initializer_list<Matrix::T>::size));
  this->R = std::size(list);

  data = new Matrix::T[R * C];
  std::fill(data, data + R * C, 0);

  auto curr = data;
  for (const auto &sub : list) {
    std::ranges::copy(sub, curr);
    curr += C;
  }
}

Matrix::Matrix(const Matrix &m) : R(m.R), C(m.C) {
  data = new Matrix::T[R * C];
  std::copy(m.data, m.data + m.R * m.C, data);
}

Matrix::Matrix(Matrix &&m) { swap(*this, m); }

Matrix::~Matrix() {
  if (data != nullptr) delete[] data;
}

class MatrixWithLabel : public Matrix {
  using LT = std::string;
  LT label = "A";

 public:
  void setLabel(LT label);
  LT getLabel() const;

  using Matrix::Matrix;
  MatrixWithLabel(LT label, size_t R, size_t C);
};

void MatrixWithLabel::setLabel(MatrixWithLabel::LT label) {
  this->label = label;
}

MatrixWithLabel::LT MatrixWithLabel::getLabel() const { return this->label; }

MatrixWithLabel::MatrixWithLabel(MatrixWithLabel::LT label, size_t R, size_t C)
    : Matrix(R, C), label(label) {}