#include <boost/mpl/int.hpp>

#include <typeinfo>
#include <iostream>
#include <type_traits>

namespace mpl = boost::mpl;

template <bool> // handle integral constant wrappers
struct f_impl
{
    template <class T> 
        static void print(T x) { std::cout << x.value; }
};

template <>     // specialization for non-wrappers
struct f_impl<false>
{
    template <class T>
        static void print(T x) { std::cout << x; }
};

template <class T> 
void f(T x)
{
    f_impl<std::is_class<T>::value>::print(x);
};

int main()
{
    f(mpl::int_<4>{});
    f(2);
}
