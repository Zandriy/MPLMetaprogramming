#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/zip_view.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/unpack_args.hpp>

#include <iostream>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

typedef mpl::vector_c<int, 1, 2, 3> V1;
typedef mpl::vector_c<int, 10, 20, 30> V2;
typedef mpl::vector_c<int, 100, 200, 300> V3;

typedef mpl::transform_view<
   mpl::zip_view<mpl::vector<V1,V2,V3>>
 , mpl::plus<
       mpl::at<_, mpl::int_<0>>
     , mpl::at<_, mpl::int_<1>>
     , mpl::at<_, mpl::int_<2>>
   >
> Res0;

typedef mpl::transform_view<
    mpl::zip_view<mpl::vector<V1,V2,V3>>
  , mpl::unpack_args<mpl::plus<_,_,_>>
> Res1;

int main()
{
    std::cout << "### Res0 ###\n";
    std::cout << "### " << mpl::at<Res0, mpl::int_<0>>::type() << "\n";
    std::cout << "### " << mpl::at<Res0, mpl::int_<1>>::type() << "\n";
    std::cout << "### " << mpl::at<Res0, mpl::int_<2>>::type() << "\n";

    std::cout << "### Res1 ###\n";
    std::cout << "### " << mpl::at<Res1, mpl::int_<0>>::type() << "\n";
    std::cout << "### " << mpl::at<Res1, mpl::int_<1>>::type() << "\n";
    std::cout << "### " << mpl::at<Res1, mpl::int_<2>>::type() << "\n";
}
