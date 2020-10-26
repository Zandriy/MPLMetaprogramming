#include <boost/mpl/inherit.hpp>
#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/vector.hpp>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

// fine-grained struct element
template <class T>
struct wrap
{
    T value;
};

typedef mpl::vector<short[2], long, char *, int> member_types;

mpl::inherit_linearly<
    member_types, mpl::inherit<wrap<_2>, _1>>::type generated;

int main()
{
    long &x = static_cast<wrap<long> &>(generated).value;
}