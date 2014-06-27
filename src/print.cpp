#ifndef _PRINT_
#define	_PRINT_
 ///Functions handling a predefined list with printing a spreadsheet.
/**
 * @file print.cpp
 * @author 	Firuz Ibragimov, <ibragfir@fit.cvut.cz>
 * @date	19.06.2013 
 *
 */

 #include <ncurses.h>

void print_numbers(){
	///draws y coordinates
	int y=1;
	move(y,0);
	for(int c=0;c<=20;c++){
		printw ("%d",c);
		move(++y,0);
		refresh();
	}
	y=1;
	while(y<=21){
		mvchgat(y,0,2,A_STANDOUT,1,NULL);
		++y;
	}	
	refresh();
}
void print_bar(){
	///draws help bar
	move(0,70);
	printw("Help bar:");
	mvprintw(1,63,	"ABS()-absolute value,				example: ABS(5-10) will return 5");
	mvprintw(2,63,	"AVG()-average value, 				example: AVG(1,2,3) will return 2");
	mvprintw(3,63,	"COS()-cosine value,  				example: COS(1) will return 0.5");
	mvprintw(5,63,	"FAC()-factorial value, 				example: FAC(4) will return 24");
	mvprintw(6,63,	"LOG()-natural logarithm value,			example: LOG(5) will return 1.6");
	mvprintw(10,63,	"SQR()-square root value,				example: SQR(9) will return 3");
	mvprintw(7,63,	"POW()-squared value,				example: POW(5) will return 25");
	mvprintw(4,63,	"TAN()-tangent value,				example: TAN(1) will return 1.6");
	mvprintw(9,63,	"SUM()-sum value,					example: SUM(1,2,3) will return 6");
	mvprintw(8,63,	"SIN()-sine value,				example: SIN(1) will return 0.8");
	mvprintw(26,50,	"press <F5> to exit");
}
void print_cmd(){
	///draws command and value lines
	move(23,0);
	clrtoeol();
	move(24,0);
	clrtoeol();
	mvprintw(23,0,"command: ");
	mvprintw(24,0,"value: ");
	refresh();
}
void print(){
	///draws x coordinates
	int x=2;
	int y=0;
	char ch='A';
	while(ch>='A' && ch<='F')
	{
		mvprintw(y,x+5,"%c",ch);
		x+=10;
		move(y,x);
		++ch;
		refresh();
	}
	mvchgat(0, 2, x-2, A_STANDOUT, 1, NULL);
	for(y=0;y<=21;y++)
		for(x=12;x<=62;x+=10)
		{	move(y,x);
			addch(ACS_VLINE);
		}
	refresh();	
	print_numbers();
	print_bar();
	print_cmd();
}
#endif	/* _PRINT_ */