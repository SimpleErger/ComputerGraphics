#include <iostream>
#include <cmath>
#include <vector>

struct Point {
    float x;
    float y;
};

void multiplyMatrix(const std::vector<std::vector<float>>& matrixA, const std::vector<std::vector<float>>& matrixB, std::vector<std::vector<float>>& result) {
    int rowsA = matrixA.size();
    int colsA = matrixA[0].size();
    int colsB = matrixB[0].size();

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
            for (int k = 0; k < colsA; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

void translate(std::vector<Point>& points, float tx, float ty) {
    std::vector<std::vector<float>> translationMatrix = {
        {1.0, 0.0, tx},
        {0.0, 1.0, ty},
        {0.0, 0.0, 1.0}
    };

    for (auto& point : points) {
        std::vector<std::vector<float>> pointMatrix = {
            {point.x},
            {point.y},
            {1.0}
        };

        std::vector<std::vector<float>> resultMatrix(3, std::vector<float>(1, 0.0));
        multiplyMatrix(translationMatrix, pointMatrix, resultMatrix);

        point.x = resultMatrix[0][0];
        point.y = resultMatrix[1][0];
    }
}

void rotate(std::vector<Point>& points, float angle) {
    float radians = angle * 3.14159 / 180.0;
    float cosTheta = cos(radians);
    float sinTheta = sin(radians);

    std::vector<std::vector<float>> rotationMatrix = {
        {cosTheta, -sinTheta, 0.0},
        {sinTheta, cosTheta, 0.0},
        {0.0, 0.0, 1.0}
    };

    for (auto& point : points) {
        std::vector<std::vector<float>> pointMatrix = {
            {point.x},
            {point.y},
            {1.0}
        };

        std::vector<std::vector<float>> resultMatrix(3, std::vector<float>(1, 0.0));
        multiplyMatrix(rotationMatrix, pointMatrix, resultMatrix);

        point.x = resultMatrix[0][0];
        point.y = resultMatrix[1][0];
    }
}

void scale(std::vector<Point>& points, float sx, float sy) {
    std::vector<std::vector<float>> scalingMatrix = {
        {sx, 0.0, 0.0},
        {0.0, sy, 0.0},
        {0.0, 0.0, 1.0}
    };

    for (auto& point : points) {
        std::vector<std::vector<float>> pointMatrix = {
            {point.x},
            {point.y},
            {1.0}
        };

        std::vector<std::vector<float>> resultMatrix(3, std::vector<float>(1, 0.0));
        multiplyMatrix(scalingMatrix, pointMatrix, resultMatrix);

        point.x = resultMatrix[0][0];
        point.y = resultMatrix[1][0];
    }
}

int main() {
    // Define the initial object coordinates
    std::vector<Point> object = {
        {10.0, 10.0},
        {20.0, 10.0},
        {20.0, 20.0},
        {10.0, 20.0}
    };

    // Perform transformations
    translate(object, 5.0, 5.0);
    rotate(object, 45.0);
    scale(object, 2.0, 2.0);

    // Display the transformed object coordinates
    std::cout << "Transformed object coordinates:\n";
    for (const auto& point : object) {
        std::cout << "(" << point.x << ", " << point.y << ")\n";
    }

    return 0;
}
