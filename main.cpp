#include "ascii_render.h"

int main()
{

    // set up the animation
    std::vector<ascii_animation::frame> frames {};
    frames.emplace_back(0, 0, '#', ascii_animation::red);
    frames.emplace_back(0, 0, '#', ascii_animation::yellow);
    frames.emplace_back(0, 0, '#', ascii_animation::green);
    frames.emplace_back(0, 0, '#', ascii_animation::blue);
    frames.emplace_back(0, 0, '#', ascii_animation::magenta);
    ascii_animation::animation animation (frames);
    animation.set_fps(12);

    // run the animation
    while (true)
    {
        ascii_animation::clear();
        ascii_animation::render(animation.get_frame());
        animation.advance();
        ascii_animation::wait(animation.frame_duration_microseconds);
    }
}