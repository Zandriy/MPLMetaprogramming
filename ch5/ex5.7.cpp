#include <boost/mpl/list.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/size.hpp>
#include <boost/static_assert.hpp>

namespace mpl = boost::mpl;

using types_list = mpl::list<int, bool, char, long>;
using types_insert = mpl::list<void, void*, const bool>;
using types_result = mpl::list<int, void, void*, const bool, bool, char, long>;

using numbers = mpl::vector_c<int,0,1,2,8,9>;
using numbers_result = mpl::vector_c<int,0,1,2,3,4,5,6,7,8,9>;

BOOST_STATIC_ASSERT((!mpl::empty<types_list>::value));
BOOST_STATIC_ASSERT((mpl::empty<mpl::clear<types_list>::type>::value));

using types_pos = mpl::find<types_list, bool>::type;
BOOST_STATIC_ASSERT((mpl::equal<mpl::insert_range<types_list,types_pos,types_insert>::type, types_result>::value));

using numbers_pos = mpl::find<numbers,mpl::integral_c<int,8>>::type;
BOOST_STATIC_ASSERT((mpl::equal<mpl::insert_range<numbers,numbers_pos,mpl::range_c<int,3,8>>::type, numbers_result>::value));

BOOST_STATIC_ASSERT((mpl::size<types_list>::value == 4));
BOOST_STATIC_ASSERT((mpl::size<numbers_result>::value == 10));

int main()
{
}