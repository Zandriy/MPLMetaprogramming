#include <boost/mpl/vector.hpp>
#include <boost/mpl/find.hpp>
#include <boost/static_assert.hpp>

namespace mpl = boost::mpl;

typedef mpl::vector<char,short,int,long,float,double> types;

// locate the position of long in types
typedef mpl::find<types, long>::type long_pos;
// get finish position 
typedef mpl::end<types>::type finish;

// assert that long was found in the sequence
BOOST_STATIC_ASSERT((!boost::is_same<long_pos, finish>::value));

int main()
{
}
