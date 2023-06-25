import tkinter as tk

class Point3D:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

def transform(points, matrix):
    return [Point3D(matrix[0][0] * p.x + matrix[0][1] * p.y + matrix[0][2] * p.z + matrix[0][3],
                    matrix[1][0] * p.x + matrix[1][1] * p.y + matrix[1][2] * p.z + matrix[1][3],
                    matrix[2][0] * p.x + matrix[2][1] * p.y + matrix[2][2] * p.z + matrix[2][3])
            for p in points]

def draw(points, color):
    for i in range(len(points)):
        p1 = points[i]
        p2 = points[(i + 1) % len(points)]
        canvas.create_line(p1.x, p1.y, p2.x, p2.y, fill=color, width=2)

window = tk.Tk()
window.title("3D Transformations and Projections")

canvas = tk.Canvas(window, width=500, height=500)
canvas.pack()

original_object = [
    Point3D(100, 100, 100), Point3D(200, 100, 100), Point3D(200, 200, 100), Point3D(100, 200, 100),
    Point3D(100, 100, 200), Point3D(200, 100, 200), Point3D(200, 200, 200), Point3D(100, 200, 200)
]

objects = [
    (original_object, 'blue', [[1, 0, 0, 50], [0, 1, 0, 50], [0, 0, 1, 50], [0, 0, 0, 1]]),  # Translation
    (original_object, 'red', [[2, 0, 0, 0], [0, 2, 0, 0], [0, 0, 2, 0], [0, 0, 0, 1]]),  # Scaling
    (original_object, 'green', [[1, 0, 0, 0], [0, 0.707, -0.707, 0], [0, 0.707, 0.707, 0], [0, 0, 0, 1]]),  # Rotation around X-axis
    (original_object, 'orange', [[0.707, 0, 0.707, 0], [0, 1, 0, 0], [-0.707, 0, 0.707, 0], [0, 0, 0, 1]]),  # Rotation around Y-axis
    (original_object, 'purple', [[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 0, 0], [0, 0, 0, 1]]),  # Parallel Projection
    (original_object, 'brown', [[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, -1 / 200, 0]])  # Perspective Projection
]

for obj, color, matrix in objects:
    transformed_object = transform(obj, matrix)
    draw(transformed_object, color)

window.mainloop()
