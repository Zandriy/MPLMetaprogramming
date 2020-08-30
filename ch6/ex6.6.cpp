#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/list_c.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/shift_right.hpp>
#include <boost/mpl/unique.hpp>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

// starting sequences
typedef mpl::vector_c<int, 1, 2, 3> v123;
typedef mpl::list_c<int, 1, 2, 3>   l123;

// transformation
typedef mpl::plus<_1,mpl::int_<5> > add5;

// using the default inserters
typedef mpl::transform<v123, add5>::type          v678;
typedef mpl::transform<l123, add5>::type          l678;
typedef mpl::reverse_transform<v123, add5>::type  v876;
typedef mpl::reverse_transform<l123, add5>::type  l876;

// this inserter is equivalent to the default
typedef mpl::transform<v123, add5, mpl::back_inserter<mpl::vector<>>
>::type                                            v678_vv;

// also equivalent to the default
typedef mpl::reverse_transform<l123, add5, mpl::front_inserter<mpl::list<>>
>::type                                            l678_ll;

// properties of input sequence don't affect the result
typedef mpl::reverse_transform<v123, add5, mpl::front_inserter<mpl::list<>>
>::type                                            l678_vl;

typedef mpl::equal_to<mpl::shift_right<_1, mpl::int_<1>>
    , mpl::shift_right<_2, mpl::int_<1>>
> same_except_last_bit;                    // predicate

typedef mpl::vector_c<int, 0,1,2,3,4,5> v;

typedef mpl::unique<v, same_except_last_bit
>::type                      v024;          // 0, 2, 4

typedef mpl::reverse_unique<v, same_except_last_bit
>::type                      v531;          // 5, 3, 1

int main()
{
}
