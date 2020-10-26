namespace crtp
{
    template <class T>
    struct signed_number
    {
        friend T abs(T x)
        {
            return x < 0 ? -x : x;
        }
    };
} // namespace crtp

class Float : crtp::signed_number<Float>
{
public:
    Float(float x)
        : value(x)
    {
    }

    Float operator-() const
    {
        return Float(-value);
    }

    bool operator<(float x) const
    {
        return value < x;
    }

    float value;
};

Float const minus_pi = -3.14159265;
Float const pi = abs(minus_pi);

int main()
{
}