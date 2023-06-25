class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

def compute_intersection(p1, p2, edge):
    edge_start, edge_end = edge
    d1 = (p1.x - edge_start.x) * (edge_end.y - edge_start.y) - (p1.y - edge_start.y) * (edge_end.x - edge_start.x)
    d2 = (p2.x - edge_start.x) * (edge_end.y - edge_start.y) - (p2.y - edge_start.y) * (edge_end.x - edge_start.x)

    if d1 * d2 < 0:
        dx = p2.x - p1.x
        dy = p2.y - p1.y
        u = abs(d1) / (abs(d1) + abs(d2))
        return Point(p1.x + u * dx, p1.y + u * dy)

def clip_polygon(subject_polygon, clip_window):
    output_polygon = subject_polygon

    for edge in clip_window:
        input_polygon = output_polygon
        output_polygon = []

        s = input_polygon[-1]
        for p in input_polygon:
            if is_inside(p, edge):
                if not is_inside(s, edge):
                    output_polygon.append(compute_intersection(s, p, edge))
                output_polygon.append(p)
            elif is_inside(s, edge):
                output_polygon.append(compute_intersection(s, p, edge))
            s = p

    return output_polygon

def is_inside(point, edge):
    edge_start, edge_end = edge
    return (edge_end.x - edge_start.x) * (point.y - edge_start.y) > (edge_end.y - edge_start.y) * (point.x - edge_start.x)

# Define the polygon vertices in counterclockwise order
subject_polygon = [
    Point(0, 0),
    Point(50, 0),
    Point(50, 50),
    Point(0, 50)
]

# Define the rectangular window vertices in counterclockwise order
clip_window = [
    (Point(10, 10), Point(40, 10)),
    (Point(40, 10), Point(40, 40)),
    (Point(40, 40), Point(10, 40)),
    (Point(10, 40), Point(10, 10))
]

clipped_polygon = clip_polygon(subject_polygon, clip_window)

print("Clipped Polygon:")
for p in clipped_polygon:
    print(f"({p.x}, {p.y})")
