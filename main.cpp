#include <iostream>
#include <cstdio> //this to use putch() FUNCTION
#include <windows.h>
#include <process.h>
#include <conio.h>
#include <string>
using namespace std;
const int global_width = 36;
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

        frame_zero = zero;
        frame_width = frame_zero + width;
        frame_height = frame_zero + height;
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
    for (x.set_point(frame_zero , frame_zero); x <= point(frame_width , frame_zero); x += point(1, 0))
    {
        x.gotoxy();
        putch('*');
    }

    //set the Right line of the frame
    //              Start               END
    for (x.set_point(frame_width  , frame_zero); x <= point(frame_width  , frame_height ); x += point(0, 1))
    {
        x.gotoxy();
        putch('*');
    }
    //set the Left line of the frame
    //              Start               END
    for (x.set_point(frame_zero , frame_zero); x <= point(frame_zero, frame_height ); x += point(0, 1))
    {
        x.gotoxy();
        putch('*');
    }
    //set the bottom line of the frame
    //              Start               END
    for (x.set_point(frame_zero , frame_height ); x <= point(frame_width , frame_height ); x += point(1, 0))
    {
        x.gotoxy();
        putch('*');
    }
    cout<<"\nPRESS |'w' hit blocks||'a' move left|"<<endl;
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
        destroyer_zero = zero;
        destroyer_left = zero + width / 2;
        destroyer_top = zero + height - 1;
        destroyer_width = zero + width;
        draw_destroyer();

    }

    /**@function void draw_destroyer
      *this function use to set the position of the
      *destroyer body '^' then put it
      */
    void draw_destroyer(){
        x.set_point( destroyer_left , destroyer_top );
        x.gotoxy();
        putch('^');
    }

    /**@function void delete_destroyer
      *the function which use to clear the old position of the destroyer body
      *before go to the new one
      */
    void delete_destroyer(){
        x.set_point( destroyer_left, destroyer_top);
        x.gotoxy();
        putch(' ');
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
    /**@function get_destroyer_left
      *this function used to
      *@return int destroyer_left
      */
    int get_destroyer_left(){
        return destroyer_left;
    }
};

