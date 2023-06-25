import tkinter as tk

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

def apply_transformation(points, transformation_matrix):
    transformed_points = []
    for point in points:
        # Convert point to homogeneous coordinates
        homogeneous_point = [point.x, point.y, 1]

        # Apply transformation matrix to the homogeneous point
        transformed_point = [0, 0, 0]
        for i in range(3):
            for j in range(3):
                transformed_point[i] += transformation_matrix[i][j] * homogeneous_point[j]

        # Convert back to Cartesian coordinates
        transformed_x = transformed_point[0] / transformed_point[2]
        transformed_y = transformed_point[1] / transformed_point[2]

        transformed_points.append(Point(transformed_x, transformed_y))

    return transformed_points

def draw_object(points, color):
    num_points = len(points)
    for i in range(num_points):
        p1 = points[i]
        p2 = points[(i + 1) % num_points]
        canvas.create_line(p1.x, p1.y, p2.x, p2.y, fill=color, width=2)

# Create a Tkinter window
window = tk.Tk()
window.title("2D Transformations")

# Create a Canvas widget
canvas = tk.Canvas(window, width=500, height=500)
canvas.pack()

# Define the original object vertices in counterclockwise order
original_object = [
    Point(100, 100),
    Point(200, 100),
    Point(200, 200),
    Point(100, 200)
]

# Define the transformation matrix for translation
translation_matrix = [
    [1, 0, 50],
    [0, 1, 50],
    [0, 0, 1]
]

# Apply translation to the object
translated_object = apply_transformation(original_object, translation_matrix)

# Draw the translated object
draw_object(translated_object, 'blue')

# Define the transformation matrix for scaling
scaling_matrix = [
    [2, 0, 0],
    [0, 2, 0],
    [0, 0, 1]
]

# Apply scaling to the object
scaled_object = apply_transformation(original_object, scaling_matrix)

# Draw the scaled object
draw_object(scaled_object, 'red')

# Define the transformation matrix for rotation
import math

theta = math.radians(45)  # Rotate by 45 degrees
rotation_matrix = [
    [math.cos(theta), -math.sin(theta), 0],
    [math.sin(theta), math.cos(theta), 0],
    [0, 0, 1]
]

# Apply rotation to the object
rotated_object = apply_transformation(original_object, rotation_matrix)

# Draw the rotated object
draw_object(rotated_object, 'green')

# Start the Tkinter event loop
window.mainloop()
