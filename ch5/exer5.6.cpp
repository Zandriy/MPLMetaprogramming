#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/static_assert.hpp>

namespace mpl = boost::mpl;

template <class T> struct dimensions;

typedef dimensions<char [10][5][2]> seq;
namespace boost { namespace mpl {
    template <> struct size<seq> : mpl::int_<3> {};
    template <> struct at_c<seq,0> : mpl::int_<2> {};
    template <> struct at_c<seq,1> : mpl::int_<5> {};
    template <> struct at_c<seq,2> : mpl::int_<10> {};
}}

BOOST_STATIC_ASSERT(( mpl::size<seq>::value == 3 ));
BOOST_STATIC_ASSERT(( mpl::at_c<seq,0>::type::value == 2 ));
BOOST_STATIC_ASSERT(( mpl::at_c<seq,1>::type::value == 5 ));
BOOST_STATIC_ASSERT(( mpl::at_c<seq,2>::type::value == 10 ));

int main()
{
}