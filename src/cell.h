#ifndef CELL_H
#define	CELL_H
#include <list>
#include <string>

///All information about a cell kept in here(formula, calculated value, coordinate of a cell).

class Cell{
	int 									m_y;
	int 									m_x;
	double 									m_value;
	std::string								m_str;
	bool									flag;
	bool									is_str;
	std::list<char>							m_formula;
 public:
	inline 					Cell 			();
   	inline 					~Cell 			();
   	inline 	void 			delete_all 		();
	inline 	void 			set_yx			(int y,int x);
	inline 	bool 			this_cell		(int y,int x)const;
	inline 	double 			get_value		()const;
	inline 	std::string 	get_string  	()const;
	inline 	void			add_formula		(const std::list<char>& );
	inline 	void 			set_value		(double val);
	inline 	void 			set_value 		(const std::string& val);
	inline 	bool			changed			()const;
	inline 	bool			is_string 		()const;
	inline 	std::list<char> get_formula		()const;
};

#endif	/* CELL_H */