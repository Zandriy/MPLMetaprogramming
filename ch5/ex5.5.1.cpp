#include <boost/mpl/vector.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/advance.hpp>
#include <type_traits>
#include <boost/static_assert.hpp>

namespace mpl = boost::mpl;

using types = mpl::vector<char,short,int,long,float,double>;

using front = mpl::front<types>::type;
using front_equivalent = mpl::deref<mpl::begin<types>::type>::type;
BOOST_STATIC_ASSERT((std::is_same<front,front_equivalent>::value));

using back = mpl::back<types>::type;
using back_equivalent = mpl::deref<mpl::prior<mpl::end<types>::type>::type>::type;
BOOST_STATIC_ASSERT((std::is_same<back,back_equivalent>::value));

using at = mpl::at<types,mpl::int_<3>>::type;
using at_equivalent = mpl::deref<mpl::advance<mpl::begin<types>::type, mpl::int_<3>>::type>::type;
BOOST_STATIC_ASSERT((std::is_same<at,at_equivalent>::value));

int main()
{
}