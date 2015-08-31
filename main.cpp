#include <iostream>
#include <cstdio> //this to use puts() FUNCTION
#include <windows.h>
#include <process.h>
#include <conio.h>
#include <string>
using namespace std;
/*
 *@class point
 *which use to handle the console area
 *in X , Y
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

int main(int argc, char const *argv[]) {
  return 0;
}
