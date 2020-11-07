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

using false_ = bool_<false>;
using true_ = bool_<true>;

template <bool, class, class, class, class>
struct logical_or_impl : true_
{
};

template <class T0, class T1, class T2, class T3>
struct logical_or_impl<false, T0, T1, T2, T3> : logical_or_impl<T0::value, T1, T2, T3, false_>
{
};

template <>
struct logical_or_impl<false, false_, false_, false_, false_> : false_
{
};

template <class T0, class T1, class T2=false_, class T3=false_, class T4=false_>
struct logical_or : logical_or_impl<T0::value,T1, T2, T3, T4>
{
};

template<bool, class, class, class, class>
struct logical_and_impl : false_
{
};

template<class T0, class T1, class T2, class T3>
struct logical_and_impl<true, T0, T1, T2, T3> : logical_and_impl<T0::value, T1, T2, T3, true_>
{
};

template<>
struct logical_and_impl<true, true_, true_, true_, true_> : true_
{
};

template <class T0, class T1, class T2=true_, class T3=true_, class T4=true_>
struct logical_and : logical_and_impl<T0::value, T1, T2, T3, T4>
{
};

template <class T>
using Or = logical_or<std::is_polymorphic<T>, std::is_class<T>>;

template <class T>
using Or5 = logical_or<std::is_polymorphic<T>, std::is_class<T>, std::is_move_assignable<T>, std::is_destructible<T>, std::is_copy_assignable<T>>;

template <class T>
using And = logical_and<std::is_polymorphic<T>, std::is_class<T>>;

template <class T>
using And5 = logical_and<std::is_polymorphic<T>, std::is_class<T>, std::is_move_assignable<T>, std::is_destructible<T>, std::is_copy_assignable<T>>;

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
   std::cout << std::boolalpha << Or<Poly>::value << "\n";
   std::cout << std::boolalpha << Or<NotPoly>::value << "\n";
   std::cout << std::boolalpha << And<Poly>::value << "\n";
   std::cout << std::boolalpha << And<NotPoly>::value << "\n";
   std::cout << "==========================================\n";
   std::cout << std::boolalpha << Or5<Poly>::value << "\n";
   std::cout << std::boolalpha << Or5<NotPoly>::value << "\n";
   std::cout << std::boolalpha << And5<Poly>::value << "\n";
   std::cout << std::boolalpha << And5<NotPoly>::value << "\n";
}
