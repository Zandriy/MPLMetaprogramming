#include <iostream>
#include <string>

template <class T>
struct type_descriptor
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
struct type_descriptor<T*>
{
    using type = T;
    static std::string value()
    {
        return type_descriptor<T>::value() + "*";
    }
};

template <class T>
struct type_descriptor<T&>
{
    using type = T;
    static std::string value()
    {
        return type_descriptor<T>::value() + "&";
    }
};

template <class T>
struct type_descriptor<const T>
{
    using type = T;
    static std::string value()
    {
        return type_descriptor<T>::value() + "const";
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