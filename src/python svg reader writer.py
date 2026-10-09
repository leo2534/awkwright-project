class point():
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
class path():
    def __init__(self, moveto, lineto):
        self.moveto = moveto
        self.lineto = lineto


def setup(width, height, vieww, viewh):
    with open("files/mySVG.svg", "w") as f:
        f.seek(0)
        f.write('<?xml version="1.0" encoding="utf-8"?>')
        
        f.write('\n<svg width="' + str(width) + 'px" height="' + str(height) + 'px" viewBox="0 0 ' + str(vieww) + ' ' + str(viewh) + '" xmlns="http://www.w3.org/2000/svg">')
        f.close()
        
def data(fill_rule, clip_rule, fill, inner_path, outer_path):
    with open("files/mySVG.svg", "a") as f:
        f.write('\n<path fill-rule="'+ str(fill_rule) + '" clip-rule="'+ str(clip_rule) +'" d="M ' + str(outer_path.moveto.x) + ' '  +  str(outer_path.moveto.y))
        for line in outerLine:
            f.write(' L '+ str(line.x) + ' ' + str(line.y))
        f.write(' Z M ' + str(inner_path.moveto.x) + ' ' + str(inner_path.moveto.y))
        for line in innerLine:
            f.write(' L '+ str(line.x) + ' ' + str(line.y))
        f.write(' Z" fill="'+ str(fill) +'"/>')
# + ' L '+str(outer_path.lineto[0].x)+' '+str(outer_path.lineto[0].y)+' L '+str(outer_path.lineto[1].x)+' '+str(outer_path.lineto[1].y)+' L '+str(outer_path.lineto[2].x)+' '+str(outer_path.lineto[2].y)+' L '+str(outer_path.lineto[3].x)+' '+str(outer_path.lineto[3].y)+' Z M '+str(inner_path.moveto.x)+' '+str(inner_path.moveto.y)+' L '+str(inner_path.lineto[0].x)+' '+str(inner_path.lineto[0].y)+' L '+str(inner_path.lineto[1].x)+' '+str(inner_path.lineto[1].y)+' L '+str(inner_path.lineto[2].x)+' '+str(inner_path.lineto[2].y)+' L '+str(inner_path.lineto[3].x)+' '+str(inner_path.lineto[3].y)+' Z" fill="'+ str(fill) +'"/>')

        f.close

def end():
    with open("files/mySVG.svg", "a") as f:
        f.write('\n</svg>')
        f.close
ip1 = point(3,3)
ip2 = point(3,7)
ip3 = point(7,7)
ip4 = point(7,3)
ip5 = point(5,5)

op1 = point(8,2)
op2 = point(8,8)
op21 = point(6.5,7)
op22 = point(6.5, 4.5)
op23 = point(5, 6)
op24 = point(3.5,4.5)
op25 = point(3.5, 7)
op3 = point(2,8)
op4 = point(2,2)
innerLine = [ip1,ip2,op21,op22,op23,op24,op25,ip3,ip4, ip5]
outerLine = [op1,op2,op3,op4]

startInner = innerLine[len(innerLine)-1]
startOuter = outerLine[len(outerLine)-1]

for i in enumerate(innerLine):
    
    pathInner = path(startInner,innerLine)
    pathOuter = path(startOuter, outerLine)
print(str(pathOuter.moveto.x))
print("path")
print(pathInner.lineto)
print(pathInner.moveto)

setup(800, 800, 24, 24)
data("even-odd","even-odd", "#ff00ff",pathInner, pathOuter)
end()


with open("files/mySVG.svg", "r") as f:
    print(f.read())
