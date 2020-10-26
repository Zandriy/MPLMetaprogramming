#include <boost/mpl/fold.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/placeholders.hpp>
#include <iostream>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

#include <algorithm>
#include <cmath>

template <class R, class F, F f, class G, G g>
struct compose_fg2
{
    typedef R result_type;
    template <class T>
    R operator()(T const &x) const
    {
        return f(g(x));
    }
};

float input[5] = {0.0, 0.1, 0.2, 0.3, 0.4};
float output[5];

float log2(float x) { return std::log(x) / std::log(2.0f); }

float sin_squared(float x) { return std::sin(std::sin(x)); }

typedef float (*floatfun)(float);

int main()
{
    std::transform(input, input + 5, output, compose_fg2<float, floatfun, sin_squared, floatfun, log2>());

    for (auto o : output)
    {
        std::cout << " | " << o;
    }

    std::cout << "\n";
}