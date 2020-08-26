#include <boost/type_traits.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/static_assert.hpp>

using namespace boost::mpl::placeholders;

template <class UnaryMetaFunctionClass, class Arg>
struct apply1 : UnaryMetaFunctionClass::template apply<Arg>
{};

template <class F, class X>
struct twice_1 : apply1<F, typename apply1<F,X>::type>
{};

template <class X>
struct two_pointers : twice_1<typename boost::mpl::lambda<boost::add_pointer<_1>>::type, X>
{};
// =====================
template <class F, class X>
struct twice : apply1<typename boost::mpl::lambda<F>::type, typename apply1<typename boost::mpl::lambda<F>::type, X>::type>
{};

struct add_pointer_f
{
    template <class T>
    struct apply : boost::add_pointer<T> {};
};
// =====================

int main()
{
    BOOST_STATIC_ASSERT((boost::is_same<twice<typename boost::mpl::lambda<boost::add_pointer<_1>>::type, int>::type, int**>::value));
    BOOST_STATIC_ASSERT((boost::is_same<typename two_pointers<int>::type, int**>::value));

    // =====================

    int* x;

    twice<add_pointer_f, int>::type          p = &x;
    twice<boost::add_pointer<_1>, int>::type q = &x;

    BOOST_STATIC_ASSERT((boost::is_same<decltype(p), decltype(q)>::value));
}
