#include <boost/mpl/vector.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector_c.hpp>

namespace mpl = boost::mpl;

/////////////////////////////////////
typedef boost::mpl::vector<signed char, short, int, long> signed_types;
/////////////////////////////////////
static int const five = mpl::int_<5>::value;
/////////////////////////////////////
typedef mpl::vector<mpl::int_<1>, mpl::int_<0>, mpl::int_<0>, mpl::int_<0>
, mpl::int_<0>, mpl::int_<0>, mpl::int_<0>> Mass;

typedef mpl::vector<mpl::int_<0>, mpl::int_<1>, mpl::int_<0>, mpl::int_<0>
, mpl::int_<0>, mpl::int_<0>, mpl::int_<0>> Length;
/////////////////////////////////////

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

int main()
{
}
