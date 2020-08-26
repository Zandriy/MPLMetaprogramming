#include <boost/mpl/vector_c.hpp>

namespace mpl = boost::mpl;

typedef mpl::vector_c<int,1,0,0,0,0,0,0> mass;
typedef mpl::vector_c<int,0,1,0,0,0,0,0> length;  // or position
typedef mpl::vector_c<int,0,0,1,0,0,0,0> time;
typedef mpl::vector_c<int,0,0,0,1,0,0,0> charge;
typedef mpl::vector_c<int,0,0,0,0,1,0,0> temperature;
typedef mpl::vector_c<int,0,0,0,0,0,1,0> intensity;
typedef mpl::vector_c<int,0,0,0,0,0,0,1> amount_of_substance;

// base dimension: mass(m), length(l)  time(t)
typedef mpl::vector_c<int,0,1,-1,0,0,0,0> velocity;     // l/t
typedef mpl::vector_c<int,0,1,-2,0,0,0,0> acceleration; // l/(t2)
typedef mpl::vector_c<int,1,1,-1,0,0,0,0> momentum;     // ml/t
typedef mpl::vector_c<int,1,1,-2,0,0,0,0> force;        // ml/(t2)

typedef mpl::vector_c<int,0,0,0,0,0,0,0> scalar;

template <class T, class Dimensions>
struct quantity
{
    explicit quantity(T x)
        : m_value(x)
    {}

    T value() const { return m_value; }
private:
    T m_value;
};

template <class T, class D>
quantity<T,D> operator+(quantity<T,D> x, quantity<T,D> y)
{
    return quantity<T,D>(x.value() + y.value());
}

template <class T, class D>
quantity<T,D> operator-(quantity<T,D> x, quantity<T,D> y)
{
    return quantity<T,D>(x.value() - y.value());
}

int main()
{
    quantity<float,length> l( 1.0f );
    quantity<float,mass> m( 2.0f );

    m = quantity<float,mass>(1);

    quantity<float,length> len1( 1.0f );
    quantity<float,length> len2( 2.0f );

    len1 = len1 + len2;
    len1 = len2 + quantity<float,length>( 3.7f );
}
