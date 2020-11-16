#include <boost/mpl/plus.hpp>
#include <boost/mpl/long.hpp>

#include <iostream>

namespace mpl = boost::mpl;

template <unsigned long N>
struct binary : mpl::plus<mpl::long_<binary<N/10>::value * 2>, mpl::long_<N%10>>
{
};

template <>
struct binary<0> : mpl::long_<0>
{
};

int main()
{
    std::cout << binary<101010>::value << std::endl;
    return 0;
}
