#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/lower_bound.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/int.hpp>

#include <iostream>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

template<class Seq, class MinSize>
    struct first_size_larger_than
      : mpl::deref<
          typename mpl::lower_bound<
              mpl::transform_view<Seq, mpl::sizeof_<_> >
            , MinSize
          >::type
        >
    {};

typedef mpl::vector<char, short, int, long> Vec;
typedef first_size_larger_than<Vec, mpl::int_<3>>::type PosSize;

int main()
{
    std::cout << "### " << PosSize() << "\n";
}
