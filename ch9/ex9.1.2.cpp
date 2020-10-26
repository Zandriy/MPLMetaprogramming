#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/placeholders.hpp>

#include <typeinfo>
#include <iostream>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

struct visit_type    // generalized visitation function object
{
    template <class Visitor>
        void operator()(Visitor) const
        {
            Visitor::visit();
        }
};

template <class T>   // specific visitor for type printing
struct print_visitor
{
    static void visit()
    {
        std::cout << typeid(T).name() << std::endl;
    }
};

typedef mpl::vector<int&, long&, char*&> s;

int main()
{
    mpl::for_each<s, print_visitor<_1> >(visit_type());
}
