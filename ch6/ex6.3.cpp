#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/inserter.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/back.hpp>

#include <boost/mpl/equal.hpp>
#include <boost/static_assert.hpp>
#include <iostream>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

typedef mpl::copy<
      mpl::list<float, int, bool>
    , mpl::inserter<mpl::vector<char>, mpl::push_back<_,_>>
>::type result_vec0;

typedef mpl::copy<
      mpl::list<char, float, int, bool>
    , mpl::back_inserter<mpl::vector<>>
>::type result_vec1;

typedef mpl::copy<
      mpl::list<bool, int, float, char>
    , mpl::front_inserter<mpl::vector<>>
>::type result_vec2;

BOOST_STATIC_ASSERT((mpl::equal<result_vec0, result_vec1>::value));
BOOST_STATIC_ASSERT((mpl::equal<result_vec1, result_vec2>::value));

/////////////////////////////////////////////////////////

typedef mpl::vector<
      mpl::vector_c<int, 1, 2, 3>
    , mpl::vector_c<int, 4, 5, 6>
    , mpl::vector_c<int, 7, 8, 9>
> S;

typedef mpl::transform<
      S                   // input sequence
    , mpl::front<_>       // transformation selects front element
    , mpl::inserter<
          mpl::int_<0>    // result starts with 0
        , mpl::plus<_,_>  // and adds each output element
      >
>::type sum; // 0 + 1 + 4 + 7 == 12

typedef mpl::transform<
      S
    , mpl::back<_>
    , mpl::inserter<
          mpl::int_<0>
        , mpl::plus<_,_>
      >
>::type sum_back; // 0 + 3 + 6 + 9 == 18

int main()
{
    std::cout << sum::value << "\n";
    std::cout << sum_back::value << "\n";
}
