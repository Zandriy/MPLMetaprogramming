#include <boost/type_traits.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/static_assert.hpp>

template <class F, class X>
struct twice : boost::mpl::apply<F, typename boost::mpl::apply<F,X>::type>
{};

template <class F, class X>
struct twice_twice : twice<F, typename twice<F,X>::type>
{};

int main()
{
    namespace mpl = boost::mpl;
    using namespace mpl::placeholders;

    typedef twice_twice<boost::add_pointer<_1>, int>::type pointer4;

    BOOST_STATIC_ASSERT((boost::is_same<int****, pointer4>::value));
}
