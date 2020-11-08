#include <boost/mpl/begin.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/static_assert.hpp>
#include <type_traits>

namespace boost
{
  namespace mpl
  {

    struct nil
    {
      using type = nil;
    };

    struct tree_tag
    {
    };

    template <class T0, class T1, class T2>
    struct tree
    {
      using tag = tree_tag;
      using type = tree;
      using is_leaf = false_;
      
      template<class T>
      using t = typename std::conditional<mpl::or_<std::is_pointer<T>, std::is_fundamental<T>>::value, tree<T, nil, nil>, T>::type;
      using t0 = t<T0>;
      using t1 = t<T1>;
      using t2 = t<T2>;
    };

    template <class T>
    struct tree<T, nil, nil>
    {
      using tag = tree_tag;
      using type = T;
      using is_leaf = true_;

      using t0 = T;
      using t1 = nil;
      using t2 = nil;
    };

    template <class Tree, class Pos>
    struct tree_iterator
    {
      typedef mpl::random_access_iterator_tag category;
      typedef Pos pos;
    };

    template <class Tree, class Pos>
    struct next<tree_iterator<Tree, Pos>>
    {
      typedef tree_iterator<
          Tree, typename mpl::next<Pos>::type>
          type;
    };

    template <class Tree, class Pos>
    struct prior<tree_iterator<Tree, Pos>>
    {
      typedef tree_iterator<
          Tree, typename mpl::prior<Pos>::type>
          type;
    };

    template <class Tree, int N>
    struct tree_at;

    template <class Tree>
    struct tree_at<Tree, 0>
    {
      typedef typename Tree::t0 type;
    };

    template <class Tree>
    struct tree_at<Tree, 1>
    {
      typedef typename Tree::t1 type;
    };

    template <class Tree>
    struct tree_at<Tree, 2>
    {
      typedef typename Tree::t2 type;
    };

    template <>
    struct at_impl<tree_tag>
    {
      template <class Tree, class N>
      struct apply : tree_at<Tree, N::value>
      {
      };
    };

    template <>
    struct begin_impl<tree_tag>
    {
      template <class Tree>
      struct apply
      {
        typedef tree_iterator<Tree, int_<0>> type;
      };
    };

    template <class T0, class T1, class T2>
    struct tree_size
        : mpl::int_<3>
    {
    };

    template <class T0, class T1>
    struct tree_size<T0, T1, nil>
        : mpl::int_<2>
    {
    };

    template <class T0>
    struct tree_size<T0, nil, nil>
        : mpl::int_<1>
    {
    };

    template <>
    struct tree_size<nil, nil, nil>
        : mpl::int_<0>
    {
    };

    template <>
    struct size_impl<tree_tag>
    {
      template <class Tree>
      struct apply
          : tree_size<
                typename Tree::t0, typename Tree::t1, typename Tree::t2>
      {
      };
    };

    template <class Tree, class Pos>
    struct deref<tree_iterator<Tree, Pos>>
        : at<Tree, Pos>
    {
    };

    template <class Tree, class Pos, class N>
    struct advance<tree_iterator<Tree, Pos>, N>
    {
      typedef tree_iterator<
          Tree, typename mpl::plus<Pos, N>::type>
          type;
    };

  } // namespace mpl
} // namespace boost

/////////////////////////////////////////////////

namespace mpl = boost::mpl;
using namespace mpl::placeholders;

/////////////////////////////////////////////////

template<class T0, bool LT0, class T1, bool LT1, class T2, bool LT2>
struct preorder_view_impl;

template<class T>
using preorder_tree_unpack = preorder_view_impl<typename T::t0, T::t0::is_leaf::value,
                              typename T::t1, T::t1::is_leaf::value,
                              typename T::t2, T::t2::is_leaf::value>;

template<class T, bool b>
struct preorder_choose_leaf
{
  using type = typename preorder_tree_unpack<T>::type::type;
};

template<class T>
struct preorder_choose_leaf<T, true>
{
  using type = mpl::vector<typename T::type>;
};

