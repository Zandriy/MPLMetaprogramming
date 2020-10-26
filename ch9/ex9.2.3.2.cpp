#include <boost/mpl/bool.hpp>
#include <boost/type_traits.hpp>

#include <iostream>

namespace mpl = boost::mpl;

// implementation for polymorphic types
template <class T, class U>
T desperate_cast_impl2(U& x,  mpl::true_)

{
    std::cout << "dynamic_cast\n";
    return dynamic_cast<T>(x);
}

// implementation for non-polymorphic types
template <class T, class U>
T desperate_cast_impl2(U& x,  mpl::false_)
{
    std::cout << "static_cast\n";
    return static_cast<T>(x);
}

// dispatcher
template <class T, class U>
T desperate_cast_impl(U& x)
{
    return desperate_cast_impl2<T>(
              x
            , boost::is_polymorphic<
                typename boost::remove_pointer<U>::type
              >()
            );
}

// public interface
template <class T, class U>
T desperate_cast(U const& x) { return desperate_cast_impl<T>(x); }

template <class T, class U>
T desperate_cast(U& x) { return desperate_cast_impl<T>(x); }



int main()
{
    double d = desperate_cast<double>(5);

    struct AV { virtual ~AV(){} };
    struct BV : AV {};
    BV bv;
    AV* av = desperate_cast<AV*>(&bv);

    struct AS {};
    struct BS : AS {};
    BS bs;
    AS* as = desperate_cast<AS*>(&bs);
}
