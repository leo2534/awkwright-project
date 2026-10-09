#include <iostream>

void bresenham(int x1,int y1,int x2,int y2, bool swap=false, bool negativex=false){
    //*note: for steeper gradients do this
    //m=deltay/deltax
    //if(m<1) then swap x and y
    //if deltay>deltax then swap x and y

    //*note: for negative x do this
    //if x1>x2 then swap x1 and x2
    //and invert coordinates

    std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << std::endl;
    int dx=x2-x1;
    int dy=y2-y1;
    if(x1>x2){
        std::cout << "swap" << std::endl;
        bresenham(x2,y2,x1,y1, false, true);
        return;
    }
    if(dy>dx){
        std::cout << "steep gradient" << std::endl;
        bresenham(y1,x1,y2,x2, true);
        return;
    }
    if(x1>x2){
        std::cout << "swap" << std::endl;
        bresenham(x1,y1,x2,y2, false, true);
        return;
    }

    int D = 2*dy-dx;
    int y= y1;
    if(negativex){
        for(int x=x1;x>=x2;x--){
            if(D>0){
            y++;
            D=D-2*dx;
        }
        D=D+2*dy;
        if(swap){
            std::cout << y << " - " << x << std::endl;
        }
        else{
            std::cout << -x << " " << y << std::endl;
        }
        }
    }

    
    for(int x=x1;x<=x2;x++){
        if(swap){
            if (negativex){
                std::cout << y << " " << -x << std::endl;
            }
            else{
                std::cout << y << " - " << x << std::endl;
            }
        }
        else{
            if(negativex){
                std::cout << -x << " " << y << std::endl;
            }
            else{
                std::cout << x << " " << y << std::endl;
            }
        }
        if(D>0){
            y++;
            D=D-2*dx;
        }
        D=D+2*dy;
    }
}
int main(){
    int x1,y1,x2,y2;
    std::cout<<"Enter the first point"<<std::endl;
    std::cin>>x1>>y1;
    std::cout<<"Enter the second point"<<std::endl;
    std::cin>>x2>>y2;
    bresenham(x1,y1,x2,y2);
}