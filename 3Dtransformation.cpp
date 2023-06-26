#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Define a 3D point structure
struct Point3D {
    double x, y, z;
};

// Define a 3D object structure
struct Object3D {
    vector<Point3D> vertices;
};

// Define transformation matrices
struct TransformationMatrix {
    double matrix[4][4];

    TransformationMatrix() {
        // Initialize matrix as an identity matrix
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrix[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
    }
};

// Multiply two transformation matrices
TransformationMatrix multiplyMatrices(const TransformationMatrix& m1, const TransformationMatrix& m2) {
    TransformationMatrix result;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.matrix[i][j] = 0.0;
            for (int k = 0; k < 4; k++) {
                result.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
            }
        }
    }

    return result;
}

// Apply a transformation matrix to a 3D object
void applyTransformation(Object3D& object, const TransformationMatrix& transformationMatrix) {
    for (int i = 0; i < object.vertices.size(); i++) {
        double x = object.vertices[i].x;
        double y = object.vertices[i].y;
        double z = object.vertices[i].z;

        // Add a homogeneous coordinate
        double homogeneousCoord = 1.0;

        // Perform matrix multiplication
        double newX = transformationMatrix.matrix[0][0] * x +
                      transformationMatrix.matrix[0][1] * y +
                      transformationMatrix.matrix[0][2] * z +
                      transformationMatrix.matrix[0][3] * homogeneousCoord;

        double newY = transformationMatrix.matrix[1][0] * x +
                      transformationMatrix.matrix[1][1] * y +
                      transformationMatrix.matrix[1][2] * z +
                      transformationMatrix.matrix[1][3] * homogeneousCoord;

        double newZ = transformationMatrix.matrix[2][0] * x +
                      transformationMatrix.matrix[2][1] * y +
                      transformationMatrix.matrix[2][2] * z +
                      transformationMatrix.matrix[2][3] * homogeneousCoord;

        // Update the object's vertex coordinates
        object.vertices[i].x = newX;
        object.vertices[i].y = newY;
        object.vertices[i].z = newZ;
    }
}

// Print the vertices of a 3D object
void printObject(const Object3D& object) {
    for (int i = 0; i < object.vertices.size(); i++) {
        cout << "Vertex " << i + 1 << ": (" << object.vertices[i].x << ", "
             << object.vertices[i].y << ", " << object.vertices[i].z << ")" << endl;
    }
}

int main() {
    // Create a 3D object
    Object3D object;
    object.vertices.push_back({1.0, 1.0, 1.0});
    object.vertices.push_back({2.0, 2.0, 2.0});
    object.vertices.push_back({3.0, 3.0, 3.0});

    // Define a translation matrix
    TransformationMatrix translationMatrix;
    translationMatrix.matrix[0][3] = 1.0; // Translation along the x-axis
    translationMatrix.matrix[1][3] = 2.0; // Translation along the y-axis
    translationMatrix.matrix[2][3] = 3.0; // Translation along the z-axis

    // Apply translation to the object
    applyTransformation(object, translationMatrix);

    // Print the transformed object
    cout << "Transformed object:" << endl;
    printObject(object);

    return 0;
}
