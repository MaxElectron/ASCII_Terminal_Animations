#include <cmath>
#include <stdexcept>
#include <vector>

namespace basic_geometry
{
    struct point
    {
        std::pair<double, double> coordinates;
        point (double x = 0, double y = 0) : coordinates(std::make_pair(x, y)) {};
    };

    struct segment
    {
        std::pair<point, point> ends;
        segment (point a, point b) : ends(std::make_pair(a, b)) {};

        double length()
        {
            return sqrt((ends.first.coordinates.first - ends.second.coordinates.first) *
                (ends.first.coordinates.first - ends.second.coordinates.first) +
                (ends.first.coordinates.second - ends.second.coordinates.second) *
                (ends.first.coordinates.second - ends.second.coordinates.second));
        }
    };

    struct polygon
    {
        std::vector<point> verticies;
        polygon (std::vector<point>& points) : verticies(points) {};

        bool is_triangle()
        {
            return verticies.size() == 3;
        }
    };

    template <typename T> int uneven_sign(T value) {
        return (T(0) < value) - (value < T(0)) + (value == T(0));
    }

    // uneven_sign(asin((dx_1*dy_2 - dx_2*dy_1)/(d1 * d2))) * acos((dx_1*dx_2 + dy_1*dy_2)/(d1 * d2))
    double angle_between_segments(segment segment_1, segment segment_2)
    {
        return uneven_sign(asin(((segment_1.ends.second.coordinates.first - segment_1.ends.first.coordinates.first) *
            (segment_2.ends.second.coordinates.second - segment_2.ends.first.coordinates.second) -
            (segment_2.ends.second.coordinates.first - segment_2.ends.first.coordinates.first) *
            (segment_1.ends.second.coordinates.second - segment_1.ends.first.coordinates.second)) /
            (segment_1.length() * segment_2.length()))) *
            acos(((segment_1.ends.second.coordinates.first - segment_1.ends.first.coordinates.first) *
            (segment_2.ends.second.coordinates.first - segment_2.ends.first.coordinates.first) +
            (segment_1.ends.second.coordinates.second - segment_1.ends.first.coordinates.second) *
            (segment_2.ends.second.coordinates.second - segment_2.ends.first.coordinates.second)) /
            (segment_1.length() * segment_2.length()));
    }

    // if winding number is well-defined returns the winding number, throws std::invalid_argument otherwise
    int winding_number(point center, polygon chain)
    {
        const double ERROR_MARGIN = 0.001;
        double winding_number_approximation = 0;
        point previous = chain.verticies[chain.verticies.size() - 1];
        for (point current : chain.verticies)
        {
            double change_of_angle = angle_between_segments(segment(center, previous), segment(center, current));
            if ((-acos(-1) + ERROR_MARGIN > change_of_angle) || (acos(-1) - ERROR_MARGIN < change_of_angle))
            {
                throw std::invalid_argument("Center lies on the chain");
            }
            winding_number_approximation += change_of_angle / (2 * acos(-1));
            previous = current;
        }
        return static_cast<int>(std::round(winding_number_approximation));
    }
}