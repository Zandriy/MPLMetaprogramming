#include <boost/mpl/bool.hpp>
#include <boost/type_traits.hpp>

#include <iostream>
#include <functional>
#include <algorithm>
#include <cmath>

namespace mpl = boost::mpl;

template <class F, bool F_empty, class G, bool G_empty>
class storage;

template <class F, class G>
class storage<F,false,G,false> // neither F nor G is empty
{
protected:
    storage(F const& f, G const& g)
       : f(f), g(g)
    {}

    F const& get_f() const { return f; }
    G const& get_g() const { return g; }
private:
    F f;
    G g;
};

template <class F, class G>
class storage<F,false,G,true> // G is empty
    : private G
{
protected:
    storage(F const& f, G const& g)
       : G(g), f(f)
    {}

    F const& get_f() const { return f; }
    G const& get_g() const { return *this; }
private:
    F f;
};

template <class F, class G>
class storage<F,true,G,false> // F is empty
    : private F 
{
protected:
    storage(F const& f, G const& g)
       : F(f), g(g)
    {}

    F const& get_f() const { return *this; }
    G const& get_g() const { return g; }
private:
    G g;
};

template <class F, class G>
class storage<F,true,G,true> // F and G are both empty
    : private F, private G
{
protected:
    storage(F const& f, G const& g)
       : F(f), G(g)
    {}

    F const& get_f() const { return *this; }
    G const& get_g() const { return *this; }
};

template <class R, class F, class G>
class compose_fg
  : storage<
      F,boost::is_empty<F>::value
    , G,boost::is_empty<G>::value
  >
{
   typedef
     storage<
        F,boost::is_empty<F>::value
      , G,boost::is_empty<G>::value
     > base;

public:
   compose_fg(F const& f, G const& g)
     : base(f, g)
   {}

   template <class T>
   R operator()(T const& x) const
   {

       F const& f = this->get_f();
       G const& g = this->get_g();
       return f(g(x));
    }
};

template <class R, class F, class G>
compose_fg<R,F,G> compose(F const& f, G const& g)
{
    return compose_fg<R,F,G>(f,g);
}

float input[5] = {0.0, 0.1, 0.2, 0.3, 0.4};
float output1[5];
float output2[5];
float output3[5];

float sin_squared(float x) { return std::sin(std::sin(x)); }
float negate(float x) { return -x; }

int main()
{
    std::transform(
          input, input+5, output1
        , compose<float>(std::negate<float>(), &sin_squared)
    );

    for (auto o : output1) 
    {
        std::cout << " | " << o;
    }

    std::cout << "\n==============================\n";

    std::transform(
          input, input+5, output2
        , compose<float>(&sin_squared, std::negate<float>())
    );

    for (auto o : output2) 
    {
        std::cout << " | " << o;
    }

    std::cout << "\n==============================\n";


    std::transform(
          input, input+5, output3
        , compose<float>(&negate, &sin_squared)
    );

    for (auto o : output3) 
    {
        std::cout << " | " << o;
    }
}
