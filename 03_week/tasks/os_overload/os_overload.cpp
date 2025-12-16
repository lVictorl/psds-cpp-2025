#include <iostream>
#include <utility>
#include <vector>

struct Coord2D {
    int x = 0, y = 0;
    Coord2D(int x_val = 0, int y_val = 0) : x(x_val), y(y_val) {}
};

std::ostream& operator<<(std::ostream& os, const Coord2D& c) {
    return os << "(" << c.x << ", " << c.y << ")";
}

struct Circle {
    Coord2D coord{0, 0};
    unsigned radius = 1;
    Circle(const Coord2D& c = {0, 0}, unsigned r = 1) : coord(c), radius(r) {}
};

std::ostream& operator<<(std::ostream& os, const Circle& c) {
    os << "circle[";
    if (c.radius > 0) {
        os << c.coord << ", r = " << c.radius;
    }
    return os << "]";
}

using CircleRegion = std::pair<Circle, bool>;
using CircleRegionList = std::vector<CircleRegion>;

std::ostream& operator<<(std::ostream& os, const CircleRegion& r) {
    return os << (r.second ? "+" : "-") << r.first;
}

std::ostream& operator<<(std::ostream& os, const CircleRegionList& list) {
    os << "{";
    if (!list.empty()) {
        os << "\n";
        for (size_t i = 0; i < list.size(); ++i) {
            os << "\t" << list[i] << (i + 1 < list.size() ? ",\n" : "\n");
        }
    }
    return os << "}";
}