#include <boost/type_traits.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/static_assert.hpp>

template <class F, class X>
struct twice : boost::mpl::apply<F, typename boost::mpl::apply<F,X>::type>
{};

struct add_pointer_f
{
    template <class T>
    struct apply : boost::add_pointer<T> {};
};

int main()
{
    namespace mpl = boost::mpl;
    using namespace mpl::placeholders;

    using pointer4 = twice<add_pointer_f, twice<add_pointer_f, int>::type>::type;

    BOOST_STATIC_ASSERT((boost::is_same<int****, pointer4>::value));
}
