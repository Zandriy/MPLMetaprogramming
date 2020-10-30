#include <iostream>
#include <boost/type_traits/is_same.hpp>

template <class T>
struct add_const_ref
{
    using type = const T &;
};

template <class T>
struct add_const_ref<T &>
{
    using type = T &;
};

int main()
{
    std::cout << "test #0: " << std::boolalpha
              << boost::is_same<const int &, add_const_ref<int>::type>::value << "\n";
    std::cout << "test #1: " << std::boolalpha
              << boost::is_same<int &, add_const_ref<int &>::type>::value << "\n";
}
