#include <iostream>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

template <class C, class X, class Y, int I = 0>
struct replace_type;

template <class C, class X, class Y>
struct replace_type<C *, X, Y>
{
    BOOST_STATIC_ASSERT((boost::is_same<C, X>::value));
    using type = Y *;
};

template <class C, class X, class Y, int I>
struct replace_type<C const *[I], X const, Y>
{
    BOOST_STATIC_ASSERT((boost::is_same<C, X>::value));
    using type = Y *[I];
};

template <class C, class X, class Y>
struct replace_type<C (*)(C), X, Y>
{
    BOOST_STATIC_ASSERT((boost::is_same<C, X>::value));
    using type = Y (*)(Y);
};

int main()
{
    std::cout << "test #0: " << std::boolalpha
              << boost::is_same<int *, replace_type<void *, void, int>::type>::value << "\n";
    std::cout << "test #1: " << std::boolalpha
              << boost::is_same<long *[10], replace_type<int const *[10], int const, long>::type>::value << "\n";
    std::cout << "test #2: " << std::boolalpha
              << boost::is_same<long &(*)(long &), replace_type<char &(*)(char &), char &, long &>::type>::value << "\n";
}