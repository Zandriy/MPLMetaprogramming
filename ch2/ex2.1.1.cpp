#include <iostream>
#include <typeinfo>
#include <vector>
#include <list>

namespace my {
template <class ForwardIterator1, class ForwardIterator2>
void iter_swap(ForwardIterator1 i1, ForwardIterator2 i2)
{
    typename ForwardIterator1::value_type tmp = *i1;
    *i1 = *i2;
    *i2 = tmp;
}
}

template<class C>
void print(const C& container)
{
    std::cout << typeid(C).name() << "\t";
    for (auto& n : container) std::cout << n << " | ";
    std::cout << "\n";
}

int main()
{
    std::vector<int> v{1,2,3};
    std::list<int> l{4,5,6};

    print(v);
    print(l);

    my::iter_swap(v.begin(), l.begin());

    print(v);
    print(l);
}
