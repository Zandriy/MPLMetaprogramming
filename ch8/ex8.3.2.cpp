#include <boost/mpl/int.hpp>
#include <boost/mpl/greater_equal.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>
#include <type_traits>

namespace mpl = boost::mpl;

template <int n>
struct NEGATIVE_NUMBER
  : mpl::greater_equal<mpl::int_<n>, mpl::int_<0> >
{};

template <int n>
struct requires_NONNEGATIVE_argument
  : mpl::greater_equal<mpl::int_<n>, mpl::int_<0> >
{};

template <class N>
struct test
{
     BOOST_MPL_ASSERT_MSG(std::is_function<N>::value, NOT_an_INTEGRAL_CONSTANT_WRAPPER, (types<N>));
//     BOOST_MPL_ASSERT_MSG(N::value >= 0, not_ALLOWED_NEGATIVE_NUMBER, (N));
//     BOOST_MPL_ASSERT((requires_NONNEGATIVE_argument<N::value>));
//     BOOST_MPL_ASSERT((NEGATIVE_NUMBER<N::value>));
//     BOOST_MPL_ASSERT_RELATION(N::value, >=, 0);
//     BOOST_MPL_ASSERT_NOT((mpl::less<N,mpl::int_<0> >));
//     BOOST_MPL_ASSERT((std::is_void<typename N::value_type>));
//     BOOST_MPL_ASSERT((mpl::greater_equal<N, mpl::int_<0>>));
     static constexpr int value{ N::value };
};

int main()
{
   typedef mpl::transform<mpl::vector<void>, test<mpl::_>> type;
   const int t = test<mpl::int_<-6> >::value;
}
