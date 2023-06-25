import tkinter as tk

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

def calculate_point(p0, p1, p2, p3, t):
    # Calculate the coordinates of a point on the Bezier curve at parameter t
    x = (1 - t) ** 3 * p0.x + 3 * (1 - t) ** 2 * t * p1.x + 3 * (1 - t) * t ** 2 * p2.x + t ** 3 * p3.x
    y = (1 - t) ** 3 * p0.y + 3 * (1 - t) ** 2 * t * p1.y + 3 * (1 - t) * t ** 2 * p2.y + t ** 3 * p3.y
    return Point(x, y)

def draw_curve(p0, p1, p2, p3):
    # Draw the Bezier curve using a series of line segments
    for i in range(num_segments):
        t0 = i / num_segments
        t1 = (i + 1) / num_segments
        p_start = calculate_point(p0, p1, p2, p3, t0)
        p_end = calculate_point(p0, p1, p2, p3, t1)
        canvas.create_line(p_start.x, p_start.y, p_end.x, p_end.y, fill='blue', width=2)

window = tk.Tk()
window.title("Bezier Curve")

canvas = tk.Canvas(window, width=500, height=500)
canvas.pack()

# Define the control points of the Bezier curve
p0 = Point(100, 100)
p1 = Point(200, 400)
p2 = Point(300, 100)
p3 = Point(400, 400)

num_segments = 100

# Draw the Bezier curve
draw_curve(p0, p1, p2, p3)

window.mainloop()
