#include <boost/mpl/bool.hpp>
#include <boost/type_traits.hpp>

#include <iostream>
#include <functional>
#include <algorithm>
#include <cmath>

namespace mpl = boost::mpl;

template <class R, class F, class G>
class compose_fg
{
    public:
        compose_fg(F const& f, G const& g)
            : f(f), g(g)
        {}

        template <class T>
            R operator()(T const& x) const
            {
                return f(g(x));
            }

    private:
        F f;
        G g;
};

template <class R, class F, class G>
compose_fg<R,F,G> compose(F const& f, G const& g)
{
    return compose_fg<R,F,G>(f,g);
}

float input[5] = {0.0, 0.1, 0.2, 0.3, 0.4};
float output1[5];
float output2[5];

float sin_squared(float x) { return std::sin(std::sin(x)); }


int main()
{
    std::transform(
            input, input+5, output1
            , compose_fg<float,std::negate<float>,float(*)(float)>(
                std::negate<float>(), &sin_squared
                )
            );

    for (auto o : output1) 
    {
        std::cout << " | " << o;
    }

    std::cout << "\n==============================\n";

    std::transform(
          input, input+5, output2
        , compose<float>(std::negate<float>(), &sin_squared)
    );

    for (auto o : output2) 
    {
        std::cout << " | " << o;
    }


}
