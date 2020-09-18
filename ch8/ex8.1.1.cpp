#include <boost/mpl/int.hpp>


struct nil {};

template <class H, class T = nil>
struct node
{
    typedef H head; typedef T tail;
};

template <class S>
struct total_size
{
    typedef typename total_size<
        typename S::tail
    >::type tail_size;


    typedef boost::mpl::int_<
        sizeof(S::head)
        + tail_size::value
    > type;
};
typedef total_size<
    node<long, node<int, node<char>>>
>::type x;

int main()
{
}
