import turtle
def draw(r):
    for i in range(2):
        turtle.circle(r,90)
        turtle.circle(r/2,90)
    turtle.seth(-45)
draw(100)