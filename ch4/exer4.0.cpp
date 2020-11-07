#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <type_traits>
#include <iostream>

namespace mpl = boost::mpl;

template <class T>
using Or = mpl::or_<std::is_polymorphic<T>, std::is_class<T>>;

template <class T>
using And = mpl::and_<std::is_polymorphic<T>, std::is_class<T>>;

struct Poly
{
   Poly() { std::cout << "Poly instantiated\n"; }
   virtual ~Poly() {}
};

struct NotPoly
{
   NotPoly() { std::cout << "NotPoly instantiated\n"; }
};

int main()
{
   Poly poly;
   NotPoly notPoly;
   std::cout << "=====================================\n";

   std::cout << std::boolalpha << Or<Poly>::value << "\n";
   std::cout << std::boolalpha << Or<NotPoly>::value << "\n";
   std::cout << std::boolalpha << And<Poly>::value << "\n";
   std::cout << std::boolalpha << And<NotPoly>::value << "\n";
}
