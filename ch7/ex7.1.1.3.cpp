#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/lower_bound.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/int.hpp>

#include <iostream>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

template<class Seq, class MinSize>
    struct padded_size
      : mpl::deref<
            typename mpl::lower_bound<
                typename mpl::transform<
                    Seq, mpl::sizeof_<_>
                 >::type
              , MinSize
            >::type
        >
    {};

typedef mpl::vector<char, short, int, long> Vec;
typedef padded_size<Vec, mpl::int_<3>>::type PosSize;

int main()
{
    std::cout << "### " << PosSize() << "\n";
}
