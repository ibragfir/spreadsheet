/**
 * @file 	сell.cpp
 * @author 	Firuz Ibragimov, <ibragfir@fit.cvut.cz>
 * @date	19.06.2013 
 */
#include <cstring>
#include <ncurses.h>
#include <cstdlib>
#include <cmath>
#include <utility>
#include "cell.h"

Cell::Cell(){///Constructor, sets the "flag" value and the "is_str" value to false.
	flag=false;
	is_str=false;
}
Cell::~Cell 		(){/**Destructor(empty).*/}
void 	Cell::set_yx		(int y,int x){///sets an y and x coordinates
		m_y=y;
		m_x=x;
}
void 	Cell::delete_all 	(){///deletes the cell and cleans all the values
	m_formula.clear();
	m_str.	  clear();
	flag    = false;
	is_str  = false;
	m_value = 0;
}
bool 	Cell::this_cell		(int y,int x)const{
/**@returns true if the given coordinates are converged with coordinates of a cell, otherwise false*/ 
	return (m_y==y && m_x==x);
}
bool 	Cell::changed		()const{
	return flag;/// @returns true if the cell has been edited, otherwise false
}
std::string Cell::get_string()const{
	return m_str;///@returns a string value of the cell
}
double 	Cell::get_value		()const{
	return (flag) ? m_value : 0;///@returns double value of the cell if the cell has been edited, otherwise returns 0
}
void	Cell::add_formula	(const std::list<char>& formula ){
	m_formula=formula;///adds an expression
}
void 	Cell::set_value		(double val){
	/**if a user adds just a number (not an expresssion) sets the value to a given number, flag to true,
	   is_str to false and erases a linked list with formula*/
	m_value=val;
	flag=true;	
	is_str=false;
	m_str.clear();
}
void	Cell::set_value 	(const std::string& val){
	/**if a user adds just a string (not an expresssion) sets the m_str to a given string, flag to true,
	   is_str to true and erases a linked list with formula*/
	m_str=val;
	flag=true;
	is_str=true;
	m_formula.clear();
}
bool 	Cell::is_string		()const{
	///@returns true if cell's value is just a string, otherwise false
	return is_str;
}
std::list<char> Cell::get_formula()const{
	///@returns a linked list with a formula to recalculate
	return m_formula;
}