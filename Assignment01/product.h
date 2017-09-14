// product.h
// Corey S. Gray
// 12 Sep 2017

// For CS 311 Fall 2017
// Header for class Product
// Tracks product's name and number of sales

#ifndef FILE_PRODUCT_H_INCLUDED
#define FILE_PRODUCT_H_INCLUDED

#include <string> // For std::string, std::to_string
#include <ostream> // For std::ostream

// class Product
// Product name and number of sales
// Invariants: _sales >= 0
class Product {

// ***** Product: Constructors, destructor, and assignment operators *****
public:

	// Default constructor
	// Sets the product name to an empty string and the number of items sold to zero.
	// Pre: None.
	// Post: Unnamed product with no sales.
	Product()
	{
		_name = "";
		_sales = 0;
	}

	// Constructor from data
	// Sets product name and number of sales according to parameters.
	// Pre: sales >= 0, otherwise _sales will be 0
	// Post: Product named accordingly with set number of sales.
	Product(std::string name, int sales)
	{
		_name = name;
		if (sales >= 0)
			_sales = sales;
		else
			_sales = 0;
	}

	// Copy constructor
	Product(const Product & other) = default;

	// Move constructor
	Product(Product && other) = default;

	// Destructor
	~Product() = default;

	// Copy assignment operator
	Product & operator=(const Product & other) = default;

	// Move assignment operator
	Product & operator=(Product && other) = default;

// ***** Product: General public operators *****
public:
	// operator++ (pre)
	// Pre: None.
	// Post:
	//		_sales increased by 1
	//		Return is *this
	Product & operator++()
	{
		++_sales;
		return *this;
	}

	// operator++ (post)
	// Pre: None.
	// Post:
	//		_sales increased by 1
	//		Return is a copy of old *this
	Product operator++(int dummy)
	{
		Product copy = *this;
		++*this;
		return copy;
	}

	// operator-- (pre)
	// Pre: Product in question has more than 0 sales, otherwise nothing happens.
	// Post:
	//		_sales decreased by 1
	//		Return is *this.
	Product & operator--()
	{
		if (_sales > 0)
			--_sales;
		return *this;
	}

	// operator-- (post)
	// Pre: Product in question has more than 0 sales, otherwise nothing happens.
	// Post:
	//		_sales decreased by 1
	//		Return is a copy of old *this.
	Product operator--(int dummy)
	{
		Product copy = *this;
		--*this;
		return copy;
	}

// ***** Product: General public member functions *****
public:

	// getName
	// Pre: None.
	// Post: Returns product's name as a string.
	std::string getName() const;
	
	// getSales
	// Pre: None.
	// Post: Returns product's number of sales as an int.
	int getSales() const;

	// setName
	// Pre: None.
	// Post: Set's the product's name to the string.
	void setName(const std::string & );

	// setSales
	// Pre: Parameter int be greater than 0.
	// Post: Sets the product's number of sales to the int.
	void setSales(const int &);

	// toString
	// Pre: None.
	// Post:
	//		Returns a string with the product's name and number of sales formatted as:
	//		<name> (sales: <num>)
	//		where <name> is the product's name and <num> is its number of sales
	std::string toString() const;

// ***** Product: Data members *****	
private:
	std::string _name; // Product's name
	int _sales; // Product's number of items sold

}; // End class Product

// ***** class Product - Declarations of associated global operators *****

// equality (==)
// Checks whether two products' names and sales are both the same.
// Pre: Two objects of class Product
// Post:
//		Returns a boolean.
//		True if both names and sales are the same. False otherwise.
bool operator==(const Product &, const Product &);

// inequality (!=)
// Checks whether two products' names and sales are not both the same.
// Pre: Two objects of class Product.
// Post:
//		Returns a boolean.
//		True if either name or sales is different. False if both names and sales are the same.
bool operator!=(const Product &, const Product &);

// operator<< (ostream,Product)
// Prints given Product object as "<name> (sales: <num>)"
// where <name> is the product's name and <num> is the number of products sold.
// Pre: An object of class Product and valid ostream.
// Post:
//		Given Product object is printed to given stream as described.
//		Return is given stream.
std::ostream & operator<<(std::ostream &, const Product &);

#endif //#ifndef FILE_PRODUCT_H_INCLUDED