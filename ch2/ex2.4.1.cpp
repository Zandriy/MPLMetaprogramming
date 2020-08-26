#include <iostream>
#include <typeinfo>
#include <vector>
#include <list>

namespace my {
template <class ForwardIterator1, class ForwardIterator2>
void iter_swap(ForwardIterator1 i1, ForwardIterator2 i2)
{
    std::cout << "### Two types\n";
    typename std::iterator_traits<ForwardIterator1>::value_type tmp = *i1;
    *i1 = *i2;
    *i2 = tmp;
}

template <class ForwardIterator>
void iter_swap(ForwardIterator i1, ForwardIterator i2)
{
    std::cout << "### One type\n";
    std::swap(i1,i2);
}
}

template<class C>
void print(const C& container)
{
    std::cout << typeid(C).name() << "\t";
    for (auto& n : container) std::cout << n << " | ";
    std::cout << "\n";
}

template<>
void print(const int& i)
{
    std::cout << typeid(i).name() << "\t" << i << "\n";
}

void f(int* p1, int* p2)
{
   my::iter_swap(p1,p2);
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
    std::cout << "===================\n";
    int i1 = 1;
    int i2 = 2;
    print(i1);
    print(i2);
    f(&i1, &i2);
    print(i1);
    print(i2);
}
