#include <boost/static_assert.hpp>
#include <iostream>

template <unsigned long N>
struct binary   {
    BOOST_STATIC_ASSERT((N%10 <= 1));
    static unsigned const value = binary<N/10>::value * 2 + N%10;
};

template <>
struct binary<0>
{
    static unsigned const value = 0;
};

unsigned binary_for(unsigned long N)
{
    for (unsigned bit = 0x1, result = 0; N; N /= 10, bit <<= 1)
    {
        if (N%10)
            result += bit;
        if (!(N/10))
            return result;
    }
    return 0;
}

int main()
{
    std::cout << binary<101010>::value << std::endl;
    std::cout << binary<424242>::value << std::endl;
    std::cout << binary_for(101010) << std::endl;
    return 0;
}
