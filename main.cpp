#include <iostream>
#include <cstdio> //this to use puts() FUNCTION
#include <windows.h>
#include <process.h>
#include <conio.h>
#include <string>
using namespace std;
const int global_width=50;
const int global_height=25;
const int global_zero=0;
/**
 *@class point
 *which use to handle the console area
 *int X , Y
 */
class point
{
	int x, y;
public:
    point(int u=0, int v=0) // u&v initializing values when creating new object without setting constructor parameters
	{
		set_point(u,v); //the
	}

    /** this function to set the x and y of the point position
      * @para int u >> X axis
      * @para int v >> Y axis
      */
	void set_point(int u, int v)
	{
		x = u;
		y = v;
	}

    //system function to set position with co-ordinates
	void gotoxy()
	{//function definition
		HANDLE hConsoleOutput;
		COORD dwCursorPosition;
		cout.flush();
		dwCursorPosition.X = x;
		dwCursorPosition.Y = y;
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
	}

    //set operator
	int operator <= (point p){ return (x <= p.x && y <= p.y); }
	int operator >= (point p){ return (x >= p.x && y >= p.y); }
	point operator += (point p){ return point(x += p.x, y += p.y); }
};
/**
  * @class frame
  * the game frame
  */
class frame
{
    // frame variables
    int frame_width;
    int frame_height;
    int frame_zero;
public:
    frame ()
    {
        frame_width = global_width ;
        frame_height = global_height;
        frame_zero = global_zero;
    }
/**
 * This function to draw the frame game using class point
 */
void draw_frame()
{
    system("cls");
    point x;    //new object from point class  NOTE without constructor parameter because it's set default.
    //set the top line of the frame
    //              Start               END
	for (x.set_point(frame_zero, frame_zero); x <= point(frame_width, frame_zero); x += point(1, 0))
	{
		x.gotoxy();
		puts("*");
	}

    //set the Right line of the frame
    //              Start               END
	for (x.set_point(frame_width, frame_zero); x <= point(frame_width, frame_height); x += point(0, 1))
	{
		x.gotoxy();
        puts("*");
	}
    //set the bottom line of the frame
    //              Start               END
	for (x.set_point(frame_zero,frame_height); x <= point(frame_width, frame_height); x += point(1, 0))
	{
		x.gotoxy();
		puts("*");
	}
    //set the Left line of the frame
    //              Start               END
	for (x.set_point(frame_zero,frame_zero); x <= point(frame_zero, frame_height); x += point(0, 1))
	{
		x.gotoxy();
		puts("*");
	}
	cout<<"PRESS |'w' hit blocks||'a' move left|"<<endl;
	cout<<"      |'d' move right||'r' reload blocks|"<<endl;
	cout<<"      |'q' Quite"<<endl;
}
};

class destroyer{
    //destroyer properties
    int destroyer_width;
    int destroyer_bodyLeft;
    int destroyer_bodyTop;
    int destroyer_zero;
public:
    destroyer(){
        destroyer_bodyLeft = global_width / 2;
        destroyer_bodyTop = global_height - 1;
        destroyer_width = global_width;
        destroyer_zero = global_zero;
    }
    point x; // public object for the coordinates  X  Y

    /**@function void draw_destroyer
      *this function use to set the position of the
      *destroyer body '^' then put it
      */
    void draw_destroyer()
    {
        x.set_point( destroyer_bodyLeft , destroyer_bodyTop );
        x.gotoxy();
        puts("^");
    }

    /**@function void delete_destroyer
      *the function which use to clear the old position of the destroyer body
      *before go to the new one
      */
    void delete_destroyer()
    {
        x.set_point( destroyer_bodyLeft, destroyer_bodyLeft);
        x.gotoxy();
        puts(" ");
    }

    /**
      *this function to move the body to right
      *at the new position setting
      */
    void move_destroyer_right()
    {
        if(destroyer_left < destroyer_width-1)
        {
            delete_destroyer();
            x.set_point(bodyLeft+1, bodyTop);
            x.gotoxy();
            puts("i");
            bodyLeft=bodyLeft+1;
        }
    }

    /**
     *this function to move the body to left
     *at the new position setting
     */
    void moveLeft()
    {
        if(bodyLeft > zero+1)
        {
            deleteBody();
            x.set_point(bodyLeft-1, bodyTop);
            x.gotoxy();
            puts("i");
            bodyLeft=bodyLeft-1;
        }
    }

    void killElement()
    {
        for(int i=2;i<2+3;i++)
        {
            x.set_point(bodyLeft, i);
            x.gotoxy();
            puts(" ");
        }
    }
};

int main(int argc, char const *argv[]) {
    frame game_frame;
    game_frame.draw_frame();
    return 0;
}
