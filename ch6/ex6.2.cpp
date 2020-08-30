#include <boost/mpl/deref.hpp>
#include <boost/mpl/max_element.hpp>
#include <boost/mpl/replace.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/static_assert.hpp>
#include <type_traits>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

template <class Seq>
struct biggest_float_as_double
: mpl::deref<
    typename mpl::max_element<
        typename mpl::replace<
           Seq
           , float
           , double
        >::type
        , mpl::less<mpl::sizeof_<_1>, mpl::sizeof_<_2> >
    >::type
>   {};

typedef boost::mpl::vector<float,float,float> FloatVec;
typedef boost::mpl::vector<float,long double,int> MixVec;

BOOST_STATIC_ASSERT((std::is_same<biggest_float_as_double<FloatVec>::type, double>::type::value));
BOOST_STATIC_ASSERT((std::is_same<biggest_float_as_double<MixVec>::type, long double>::type::value));

int main()
{
}
