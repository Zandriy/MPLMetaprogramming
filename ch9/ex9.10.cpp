#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>

namespace mpl = boost::mpl;

typedef char yes;      // sizeof(yes) == 1
typedef char (&no)[2]; // sizeof(no)  == 2

template <class T>
struct is_class_or_union
{
    // SFINAE eliminates this when the type of arg is invalid
    template <class U>
    static yes tester(int U::*arg);

    // overload resolution prefers anything at all over "..."
    template <class U>
    static no tester(...);

    // see which overload is chosen when U == T
    static bool const value = sizeof(tester<T>(0)) == sizeof(yes);

    typedef mpl::bool_<value> type;
};

struct X
{
};
BOOST_STATIC_ASSERT(is_class_or_union<X>::value);
BOOST_STATIC_ASSERT(!is_class_or_union<int>::value);

int main()
{
}