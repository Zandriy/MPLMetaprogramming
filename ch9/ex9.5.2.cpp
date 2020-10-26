#include <boost/mpl/fold.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/placeholders.hpp>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

// fine-grained struct element; wraps a T
template <class T>
struct wrap
{
    T value;
};

// one more level of indirection
template <class U, class V>
struct inherit : U, V
{
};

typedef mpl::vector<short[2], long, char *, int> member_types;

struct empty
{
};

mpl::fold<
    member_types, empty, inherit<wrap<_2>, _1>>::type generated;

inherit<wrap<int>, inherit<wrap<char *>, inherit<wrap<long>, inherit<wrap<short[2]>, empty>>>> like_generated;

int main()
{
    long& x = static_cast<wrap<long> &>(generated).value;
    long& x1 = static_cast<wrap<long> &>(like_generated).value;
}