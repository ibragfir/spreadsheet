/**
 * @file main.cpp
 * @author 	Firuz Ibragimov, <ibragfir@fit.cvut.cz>
 * @date	19.06.2013 
 */

#include <ncurses.h>
#include "sheet.cpp"
using namespace std;


int main(int argc, char *argv[]){
	initscr();			/* Start curses mode 		*/
	keypad(stdscr, TRUE);
	int ch;
	Sheet sheet;
	sheet.set_yx();
	sheet.print();
	int a=1;
	int b=3;
	move(a,b);
	noecho();
	/*
	* in this loop user moves among the cells to add an expression/value to specific place,
	* if the ENTER key is typed, cell is chosen. F5 key finishes the program 
	*/
	while((ch = getch()) != KEY_F(5))								 
	{	switch(ch)
		{	case KEY_LEFT://left key pressed, moves one cell left
				sheet.print_cmd();//prints a command and value line 
				move(a,b);
				if(b>=11){
					b-=10;
					move(a,b);
				}
				sheet.print_val_formula(a,b);//prints an expression inserted by a user and a calculated value of a specific cell
				move(a,b);
				break;
			case KEY_RIGHT://right key pressed, moves one cell right
				sheet.print_cmd();
				move(a,b);
				if(b<50){
					b+=10;
					move(a,b);
				}
				sheet.print_val_formula(a,b);
				move(a,b);
				break;
			case KEY_UP://up key pressed, moves one cell up
				sheet.print_cmd();
				move(a,b);
				if(a>1)
					move(--a,b);
				sheet.print_val_formula(a,b);
				move(a,b);
				break;
			case KEY_DOWN://down key pressed, moves one cell down
				sheet.print_cmd();
				move(a,b);
				if(a<21)
					move(++a,b);
				sheet.print_val_formula(a,b);
				move(a,b);
				break;
				case KEY_DC://del key pressed, deletes the cell and frees an allocated memory
				sheet.delete_cell(a,b);
				sheet.evaluate_in_order();
				move(a,b);
				refresh();
				break;
			case 10://enter key, cell is chosen
				echo();
				sheet.get_expr(a,b);//gets an expression/string from a user
				sheet.evaluate_in_order();//evaluates all the cells in order they were added
				move(a,b);
				noecho();			
				break;
		}
	}
	endwin();/* End curses mode 		*/
	return 0;
}
