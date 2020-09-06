#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/lower_bound.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/plus.hpp>

#include <iostream>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

typedef mpl::vector<char&, long, double, int volatile&> V1;
typedef mpl::vector<char, long&, double volatile&, float> V2;

template<typename seq>
struct found :
    mpl::contains<
        mpl::transform_view<
            seq
          , boost::remove_cv< boost::remove_reference<_>>
        >
      , int
    >::type
{};

/////////////////////////////////////////////////////////////

template<unsigned int Min, unsigned int Max, unsigned int N>
struct number_iter
: mpl::lower_bound<
      mpl::transform_view<
          mpl::range_c<int,Min,Max>
        , mpl::plus<_1,_1,_1>
      >
    , mpl::int_<N>
  >::type::base
{};

/////////////////////////////////////////////////////////////

typedef mpl::vector_c<int, 4, 200, 3> seq1;
typedef mpl::vector_c<int, 400, 2, 300> seq2;

typedef mpl::sort<
    mpl::joint_view<seq1,seq2>
    , mpl::less<_1,_2>
    , mpl::back_inserter< mpl::vector<> >
>::type result;

/////////////////////////////////////////////////////////////

int main()
{
    std::cout << "### found " << (found<V1>::value ? "YES" : "NO") << "\n";
    std::cout << "### found " << (found<V2>::value ? "YES" : "NO") << "\n";

    /////////////////////////////////////////////////////////////

    std::cout << "### number_iter " << mpl::deref<number_iter<0, 512, 16>>::type() << "\n";

    /////////////////////////////////////////////////////////////

    std::cout << "### sort " << mpl::at<result, mpl::int_<0>>::type() << "\n";
    std::cout << "### sort " << mpl::at<result, mpl::int_<1>>::type() << "\n";
    std::cout << "### sort " << mpl::at<result, mpl::int_<2>>::type() << "\n";
}
