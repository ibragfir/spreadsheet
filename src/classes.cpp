///This file contains only base and derived classes 
/**
 * @file 	classes.cpp
 * @author 	Firuz Ibragimov, <ibragfir@fit.cvut.cz>
 * @date	19.06.2013 
 */
#ifndef CLASSES
#define	CLASSES
///class handling a mathematical expression
class Expression{
 protected:
	double m_value;
	double m_left;
	double m_right;
 public:
 	Expression(double left,double right):m_left(left),m_right(right){}
 	double get_value(){return m_value;}
 	virtual void evaluate()=0;
};

	///class derived from Expression class, to multiplicate two variables
class Multiplication: public Expression{
 public:
 	Multiplication(double left, double right):Expression(left,right){}
 	void evaluate(){
 		///multiplicates two variables
 		m_value=m_left*m_right;
 	}
};
	///class derived from Expression class, to divide two variables
class Division: public Expression{
 public:
 	Division(double left,double right):Expression(left,right){}
 	void evaluate(){
 		///divides two variables
 		m_value=m_left/m_right;
 	}
};
	///class derived from Expression class, to add two variables
class Addition:public Expression{
 public:
 	Addition(double left,double right):Expression(left,right){}
 	void evaluate(){
 		///adds two variables
 		m_value=m_left+m_right;
 	}
};
	///class derived from Expression class, to subtract two variables
class Subtraction: public Expression{
 public:
 	Subtraction(double left,double right):Expression(left,right){}
 	void evaluate(){
 		///subtracts two variables
 		m_value=m_left-m_right;
 	}
};

#endif