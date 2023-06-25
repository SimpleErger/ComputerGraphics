import matplotlib.pyplot as plt

def bresenham_line(x0, y0, x1, y1):
    dx = abs(x1 - x0)
    dy = abs(y1 - y0)
    steep = dy > dx
    if steep:
        x0, y0 = y0, x0
        x1, y1 = y1, x1
        dx, dy = dy, dx
    if x0 > x1:
        x0, x1 = x1, x0
        y0, y1 = y1, y0
    y = y0
    y_step = 1 if y0 < y1 else -1
    error = dx / 2
    line_points = []
    for x in range(x0, x1 + 1):
        line_points.append((y, x) if steep else (x, y))
        error -= dy
        if error < 0:
            y += y_step
            error += dx
    return line_points

# Define the line coordinates
x0, y0 = 2, 2
x1, y1 = 14, 9

# Compute the line points using Bresenham's algorithm
line_points = bresenham_line(x0, y0, x1, y1)

# Plot the line
plt.plot([point[0] for point in line_points], [point[1] for point in line_points], marker='o')

# Set the plot limits and labels
plt.xlim(min(x0, x1) - 1, max(x0, x1) + 1)
plt.ylim(min(y0, y1) - 1, max(y0, y1) + 1)
plt.xlabel('X')
plt.ylabel('Y')

# Display the plot
plt.show()
