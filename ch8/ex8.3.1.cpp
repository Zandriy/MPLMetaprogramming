#include <boost/mpl/int.hpp>
#include <boost/static_assert.hpp>

namespace mpl = boost::mpl;

template <class N>
struct test
{
     BOOST_STATIC_ASSERT(N::value >= 0); // for nonnegative N
     static constexpr int value{ N::value };
};

int main()
{
   const int t = test<mpl::int_<-6> >::value;
}
