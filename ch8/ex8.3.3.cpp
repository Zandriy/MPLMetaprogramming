#include <boost/mpl/int.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/print.hpp>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;


#if 1

template <class T> struct incomplete;

template <class T>
struct test
{
     incomplete<T> x; // temporary diagnostic
};

test<mpl::int_<1>> t;

#else

template <class T, class U>
struct plus_dbg
{
     typedef typename
	     mpl::print< typename mpl::plus<T,U>::type >::type
     type;
};

typedef mpl::fold<
      mpl::range_c<int,1,6>
    , mpl::int_<0>
    , plus_dbg<_1,_2>
>::type sum;

#endif

int main() {}
