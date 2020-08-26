#include <type_traits>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <list>

namespace my {

template <bool use_swap> struct iter_swap_impl;

template <class ForwardIterator1, class ForwardIterator2>
void iter_swap(ForwardIterator1 i1, ForwardIterator2 i2)
{
    typedef std::iterator_traits<ForwardIterator1> traits1;
    typedef typename traits1::value_type v1;
    typedef typename traits1::reference r1;

    typedef std::iterator_traits<ForwardIterator2> traits2;
    typedef typename traits2::value_type v2;
    typedef typename traits2::reference r2;

    bool const use_swap = std::is_same<v1, v2>::value
        && std::is_reference<r1>::value
        && std::is_reference<r2>::value;

    iter_swap_impl<use_swap>::do_it(i1, i2);
}

template <>
struct iter_swap_impl<true>
{
template <class ForwardIterator1, class ForwardIterator2>
static void do_it(ForwardIterator1 i1, ForwardIterator2 i2)
{
    std::cout << "### True\n";
    std::swap(*i1, *i2);
}
};

template <>
struct iter_swap_impl<false>
{
template <class ForwardIterator1, class ForwardIterator2>
static void do_it(ForwardIterator1 i1, ForwardIterator2 i2)
{
    std::cout << "### False\n";
    typename std::iterator_traits<ForwardIterator1>::value_type tmp = *i1;
    *i1 = *i2;
    *i2 = tmp;
}
};

}

template<class C>
void print(const C& container)
{
    std::cout << typeid(C).name() << "\t";
    std::for_each(container.begin(), container.end(), [](const int n) { std::cout << n << '|'; });
    std::cout << "\n";
}

int main()
{
    std::cout << "#####################\n";
    std::vector<int> v{1,2,3};
    std::list<int> l{4,5,6};
    print(v);
    print(l);
    my::iter_swap(v.begin(), l.begin());
    print(v);
    print(l);
    std::cout << "#####################\n";
    std::vector<bool> v1{true,true,true};
    std::vector<bool> v2{false,false,false};
    print(v1);
    print(v2);
    my::iter_swap(v1.begin(), v2.begin());
    print(v1);
    print(v2);
    std::cout << "#####################\n";
}
