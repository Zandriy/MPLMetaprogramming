#include <type_traits>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <iostream>

namespace mpl = boost::mpl;

template <class T>
using is_data_member_pointer = mpl::and_<std::is_member_pointer<T>, mpl::not_<std::is_member_function_pointer<T>>>;

template <class T>
using is_pointer_to_function = mpl::or_<std::is_member_function_pointer<T>,
    mpl::and_<std::is_pointer<T>, std::is_function<typename std::remove_pointer<T>::type>>>;

template <class T>
using is_reference_to_function_pointer = mpl::and_<std::is_reference<T>, std::is_pointer<typename std::remove_reference<T>::type>,
    std::is_function<typename std::remove_pointer<typename std::remove_reference<T>::type>::type>>;

template <class T>
using is_reference_to_non_const = mpl::and_<std::is_reference<T>, mpl::not_<std::is_const<typename std::remove_reference<T>::type>>>; 

struct S
{
    int f() const { return i; }
    int i{};
};

int main()
{
    typedef int (*fp)();
    typedef int (*&rfp)();
    typedef int (S::*fsp)();
    typedef int S::*sp;
    typedef int &ref;
    typedef const int &cref;

    std::cout << "=== is_data_member_pointer:\n";
    std::cout << "pointer to function: " << std::boolalpha << is_data_member_pointer<fp>::value << "\n";
    std::cout << "reference to function pointer: " << std::boolalpha << is_data_member_pointer<rfp>::value << "\n";
    std::cout << "pointer to member function: " << std::boolalpha << is_data_member_pointer<fsp>::value << "\n";
    std::cout << "pointer to member data: " << std::boolalpha << is_data_member_pointer<sp>::value << "\n";
    std::cout << "reference: " << std::boolalpha << is_data_member_pointer<ref>::value << "\n";
    std::cout << "const reference: " << std::boolalpha << is_data_member_pointer<cref>::value << "\n";

    std::cout << "=== is_pointer_to_function:\n";
    std::cout << "pointer to function: " << std::boolalpha << is_pointer_to_function<fp>::value << "\n";
    std::cout << "reference to function pointer: " << std::boolalpha << is_pointer_to_function<rfp>::value << "\n";
    std::cout << "pointer to member function: " << std::boolalpha << is_pointer_to_function<fsp>::value << "\n";
    std::cout << "pointer to member data: "<< std::boolalpha << is_pointer_to_function<sp>::value << "\n";
    std::cout << "reference: " << std::boolalpha << is_pointer_to_function<ref>::value << "\n";
    std::cout << "const reference: " << std::boolalpha << is_pointer_to_function<cref>::value << "\n";

    std::cout << "=== is_reference_to_function_pointer: \n";
    std::cout << "pointer to function: " << std::boolalpha << is_reference_to_function_pointer<fp>::value << "\n";
    std::cout << "reference to function pointer: " << std::boolalpha << is_reference_to_function_pointer<rfp>::value << "\n";
    std::cout << "pointer to member function: " << std::boolalpha << is_reference_to_function_pointer<fsp>::value << "\n";
    std::cout << "pointer to member data: "<< std::boolalpha << is_reference_to_function_pointer<sp>::value << "\n";
    std::cout << "reference: " << std::boolalpha << is_reference_to_function_pointer<ref>::value << "\n";
    std::cout << "const reference: " << std::boolalpha << is_reference_to_function_pointer<cref>::value << "\n";

    std::cout << "=== is_reference_to_non_const:\n";
    std::cout << "pointer to function: " << std::boolalpha << is_reference_to_non_const<fp>::value << "\n";
    std::cout << "reference to function pointer: " << std::boolalpha << is_reference_to_non_const<rfp>::value << "\n";
    std::cout << "pointer to member function: " << std::boolalpha << is_reference_to_non_const<fsp>::value << "\n";
    std::cout << "pointer to member data: " << std::boolalpha << is_reference_to_non_const<sp>::value << "\n";
    std::cout << "reference: " << std::boolalpha << is_reference_to_non_const<ref>::value << "\n";
    std::cout << "const reference: " << std::boolalpha << is_reference_to_non_const<cref>::value << "\n";
}
