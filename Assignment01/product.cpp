// product.cpp
// Corey S. Gray
// 12 Sep 2017

// For CS 311 Fall 2017
// Source for class Product
// Tracks product's name and number of sales

#include "product.h" // For class Product
#include <string>
#include <ostream>
#include <iostream>

// getName
// (See header for documentation.)
std::string Product::getName() const
{
	std::string name = _name;
	return name;
}

// getSales
// (See header for documentation.)
int Product::getSales() const
{
	int sales = _sales;
	return sales;
}

// setName (string)
// (See header for documentation.)
void Product::setName(const std::string & name )
{
	_name = name;
}

// setSales (int)
// (See header for documentation.)
void Product::setSales(const int & sales)
{
	// Checks that parameter int is not negative
	if (sales >= 0)
		_sales = sales;
}

// toString (ostream,Product)
// (See header for documentation.)
std::string Product::toString() const
{
	std::string output = _name + " (sales: " + std::to_string(_sales) + ")";
	return output;
}

// equality (==) (Product,Product)
// (See header for documentation.)
bool operator==(const Product & left, const Product & right)
{
	return (left.getName() == right.getName() &&
			left.getSales() == right.getSales());
}

// inequality (!=) (Product,Product)
// (See header for documentation.)
bool operator!=(const Product & left, const Product & right)
{
	return !(left == right);
}

// operator<< (ostream,Product)
// (See header for documentation.)
std::ostream & operator<<(std::ostream & os, const Product & obj)
{
	os << obj.toString();
	return os;
}