class blocks{
    // blocks @param
    int blocks_height;
    int blocks_width;
    int blocks_left;
    int blocks_zero;
    int blocks_top;
    int correct_score;
    int wrong_score;
    char  blocks_sign;
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
        blocks_top = zero + 1;
        blocks_left = zero + 2;
        correct_score = 0; // the score initialize
        wrong_score = 0; //the wrong score initialize
        blocks_sign = '.';
        create_blocks();
        print_correct_score(); //print zero correct score before any action from the user
        print_wrong_score(); //print zero wrong score before any action from the user
    }

    /**@function void create_blocks
      *used to set the dynamic size of the rows arrays
      *and set the values with printing in the game screen
      */
    void create_blocks(){
        blocks_array_row_1 = new char[blocks_width]; //init first row array size
        blocks_array_row_2 = new char[blocks_width]; //init second row array size
        blocks_array_row_3 = new char[blocks_width]; //init third row array size
        int i; //for function counter

        /** this for first row in the blocks structure */
        for ( i = 0 ; i < blocks_width - 1 ; i++){
            if( i % 2){ //the shape function
                blocks_array_row_1 [i] = blocks_sign; //set element value
                if (blocks_array_row_1 [i] == blocks_sign){// check if index is set with value
                    x.set_point(i + blocks_zero , blocks_top + 1); // set its position
                    x.gotoxy(); //handle the coordinates
                    putch(blocks_sign); // print its sign
                }
            } else { // reverse shape function
                blocks_array_row_1 [i] =' '; // set empty element value
                //do nothing
            }
        }

        /** this for second row in the blocks structure */
        for ( i = 0 ; i < blocks_width - 1 ; i++){
            if(! (i % 2)){ //the shape function
                blocks_array_row_2 [i] = blocks_sign; //set element value
                if (blocks_array_row_2 [i] == blocks_sign){ // check if index is set with value
                    x.set_point(i + blocks_zero , blocks_top + 2); // set its position
                    x.gotoxy(); //handle the coordinates
                    putch(blocks_sign); // print its sign
                }
            } else { // reverse shape function
                blocks_array_row_2 [i] =' '; // set empty element value
                //do nothing
            }
        }

        /** this for third row in the blocks structure */
        for ( i = 0 ; i < blocks_width - 1 ; i++){
            if( i % 2){ //the shape function
                blocks_array_row_3 [i] = blocks_sign; //set element value
                if (blocks_array_row_3 [i] == blocks_sign){// check if index is set with value
                    x.set_point(i + blocks_zero , blocks_top + 3); // set its position
                    x.gotoxy(); //handle the coordinates
                    putch(blocks_sign); // print its sign
                }
            } else { // reverse shape function
                blocks_array_row_3 [i] =' '; // set empty element value
                //do nothing
            }
        }
    }

    /**@function void replace_blocks_element
      *used to replace the sign of an element with space
      */
    void replace_blocks_element(int destroyer_left, int row){
            x.set_point( destroyer_left , blocks_top + row); // set position
            x.gotoxy(); // go to the wanted position
            putch(' '); // replace the sign with empty space
            correct_score += 1; //update the score in positive
            print_correct_score();
          //  Beep(900 * 1 / row , 300 * 1 / row); // destroying sound variable with the row number
            cout << "\a";
    }

    void destroy_blocks_element(int destroyer_left){

            // destroy the third element if is set with a sign the return void
            if(blocks_array_row_3[destroyer_left - blocks_zero] == blocks_sign){ // check the sign in the row array
                blocks_array_row_3[destroyer_left - blocks_left] = ' '; //update the value with space 'empty'
                replace_blocks_element(destroyer_left , 3); //replacement function
                return; //void return
            }

            // destroy the third element if is set with a sign the return void
            if(blocks_array_row_2[destroyer_left - blocks_zero] == blocks_sign){ // check the sign in the row array
                blocks_array_row_2[destroyer_left - blocks_left] = ' '; //update the value with space 'empty'
                replace_blocks_element(destroyer_left , 2); //replacement function
                return; //void return
            }

            // destroy the third element if is set with a sign the return void
            if(blocks_array_row_1[destroyer_left - blocks_zero] == blocks_sign){
                blocks_array_row_1[destroyer_left - blocks_left] = ' '; //update the value with space 'empty'
                replace_blocks_element(destroyer_left , 1); //replacement function
                return; //void return
            }
            wrong_score += 1; // update the wrong score in positive
            print_wrong_score();
            Beep(500,500); // warning sound
    }

    /**@function void print_blocks_score
      *this function used when an element from the block destroyed successfully
      */
    void print_correct_score(){
        // the text message
        x.set_point( blocks_width + 5 , blocks_height -1);
        x.gotoxy();
        puts(" Your score is : ");
        // the value message
        x.set_point( blocks_width + 1.5 * strlen(" Your score is :") , blocks_height-1);
        x.gotoxy();
        cout<<correct_score;
    }

      /**@function void print_wrong_score
      *this function used when no element from the block destroyed
      */
    void print_wrong_score(){
        // the text message
        x.set_point( blocks_width + 5 , blocks_height );
        x.gotoxy();
        puts(" Your wrong is : ");
        // the value message
        x.set_point( blocks_width + 1.5 * strlen(" Your wrong is :") , blocks_height);
        x.gotoxy();
        cout<<wrong_score;
    }
};

int main(int argc, char const *argv[]) {
    //the game frame set an object with the constants to draw
    frame game_frame( global_width , global_height, global_zero );

    //object from destroyer
    destroyer game_destroyer( global_width , global_height, global_zero );

    //start the action
    blocks game_blocks(global_width,global_zero);

    char game_action; //used to sort the user action
    bool game_continue = TRUE; //the non quite variable
    while( game_continue ){ //check the user need to continue
        game_action = getch(); // get the action cat from the user
        //check the action
        if(game_action == 'a'){ // this to move left
            game_destroyer.move_destroyer_left();
        }

         if(game_action == 'd'){ // this to move right
            game_destroyer.move_destroyer_right();
        }

        if(game_action == 'q'){ // this to exit the game
            game_continue = FALSE; //QUITE
        }

        if(game_action =='w'){//destroy block element
            game_blocks.destroy_blocks_element(game_destroyer.get_destroyer_left());
        }

        if(game_action =='r'){ // reload the the game blocks
            game_blocks.create_blocks();
            game_destroyer.delete_destroyer();
            game_destroyer.draw_destroyer();
        }
    }

    system("cls"); //clear the screen
    cout << "you just exit it,thank you ."; // goodbye statement
    system("pause"); //this to controlled pause

    return 0;
}
/*just note in a git commit */
