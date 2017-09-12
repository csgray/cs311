// product.cpp
// Corey S. Gray
// 12 Sep 2017

// For CS 311 Fall 2017
// Source for class Product
// Tracks product's name and number of sales

#include "product.h" // For class Product
#include <string>
#include <ostream>

// getName
// Pre:
// Post:
std::string Product::getName() const
{
	std::string name;
	return name;
}

// getSales
// Pre:
// Post:
int Product::getSales() const
{
	int sales = 0;
	return sales;
}

// setName
// Pre:
// Post:
void Product::setName(std::string)
{

}

// setSales
// Pre:
// Post:
void Product::setSales(int)
{

}

//toString
std::string Product::toString() const
{
	std::string output;
	return output;
}

// equality (==)
//
// Pre:
// Post:
bool operator==(const Product & left, const Product & right)
{
	bool equal = false;
	return equal;
}

// inequality (!=)
//
// Pre:
// Post:
bool operator!=(const Product & left, const Product & right)
{
	bool inequal = false;
	return inequal;
}

// operator<< (ostream,Product)
//
// Pre:
// Post:
std::ostream & operator<<(std::ostream & os, const Product & obj)
{
	return os;
}