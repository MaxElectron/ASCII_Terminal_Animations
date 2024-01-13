#include "ascii_render.h"

int main()
{
    std::vector<ascii_animation::frame> frames {ascii_animation::frame(9, 16, '0'), ascii_animation::frame(9, 16, '1')};
    ascii_animation::animation animation (frames);
    animation.set_fps(2);
    while (true)
    {
        ascii_animation::clear();
        ascii_animation::render(animation.get_frame());
        animation.advance();
        ascii_animation::wait(animation.frame_duration_microseconds);
    }
}