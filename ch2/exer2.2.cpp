#include <cassert>

template <class Target, class Source>
inline Target polymorphic_downcast(Source *x)
{
    assert(dynamic_cast<Target>(x) == x);
    return static_cast<Target>(x);
}

template <class Target, class Source>
inline Target polymorphic_downcast(Source &x)
{
    assert(&dynamic_cast<Target>(x) == &x);
    return static_cast<Target>(x);
}

struct A
{
    virtual ~A() {}
};
struct B : A
{
};

int main()
{
    B b;
    A *a_ptr = &b;
    B *b_ptr = polymorphic_downcast<B *>(a_ptr);

    A &a_ref = b;
    B &b_ref = polymorphic_downcast<B &>(a_ref);
}