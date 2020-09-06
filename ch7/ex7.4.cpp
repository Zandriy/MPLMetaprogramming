#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/unpack_args.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/deref.hpp>

#include <iostream>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

template <class IteratorSeq>
struct zip_iterator
{
    typedef IteratorSeq base;
    typedef mpl::forward_iterator_tag category;
    typedef typename mpl::transform<
        IteratorSeq
      , mpl::deref<_1>
    >::type type;
};

namespace boost { namespace mpl
{
    template <class IteratorSeq>
    struct next< ::zip_iterator<IteratorSeq> >
    {
        typedef ::zip_iterator<
            typename transform<
                IteratorSeq
              , next<_1>
            >::type
        > type;
   };
}}

template <class Sequences>
struct zip_view
  : mpl::iterator_range<
        zip_iterator<
            typename mpl::transform<
                Sequences, mpl::begin<_1>
            >::type
        >
      , zip_iterator<
            typename mpl::transform<
                Sequences, mpl::end<_1>
            >::type
        >
    >
{};

typedef mpl::vector_c<int, 1, 2, 3> V1;
typedef mpl::vector_c<int, 10, 20, 30> V2;
typedef mpl::vector_c<int, 100, 200, 300> V3;

typedef mpl::transform_view<
    zip_view<mpl::vector<V1,V2,V3>>
  , mpl::unpack_args<mpl::plus<_,_,_>>
> Res;

int main()
{
    std::cout << "### " << mpl::at<Res, mpl::int_<0>>::type() << "\n";
    std::cout << "### " << mpl::at<Res, mpl::int_<1>>::type() << "\n";
    std::cout << "### " << mpl::at<Res, mpl::int_<2>>::type() << "\n";
}
