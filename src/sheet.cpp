/**
 * @file sheet.cpp
 * @author 	Firuz Ibragimov, <ibragfir@fit.cvut.cz>
 * @date	19.06.2013 
 */
#include "sheet.h"
#include "cell.cpp"
#include "classes.cpp"
#define  v_y 24//y coordinate of value line
#define  v_x 8//x coordinate of value line
#define  c_y 23//y coordinate of command line
#define  c_x 8//x coordinate of command line
using namespace std;

				Sheet::Sheet			(){/**Constructor(empty).*/ }
				Sheet::~Sheet 			(){/**Destructor(empty).*/ }
bool			Sheet::splice_part		(list<char>& l_input,list<char>::iterator it,double& new_val,double& amount){
	/** removes a calculated part and evaluates the rest
	* @returns false if an error occurred, otherwise true.
	*/

	list<char> tmp_input;
	l_input.erase(l_input.begin(),it);
	it=l_input.begin();
	list<char>::iterator tmp=it;
	int bracket=1;
	++tmp;
	while(bracket!=0 && tmp!=l_input.end()){
		if(*tmp==',')
			amount++;
		else
			if(*tmp=='(')
			++bracket;
		else
			if(*tmp==')')
			--bracket;
		++tmp;
	}
	if(bracket)
		return false;
	tmp_input.splice(tmp_input.end(),l_input,it,tmp);
	if(!evaluate(tmp_input,new_val))
		return false;
	l_input.push_front(')');
	l_input.push_front('q');
	return true;
}
int 			Sheet::get_number		(list<char>& l_input,list<char>::iterator it,char digits[]){
	/** gets a number from linked list with an expression and returns an iterator pointed to a character next to token number*/
	int tmp=0;
	bool was_dot=false;
	while((*it>='0' && *it<='9') || *it=='.'){
		if(it==l_input.end())
			break;
		if(*it=='.'){
			if(was_dot)
				return tmp;
			was_dot=true;
		}
		digits[tmp]=*it;
		++it;
		++tmp;
	}
	return --tmp;
}
int 			Sheet::get_number2		(list<char>& l_input,list<char>::iterator it,char digits[]){
	/**the same function like get_number but this functions gets an integer, because cell with A1.1 id does not exist*/
	int tmp=0;
	while((*it>='0' && *it<='9') || *it=='.'){
		if(it==l_input.end())
			break;
		if(*it=='.')
			return tmp;
		digits[tmp]=*it;
		++it;
		++tmp;
	}
	return --tmp;
}
void 			Sheet::pop_two_num		(double &a,double &b,list<double>& nums){
	/**pops up to front numbers from a linked list with an expression to calculate*/
	a=nums.front();
	nums.pop_front();
	b=nums.front();
	nums.pop_front();
}
void			Sheet::add_value		(double new_val,const list<char>& l_formula,int y, int x){
	/**Searches a cell according to coordinates and adds a calculated value*/
	for(int i=0;i<=5;++i)
	for(int j=0;j<=20;++j)
		if(data[i][j].this_cell(y,x)){
			data[i][j].set_value(new_val);
			data[i][j].add_formula(l_formula);
			return;
		}
}
void			Sheet::add_value		(const std::string& new_val, int y, int x){
	/**Searches a cell according to coordinates and adds a string value*/
	for(int i=0;i<=5;++i)
	for(int j=0;j<=20;++j)
		if(data[i][j].this_cell(y,x)){
			data[i][j].set_value(new_val);
			return;
		}
}
bool			Sheet::avg_value   		(list<char>& l_input,list<char>::iterator it,double& new_val){
	/**finding out an average value.@returns false if syntax error occurred, otherwise true */
	double amount=1;
	double a;
	list<char>::iterator tmp_it=it;
	while(tmp_it!=l_input.end()){
		if(*tmp_it==','){
			amount++;
      		--tmp_it;
      		if((*tmp_it<'0' || *tmp_it>'9') && *tmp_it!=')')
      			return false;
      		advance(tmp_it,2);
      		if(*tmp_it=='T' || *tmp_it=='L' || *tmp_it=='P' || *tmp_it=='S' || (*tmp_it>='A' && *tmp_it<='F') || (*tmp_it>='0' && *tmp_it<='9')){
      			--tmp_it;
				tmp_it=l_input.erase (tmp_it);
				l_input.insert(tmp_it,'+');    			
      		}
      		else
      			return false;
      	}
      	++tmp_it;
    }
	if(!splice_part(l_input,it,new_val,a))
		return false;
	new_val=new_val/amount;
	return true;	
}
bool			Sheet::abs_value		(list<char>& l_input,list<char>::iterator it,double& new_val){
	/**finding out an absolute value.@returns false if syntax error occurred, otherwise true */
	double amount=1;
	if(!splice_part(l_input,it,new_val,amount))
		return false;
	new_val=abs(new_val);
	return true;	
}
bool			Sheet::cos_value		(list<char>& l_input,list<char>::iterator it,double& new_val){
	/**finding out a cosine value.@returns false if syntax error occurred, otherwise true */
	double amount=1;
	if(!splice_part(l_input,it,new_val,amount))
		return false;
	new_val=cos(new_val);
	return true;
}
bool			Sheet::fac_value		(list<char>& l_input,list<char>::iterator it,double& new_val){
	/**finding out a factorial value.@returns false if syntax error occurred, otherwise true */
	double amount=1;
	if(!splice_part(l_input,it,new_val,amount))
		return false;
	int tmp=new_val;
	new_val=1;
	while(tmp>1){
		new_val*=tmp;
		--tmp;
	}
	return true;
}	
bool			Sheet::tan_value		(list<char>& l_input,list<char>::iterator it,double& new_val){
	/**finding out a tangent value.@returns false if syntax error occurred, otherwise true */
	double amount=1;
	if(!splice_part(l_input,it,new_val,amount))
		return false;
	new_val=tan(new_val);
	return true;
}
bool			Sheet::log_value		(list<char>& l_input,list<char>::iterator it,double& new_val){
	/**finding out a natural logarithm value.@returns false if syntax error occurred, otherwise true */
	double amount=1;
	if(!splice_part(l_input,it,new_val,amount))
		return false;
	new_val=log(new_val);
	return true;
}
bool			Sheet::pow_value		(list<char>& l_input,list<char>::iterator it,double& new_val){
	/**finding out a squared value.@returns false if syntax error occurred, otherwise true */
	double amount=1;
	if(!splice_part(l_input,it,new_val,amount))
		return false;
	new_val*=new_val;
	return true;
} 
bool			Sheet::sin_value		(list<char>& l_input,list<char>::iterator it,double& new_val){
	/**finding out a sine value.@returns false if syntax error occurred, otherwise true */
	double amount=1;
	if(!splice_part(l_input,it,new_val,amount))
		return false;
	new_val=sin(new_val);
	return true;
} 
bool			Sheet::sum_value		(list<char>& l_input,list<char>::iterator it,double& new_val){
	/**finding out a sum value.@returns false if syntax error occurred, otherwise true */
	double amount=1;
	list<char>::iterator tmp_it=it;
	while(tmp_it!=l_input.end()){
		if(*tmp_it==','){
      		--tmp_it;
      		if((*tmp_it<'0' || *tmp_it>'9') && *tmp_it!=')')
      			return false;
      		advance(tmp_it,2);
      		if(*tmp_it=='T' || *tmp_it=='L' || *tmp_it=='P' || *tmp_it=='S' || (*tmp_it>='A' && *tmp_it<='F') || (*tmp_it>='0' && *tmp_it<='9')){
      			--tmp_it;
				tmp_it=l_input.erase (tmp_it);
				l_input.insert(tmp_it,'+');    			
      		}
      		else
      			return false;
      	}
      	++tmp_it;
    }
	if(!splice_part(l_input,it,new_val,amount))
		return false;
	return true;
} 
bool			Sheet::sqr_value		(list<char>& l_input,list<char>::iterator it,double& new_val){
	/**finding out a square root value.@returns false if syntax error occurred, otherwise true */
	double amount=1;
	if(!splice_part(l_input,it,new_val,amount))
		return false;
	if(new_val<0)
		return false;
	new_val=sqrt(new_val);
	return true;
}		
bool			Sheet::evaluate 		(list<char>& l_input,double &value_to_add){
	/**Calculates an expression.@returns false if syntax error occurred, otherwise true */
	list  <double> 	l_numbers;
	list  <char> 	l_operators;
	list  <char>::	iterator it;
	double 			first,second;
	char 			digits[20];
	double 			new_val;

	for(it=l_input.begin();it!=l_input.end();++it){
		if(*it>='0' && *it<='9'){
			int mv=get_number2(l_input,it,digits);
			advance(it,mv);
			if(*it=='.')
				return false;
			l_numbers.push_back(atof(digits));
			memset(&digits[0], '\0', sizeof(digits));
			if(it==l_input.end())
					break;
		}
		switch(*it){
			case '*':
				if(l_numbers.empty())
					return false;
				else
					l_operators.push_back(*it);
				break;
      		case '/':
      			if(l_numbers.empty())
					return false;
				else
      				l_operators.push_back(*it);
      		   	break;
      		case '+':
      			if(l_numbers.empty())
					return false;
      			else
      				l_operators.push_back(*it);
      		   	break;
      		case '-':
      			--it;
      			if(l_numbers.empty() || *it=='/' || *it=='*' || *it=='+' || *it=='-'){
      				advance(it,2);
      				if(*it>='0' && *it<='9'){
					int mv=get_number2(l_input,it,digits);
					advance(it,mv);
						if(*it=='.')
							return false;
						l_numbers.push_back(atof(digits)*(-1));
						memset(&digits[0], '\0', sizeof(digits));
					}
					else
						return false;
      			}
  				else{
  					++it;
  					l_operators.push_back(*it);
  				}
      		   	break;
      		case 'A':
      			++it;
      			if(it==l_input.end())
      				return false;
        		if(*it>='0' && *it<='9'){
					int mv=get_number2(l_input,it,digits);
					advance(it,mv);
					if(*it=='.')
						return false;
					if(data[0][atoi(digits)].is_string())
						return false;
					if(atoi(digits)>20)
						return false;
					l_numbers.push_back(data[0][atoi(digits)].get_value());
					memset(&digits[0], '\0', 2);
					if(it==l_input.end())
						--it;
      			}
      			else 
      				if(*it=='B'){
      				++it;
      				if(*it!='S')
      					return false;
      				++it;
      				if(*it!='(')
      					return false;
      				if(!abs_value(l_input,it,new_val))
      					return false;
      				l_numbers.push_back(new_val);
      				it=l_input.begin();
      			}
      			else
      				if(*it=='V'){
      					++it;
      					if(*it!='G')
      						return false;
      					++it;
      					if(*it!='(')
      						return false;
      					if(!avg_value(l_input,it,new_val))
      						return false;
      					l_numbers.push_back(new_val);
      					it=l_input.begin();
      			}
      			else
      				return false;
      			break;
      		case 'B':
      			++it;
      			if(it==l_input.end())
      				return false;
        		if(*it>='0' && *it<='9'){
					int mv=get_number2(l_input,it,digits);
					advance(it,mv);
					if(*it=='.')
						return false;
					if(data[1][atoi(digits)].is_string())
						return false;
					if(atoi(digits)>20)
						return false;
					l_numbers.push_back(data[1][atoi(digits)].get_value());
					memset(&digits[0], '\0', 2);
					if(it==l_input.end())
						--it;
      			}
      			else
      				return false;
      			break;
      		case 'C':
      			++it;
      			if(it==l_input.end())
      				return false;
        		if(*it>='0' && *it<='9'){
					int mv=get_number2(l_input,it,digits);
					advance(it,mv);
					if(*it=='.')
						return false;
					if(data[2][atoi(digits)].is_string())
						return false;
					if(atoi(digits)>20)
						return false;
					l_numbers.push_back(data[2][atoi(digits)].get_value());
					memset(&digits[0], '\0', 2);
					if(it==l_input.end())
						--it;
					break;
      			}
      			if(*it!='O')
      				return false;
   				++it;
      			if(*it!='S')
      				return false;
      			++it;
      			if(*it!='(')
      				return false;
      			if(!cos_value(l_input,it,new_val))
      				return false;
      			l_numbers.push_back(new_val);
      			it=l_input.begin();
      			break;
      		case 'D':
      			++it;
      			if(it==l_input.end())
      				return false;
        		if(*it>='0' && *it<='9'){
					int mv=get_number2(l_input,it,digits);
					advance(it,mv);
					if(*it=='.')
						return false;
					if(data[3][atoi(digits)].is_string())
						return false;
					if(atoi(digits)>20)
						return false;
					l_numbers.push_back(data[3][atoi(digits)].get_value());
					memset(&digits[0], '\0', 2);
					if(it==l_input.end())
						--it;
      			}
      			else
      				return false;
      			break;
      		case 'E':
      			++it;
      			if(it==l_input.end())
      				return false;
        		if(*it>='0' && *it<='9'){
					int mv=get_number2(l_input,it,digits);
					advance(it,mv);
					if(*it=='.')
						return false;
					if(data[4][atoi(digits)].is_string())
						return false;
					if(atoi(digits)>20)
						return false;
					l_numbers.push_back(data[4][atoi(digits)].get_value());
					memset(&digits[0], '\0', 2);
					if(it==l_input.end())
						--it;
      			}
      			else
      				return false;
      			break;
      		case 'T':
      			++it;
      			if(*it!='A')
      				return false;
   				++it;
      			if(*it!='N')
      				return false;
      			++it;
      			if(*it!='(')
      				return false;
      			if(!tan_value(l_input,it,new_val))
      				return false;
      			l_numbers.push_back(new_val);
      			it=l_input.begin();
      			break;
      		case 'F':
      			++it;
      			if(it==l_input.end())
      				return false;
        		if(*it>='0' && *it<='9'){
					int mv=get_number2(l_input,it,digits);
					advance(it,mv);
					if(*it=='.')
						return false;
					if(data[5][atoi(digits)].is_string())
						return false;
					if(atoi(digits)>20)
						return false;
					l_numbers.push_back(data[5][atoi(digits)].get_value());
					memset(&digits[0], '\0', 2);
					if(it==l_input.end())
						--it;
					break;
      			}
      			if(*it!='A')
      				return false;
   				++it;
      			if(*it!='C')
      				return false;
      			++it;
      			if(*it!='(')
      				return false;
      			if(!fac_value(l_input,it,new_val))
      				return false;
      			l_numbers.push_back(new_val);
      			it=l_input.begin();
      			break;
      		case 'L':
      			++it;
      			if(*it!='O')
      				return false;
   				++it;
      			if(*it!='G')
      				return false;
      			++it;
      			if(*it!='(')
      				return false;
      			if(!log_value(l_input,it,new_val))
      				return false;
      			l_numbers.push_back(new_val);
      			it=l_input.begin();
      			break;
      		case 'P':
      			++it;
      			if(*it!='O')
      				return false;
   				++it;
      			if(*it!='W')
      				return false;
      			++it;
      			if(*it!='(')
      				return false;
      			if(!pow_value(l_input,it,new_val))
      				return false;
      			l_numbers.push_back(new_val);
      			it=l_input.begin();
      			break;
      		case 'S':
      			++it;
      			if(it==l_input.end())
      				return false;
      			else
      				if(*it=='I'){
      					++it;
      					if(*it!='N')
      						return false;
      					++it;
      					if(*it!='(')
      						return false;
      					if(!sin_value(l_input,it,new_val))
      						return false;
      					l_numbers.push_back(new_val);
      					it=l_input.begin();
      			}
   				else
   					if(*it=='U'){
   						++it;
      					if(*it!='M')
      						return false;
      					++it;
      					if(*it!='(')
      						return false;
      					if(!sum_value(l_input,it,new_val))
      						return false;
      					l_numbers.push_back(new_val);
      					it=l_input.begin();
   				}
   				else
   					if(*it=='Q'){
   						++it;
      					if(*it!='R')
      						return false;
      					++it;
      					if(*it!='(')
      						return false;
      					if(!sqr_value(l_input,it,new_val))
      						return false;
      					l_numbers.push_back(new_val);
      					it=l_input.begin();	
   				}
   				else
   					return false;
      			break;
      		case ',':
      			return false;
		}
	}
	if(l_numbers.size()==1){
		value_to_add=l_numbers.front();
		return (l_operators.size()) ? false : true;
	}
	if(l_numbers.size()==l_operators.size())
		return false;
	list<double>::iterator 	dbl_it = l_numbers.begin();
	list<char>::iterator  ch_it  = l_operators.begin();
	for(dbl_it=l_numbers.begin();dbl_it!=l_numbers.end();++dbl_it){
		if(*ch_it=='*'){
			first=*dbl_it;
			dbl_it=l_numbers.erase(dbl_it);
			second=*dbl_it;
			dbl_it=l_numbers.erase(dbl_it);
			Multiplication m(first,second);
			m.evaluate();
			l_numbers.insert(dbl_it,m.get_value());
			ch_it=l_operators.erase(ch_it);
			advance(dbl_it,-2);
		}
		else if(*ch_it=='/'){
			first=*dbl_it;
			dbl_it=l_numbers.erase(dbl_it);
			second=*dbl_it;
			dbl_it=l_numbers.erase(dbl_it);
			if(second==0)
				return false;
			Division d(first,second);
			d.evaluate();
			l_numbers.insert(dbl_it,d.get_value());
			ch_it=l_operators.erase(ch_it);
			advance(dbl_it,-2);
		}
		else if(ch_it!=l_operators.end())
			++ch_it;
		else
			break;
	}
	while(l_numbers.size()!=1){
		char ch=l_operators.front();
		l_operators.pop_front();
		pop_two_num(first,second,l_numbers);
		if(ch=='+'){
			Addition a(first,second);
			a.evaluate();
			l_numbers.push_front(a.get_value());
		}
		else if(ch=='-'){
			Subtraction s(first,second);
			s.evaluate();
			l_numbers.push_front(s.get_value());
		}
	}
	value_to_add=l_numbers.front();
	l_numbers.clear();
	l_operators.clear();

	return true;
}
void			Sheet::error 			(int y,int x){
	/**prints out an error message if a given expression is syntactically wrong*/
	mvprintw(v_y,v_x,"ERROR, wrong input,to reinput press <ESC>");
	refresh();
	noecho();
	int ch;
	ch=getch();
	while(ch!=27)
		ch=getch();
	print_cmd();
	get_expr(y,x);
}
int 			Sheet::error_char		(int a, int b)const{
	/**prints out an error message if a wrong key has been typed*/
	mvprintw(v_y,v_x,"wrong input, please try again");
	move(a,b);
	int ch=getch();
	noecho();	
	while(ch<=7 || (ch>=9 && ch<40) || (ch>=58 && ch<=64) || (ch>=91 && ch<=127))
		ch=getch();
	move(24,0);
	clrtoeol();
	mvprintw(24,0,"value: ");
	move(a,b);
	refresh();
	return ch;
}
void 			Sheet::get_expr			(int cell_y,int cell_x){
	/**Reads an expression from user*/
	list<char> l_input;
	int ch;
	int a,b,max_b;
	print_cmd();
	move(c_y,c_x);
	noecho();
	getyx(stdscr,a,b);
	max_b=b;
	ch=getch();
	if(ch!=61)
		while(ch!=10){
			if(ch<=7  || ch==9 || (ch>=11 && ch<40) || (ch>=58 && ch<=64) || (ch>=91 && ch<=127))
			  	ch=error_char(a,b);
			switch(ch){	
				case(KEY_BACKSPACE):
					if(l_input.size() && b!=8){
						list<char>::iterator it=l_input.begin();
						advance(it,b-9);
						l_input.erase(it);
						move(a,--b);
						refresh();
						delch();
						refresh();
						--max_b;
					}
					break;
				case(KEY_LEFT):
					if(b!=c_x)
						move(a,--b);
					break;
				case(KEY_RIGHT):
					if(b<max_b)
						move(a,++b);
					break;
				case(KEY_UP):
					break;
				case(KEY_DOWN):
					break;
				case(10):
					break;
				default:
					if(b!=max_b){
						print_cmd();
						list<char>::iterator it=l_input.begin();
						advance(it,b-8);
						l_input.insert(it,ch);
						move(a,8);
						for(it=l_input.begin();it!=l_input.end();++it)
							addch(*it);
						move(a,++b);
						++max_b;
					}
					else{
						l_input.push_back(ch);
						addch(ch);
						++b;
						++max_b;
						refresh();
					}
					break;
			}
			ch=getch();				
		}
	else{
		echo();
		char str[20];
		addch(ch);
		mvgetnstr(c_y,c_x+1,str,19);
		if(strlen(str)>=10){
			move(cell_y,cell_x);
			for(int i=0;i<6;++i)
				addch(str[i]);
			mvprintw(cell_y,cell_x+6,"...");
		}
		else
			mvprintw(cell_y,cell_x,str);
		print_cmd();
		move(cell_y,cell_x);
		noecho();
		string to_add (str);
		add_value(to_add,cell_y,cell_x);
		return;
	}
	if(l_input.size()==0){
		move(cell_y,cell_x);
		return;
	}
	else{
		double value_to_add;
		list<char> form_to_add=l_input;
		if(!evaluate(l_input,value_to_add))
			error(cell_y,cell_x);
		else{
			add_value(value_to_add,form_to_add,cell_y,cell_x);
			mvprintw(cell_y,cell_x,"%0.1f",value_to_add);
			print_cmd();
			cell_order.push_back(make_pair(cell_y,cell_x));
		}	
	}
}	
void 			Sheet::set_yx			(){
	/**Sets coordinates of each cell*/
	int x=-6;
	for(int i=0;i<=5; ++i){
		x=x+9;
		for(int j=0;j<=20;++j)
			data[i][j].set_yx(j+1,i+x);
	}
}
void			Sheet::delete_cell  	(int a,int b){
	/**finds out a specific cell according to coordinates and removes it*/
	for(int i=0;i<=5;++i)
	for(int j=0;j<=20;++j)
		if(data[i][j].this_cell(a,b)){
			if(!data[i][j].changed())
				return;
			data[i][j].delete_all();
			mvprintw(a,b,"         ");
			print_cmd();
			refresh();
		}
}			
void 			Sheet::print_val_formula(int a, int b ){
	/**prints a  value and a formula of the cell, where a cursor is*/
	for(int i=0;i<=5;++i)
	for(int j=0;j<=20;++j)
		if(data[i][j].this_cell(a,b)){
			if(!data[i][j].changed())
				return;
			if(!data[i][j].is_string()){
				mvprintw(v_y,v_x,"%f",data[i][j].get_value());
				list<char> l_tmp=data[i][j].get_formula();
				list<char>::iterator it=l_tmp.begin();
				move(c_y,c_x);
				while(it!=l_tmp.end()){
					addch(*it);
					++it;
				}
			}
			else{
				string m_str=data[i][j].get_string();
				move(v_y,v_x);
				for(unsigned int i=0;i<m_str.size();++i)
					addch(m_str[i]);
			}
			move(a,b);
			return;
		}
}
void			Sheet::evaluate_in_order(){
	/**Calculates every cell in order they were added*/
	list<pair<int,int> >::iterator it;			
		for(it=cell_order.begin();it!=cell_order.end();++it)
		for(int i=0;i<=5;++i)
		for(int j=0;j<=20;++j){
			if(data[i][j].this_cell(it->first,it->second)){
				if(!data[i][j].changed() || data[i][j].is_string())
					break;
				else{
					double value_to_add;
					list<char> l_input=data[i][j].get_formula();
					evaluate(l_input,value_to_add);
					data[i][j].set_value(value_to_add);
					mvprintw(it->first,it->second,"         ");
					mvprintw(it->first,it->second,"%0.1f",value_to_add);
				}
			}
		}
}
void 			Sheet::print_numbers	(){
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
void 			Sheet::print_bar		(){
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
void 			Sheet::print_cmd		(){
	///draws command and value lines
	move(23,0);
	clrtoeol();
	move(24,0);
	clrtoeol();
	mvprintw(23,0,"command: ");
	mvprintw(24,0,"value: ");
	refresh();
}
void 			Sheet::print 			(){
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
