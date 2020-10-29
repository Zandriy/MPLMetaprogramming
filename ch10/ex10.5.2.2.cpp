#include <array>
#include <iostream>

// operation tags
struct plus;
struct minus;

// expression tree node
template <class L, class OpTag, class R>
struct Expression
{
    Expression(L const &l, R const &r)
        : l(l), r(r) {}

    float operator[](unsigned index) const
    {
        return OpTag::apply(l[index], r[index]);
    }

    L const &l;
    R const &r;
};

template <class L, class R>
Expression<L, plus, R> operator+(L const &l, R const &r)
{
    return Expression<L, plus, R>(l, r);
}

template <class L, class R>
Expression<L, minus, R> operator-(L const &l, R const &r)
{
    return Expression<L, minus, R>(l, r);
}

// operation tags implement elementwise arithmetic
struct plus
{
    static float apply(float a, float b)
    {
        return a + b;
    }
};

struct minus
{
    static float apply(float a, float b)
    {
        return a - b;
    }
};

int main()
{
    constexpr size_t size{5};
    std::array<float, size> v1 {0,1,2,3,4};
    std::array<float, size> v2 {5,6,7,8,9};

    auto expr = v1 - v2 + v1;

    for (size_t i{0}; i < size; ++i)
    {
        std::cout << expr[i] << ", ";
    }
    std::cout << std::endl;
}