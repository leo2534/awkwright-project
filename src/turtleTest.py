import turtle
import random
global turtleLocations
turtleLocations = []
global turtlePath
turtlePath = []
def middleClick(x,y):
    turtle.undo()
    if len(turtlePath) > 0:
    
        turtlePath.pop()
        line.undo()
        line.undo()
        line.undo()
    else:
        print("hi")
        print("No lines to remove")
    print(turtlePath)
    
def rightClick(x,y):
    if len(turtlePath) > 0:
        turtlePath.append([x,y])
        print(turtlePath)
        length = len(turtlePath)
        line.teleport(turtlePath[length-2][0], turtlePath[length-2][1])
        line.goto(turtlePath[length-1][0], turtlePath[length-1][1])
    else:
        turtlePath.append([x,y])
        print(turtlePath)
global screensize
screensize = 1000

t= turtle.Turtle("circle")
t.speed("fastest")
t.shapesize(0.3,0.3,0.3)
screen=turtle.Screen()
screen.setup(screensize, screensize)
screen.screensize(screensize, screensize)
screen.bgcolor("green")

line = turtle.Turtle()
line.speed("fastest")
line.ht()

def move_handler(x, y):
    #if state != MOVING:  # ignore stray events
        #return

    onmove(screen, None)  # avoid overlapping events
    t.penup()
    t.goto(x, y)
    onmove(screen, move_handler)


def onmove(self, fun, add=None):

        if fun is None:
            self.cv.unbind('<motion>')
        else:

            def eventfun(event):
                fun(self.cv.canvasx(event.x), -self.cv.canvasy(event.y))
            self.cv.bind('<Motion>', eventfun, add)
            
def leftClick(x,y):
    global turtlePath
    if len(turtlePath) > 0:
        turtleLocations.append(turtlePath)
    turtlePath = []
    line.penup()
    line.goto(x,y)
    line.pendown()
    print(turtleLocations)


def setup(width, height, vieww, viewh):
    with open("C:/Users/PughL14/OneDrive - Hutchesons' Grammar School/ICT/Co-curricular programming/visual studio/projects/arkwright/files/mySVG.svg", "a") as f:
        
        f.write('\n<svg width="' + str(width) + 'px" height="' + str(height) + 'px" viewBox="0 0 ' + str(vieww) + ' ' + str(viewh) + '" xmlns="http://www.w3.org/2000/svg">')
        f.close()
        
        
def end():
    with open("C:/Users/PughL14/OneDrive - Hutchesons' Grammar School/ICT/Co-curricular programming/visual studio/projects/arkwright/files/mySVG.svg", "a") as f:
        f.write('\n</svg>')
        f.close

class point():
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
class path():
    def __init__(self, moveto, lineto):
        self.moveto = moveto
        self.lineto = lineto

def clearSVG():
    with open("C:/Users/PughL14/OneDrive - Hutchesons' Grammar School/ICT/Co-curricular programming/visual studio/projects/arkwright/files/mySVG.svg", "w") as f:
        f.write("")
        f.write('<?xml version="1.0" encoding="utf-8"?>')

def data(fill_rule, clip_rule, fill, inner_path, outer_path):
    with open("C:/Users/PughL14/OneDrive - Hutchesons' Grammar School/ICT/Co-curricular programming/visual studio/projects/arkwright/files/mySVG.svg", "a") as f:
        f.write('\n<path fill-rule="'+ str(fill_rule) + '" clip-rule="'+ str(clip_rule) +'" d="M ' + str(outer_path.moveto.x) + ' '  +  str(outer_path.moveto.y))
        for line in outer_path.lineto:
            f.write(' L '+ str(line.x) + ' ' + str(line.y))
        f.write('  M ' + str(inner_path.moveto.x) + ' ' + str(inner_path.moveto.y))
        for line in inner_path.lineto:
            f.write(' L '+ str(line.x) + ' ' + str(line.y))
            print("writing")
        f.write(' " fill="'+ str(fill) +'" style="fill:none;stroke:green;stroke-width:3" />')




def finish():
    
    print("finsih")
    clearSVG()
    print("cleared svg")
    print(turtleLocations)
    print(turtlePath)
    setup(2000,2000,2000,2000)
    print(turtleLocations)
    for paths in turtleLocations:
        
        print(paths)
        moveto = point(paths[0][0]+1000, (-paths[0][1]+1000))
        pointsList = [moveto]
        print(moveto.x)
        print(moveto.y)
        for points in paths[1:]:
            print(points)
            pointsList.append(point(points[0]+1000,(-points[1]+1000)))
        print(pointsList)
        
        
        pointList = path(moveto, pointsList)
        print([path(point(0,0), [point(0,0)])])
        print(pointList)
        data("nonzero", "nonzero", "none", path(point(0,0), [point(0,0)]), pointList)
        
    end()

def clearScreen():
    line.reset()
    line.speed("fastest")
    while turtleLocations:
        turtleLocations.pop()
    while turtlePath:
        turtlePath.pop()
        print("pop")
    
    print("return")
    print(turtleLocations)
    print(turtlePath)
    
turtle.onscreenclick(middleClick, 2)
turtle.onscreenclick(None)
#turtle.ondrag(turtle.goto)
print("running")
turtle.onscreenclick(rightClick, 3)
turtle.onscreenclick(None)
turtle.onscreenclick(leftClick)
onmove(screen, move_handler)
turtle.onkeypress(finish, "Up")
turtle.onkeypress(None)
turtle.onkeypress(clearScreen, "c")
turtle.onkeypress(None)
turtle.listen()
screen.listen()
screen.mainloop()
     
