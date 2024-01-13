#include <cstdlib> // for clearing terminal
#include <iostream>
#include <sys/ioctl.h> // for getting terminal resolution
#include <unistd.h> // for wait function
#include <vector>

namespace ascii_animation
{
    struct frame
    {
        static const char PLACEHOLDER_SYMBOL = '#';
        std::pair<size_t, size_t> resolution = std::make_pair(1, 1);
        std::vector<std::vector<char>> ascii_image;

        frame(size_t height = 0, size_t width = 0, char filling = PLACEHOLDER_SYMBOL) // same as matrix indexing, but starting from zero
        {

            // set frame sizes to window size if no width or no height specified
            bool zero_width = (width == 0);
            bool zero_height = (height == 0);
            // code source https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
            struct winsize size;
            if (zero_height || zero_width) {
                ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
            }
            if (zero_height)
            {
                resolution.first = size.ws_row;
            } else {
                resolution.first = height;
            }
            if (zero_width)
            {
                resolution.second = size.ws_col;
            } else {
                resolution.second = width;
            }

            // fill frame with placeholder
            ascii_image.resize(resolution.first);
            for (std::vector<char> &row : ascii_image)
            {
                row.resize(resolution.second);
                std::fill(row.begin(), row.end(), filling);
            }
        }
    };
    
    class animation
    {
        private:
        size_t current_frame = 0;
        std::vector<frame> frames = std::vector<frame> (1);

        public:
        long long frame_duration_microseconds = 41666;

        animation() = default;

        animation(std::vector<frame> input_frames) : frames(input_frames) {};

        void advance()
        {
            ++current_frame;
            current_frame %= frames.size();
        }

        frame get_frame() 
        {
            return frames[current_frame];
        }

        void set_fps(size_t fps)
        {
            frame_duration_microseconds = static_cast<long long>(1000000 * (1.0 / fps));
        }
    };

    void render(frame rendered_frame)
    {
        for (std::vector<char> &row : rendered_frame.ascii_image)
            {
                for (char symbol : row)
                {
                    std::cout << symbol;
                }
                std::cout << '\n';
            }
    }

    void clear()
    {
        std::system("clear");
    }

    void wait(long long duration_microseconds)
    {
        usleep(duration_microseconds);
    }

}