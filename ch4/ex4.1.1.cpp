#include <boost/mpl/if.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <type_traits>
#include <utility>
#include <iterator>
#include <vector>
#include <iostream>

namespace mpl = boost::mpl;

struct fast_swap
{
    template <class ForwardIterator1, class ForwardIterator2>
        static void do_it(ForwardIterator1 i1, ForwardIterator2 i2)
        {
            std::cout << "#### 1\n";
            std::swap(*i1, *i2);
        }
};

struct reliable_swap
{
    template <class ForwardIterator1, class ForwardIterator2>
        static void do_it(ForwardIterator1 i1, ForwardIterator2 i2)
        {
            std::cout << "#### 2\n";
            typename
                std::iterator_traits<ForwardIterator1>::value_type
                tmp = *i1;

            *i1 = *i2;
            *i2 = tmp;
        }
};

////////////////////////////////////////////////////////

template <class T>
struct param_type
: mpl::if_<
    typename std::is_scalar<T>::type
    , T
    , typename boost::add_reference<T const>::type
    >
{};

int main()
{
    int i1 = 10;
    int i2 = 20;
    std::cout << "i1 = " << i1 << " | i2 = " << i2 << "\n";

    constexpr bool use_swap_1 = mpl::true_::value;
    mpl::if_<mpl::bool_<use_swap_1>, fast_swap, reliable_swap>::type::do_it(&i1,&i2);
    std::cout << "i1 = " << i1 << " | i2 = " << i2 << "\n";

    constexpr bool use_swap_2 = mpl::false_::value;
    mpl::if_<mpl::bool_<use_swap_2>, fast_swap, reliable_swap>::type::do_it(&i1,&i2);
    std::cout << "i1 = " << i1 << " | i2 = " << i2 << "\n";

    ////////////////////////////////////////////////////////

    param_type<int>::type i = 10;
    param_type<std::vector<int>>::type v = {10, 20};
}
