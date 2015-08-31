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
    int width;
    int height;
    int zero;
public:
    frame ()
    {
        width = global_width ;
        height = global_height;
        zero = global_zero;
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
	for (x.set_point(zero, zero); x <= point(width, zero); x += point(1, 0))
	{
		x.gotoxy();
		puts("*");
	}

    //set the Right line of the frame
    //              Start               END
	for (x.set_point(width, zero); x <= point(width, height); x += point(0, 1))
	{
		x.gotoxy();
        puts("*");
	}
    //set the bottom line of the frame
    //              Start               END
	for (x.set_point(zero,height); x <= point(width, height); x += point(1, 0))
	{
		x.gotoxy();
		puts("*");
	}
    //set the Left line of the frame
    //              Start               END
	for (x.set_point(zero,zero); x <= point(zero, height); x += point(0, 1))
	{
		x.gotoxy();
		puts("*");
	}
	cout<<"PRESS |'w' hit blocks||'a' move left|"<<endl;
	cout<<"      |'d' move right||'r' reload blocks|"<<endl;
	cout<<"      |'q' Quite"<<endl;
}

};

int main(int argc, char const *argv[]) {
    frame game_frame;
    game_frame.draw_frame();
    return 0;
}
