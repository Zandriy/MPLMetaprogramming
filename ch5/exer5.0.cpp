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

#include <boost/mpl/find.hpp>
#include <boost/static_assert.hpp>

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

/////////////////////// TESTING ///////////////////////
//
namespace mpl = boost::mpl;

typedef mpl::tiny<>::type S0;
typedef mpl::tiny<int>::type S1;
typedef mpl::tiny<int, char>::type S2;
typedef mpl::tiny<int, char, float>::type S3;

template<typename S>
struct test_popToEmpty
{
    // pop the front element off S, unless it is empty
    using r1 = typename mpl::eval_if<
        mpl::empty<S>
        , mpl::identity<S>
        , mpl::pop_front<S>
        >::type;

    // likewise
    using r2 = typename mpl::eval_if<
        mpl::empty<S>
        , S                 // when invoked, S returns S
        , mpl::pop_front<S>
        >::type;

    BOOST_STATIC_ASSERT((boost::is_same<r1, r2>::value));
};

template<typename S, typename F>
struct test_iteration
{
    using find_pos = typename mpl::find<S, F>::type;
    using prior_pos = typename mpl::prior<find_pos>::type;
    using next_pos = typename mpl::next<find_pos>::type;
    using begin_pos = typename mpl::begin<S>::type;
    using end_pos = typename mpl::end<S>::type;
    using last_pos = typename mpl::prior<end_pos>::type;

    struct unknown {};
    using unknown_pos = typename mpl::find<S, unknown>::type;
   
    BOOST_STATIC_ASSERT((!boost::is_same<find_pos, end_pos>::value));
    BOOST_STATIC_ASSERT((boost::is_same<prior_pos, begin_pos>::value));
    BOOST_STATIC_ASSERT((boost::is_same<next_pos, last_pos>::value));
    BOOST_STATIC_ASSERT((boost::is_same<unknown_pos, end_pos>::value));
};

using char_pos = typename mpl::find<S3, char>::type;
BOOST_STATIC_ASSERT((boost::is_same<mpl::deref<char_pos>::type, char>::value));
using float_pos = typename mpl::find<S3, float>::type;
BOOST_STATIC_ASSERT((boost::is_same<mpl::deref<float_pos>::type, float>::value));
using int_pos = typename mpl::find<S3, int>::type;
BOOST_STATIC_ASSERT((boost::is_same<mpl::deref<int_pos>::type, int>::value));

BOOST_STATIC_ASSERT((boost::is_same<mpl::at<S3, mpl::int_<0>>::type, S3::t0>::value));
BOOST_STATIC_ASSERT((boost::is_same<mpl::at<S3, mpl::int_<1>>::type, S3::t1>::value));
BOOST_STATIC_ASSERT((boost::is_same<mpl::at<S3, mpl::int_<2>>::type, S3::t2>::value));

BOOST_STATIC_ASSERT((boost::is_same<mpl::size<S0>::type, mpl::int_<0>>::value));
BOOST_STATIC_ASSERT((boost::is_same<mpl::size<S1>::type, mpl::int_<1>>::value));
BOOST_STATIC_ASSERT((boost::is_same<mpl::size<S2>::type, mpl::int_<2>>::value));
BOOST_STATIC_ASSERT((boost::is_same<mpl::size<S3>::type, mpl::int_<3>>::value));


int main()
{
    test_popToEmpty<S0> s0;
    test_popToEmpty<S1> s1;
    test_popToEmpty<S2> s2;
    test_popToEmpty<S3> s3;

    test_iteration<S3, char> iterations;

    using S_PUSH1 = mpl::push_back<S0, long>::type; 
    BOOST_STATIC_ASSERT((boost::is_same<mpl::size<S_PUSH1>::type, mpl::int_<1>>::value));
    using S_PUSH2 = mpl::push_back<S_PUSH1, char*>::type; 
    BOOST_STATIC_ASSERT((boost::is_same<mpl::size<S_PUSH2>::type, mpl::int_<2>>::value));
    using S_PUSH3 = mpl::push_back<S_PUSH2, bool>::type; 
    BOOST_STATIC_ASSERT((boost::is_same<mpl::size<S_PUSH3>::type, mpl::int_<3>>::value));
    using S_POP2 = mpl::pop_front<S_PUSH3>::type; 
    BOOST_STATIC_ASSERT((boost::is_same<mpl::size<S_POP2>::type, mpl::int_<2>>::value));
    using S_POP1 = mpl::pop_front<S_POP2>::type; 
    BOOST_STATIC_ASSERT((boost::is_same<mpl::size<S_POP1>::type, mpl::int_<1>>::value));
    using S_POP0 = mpl::pop_front<S_POP1>::type; 
    BOOST_STATIC_ASSERT((boost::is_same<mpl::size<S_POP0>::type, mpl::int_<0>>::value));
}

