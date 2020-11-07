#include <boost/mpl/apply.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/multiplies.hpp>
#include <boost/static_assert.hpp>
#include <type_traits>

namespace mpl = boost::mpl;

template <typename N, typename Predicate>
struct next_if
  : mpl::if_<
        typename mpl::apply<Predicate, N>::type
      , typename mpl::next<N>::type, N
  >
{
};

template< typename N1, typename N2 >
struct formula
  : mpl::if_<
        mpl::not_equal_to<N1,N2>
      , typename mpl::if_<
            mpl::greater<N1,N2>
          , typename mpl::minus<N1,N2>::type
          , N1
        >::type
      , typename mpl::plus<
            N1
            , typename mpl::multiplies<N1,
                 mpl::int_<2> >::type
      >::type
  >::type
{};

template <typename N, typename Predicate>
struct next_if_cleaned
  : mpl::if_<
        mpl::apply<Predicate, N>
      , mpl::next<N>, N
  >
{
};

template< typename N1, typename N2 >
struct formula_cleaned
  : mpl::if_<
        mpl::not_equal_to<N1,N2>
      , mpl::if_<
            mpl::greater<N1,N2>
          , typename mpl::minus<N1,N2>::type
          , N1
        >
      , mpl::plus<
            N1
            , typename mpl::multiplies<N1,
                 mpl::int_<2> >::type
      >
  >::type
{};

struct check_integral
{
  template<class T>
  struct apply : std::is_integral<typename T::type>
  {};
};

BOOST_STATIC_ASSERT((std::is_same<next_if<mpl::int_<3>, check_integral>::type, next_if_cleaned<mpl::int_<3>, check_integral>::type>::value));
BOOST_STATIC_ASSERT((next_if<mpl::int_<3>, check_integral>::type::value == next_if_cleaned<mpl::int_<3>, check_integral>::type::value));

BOOST_STATIC_ASSERT((std::is_same<formula<mpl::int_<3>, mpl::int_<2>>::type, formula_cleaned<mpl::int_<3>, mpl::int_<2>>::type>::value));
BOOST_STATIC_ASSERT((formula<mpl::int_<3>, mpl::int_<2>>::type::value == formula_cleaned<mpl::int_<3>, mpl::int_<2>>::type::value));
BOOST_STATIC_ASSERT((std::is_same<formula<mpl::int_<3>, mpl::int_<3>>::type, formula_cleaned<mpl::int_<3>, mpl::int_<3>>::type>::value));
BOOST_STATIC_ASSERT((formula<mpl::int_<3>, mpl::int_<3>>::type::value == formula_cleaned<mpl::int_<3>, mpl::int_<3>>::type::value));

int main()
{
}