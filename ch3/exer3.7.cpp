#include <boost/mpl/lambda.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include <vector>
#include <boost/static_assert.hpp>
#include <type_traits>

#include <iostream>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

typedef mpl::lambda<mpl::lambda<_1>>::type t1;
typedef mpl::apply<_1, mpl::plus<_1, _2>>::type t2;
typedef mpl::apply<_1, std::vector<int>>::type t3;
typedef mpl::apply<_1, std::vector<_1>>::type t4;
typedef mpl::apply<mpl::lambda<_1>, std::vector<int>>::type t5;
typedef mpl::apply<mpl::lambda<_1>, std::vector<_1>>::type t6;
typedef mpl::apply<mpl::lambda<_1>, mpl::plus<_1, _2>>::type t7;
typedef mpl::apply<_1, mpl::lambda<mpl::plus<_1, _2>>>::type t8;

int main()
{
   BOOST_STATIC_ASSERT((std::is_same<t1::apply<int>::type, int>::value));
   BOOST_STATIC_ASSERT((std::is_same<t1::apply<std::add_const<int>::type>::type, const int>::value));

   BOOST_STATIC_ASSERT((std::is_same<t2, mpl::plus<mpl::arg<1>, mpl::arg<2>>>::value));
   BOOST_STATIC_ASSERT((mpl::lambda<t2>::type::apply< mpl::int_<21>, mpl::int_<21>>::type::value == 42));

   BOOST_STATIC_ASSERT((std::is_same<t3, std::vector<int>>::value));
   BOOST_STATIC_ASSERT((std::is_same<t4, std::vector<mpl::arg<1>>>::value));
   BOOST_STATIC_ASSERT((std::is_same<t3, mpl::lambda<t4>::type::apply<int>::type>::value));

   BOOST_STATIC_ASSERT((std::is_same<t5, std::vector<int>>::value));
   BOOST_STATIC_ASSERT((std::is_same<t6::apply<int>::type, std::vector<int>>::value));
   BOOST_STATIC_ASSERT((std::is_same<t5, t6::apply<int>::type>::value));

   BOOST_STATIC_ASSERT((t7::apply<mpl::int_<21>, mpl::int_<21>>::type::value == 42));
   BOOST_STATIC_ASSERT((t8::type::apply<mpl::int_<21>, mpl::int_<21>>::type::value == 42));
   BOOST_STATIC_ASSERT((std::is_same<t7, t8::type>::value));
   
  // t8::type::apply<
 }