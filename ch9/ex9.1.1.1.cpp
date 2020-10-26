#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>

#include <typeinfo>
#include <iostream>

namespace mpl = boost::mpl;

struct print_type
{
    template <class T>
        void operator() (T) const
        {
            std::cout << typeid(T).name() << std::endl;
        }
};

typedef mpl::vector<int, long, char*> s;

int main ()
{
    mpl::for_each<s>(print_type());
}
