#include <iostream>
#include <cstdio> //this to use puts() FUNCTION
#include <windows.h>
#include <process.h>
#include <conio.h>
#include <string>
using namespace std;
const int global_width = 35;
const int global_height = 20;
const int global_zero = 0;
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
    point x;//new object from point class  NOTE without constructor parameter because it's set default.
public:
    //constructor
    frame (int width,int height,int zero){
        frame_width = width ;
        frame_height = height;
        frame_zero = zero;
        //draw the frame
        draw_frame();
    }
/**
 * This function to draw the frame game using class point
 */
void draw_frame()
{
    system("cls");
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
    int destroyer_left;
    int destroyer_top;
    int destroyer_zero;
    point x; // public object for the coordinates  X  Y
public:
    //constructor
    destroyer( int width , int height , int zero ) {
        destroyer_left = width / 2;
        destroyer_top = height - 1;
        destroyer_width = width;
        destroyer_zero = zero;
        draw_destroyer();

    }

    /**@function void draw_destroyer
      *this function use to set the position of the
      *destroyer body '^' then put it
      */
    void draw_destroyer(){
        x.set_point( destroyer_left , destroyer_top );
        x.gotoxy();
        puts("^");
    }

    /**@function void delete_destroyer
      *the function which use to clear the old position of the destroyer body
      *before go to the new one
      */
    void delete_destroyer(){
        x.set_point( destroyer_left, destroyer_top);
        x.gotoxy();
        puts(" ");
    }

    /**@function void move_destroyer_right
      *this function to move the body to right
      *at the new position setting
      */
    void move_destroyer_right(){
        //check the width between the destroyer body and the frame
        if(destroyer_left < destroyer_width - 1){
            delete_destroyer(); //clear the destroyer body for the new
            destroyer_left += 1 ; //update the destroyer_left property
            draw_destroyer(); //set the new one
        }
    }

    /**@function void move_destroyer_left
     *this function to move the body to left
     *at the new position setting
     */
    void move_destroyer_left(){
        //check the width between the destroyer body and the frame
        if(destroyer_left > destroyer_zero+1){
            delete_destroyer(); //clear the destroyer body for the new
            destroyer_left -= 1 ; //update the destroyer_left property
            draw_destroyer(); //set the new one
        }
    }
};

class blocks{
    // blocks @param
    int blocks_height;
    int blocks_width;
    int blocks_zero;
    int blocks_top;
    char* blocks_array_row_1;
    char* blocks_array_row_2;
    char* blocks_array_row_3;
    point x; // public object for the coordinates  X  Y
public:
    //constructor
    blocks(int width , int zero ){
        blocks_height = 3;
        blocks_width = width - 2;
        blocks_zero = zero + 2;
        blocks_top = zero + 2;
        draw_blocks();
    }

    void draw_blocks(){
        blocks_array_row_1 = new char[blocks_width];
        blocks_array_row_2 = new char[blocks_width];
        blocks_array_row_3 = new char[blocks_width];
    }

};

int main(int argc, char const *argv[]) {
    //the game frame set an object with the constants to draw
    frame game_frame( global_width , global_height, global_zero );

    //object from destroyer
    destroyer game_destroyer( global_width , global_height, global_zero );

    //start the action
    blocks game_blocks(global_width,global_zero);

    char game_action;
    while(TRUE){
        game_action = getch(); // get the action cat from the user
        //check the action
        if(game_action == 'a'){ // this to move left
            game_destroyer.move_destroyer_left();
        }
         if(game_action == 'd'){ // this to move right
            game_destroyer.move_destroyer_right();
        }
        if(game_action == 'q'){ // this to exit the game
            system("cls");
            cout << "you just exit it,thank you ";
            system("pause");
            break;
        }
    }
    return 0;
}
