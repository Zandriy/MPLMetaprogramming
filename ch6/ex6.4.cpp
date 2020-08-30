#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/iter_fold.hpp>
#include <boost/mpl/reverse_iter_fold.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/deref.hpp>

#include <boost/mpl/equal.hpp>
#include <boost/static_assert.hpp>

namespace mpl = boost::mpl;
using namespace boost::mpl::placeholders;

template <class Seq>
struct reverse
: mpl::fold<
    Seq
    , typename mpl::clear<Seq>::type // initial type
    , mpl::push_front<_,_>           // binary operation
    >
{};

using Reversed = reverse<mpl::vector<bool, int, char>>::type;
using Result = mpl::vector<char, int, bool>;

BOOST_STATIC_ASSERT((mpl::equal<Reversed, Result>::value));

//////////////////////////////////////////////////////////////////////

template <class Seq>
struct not_reverse
: mpl::reverse_fold<
    Seq
    , typename mpl::clear<Seq>::type
    , mpl::push_front<_,_>
    >
{};

using NotReversed = not_reverse<mpl::vector<char, int, bool>>::type;

BOOST_STATIC_ASSERT((mpl::equal<NotReversed, Result>::value));

//////////////////////////////////////////////////////////////////////

template <class Seq>
struct reverse_iter
: mpl::iter_fold<
    Seq
    , typename mpl::clear<Seq>::type
    , mpl::push_front<_1,mpl::deref<_2>>
    >
{};

using ReversedIter = reverse_iter<mpl::vector<bool, int, char>>::type;

BOOST_STATIC_ASSERT((mpl::equal<ReversedIter, Result>::value));

//////////////////////////////////////////////////////////////////////

template <class Seq>
struct not_reverse_iter
: mpl::reverse_iter_fold<
    Seq
    , typename mpl::clear<Seq>::type
    , mpl::push_front<_1,mpl::deref<_2>>
    >
{};

using NotReversedIter = not_reverse<mpl::vector<char, int, bool>>::type;

BOOST_STATIC_ASSERT((mpl::equal<NotReversedIter, Result>::value));

int main()
{
}
