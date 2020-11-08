#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/static_assert.hpp>

namespace mpl = boost::mpl;

template <class V_IN, class V_RES, int AT, bool DOUBLE>
struct double_first_half_impl :  double_first_half_impl<V_IN,
    typename mpl::push_front<V_RES, mpl::integral_c<int, mpl::at_c<V_IN, AT-1>::type::value*(DOUBLE?2:1)>>::type,
    AT-1, ((AT-1) <= mpl::size<V_IN>::value / 2)>
{
};

template <class V_IN, class V_RES>
struct double_first_half_impl<V_IN, V_RES, 0, true>
{
    using type = typename V_RES::type;
};

template <class V>
struct double_first_half : double_first_half_impl<V, mpl::vector_c<int>, mpl::size<V>::type::value, false>
{
};

BOOST_STATIC_ASSERT((mpl::equal<
                     double_first_half<mpl::vector_c<int, 1, 2, 3, 4>>::type, mpl::vector_c<int, 2, 4, 3, 4>>::value));

int main()
{
}
