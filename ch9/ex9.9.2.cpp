#include <iterator>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <vector>
#include <iostream>

template <class Iterator>
typename boost::enable_if<
    boost::is_arithmetic< // enabling condition
        typename boost::iterator_value<Iterator>::type>,
    typename // return type
    boost::iterator_value<Iterator>::type>::type
sum(Iterator start, Iterator end)
{
    typename boost::iterator_value<Iterator>::type x(0);
    for (; start != end; ++start)
        x += *start;
    return x;
}

// given an Iterator that points to a container, get the
// value_type of that container's iterators.
template <class Iterator>
struct inner_value
    : boost::iterator_value<
          typename boost::iterator_value<Iterator>::type::iterator>
{
};

template <class Iterator>
typename boost::lazy_disable_if<
    boost::is_arithmetic< // disabling condition
        typename boost::iterator_value<Iterator>::type>,
    inner_value<Iterator> // result metafunction
    >::type
sum(Iterator start, Iterator end)
{
    typename inner_value<Iterator>::type x(0);
    for (; start != end; ++start)
        x += sum(start->begin(), start->end());
    return x;
}

int main()
{
    std::vector<std::vector<int>> v{{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5}};
    std::cout << "sum is " << sum(v.begin(), v.end()) << "\n";
}
