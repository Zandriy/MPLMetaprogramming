#include <vector>
#include <algorithm>
#include <iostream>
#include <type_traits>

template <class Container, class Value>
typename std::conditional<std::is_const<Container>::value,
   typename Container::const_iterator,
   typename Container::iterator>
::type
container_find(Container& c, Value const& v)
{
    return std::find(c.begin(), c.end(), v);
}

int main()
{
    const std::vector<int> v{23, 346, 632, 33, 42, 6762};

    auto it = container_find(v, 42);

    if (it != v.end())
    {
        std::cout << "Value found\n";
    }
}
