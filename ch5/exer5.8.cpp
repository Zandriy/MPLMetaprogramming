#include <boost/mpl/begin.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/static_assert.hpp>

namespace mpl = boost::mpl;

struct fib_tag
{
};

struct fibonacci_series
{
    using tag = fib_tag;
    using type = fibonacci_series;

    constexpr static long calc(int num, long prev, long next)
    {
        long temp = prev;
        prev = next;
        next = prev ? prev + temp : 1;
        return num ? calc(--num, prev, next) : next;
    }
    constexpr static long calc(int num)
    {
        return num ? calc(--num, 0, 0) : 0;
    }
};

template <class Fib, class Pos>
struct fib_iterator
{
    using category = mpl::random_access_iterator_tag;
    using pos = Pos;
};

namespace boost
{
    namespace mpl
    {
        template <class Fib, class Pos>
        struct next<fib_iterator<Fib, Pos>>
        {
            typedef fib_iterator<
                Fib, typename mpl::next<Pos>::type>
                type;
        };

        template <>
        struct begin_impl<fib_tag>
        {
            template <class Fib>
            struct apply
            {
                typedef fib_iterator<Fib, int_<0>> type;
            };
        };

        template <class Fib, int N>
        struct fib_at
        {
            typedef typename long_<Fib::calc(N)>::type type;
        };

        template <>
        struct at_impl<fib_tag>
        {
            template <class Fib, class N>
            struct apply : fib_at<Fib, N::value>
            {
            };
        };

        template <class Fib, class Pos>
        struct deref<fib_iterator<Fib, Pos>>
            : at<Fib, Pos>
        {
        };
    } // namespace mpl
} // namespace boost

typedef mpl::advance_c<
    mpl::begin<fibonacci_series>::type, 6>::type i;
BOOST_STATIC_ASSERT(mpl::deref<i>::type::value == 8);

typedef mpl::advance_c<i, 4>::type j;
BOOST_STATIC_ASSERT(mpl::deref<j>::type::value == 55);

int main()
{
}