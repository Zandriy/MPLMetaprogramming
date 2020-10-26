#include <boost/mpl/transform.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/placeholders.hpp>

#include <typeinfo>
#include <iostream>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

template <class T> struct wrap {};

struct print_type
{
    template <class T>
        void operator()(wrap<T>) const   // deduce T
        {
            std::cout << typeid(T).name() << std::endl;
        }
};

// contains references
typedef mpl::vector<int&, long&, char*&> s;

int main ()
{
    mpl::for_each<
        mpl::transform<s, wrap<_1> >::type
    >(print_type());
    // or
    mpl::for_each<s, wrap<_1> >(print_type());
}
