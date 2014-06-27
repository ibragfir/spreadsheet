#ifndef SHEET_H
#define	SHEET_H
#include "cell.h"
///Contains the whole spreadsheet and functions (parsing,maths...)
class Sheet{
 public:
 	inline 				Sheet				( );
   	inline 				~Sheet 				( );
 	inline 	void 		set_yx				( );
 	inline 	void 		get_expr			( int, int );
 	inline 	void 		error 				( int, int );
 	inline 	int 		error_char			( int, int )const;
 	inline 	void		add_value			( double,const std::list<char>&, int, int );
 	inline 	void		add_value			( const std::string&, int, int );
 	inline 	bool 		evaluate			( std::list<char>&, double& );
 	inline 	bool		abs_value			( std::list<char>&, std::list<char>::iterator, double& );
 	inline 	bool 		avg_value 			( std::list<char>&, std::list<char>::iterator, double& );
 	inline 	bool		cos_value			( std::list<char>&, std::list<char>::iterator, double& );
 	inline 	bool		fac_value			( std::list<char>&, std::list<char>::iterator, double& );
 	inline 	bool		tan_value			( std::list<char>&, std::list<char>::iterator, double& );
 	inline 	bool		log_value			( std::list<char>&, std::list<char>::iterator, double& );
 	inline 	bool		pow_value			( std::list<char>&, std::list<char>::iterator, double& );
 	inline 	bool		sin_value			( std::list<char>&, std::list<char>::iterator, double& );
 	inline 	bool		sum_value			( std::list<char>&, std::list<char>::iterator, double& );
 	inline 	bool		sqr_value			( std::list<char>&, std::list<char>::iterator, double& );
 	inline 	bool		splice_part			( std::list<char>&, std::list<char>::iterator, double&, double& );
 	inline  int 		get_number			( std::list<char>&, std::list<char>::iterator it,char[]);
 	inline  int 		get_number2			( std::list<char>&, std::list<char>::iterator it,char[]);
 	inline 	void		pop_two_num			( double &,double&, std::list<double>&);
 	inline 	void 		print_val_formula 	( int, int );
 	inline 	void		delete_cell			( int, int );
 	inline 	void		evaluate_in_order	( );
 	inline	void		print_numbers		( );
 	inline	void		print_bar			( );
 	inline	void		print_cmd			( );
 	inline	void		print 				( );

 private:	
	std::list<std::pair<int,int> >	cell_order;
	Cell 							data[6][21];
};



#endif	/* SHEET_H */