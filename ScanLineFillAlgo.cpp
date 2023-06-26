#include <iostream>
#include <vector>
#include <algorithm>

struct Point {
    int x;
    int y;
};

void scanLineFill(const std::vector<Point>& polygon) {
    int ymin = polygon[0].y;
    int ymax = polygon[0].y;

    // Find the minimum and maximum y-coordinate values
    for (const auto& point : polygon) {
        ymin = std::min(ymin, point.y);
        ymax = std::max(ymax, point.y);
    }

    // For each scan line
    for (int y = ymin; y <= ymax; y++) {
        std::vector<int> intersectX;

        // Find the intersections of the scan line with the edges of the polygon
        for (std::size_t i = 0; i < polygon.size(); i++) {
            const Point& p1 = polygon[i];
            const Point& p2 = polygon[(i + 1) % polygon.size()];

            if ((p1.y <= y && p2.y > y) || (p1.y > y && p2.y <= y)) {
                // Check if the edge is not horizontal
                if (p1.y != p2.y) {
                    int x = p1.x + ((y - p1.y) / (p2.y - p1.y)) * (p2.x - p1.x);
                    intersectX.push_back(x);
                }
            }
        }

        // Sort the intersections in ascending order
        std::sort(intersectX.begin(), intersectX.end());

        // Fill the pixels between the intersections
        for (std::size_t i = 0; i < intersectX.size(); i += 2) {
            int xStart = intersectX[i];
            int xEnd = intersectX[i + 1];

            for (int x = xStart; x <= xEnd; x++) {
                std::cout << "(" << x << ", " << y << ") "; // Output or process the filled pixel
            }
        }

        std::cout << std::endl; // Move to the next line
    }
}

int main() {
    // Define the polygon vertices
    std::vector<Point> polygon = {
        {50, 50},
        {150, 100},
        {200, 50},
        {150, 150},
        {100, 100}
    };

    // Apply the scan line fill algorithm
    scanLineFill(polygon);

    return 0;
}
