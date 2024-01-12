#include <iostream>
#include <vector>
#include <unistd.h>

namespace ascii_animation
{
    class animation
    {
        private:
        size_t current_frame = 0;
        std::vector<frame> frames;

        public:
        long long frame_duration_microseconds;

        void advance()
        {
            ++current_frame;
            current_frame %= frames.size();
        }

        frame get_frame() 
        {
            return frames[current_frame];
        }
    };

    struct frame
    {

    };

    void render(frame rendered_frame)
    {

    }

    void wait(long long duration_microseconds)
    {

    }

}