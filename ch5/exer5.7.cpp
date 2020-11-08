#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/static_assert.hpp>

namespace mpl = boost::mpl;

template <class T> struct dimensions;

template <class T>
struct dimensions<T&>
{
};

typedef dimensions<char [10][5][2]> seq;
namespace boost { namespace mpl {
    template <> struct size<seq> : mpl::int_<3> {};
    template <> struct at_c<seq,0> : mpl::int_<2> {};
    template <> struct at_c<seq,1> : mpl::int_<5> {};
    template <> struct at_c<seq,2> : mpl::int_<10> {};
    template <> struct push_back<seq, char> : dimensions<char&> {};
    template <> struct pop_back<seq> : dimensions<char&> {};
}}

BOOST_STATIC_ASSERT(( mpl::size<seq>::value == 3 ));
BOOST_STATIC_ASSERT(( mpl::at_c<seq,0>::type::value == 2 ));
BOOST_STATIC_ASSERT(( mpl::at_c<seq,1>::type::value == 5 ));
BOOST_STATIC_ASSERT(( mpl::at_c<seq,2>::type::value == 10 ));
BOOST_STATIC_ASSERT(( mpl::equal<mpl::push_back<seq, char>, seq>::value ));
BOOST_STATIC_ASSERT(( mpl::equal<mpl::pop_back<seq>, seq>::value ));

int main()
{
}