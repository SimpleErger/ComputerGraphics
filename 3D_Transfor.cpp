#include <graphics.h>
#include <conio.h>
#include <stdio.h>

struct Point3D {
    int x;
    int y;
    int z;
};

void transform(Point3D points[], int count, int matrix[][4]) {
    for (int i = 0; i < count; i++) {
        int x = points[i].x;
        int y = points[i].y;
        int z = points[i].z;

        points[i].x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3];
        points[i].y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3];
        points[i].z = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z + matrix[2][3];
    }
}

void draw(Point3D points[], int count) {
    for (int i = 0; i < count; i++) {
        int j = (i + 1) % count;
        line(points[i].x, points[i].y, points[j].x, points[j].y);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int object_count = 8;
    Point3D original_object[8] = {
        {100, 100, 100}, {200, 100, 100}, {200, 200, 100}, {100, 200, 100},
        {100, 100, 200}, {200, 100, 200}, {200, 200, 200}, {100, 200, 200}
    };

    // Translation: Translate the object by adding offsets
    int translation_matrix[4][4] = {
        {1, 0, 0, 50},
        {0, 1, 0, 50},
        {0, 0, 1, 50},
        {0, 0, 0, 1}
    };
    Point3D translated_object[8];
    for (int i = 0; i < object_count; i++) {
        translated_object[i] = original_object[i];
    }
    transform(translated_object, object_count, translation_matrix);
    draw(translated_object, object_count);

    // Scaling: Scale the object by multiplying factors
    int scaling_matrix[4][4] = {
        {2, 0, 0, 0},
        {0, 2, 0, 0},
        {0, 0, 2, 0},
        {0, 0, 0, 1}
    };
    Point3D scaled_object[8];
    for (int i = 0; i < object_count; i++) {
        scaled_object[i] = original_object[i];
    }
    transform(scaled_object, object_count, scaling_matrix);
    draw(scaled_object, object_count);

    // Rotation around X-axis: Rotate the object around the X-axis
    int rotation_x_matrix[4][4] = {
        {1, 0, 0, 0},
        {0, 0, -1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 1}
    };
    Point3D rotated_x_object[8];
    for (int i = 0; i < object_count; i++) {
        rotated_x_object[i] = original_object[i];
    }
    transform(rotated_x_object, object_count, rotation_x_matrix);
    draw(rotated_x_object, object_count);

    // Rotation around Y-axis: Rotate the object around the Y-axis
    int rotation_y_matrix[4][4] = {
        {0, 0, 1, 0},
        {0, 1, 0, 0},
        {-1, 0, 0, 0},
        {0, 0, 0, 1}
    };
    Point3D rotated_y_object[8];
    for (int i = 0; i < object_count; i++) {
        rotated_y_object[i] = original_object[i];
    }
    transform(rotated_y_object, object_count, rotation_y_matrix);
    draw(rotated_y_object, object_count);

    // Parallel Projection: Project the object onto the parallel plane
    int parallel_projection_matrix[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 1}
    };
    Point3D parallel_projected_object[8];
    for (int i = 0; i < object_count; i++) {
        parallel_projected_object[i] = original_object[i];
    }
    transform(parallel_projected_object, object_count, parallel_projection_matrix);
    draw(parallel_projected_object, object_count);

    // Perspective Projection: Project the object with perspective
    int perspective_projection_matrix[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, -1/200, 0}
    };
    Point3D perspective_projected_object[8];
    for (int i = 0; i < object_count; i++) {
        perspective_projected_object[i] = original_object[i];
    }
    transform(perspective_projected_object, object_count, perspective_projection_matrix);
    draw(perspective_projected_object, object_count);

    getch();
    closegraph();
    return 0;
}
