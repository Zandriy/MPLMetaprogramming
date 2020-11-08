#include <boost/mpl/map.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/order.hpp>
#include <boost/mpl/key_type.hpp>
#include <type_traits>
#include <boost/static_assert.hpp>

namespace mpl = boost::mpl;

using types_map = mpl::map<mpl::pair<void, const int>, mpl::pair<int, bool>, mpl::pair<char, char*>, mpl::pair<long, bool>>;

BOOST_STATIC_ASSERT((mpl::has_key<types_map, char>::value));
BOOST_STATIC_ASSERT((std::is_same<mpl::at<types_map, int>::type, mpl::at<types_map, long>::type>::value));
BOOST_STATIC_ASSERT((mpl::order<types_map, void>::value != mpl::order<types_map, char>::value));

int main()
{
}