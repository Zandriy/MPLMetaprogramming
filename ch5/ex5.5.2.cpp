#include <boost/mpl/list.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/static_assert.hpp>

namespace mpl = boost::mpl;

using types_list = mpl::list<int, bool, char, long>;
using insert_result = mpl::list<int, short, bool, char, long>;
using erase_one_result = mpl::list<int, char, long>;
using erase_mult_result = mpl::list<int, long>;

using pos = mpl::find<types_list, bool>::type;
using pos_to = mpl::find<types_list, long>::type;

BOOST_STATIC_ASSERT((mpl::equal<mpl::insert<types_list, pos, short>::type, insert_result::type>::value));
BOOST_STATIC_ASSERT((mpl::equal<mpl::erase<types_list, pos>::type, erase_one_result::type>::value));
BOOST_STATIC_ASSERT((mpl::equal<mpl::erase<types_list, pos, pos_to>::type, erase_mult_result::type>::value));

BOOST_STATIC_ASSERT((mpl::equal<mpl::clear<types_list>::type, mpl::end<types_list>::type>::value));
BOOST_STATIC_ASSERT((mpl::empty<mpl::clear<types_list>::type>::value));

int main()
{
}