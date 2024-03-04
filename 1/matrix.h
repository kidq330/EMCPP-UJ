#include <iostream>
#include <ranges>
#include <numeric>
#include <iterator>

class Matrix
{
    using T = double;
    size_t R, C;
    T *data;

public:
    inline const T &operator()(size_t i, size_t j) const;
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

Matrix::Matrix() = default;

Matrix::Matrix(size_t R, size_t C)
    : R(R), C(C), data(new Matrix::T[R * C]) {}

Matrix::Matrix(std::initializer_list<std::initializer_list<Matrix::T>> list)
{
    this->C = std::ranges::max(
        list | std::views::transform(&std::initializer_list<Matrix::T>::size));
    this->R = std::size(list);

    data = new Matrix::T[R * C];
    std::ranges::fill(data, data + R * C, 0);

    auto curr = data;
    for (const auto &sub : list)
    {
        std::ranges::copy(sub, curr);
        curr += C;
    }
}

Matrix::Matrix(const Matrix &m) : Matrix(m.R, m.C)
{
    for (size_t i = 0; i < R; ++i)
    {
        for (size_t j = 0; j < R; ++j)
        {
            (*this)(i, j) = m(i, j);
        }
    }
}

// Matrix::Matrix(Matrix &&m) = default;
Matrix::Matrix(Matrix &&m)
{
    // swap vs exchange
    std::cout << "dupa";
}

Matrix::~Matrix() = default;

const Matrix::T &Matrix::operator()(size_t i, size_t j) const
{
    return *(data + i * C + j);
}
Matrix::T &Matrix::operator()(size_t i, size_t j)
{
    return *(data + i * C + j);
}

Matrix Matrix::operator-() const
{
    auto m = *this;
    for (size_t i = 0; i < m.R; ++i)
    {
        for (size_t j = 0; j < m.C; ++j)
        {
            m(i, j) *= -1;
        }
    }
    return m;
}

Matrix &Matrix::operator=(Matrix m)
{
    swap(*this, m);
    return *this;
}

std::ostream &
operator<<(std::ostream &out, const Matrix &m)
{
    for (size_t i = 0; i < m.R; ++i)
    {
        for (size_t j = 0; j < m.C; ++j)
        {
            out << m(i, j) << ' ';
        }
        out << '\n';
    }
    return out;
}

void swap(Matrix &m1, Matrix &m2)
{
    using std::swap;
    std::swap(m1.C, m2.C);
    std::swap(m1.R, m2.R);
    std::swap(m1.data, m2.data);
}

class MatrixWithLabel : Matrix
{
    using LT = std::string;
    LT label = "A";

public:
    void setLabel(LT label);
    LT getLabel() const;

    using Matrix::Matrix;
    MatrixWithLabel(LT label, size_t R, size_t C);
};

MatrixWithLabel::MatrixWithLabel(MatrixWithLabel::LT label, size_t R, size_t C)
    : Matrix(R, C), label(label) {}

void MatrixWithLabel::setLabel(MatrixWithLabel::LT label)
{
    this->label = label;
}

MatrixWithLabel::LT MatrixWithLabel::getLabel() const
{
    return this->label;
}