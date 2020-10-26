#include <memory>
#include <functional>
#include <ctime>
#include <cstdlib>

using float_function = std::function<float(float)>;
using pixel_map = float;

class screensaver
{
public:
    explicit screensaver(float_function f)
        : get_seed(f)
    {
    }

    pixel_map next_screen()
    {
        float center_pixel_brightness = static_cast<float>(rand())/rand();
        float seed = this->get_seed(center_pixel_brightness);
        // ...
        return seed;
    }

private:
    float_function get_seed;
    // ...
};

float func(float f) {return f;}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    screensaver ss(float_function(func));
}