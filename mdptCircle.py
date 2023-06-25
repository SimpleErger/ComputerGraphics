import matplotlib.pyplot as plt

def draw_circle(radius):
    x = 0
    y = radius
    d = 1 - radius

    plt.plot(x, y, 'ro')  # Plot the initial point

    while y > x:
        if d < 0:
            d += 2 * x + 3
        else:
            d += 2 * (x - y) + 5
            y -= 1
        x += 1

        # Plot the eight symmetric points
        plt.plot(x, y, 'ro')
        plt.plot(x, -y, 'ro')
        plt.plot(-x, y, 'ro')
        plt.plot(-x, -y, 'ro')
        plt.plot(y, x, 'ro')
        plt.plot(y, -x, 'ro')
        plt.plot(-y, x, 'ro')
        plt.plot(-y, -x, 'ro')

    plt.axis('equal')  # Set equal aspect ratio
    plt.show()  # Display the plot

# Usage example:
radius = 5                                                               
draw_circle(radius)
