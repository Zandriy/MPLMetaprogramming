#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace mpl = boost::mpl;
using namespace mpl::placeholders;

template <class T>
struct returning_ptr
{
 	typedef T* type();
};

typedef mpl::transform<
      mpl::vector5<int&,char,long[5],bool,double>
    , returning_ptr<_1>
>::type functions;

int main() {}
