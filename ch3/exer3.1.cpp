#include <boost/static_assert.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>
#include<boost/mpl/placeholders.hpp>

int main()
{
    using namespace boost::mpl::placeholders;

    typedef boost::mpl::vector_c<int,1,2,3> in;
    typedef boost::mpl::vector_c<int,2,3,4> result;
    BOOST_STATIC_ASSERT((
                boost::mpl::equal<boost::mpl::transform<in, boost::mpl::plus<_1, boost::mpl::int_<1>>>::type, result>::type::value
                ));
}
