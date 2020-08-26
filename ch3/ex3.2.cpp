#include <boost/type_traits.hpp>
#include <boost/static_assert.hpp>

template <class F, class X>
struct twice_0
{
    typedef typename F::template apply<X>::type once;    // f(x)
    typedef typename F::template apply<once>::type type; // f(f(x))
};

// =====================

template <class F, class X>
struct twice_1 : F::template apply<typename F::template apply<X>::type>
{};

// =====================

template <class UnaryMetaFunctionClass, class Arg>
struct apply1 : UnaryMetaFunctionClass::template apply<Arg>
{};

template <class F, class X>
struct twice : apply1<F, typename apply1<F,X>::type>
{};

struct add_pointer_f
{
   template <class T>
   struct apply : boost::add_pointer<T> {};
};

// =====================

int main()
{
    BOOST_STATIC_ASSERT((boost::is_same<twice_0<add_pointer_f, int>::type, int**>::value));
    BOOST_STATIC_ASSERT((boost::is_same<twice_1<add_pointer_f, int>::type, int**>::value));
    BOOST_STATIC_ASSERT((boost::is_same<twice<add_pointer_f, int>::type, int**>::value));
}
