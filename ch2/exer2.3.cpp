#include <iostream>
#include <string>
#include <type_traits>

template <class T>
struct check_reference
{
    using type = typename std::remove_reference<T>::type;
    static const bool is = std::is_reference<T>::value;
    static std::string value()
    {
        return is ? "&" : "";
    }
};

template <class T>
struct check_pointer
{
    using type = typename std::remove_pointer<T>::type;
    static const bool is = std::is_pointer<T>::value;
    static std::string value()
    {
        return is ? "*" : "";
    }
};

template <class T>
struct check_const
{
    using type = typename std::remove_const<T>::type;
    static const bool is = std::is_const<T>::value;
    static std::string value()
    {
        return is ? "const" : "";
    }
};

template <class T>
struct check_type
{
    using type = T;
    static std::string value()
    {
        if (std::is_same<char, T>::value)
            return "char ";
        if (std::is_same<short, T>::value)
            return "short ";
        if (std::is_same<int, T>::value)
            return "int ";
        if (std::is_same<long, T>::value)
            return "long ";
        return "unknown ";
    }
};

template <class T>
struct type_descriptor
{
    std::string value() const
    {
        std::string result;

        using checkRef = check_reference<T>;
        result += checkRef::value();

        using checkPoint = check_pointer<typename checkRef::type>;
        result = checkPoint::value() + result;

        using checkConst = check_const<typename checkPoint::type>;
        result = checkConst::value() + result;

        using checkType = check_type<typename checkConst::type>;
        result = checkType::value() + result;

        return result;
    }
};

template <class T>
std::ostream &operator<<(std::ostream &os, const type_descriptor<T> &td)
{
    os << td.value();
    return os;
}

int main()
{
    std::cout << type_descriptor<int>() << std::endl;

    std::cout << type_descriptor<char *>() << std::endl;

    std::cout << type_descriptor<long const *&>() << std::endl;
}