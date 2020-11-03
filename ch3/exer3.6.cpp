#include <boost/type_traits.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/lambda.hpp>

namespace mpl = boost::mpl;
using namespace mpl::placeholders;

template <class F, class X>
struct twice : mpl::apply<F, typename mpl::apply<F,X>::type>
{};

using func = typename mpl::lambda<boost::add_pointer<_1>>::type;
using twice_lambda = typename mpl::lambda<func>::type::apply<mpl::lambda<func>::type::apply<int>::type>;

int main()
{
    using tw1 = twice<boost::add_pointer<_1>, int>::type;
    using tw2 = twice_lambda::type;
    
    BOOST_STATIC_ASSERT((boost::is_same<tw1, tw2>::value));
}
