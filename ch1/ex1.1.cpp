#include <boost/mpl/long.hpp>
#include <boost/mpl/alias.hpp>
#include <iostream>

template< long n > struct binary
    : mpl::long_< ( binary< n / 10 >::value << 1 ) + n % 10 >
{
};

template<> struct binary<0>
    : mpl::long_<0>
{
};

int main()
{
    std::cout << binary<101010>::value << std::endl;
    return 0;
}
