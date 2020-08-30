#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/push_back.hpp>

namespace boost { namespace mpl {

    struct none {}; // tag type to denote no element
    struct tiny_tag {}; // tag type for tag dispatching technique to allow for easy customization

    template <class T0 = none, class T1 = none, class T2 = none>
        struct tiny
        {
            typedef tiny_tag tag;
            typedef tiny type;

            typedef T0 t0;
            typedef T1 t1;
            typedef T2 t2;
            //    ...
        };

    template <class Tiny, class Pos>
        struct tiny_iterator
        {
            typedef mpl::random_access_iterator_tag category;
        };

    template <class Tiny, class Pos>
        struct next<tiny_iterator<Tiny,Pos>>
        {
            typedef tiny_iterator<
                Tiny
                , typename mpl::next<Pos>::type
                > type;
        };

    template <class Tiny, class Pos>
        struct prior<tiny_iterator<Tiny,Pos>>
        {
            typedef tiny_iterator<
                Tiny
                , typename mpl::prior<Pos>::type
                > type;
        };

    template <class Tiny, int N> struct tiny_at;

    template <class Tiny>
        struct tiny_at<Tiny,0>
        {
            typedef typename Tiny::t0 type;
        };

    template <class Tiny>
        struct tiny_at<Tiny,1>
        {
            typedef typename Tiny::t1 type;
        };

    template <class Tiny>
        struct tiny_at<Tiny,2>
        {
            typedef typename Tiny::t2 type;
        };
    /*
    // mpl::at as reference
    template<class Sequence, class N>
    struct at
    : at_impl<typename Sequence::tag>
    ::template apply<Sequence,N> 
    {
    };

    // possible partially specializing of mpl::at
    template <class T0, class T1, class T2, class Pos>
    struct at<tiny<T0,T1,T2>,Pos>
    : tiny_at<tiny<T0,T1,T2>,Pos::value>
    {
    };
    */
    // better solution to make mpl::at working by tag dispatching technique
    template <>
        struct at_impl<tiny_tag>
        {
            template <class Tiny, class N>
                struct apply : tiny_at<Tiny, N::value>
            {};
        };

    template <class Tiny, class Pos>
        struct deref< tiny_iterator<Tiny,Pos> >
        : at<Tiny,Pos>
        {
        };

    template <class Tiny, class Pos, class N>
        struct advance<tiny_iterator<Tiny,Pos>,N>
        {
            typedef tiny_iterator<
                Tiny
                , typename mpl::plus<Pos,N>::type
                > type;
        };

    template <class Tiny, class Pos1, class Pos2>
        struct distance<
        tiny_iterator<Tiny,Pos1>
        , tiny_iterator<Tiny,Pos2>
        >
        : mpl::minus<Pos2,Pos1>
        {};

    template <>
        struct begin_impl<tiny_tag>
        {
            template <class Tiny>
                struct apply
                {
                    typedef tiny_iterator<Tiny,int_<0> > type;
                };
        };

    /* O(N) end_impl
    template <>
        struct end_impl<tiny_tag>
        {
            template <class Tiny>
                struct apply
                : eval_if<
                  is_same<none,typename Tiny::t0>
                  , int_<0>
                  , eval_if<
                  is_same<none,typename Tiny::t1>
                  , int_<1>
                  , eval_if<
                  is_same<none,typename Tiny::t2>
                  , int_<2>
                  , int_<3>
                  >
                  >
                  >
            {};
        };
   */

    // O(1) end_impl
    template <class T0, class T1, class T2>
        struct tiny_size
        : mpl::int_<3> {};

    template <class T0, class T1>
        struct tiny_size<T0,T1,none>
        : mpl::int_<2> {};

    template <class T0>
        struct tiny_size<T0,none,none>
        : mpl::int_<1> {};

    template <>
        struct tiny_size<none,none,none>
        : mpl::int_<0> {};

    template <>
        struct end_impl<tiny_tag>
        {
            template <class Tiny>
                struct apply
                {
                    typedef tiny_iterator<
                        Tiny
                        , typename tiny_size<
                        typename Tiny::t0
                        , typename Tiny::t1
                        , typename Tiny::t2
                        >::type
                        >
                        type;
                };
        };

    template <>
        struct size_impl<tiny_tag>
        {
            template <class Tiny>
                struct apply
                : tiny_size<
                  typename Tiny::t0
                  , typename Tiny::t1
                  , typename Tiny::t2
                  >
            {};
        };

    template <>
        struct clear_impl<tiny_tag>
        {
            template <class Tiny>
                struct apply : tiny<>
            {};
        };

    template <>
        struct push_front_impl<tiny_tag>
        {
            template <class Tiny, class T>
                struct apply
                : tiny<T, typename Tiny::t0, typename Tiny::t1>
                {};
        };

    template <class Tiny, class T, int N>
        struct tiny_push_back;

    template <class Tiny, class T>
        struct tiny_push_back<Tiny,T,0>
        : tiny<T,none,none>
        {};

    template <class Tiny, class T>
        struct tiny_push_back<Tiny,T,1>
        : tiny<typename Tiny::t0,T,none>
        {};

    template <class Tiny, class T>
        struct tiny_push_back<Tiny,T,2>
        : tiny<typename Tiny::t0,typename Tiny::t1,T>
        {};

    template <>
        struct push_back_impl<tiny_tag>
        {
            template <class Tiny, class T>
                struct apply
                : tiny_push_back<
                  Tiny, T, size<Tiny>::value
                  >
            {};
        };

    template <>
        struct pop_front_impl<tiny_tag>
        {
            template <class Tiny>
                struct apply
                : tiny<typename Tiny::t1, typename Tiny::t2, none>
                {};
        };
}}

int main()
{
}

