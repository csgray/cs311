// product.h
// Corey S. Gray
// 12 Sep 2017

// For CS 311 Fall 2017
// Header for class Product
// Tracks product's name and number of sales

#ifndef FILE_PRODUCT_H_INCLUDED
#define FILE_PRODUCT_H_INCLUDED

#include <string> // For std::string
#include <ostream> // For std::ostream

// class Product
// Product name and number of sales
// Invariants:
class Product {

// ***** Product: Constructors, destructor, and assignment operators *****
public:

	// Default constructor
	// Sets the product name to an empty string and the number of items sold to zero.
	// Pre: None.
	// Post: 
	Product()
	{

	}

	// Constructor from data
	// Sets product name and number of sales according to parameters.
	// Pre: None.
	// Post:
	Product(std::string, int)
	{

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
	Product & operator++()
	{
		return *this;
	}

	// operator++ (post)
	Product operator++(int)
	{
		return *this;
	}

	// operator-- (pre)
	Product & operator--()
	{
		return *this;
	}

	// operator-- (post)
	Product operator--(int)
	{
		return *this;
	}

// ***** Product: General public member functions *****
public:

	// getName
	// Pre:
	// Post:
	std::string getName() const;
	
	// getSales
	// Pre:
	// Post:
	int getSales() const;

	// setName
	// Pre:
	// Post:
	void setName(std::string);

	// setSales
	// Pre:
	// Post:
	void setSales(int);

	//toString
	std::string toString() const;

// ***** Product: Data members *****	
private:
	std::string _name; // Product's name
	int _sales; // Product's number of items sold

}; // End class Product

// equality (==)
//
// Pre:
// Post:
bool operator==(const Product &, const Product &);

// inequality (!=)
//
// Pre:
// Post:
bool operator!=(const Product &, const Product &);

// operator<< (ostream,Product)
//
// Pre:
// Post:
std::ostream & operator<<(std::ostream &, const Product &);

#endif //#ifndef FILE_PRODUCT_H_INCLUDED