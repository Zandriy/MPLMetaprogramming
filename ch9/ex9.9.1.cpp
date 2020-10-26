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

int main()
{
    std::vector<int> v{1,2,3,4,5};
    std::cout << "sum is " << sum(v.begin(), v.end()) << "\n";

    // Compile Error:
    // std::vector<const char*> s{"1","2","3","4","5"};
    // std::cout << "sum is " << sum(s.begin(), s.end()) << "\n";
}