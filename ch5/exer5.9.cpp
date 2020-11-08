#include <boost/mpl/begin.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/static_assert.hpp>

namespace mpl = boost::mpl;

constexpr static long fibonacci(int num, long prev, long next)
{
    long temp = prev;
    prev = next;
    next = prev ? prev + temp : 1;
    return num ? fibonacci(--num, prev, next) : next;
}

constexpr static long fibonacci(int num)
{
    return num ? fibonacci(--num, 0, 0) : 0;
}

template <unsigned N, class VECTOR>
struct fibonacci_series_T : fibonacci_series_T<N-1, typename mpl::push_front<VECTOR, mpl::integral_c<long, fibonacci(N-1)>>::type>
{
};

template <class VECTOR>
struct fibonacci_series_T<0, VECTOR>
{
    using type = VECTOR;
};

template <unsigned N>
using fibonacci_series = typename fibonacci_series_T<N, mpl::vector<>>::type;

typedef fibonacci_series<8> seq;
BOOST_STATIC_ASSERT(mpl::size<seq>::value == 8);
BOOST_STATIC_ASSERT(mpl::back<seq>::type::value == 13);

typedef mpl::advance_c<mpl::begin<seq>::type, 0>::type i;
BOOST_STATIC_ASSERT(mpl::deref<i>::type::value == 0);

typedef mpl::advance_c<i, 1>::type j;
BOOST_STATIC_ASSERT(mpl::deref<j>::type::value == 1);

typedef mpl::advance_c<j, 5>::type k;
BOOST_STATIC_ASSERT(mpl::deref<k>::type::value == 8);

BOOST_STATIC_ASSERT((mpl::equal<seq, mpl::vector_c<long, 0, 1, 1, 2, 3, 5, 8, 13>>::value));

typedef fibonacci_series<11> seq11;
BOOST_STATIC_ASSERT((mpl::equal<seq11, mpl::vector_c<long, 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55>>::value));

int main()
{
}