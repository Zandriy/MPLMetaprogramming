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
        return is ? "reference to " : "";
    }
};

template <class T>
struct check_pointer
{
    using type = typename std::remove_pointer<T>::type;
    static const bool is = std::is_pointer<T>::value;
    static std::string value()
    {
        return is ? "pointer to " : "";
    }
};

template <class T>
struct check_const
{
    using type = typename std::remove_const<T>::type;
    static const bool is = std::is_const<T>::value;
    static std::string value()
    {
        return is ? "constant " : "";
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
struct check_array
{
    using type = typename std::remove_extent<T>::type;
    static const bool is = std::is_array<T>::value;
    static std::string value()
    {
        return is ? "array of " : "";
    }
};

template <class T>
struct check_function
{
    using type = T;
    static const bool is = std::is_function<T>::value;
    static std::string value()
    {
        return is ? "function " : "";
    }
};

template <class T>
struct function_return
{
    using type = T;
};

template <class T>
struct function_return<T()>
{
    using type = T;
};

template <class T>
struct type_descriptor
{
    static std::string value()
    {
        std::string result;

        using checkArr = check_array<T>;
        result += checkArr::value();

        using checkRef = check_reference<typename checkArr::type>;
        result += checkRef::value();

        using checkPoint = check_pointer<typename checkRef::type>;
        using checkFunc = check_function<typename checkPoint::type>;

        if (checkFunc::is)
        {
            result += (checkPoint::value() + checkFunc::value() + "returning ");
            return result + type_descriptor<typename function_return<typename checkFunc::type>::type>::value();
        }
        else
            result = checkPoint::value() + result;

        using checkConst = check_const<typename checkFunc::type>;
        result = checkConst::value() + result;

        using checkType = check_type<typename checkConst::type>;
        result += checkType::value();

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

    std::cout << type_descriptor<char *(*[])()>() << std::endl;
}