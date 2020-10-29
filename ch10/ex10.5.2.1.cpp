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

    float operator[](unsigned index) const;

    L const &l;
    R const &r;
};

// addition operator
template <class L, class R>
Expression<L, plus, R> operator+(L const &l, R const &r)
{
    return Expression<L, plus, R>(l, r);
}

int main()
{
    constexpr size_t size{5};
    std::array<float, size> v1 {0,1,2,3,4};
    std::array<float, size> v2 {5,6,7,8,9};

    auto expr = v1 + v2 + v1;

    for (auto &v : expr.l.r)
    {
        std::cout << v << ", ";
    }
    std::cout << std::endl;
}