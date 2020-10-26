
template <class Derived>
struct vehicle
{
};

template <class Derived>
struct screw
{
};

template <class Vehicle>
void drive(vehicle<Vehicle> const &v)
{
    Vehicle const &v_ = static_cast<Vehicle const &>(v);
    //...
};

template <class Screw>
void drive(screw<Screw> const &s)
{
    Screw const &s_ = static_cast<Screw const &>(s);
    //...
};

int main()
{
}