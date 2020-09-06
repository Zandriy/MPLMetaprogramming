#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/equal.hpp>

#include <boost/static_assert.hpp>
#include <iostream>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

typedef mpl::vector<char*, long, double*, float*> Seq;
typedef mpl::vector<char, double, float> Res;

typedef mpl::transform_view<
        mpl::filter_view< Seq, boost::is_pointer<_1> >
      , boost::remove_pointer<_1>
    > Result;

int main()
{
    BOOST_STATIC_ASSERT((mpl::equal<Result, Res>::value));
}
