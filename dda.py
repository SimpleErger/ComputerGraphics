from matplotlib import pyplot as plt
def dda(x1,y1,x2,y2):
    dx=abs(x1-x2)
    dy=abs(y1-y2)
    steps=max(dx,dy)
    xinc=dx/steps
    yinc=dy/steps
    x=float(x1)
    y=float(y1)
    x_coordinates=[]
    y_coordinates=[]
    for i in range(steps):
        x_coordinates.append(x)
        y_coordinates.append(y)
        x=x+xinc
        y=y+yinc
        plt.plot(x_coordinates,y_coordinates,marker="o",markersize=1,markerfacecolor="green")
        plt.show()
if __name__=="__main__":
    x1,y1=20,20
    x2,y2=60,50
    dda(x1,y1,x2,y2)