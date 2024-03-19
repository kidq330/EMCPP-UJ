#include <algorithm>
#include <iostream>
#include <memory>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

// how does std::apply handle references?
// answer -> correctly, when forwarding

template <typename U>
constexpr U get_first_v() {
  throw std::runtime_error("");
}

template <typename U, typename V, typename... Vs>
constexpr decltype(auto) get_first_v(V&& v, Vs&&... vs) {
  if constexpr (std::is_same_v<U, std::decay_t<V>>) {
    return v;
  } else
    return get_first_v<U, Vs...>(std::forward<Vs>(vs)...);
}

// ISSUE: return has wrong colour here
// template <typename U, typename _Tuple>
// constexpr auto get_first(_Tuple&& t) {
//   return std::apply(
//       []<typename... Args>(Args&&... args) {
//         return get_first_v<U, Args...>(args...);
//       },
//       std::forward<_Tuple>(t));
// }

// TEST: if tuple is const returned ref should also be const
// this is in some way solved by decltype(auto), or [-> decltype(*)] construct
// in general

template <typename U, typename _Tuple>
constexpr std::shared_ptr<U> get_first(_Tuple&& t) {
  return std::apply(
      []<typename... Args>(Args&&... args) -> std::shared_ptr<U> {
        return get_first_v<std::shared_ptr<U>,
                           std::shared_ptr<std::decay_t<Args>>...>(
            std::shared_ptr<std::decay_t<Args>>(&args)...);
      },
      std::forward<_Tuple>(t));
}

template <typename... Args>
class MultiVector {
  std::tuple<std::vector<Args>...> m_vectors;

  template <typename T>
  static void print_vec(const std::vector<T>& v) {
    std::cout << "[ ";
    std::for_each(std::begin(v), std::end(v),
                  [](const T& x) { std::cout << x << ' '; });
    std::cout << "]";
  }

 public:
  template <typename T>
  void push_back(T&& v) {
    std::cout << "chuj";
    auto pc = get_first<std::vector<T>>(m_vectors);
    std::cout << pc->size() << " s1\n";
    pc->push_back(std::forward<decltype(v)>(v));
    std::cout << pc->size() << " s2\n";
    pc = get_first<std::vector<T>>(m_vectors);
    std::cout << pc->size() << " s3\n";
  }

  void print() const {
    std::apply(
        []<typename... VecsT>(const VecsT&... vecs) {
          (
              [](const auto& vec) {
                print_vec(vec);
                std::cout << ' ';
              }(vecs),
              ...);
        },
        m_vectors);
    std::cout << '\n';
  }
};

int main() {
  std::cout << "chuj";

  MultiVector<int, string, double> m;
  m.push_back(5);
  // m.push_back(string("text"));
  // m.push_back(7);
  // m.push_back(1.2);
  // m.print();  // [ 5 7 ] [ text ] [ 1.2 ]
  // auto v = std::move(m);
  // for (auto x : {1, 2, 3}) {
  //   v.push_back(x + 10);
  //   v.push_back(std::to_string(x));
  //   v.push_back(x / 10.0);
  // }
  // m.print();  // [ ] [ ] [ ]   but can be undefined
  // v.print();  // [ 5 7 11 12 13 ] [ text 1 2 3 ] [ 1.2 0.1 0.2 0.3 ]
  // MultiVector<int, int, double, int> w;
  // w.push_back(1);
  // w.push_back(2.0);
  // w.print();  // [ 1 ] [ ] [ 2 ] [ ]
}
/*
[ 5 7 ] [ text ] [ 1.2 ]
[ ] [ ] [ ]
[ 5 7 11 12 13 ] [ text 1 2 3 ] [ 1.2 0.1 0.2 0.3 ]
[ 1 ] [ ] [ 2 ] [ ]
 */