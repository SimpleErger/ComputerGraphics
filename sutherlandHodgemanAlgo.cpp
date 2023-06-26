#include<iostream>
using namespace std;

struct Point {
    int x, y;
};

// Returns the point of intersection of the line formed by points p1 and p2
// with the clip edge formed by points inside and outside
Point getIntersection(Point p1, Point p2, Point inside, Point outside) {
    Point intersection;
    int x1 = p1.x, y1 = p1.y;
    int x2 = p2.x, y2 = p2.y;
    int x3 = inside.x, y3 = inside.y;
    int x4 = outside.x, y4 = outside.y;

    int num = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
    int den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    intersection.x = num / den;
    intersection.y = (y1 - y2) * (intersection.x - x1) / (x1 - x2) + y1;

    return intersection;
}

// Clips the polygon against a single clip edge
void clipPolygon(Point polygon[], int &numVertices, Point inside, Point outside) {
    Point clippedPolygon[20];
    int numClippedVertices = 0;

    Point p1 = polygon[numVertices - 1];

    for (int i = 0; i < numVertices; i++) {
        Point p2 = polygon[i];

        // Case 1: Both points are inside the clip edge
        if (p2.x >= inside.x && p1.x >= inside.x) {
            clippedPolygon[numClippedVertices++] = p2;
        }
        // Case 2: Only p2 is outside the clip edge
        else if (p2.x >= inside.x && p1.x < inside.x) {
            clippedPolygon[numClippedVertices++] = getIntersection(p1, p2, inside, outside);
            clippedPolygon[numClippedVertices++] = p2;
        }
        // Case 3: Only p1 is outside the clip edge
        else if (p2.x < inside.x && p1.x >= inside.x) {
            clippedPolygon[numClippedVertices++] = getIntersection(p1, p2, inside, outside);
        }

        p1 = p2;
    }

    // Update the original polygon with the clipped polygon
    numVertices = numClippedVertices;
    for (int i = 0; i < numVertices; i++) {
        polygon[i] = clippedPolygon[i];
    }
}

// Applies Sutherland-Hodgman algorithm for polygon clipping
void sutherlandHodgmanClip(Point polygon[], int &numVertices, Point clipWindow[], int numEdges) {
    for (int i = 0; i < numEdges; i++) {
        Point inside = clipWindow[i];
        Point outside = clipWindow[(i + 1) % numEdges];
        clipPolygon(polygon, numVertices, inside, outside);
    }
}

// Driver code
int main() {
    Point polygon[] = { {50, 150}, {200, 50}, {350, 150}, {350, 300}, {250, 300}, {200, 250}, {150, 350}, {100, 250}, {100, 200} };
    int numVertices = sizeof(polygon) / sizeof(polygon[0]);

    Point clipWindow[] = { {100, 100}, {300, 100}, {300, 300}, {100, 300} };
    int numEdges = sizeof(clipWindow) / sizeof(clipWindow[0]);

    sutherlandHodgmanClip(polygon, numVertices, clipWindow, numEdges);

    cout << "Clipped polygon vertices:\n";
    for (int i = 0; i < numVertices; i++) {
        cout << "(" << polygon[i].x << ", " << polygon[i].y << ") ";
    }

    return 0;
}