#include <ascii_render.h>

int main()
{
    ascii_animation::animation animation;
    while (true)
    {
        ascii_animation::render(animation.get_frame());
        animation.advance();
        ascii_animation::wait(animation.frame_duration_microseconds);
    }
}