#include <iterator>
#include <vector>
#include <list>
#include <iostream>

/*
// std iterators tags implementation:
namespace std
{
    struct input_iterator_tag { };

    struct forward_iterator_tag
        : input_iterator_tag { };

    struct bidirectional_iterator_tag 
        : forward_iterator_tag { };

    struct random_access_iterator_tag
        : bidirectional_iterator_tag { };
}
*/

namespace mystd
{
    using namespace std;

    template <class InputIterator, class Distance>
        void __advance_impl(
                InputIterator& i
                , Distance n
                , input_iterator_tag)
        {
            while (n--) ++i;
        }

    template <class BidirectionalIterator, class Distance>
        void __advance_impl(
                BidirectionalIterator& i
                , Distance n
                , bidirectional_iterator_tag)

        {
            if (n >= 0)
                while (n--) ++i;
            else
                while (n++) --i;
        }

    template <class RandomAccessIterator, class Distance>
        void __advance_impl(
                RandomAccessIterator& i
                , Distance n
                , random_access_iterator_tag)
        {
            i += n;
        }

    template <class InputIterator, class Distance>
        void advance(InputIterator& i, Distance n)
        {
            typedef typename
                std::iterator_traits<InputIterator>::iterator_category
                category;

            __advance_impl(i, n, category());
        }
}


int main()
{
    std::vector<int> v{10,11,12,13,14,15};

    auto vi = v.begin();
    std::advance(vi, 2);

    std::cout << "std::advance: " << *vi << std::endl;

    vi = v.begin();
    mystd::advance(vi, 2);

    std::cout << "mystd::advance: " << *vi << std::endl;

    std::list<int> l{10,11,12,13,14,15};

    auto li = l.begin();
    std::advance(li, 5);

    std::cout << "std::advance: " << *li << std::endl;

    li = l.begin();
    mystd::advance(li, 5);

    std::cout << "mystd::advance: " << *li << std::endl;
}
