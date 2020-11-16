#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/min_element.hpp>

#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>

namespace mpl = boost::mpl;
using namespace mpl::placeholders;

template<class S>
using smallest = mpl::deref<typename mpl::min_element<mpl::transform_view<S, mpl::sizeof_<_1>>>::type::base>;

BOOST_STATIC_ASSERT((
    boost::is_same<
        smallest<mpl::vector<int[2], char, double &>>::type, char>::value));

int main()
{
}