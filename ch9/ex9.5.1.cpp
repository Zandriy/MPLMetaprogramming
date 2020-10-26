#include <boost/mpl/fold.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/placeholders.hpp>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

// fine-grained struct element; stores a T and inherits More
template <class T, class More>
struct store : More
{
    T value;
};

typedef mpl::vector<short[2], long, char *, int> member_types;

struct empty
{
};

mpl::fold<
    member_types, empty, store<_2, _1>>::type generated;

store<int, store<char *, store<long, store<short[2], empty>>>> like_generated;

template <class T, class U>
store<T, U> const &get(store<T, U> const &e)
{ return e; }

int main()
{
    long &x = static_cast<store<long, store<short[2], empty>> &>(generated).value;
    long &x1 = static_cast<store<long, store<short[2], empty>> &>(like_generated).value;

    char* s = get<char*>(generated).value;
    long l = get<long>(like_generated).value;
}