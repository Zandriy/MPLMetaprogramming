#include <type_traits>
#include <iostream>

template <bool x>
struct bool_
{
   static bool const value = x;
   typedef bool_<x> type;
   typedef bool value_type;
   operator bool() const { return x; }
};

template <class T0, class T1>
struct logical_or : bool_<T0::value || T1::value>
{
};

template <class T0, class T1>
struct logical_and : bool_<T0::value && T1::value>
{
};

template <class T>
using Or = logical_or<std::is_polymorphic<T>, std::is_class<T>>;

template <class T>
using And = logical_and<std::is_polymorphic<T>, std::is_class<T>>;

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
