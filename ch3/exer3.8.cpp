#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/placeholders.hpp>
#include <iostream>

namespace sc {

namespace mpl = boost::mpl;
using namespace mpl::placeholders;

typedef mpl::vector_c<int,1,0,0,0,0,0,0> mass;
typedef mpl::vector_c<int,0,1,0,0,0,0,0> length;  // or position (meters)
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


typedef mpl::vector_c<int,1,1> unit_default;
typedef mpl::vector_c<int,254,10000> unit_inch;  //inches=>meters 0.0254
typedef mpl::vector_c<int,3048,10000> unit_feet;  //feet=>meters 0.3048
typedef mpl::vector_c<int,10197162,100000000> unit_newton; // N=>ml/(t2) 0.10197162


template <class T, class Dimensions, class Units = unit_default>
struct quantity
{
    explicit quantity(T x)
        : m_value(x)
    {}
 
    template <class OtherDimensions>
    quantity(quantity<T,OtherDimensions> const& rhs)
        : m_value(rhs.value())
    {
        BOOST_STATIC_ASSERT((mpl::equal<Dimensions, OtherDimensions>::type::value));
    } 

    T value() const { return m_value; }
private:
    T m_value;
};

template <class Units>
float tr_unit()
{
    return (1.0f * mpl::at<Units, mpl::int_<0>>::type::value) / mpl::at<Units, mpl::int_<1>>::type::value;
}

template <class T, class D, class  OtherDimensions, class Unit = unit_default, class OtherUnit = unit_default>
quantity<T,D> operator+(quantity<T,D, Unit> x, quantity<T,OtherDimensions,OtherUnit> y)
{
    BOOST_STATIC_ASSERT((mpl::equal<D, OtherDimensions>::type::value));
    return quantity<T,D>(x.value()*tr_unit<Unit>() + y.value()*tr_unit<OtherUnit>());
}

template <class T, class D, class  OtherDimensions, class Unit = unit_default, class OtherUnit = unit_default>
quantity<T,D> operator-(quantity<T,D> x, quantity<T,OtherDimensions> y)
{
    BOOST_STATIC_ASSERT((mpl::equal<D, OtherDimensions>::type::value));
    return quantity<T,D>(x.value()*tr_unit<Unit>() - y.value()*tr_unit<OtherUnit>());
}

struct plus_f
{
    template <class T1, class T2>
    struct apply
    {
        typedef typename mpl::plus<T1,T2>::type type;
    };
};

template <class T, class D1, class D2, class D1Unit = unit_default, class D2Unit = unit_default>
quantity<T, typename mpl::transform<D1,D2,plus_f>::type> // new dimensions
operator*(quantity<T,D1,D1Unit> x, quantity<T,D2,D2Unit> y)
{
    typedef typename mpl::transform<D1,D2,plus_f>::type dim;
    return quantity<T,dim>( x.value()*tr_unit<D1Unit>() * y.value()*tr_unit<D2Unit>() );
}

template <class T, class D1, class D2, class D1Unit = unit_default, class D2Unit = unit_default>
quantity<T, typename mpl::transform<D1,D2,mpl::minus<_1,_2>>::type>
operator/(quantity<T,D1,D1Unit> x, quantity<T,D2,D2Unit> y)
{
    typedef typename mpl::transform<D1,D2,mpl::minus<_1,_2> >::type dim;
    return quantity<T,dim>( x.value()*tr_unit<D1Unit>() / (y.value()*tr_unit<D2Unit>()) );
}

} // namespace sc

int main()
{
    using namespace sc;
    quantity<float, length> a(1.0f);
    quantity<float, length, unit_inch> b(1.0f);
    quantity<float, length, unit_feet> c(1.0f);

    quantity<float, length> l = a + b + c;
    std::cout << "length sum = " << l.value() << "\n";
    auto p1 = a * b;
    std::cout << "length prod1 = " << p1.value() << "\n";
    auto p2 = a * c;
    std::cout << "length prod1 = " << p2.value() << "\n";

    quantity<float, force> f1(1.0f);
    quantity<float, force, unit_newton> f2(1.0f);

    quantity<float, force> f = f1 + f2;
    std::cout << "force sum = " << f.value() << "\n";
    auto pf = f1 * f2;
    std::cout << "force prod = " << pf.value() << "\n";
}
