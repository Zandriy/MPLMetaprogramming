#include <iostream>

template <bool x>
struct bool_
{
    static bool const value = x;
    typedef bool_<x> type;
    typedef bool value_type;
    operator bool() const { return x; }
};

using false_ = bool_<false>;
using true_ = bool_<true>;

template <int N>
struct int_
{
    static const int value = N;
    typedef int_<N> type;
    typedef int value_type;
    typedef int_<N + 1> next;
    typedef int_<N - 1> prior;
    operator int() const { return N; }
};

template <class T, T N>
struct integral_c
{
    static const T value = N;
    typedef integral_c<T, N> type;
    typedef T value_type;
    typedef integral_c<T, N + 1> next;
    typedef integral_c<T, N - 1> prior;
    operator T() const { return N; }
};

template <class, class>
struct is_same
    : false_
{
};

template <class T>
struct is_same<T, T>
    : true_
{
};

template <class N1, class N2>
struct equal_to : bool_<(N1::value == N2::value)>
{
};

template <class T>
inline T next(T x) { return ++x; }

template <class T>
inline T prior(T x) { return --x; }

int main()
{
    std::cout << std::boolalpha << false_::value << "\n";
    std::cout << std::boolalpha << true_::value << "\n";
    std::cout << std::boolalpha << is_same<int_<3>, integral_c<int, 3>>::value << "\n";
    std::cout << std::boolalpha << equal_to<int_<3>, integral_c<int, 3>>::value << "\n";

    std::cout << "=======================================\n";

    std::cout << std::boolalpha << is_same<decltype(next(3)), int_<3>::prior::value_type>::value << "\n";
    std::cout << std::boolalpha << is_same<decltype(next(3L)), int_<3>::prior::value_type>::value << "\n";
    std::cout << std::boolalpha << is_same<decltype(next(3L)), integral_c<long, 3>::value_type>::value << "\n";
}