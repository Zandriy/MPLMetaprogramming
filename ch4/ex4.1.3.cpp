#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_stateless.hpp> 
#include <type_traits>
#include <vector>
#include <string>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

template <class T>
struct param_type
: mpl::eval_if<
    mpl::or_<std::is_scalar<T>, boost::is_stateless<T>, std::is_reference<T>>
    , mpl::identity<T>
    , boost::add_reference<T const>>
{};

typedef mpl::vector<int, long, std::string> argument_types;
typedef mpl::vector<int, long, const std::string&> result_types;

typedef mpl::transform <argument_types
   , mpl::if_<
       mpl::or_<std::is_scalar<_1>, std::is_reference<_1>>
      , mpl::identity<_1>
      , boost::add_reference<std::add_const<_1>>
   >
>::type param_types;

struct StateLess {
};

int main()
{
    param_type<int>::type i = 10;
    param_type<std::vector<int>>::type v = {10, 20};
    param_type<StateLess>::type s = StateLess{};

    BOOST_STATIC_ASSERT(( boost::is_same< mpl::at_c<argument_types,0>::type, int>::value ));
    BOOST_STATIC_ASSERT(( boost::is_same< mpl::at_c<argument_types,1>::type, long>::value ));
    BOOST_STATIC_ASSERT(( boost::is_same< mpl::at_c<argument_types,2>::type, std::string>::value ));

    BOOST_STATIC_ASSERT((mpl::equal<param_types, result_types>::type::value));
}
