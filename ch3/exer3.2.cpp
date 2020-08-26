#include <boost/static_assert.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>


int main()
{
    namespace mpl = boost::mpl;
    using namespace mpl::placeholders;

    typedef boost::mpl::vector_c<int,1,2,3> in;
    typedef boost::mpl::vector_c<int,0,2,6> add;
    typedef boost::mpl::vector_c<int,1,4,9> result;
    BOOST_STATIC_ASSERT((
                boost::mpl::equal<boost::mpl::transform<in, add, boost::mpl::plus<_1, _2>>::type, result>::type::value
                ));
}
