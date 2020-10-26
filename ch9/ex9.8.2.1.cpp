#include <list>

namespace utility
{
    // fill the range with zeroes
    template <class Iterator>
    Iterator clear(Iterator const &start, Iterator const &finish);

    // perform some transformation on the sequence
    template <class Iterator>
    int munge(Iterator start, Iterator finish)
    {
        // ...
        start = clear(start, finish);
        // ...
    }
} // namespace utility

namespace paint
{
    template <class Canvas, class Color> // generalized template
    void clear(Canvas &, Color const &);

    struct some_canvas
    {
    };

    struct black
    {
    };

    std::list<some_canvas> canvases(10);
    int x = utility::munge(canvases.begin(), canvases.end());
} // namespace paint

int main()
{
    
}