template<class T0, bool LT0, class T1, bool LT1, class T2, bool LT2>
struct preorder_view_impl
 : mpl::copy<typename preorder_choose_leaf<T2, LT2>::type, mpl::back_inserter<
    typename
     mpl::copy<typename preorder_choose_leaf<T0, LT0>::type, mpl::front_inserter<
      typename
      preorder_choose_leaf<T1, LT1>::type
     >>::type
   >>::type
{
};

template <class T0, class T1, class T2>
struct preorder_view_impl<T0, true, T1, true, T2, true> : mpl::vector<typename T0::type, typename T1::type, typename T2::type>
{
};

template <class T>
struct preorder_view : preorder_tree_unpack<T>
{
};

/////////////////////////////////////////////////

template<class T0, bool LT0, class T1, bool LT1, class T2, bool LT2>
struct inorder_view_impl;

template<class T>
using inorder_tree_unpack = inorder_view_impl<typename T::t1, T::t1::is_leaf::value,
                              typename T::t0, T::t0::is_leaf::value,
                              typename T::t2, T::t2::is_leaf::value>;

template<class T, bool b>
struct inorder_choose_leaf
{
  using type = typename inorder_tree_unpack<T>::type::type;
};

template<class T>
struct inorder_choose_leaf<T, true>
{
  using type = mpl::vector<typename T::type>;
};

template<class T0, bool LT0, class T1, bool LT1, class T2, bool LT2>
struct inorder_view_impl
 : mpl::copy<typename inorder_choose_leaf<T2, LT2>::type, mpl::back_inserter<
    typename
     mpl::copy<typename inorder_choose_leaf<T1, LT1>::type, mpl::back_inserter<
      typename 
      inorder_choose_leaf<T0, LT0>::type
     >>::type
   >>::type
{
};

template <class T0, class T1, class T2>
struct inorder_view_impl<T0, true, T1, true, T2, true> : mpl::vector<typename T0::type, typename T1::type, typename T2::type>
{
};

template <class T>
struct inorder_view : inorder_tree_unpack<T>
{
};

/////////////////////////////////////////////////

template<class T0, bool LT0, class T1, bool LT1, class T2, bool LT2>
struct postorder_view_impl;

template<class T>
using postorder_tree_unpack = postorder_view_impl<typename T::t1, T::t1::is_leaf::value,
                              typename T::t2, T::t2::is_leaf::value,
                              typename T::t0, T::t0::is_leaf::value>;

template<class T, bool b>
struct postorder_choose_leaf
{
  using type = typename postorder_tree_unpack<T>::type::type;
};

template<class T>
struct postorder_choose_leaf<T, true>
{
  using type = mpl::vector<typename T::type>;
};

template<class T0, bool LT0, class T1, bool LT1, class T2, bool LT2>
struct postorder_view_impl
 : mpl::copy<typename postorder_choose_leaf<T2, LT2>::type, mpl::back_inserter<
    typename
     mpl::copy<typename postorder_choose_leaf<T1, LT1>::type, mpl::back_inserter<
      typename 
      postorder_choose_leaf<T0, LT0>::type
     >>::type
   >>::type
{
};

template <class T0, class T1, class T2>
struct postorder_view_impl<T0, true, T1, true, T2, true> : mpl::vector<typename T0::type, typename T1::type, typename T2::type>
{
};

template <class T>
struct postorder_view : postorder_tree_unpack<T>
{
};

/////////////////////////////////////////////////

typedef mpl::tree<
    double,
    mpl::tree<void *, int, long>,
    char>
    tree_seq;

BOOST_STATIC_ASSERT(( mpl::equal<
         preorder_view<tree_seq>
       , mpl::vector<double,void*,int,long,char>
       , boost::is_same<_1,_2>
       >::value ));

BOOST_STATIC_ASSERT(( mpl::equal<
         inorder_view<tree_seq>
       , mpl::vector<int,void*,long,double,char>
       , boost::is_same<_1,_2>
       >::value ));

BOOST_STATIC_ASSERT(( mpl::equal<
         postorder_view<tree_seq>
       , mpl::vector<int,long,void*,char,double>
       , boost::is_same<_1,_2>
       >::value ));

int main()
{
}