#include <boost/type_traits.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/static_assert.hpp>
#include <iostream>

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

    int* x;

    twice<add_pointer_f, int>::type          p = &x;
    twice<boost::add_pointer<_1>, int>::type q = &x;

    BOOST_STATIC_ASSERT((boost::is_same<decltype(p), decltype(q)>::value));

    constexpr int v = mpl::apply<mpl::plus<_1,_2>, mpl::int_<6>, mpl::int_<7>>::type::value;
    std::cout << "value = " << v <<"\n";
}
