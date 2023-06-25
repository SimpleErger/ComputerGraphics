import tkinter as tk

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

def scanline_fill(polygon):
    ymin = min(point.y for point in polygon)
    ymax = max(point.y for point in polygon)

    active_edges = []
    scanline = ymin

    while scanline <= ymax:
        for i in range(len(polygon)):
            p1 = polygon[i]
            p2 = polygon[(i + 1) % len(polygon)]

            if p1.y < p2.y:
                y_low = p1.y
                y_high = p2.y
                x_low = p1.x
                x_high = p2.x
            else:
                y_low = p2.y
                y_high = p1.y
                x_low = p2.x
                x_high = p1.x

            if y_low <= scanline < y_high or (y_low == scanline == y_high):
                if y_high != y_low:
                    x_intersect = x_low + (x_high - x_low) * (scanline - y_low) / (y_high - y_low)
                else:
                    x_intersect = x_low

                active_edges.append(x_intersect)

        active_edges.sort()

        if len(active_edges) % 2 == 1:
            active_edges = active_edges[:-1]

        for i in range(0, len(active_edges), 2):
            x_start = int(active_edges[i])
            x_end = int(active_edges[i + 1])

            canvas.create_line(x_start, scanline, x_end, scanline, fill='red')

        scanline += 1
        active_edges = []

# Create a Tkinter window
window = tk.Tk()
window.title("Polygon Fill")

# Create a Canvas widget
canvas = tk.Canvas(window, width=500, height=500)
canvas.pack()

# Define the polygon vertices in counterclockwise order
polygon = [
    Point(100, 100),
    Point(300, 100),
    Point(250, 200),
    Point(200, 300),
    Point(150, 200)
]

# Call the scanline_fill function to fill the polygon
scanline_fill(polygon)

# Start the Tkinter event loop
window.mainloop()
