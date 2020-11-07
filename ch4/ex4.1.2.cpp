#include <boost/mpl/if.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/mpl/identity.hpp>
#include <type_traits>
#include <boost/static_assert.hpp>
#include <vector>

namespace mpl = boost::mpl;

#define USE 0

#if USE==1
template <class T>
struct param_type
: mpl::if_<
    typename std::is_scalar<T>::type
    , T
    , typename boost::add_reference<T const>::type
    >
{};
#elif USE==2 
template <class T>
struct param_type
: mpl::if_<  // forwarding to selected transformation
    typename std::is_scalar<T>::type
    , mpl::identity<T>
    , boost::add_reference<T const>
    >::type // ::type is outside
{};
#elif USE==3 
template <class C, class TrueMetafunc, class FalseMetafunc>
struct eval_if
: mpl::if_<C,TrueMetafunc,FalseMetafunc>::type
{};

template <class T>
struct param_type
: eval_if<
    typename std::is_scalar<T>::type
    , mpl::identity<T>
    , boost::add_reference<T const>>     // no ::type here
{};
#elif USE==4 
#include <boost/mpl/eval_if.hpp>

template <class T>
struct param_type
: mpl::eval_if<
    typename std::is_scalar<T>::type
    , mpl::identity<T>
    , boost::add_reference<T const>>
{};
#else
#include <boost/mpl/eval_if.hpp>

template <class T>
struct param_type
: mpl::eval_if<
    std::is_scalar<T> // no typename and ::type
    , mpl::identity<T>
    , boost::add_reference<T const>>
{};
#endif

int main()
{
    param_type<int>::type i = 10;
    param_type<std::vector<int>>::type v = {10, 20};
    BOOST_STATIC_ASSERT((std::is_same<int, decltype(i)>::value));
    BOOST_STATIC_ASSERT((std::is_same<const std::vector<int>&, decltype(v)>::value));
}
