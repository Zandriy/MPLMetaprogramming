#include <boost/mpl/vector.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/static_assert.hpp>

namespace mpl = boost::mpl;

typedef mpl::vector<char,short,int,long,float,double> types;

// locate the position of long in types
typedef mpl::find<types, long>::type long_pos;
// dereference the iterator
typedef mpl::deref<long_pos>::type x;
// get the next position
typedef mpl::next<long_pos>::type float_pos;

// check that we have the expected dereferenced result
BOOST_STATIC_ASSERT((boost::is_same<x,long>::value));
// check that we have the expected next result
BOOST_STATIC_ASSERT((boost::is_same<mpl::deref<float_pos>::type, float>::value));

int main()
{
}

