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
// Pre:
// Post:
std::string Product::getName() const
{
	std::string name = _name;
	return name;
}

// getSales
// Pre:
// Post:
int Product::getSales() const
{
	int sales = _sales;
	return sales;
}

// setName
// Pre:
// Post:
void Product::setName(std::string name)
{
	_name = name;
}

// setSales
// Pre:
// Post:
void Product::setSales(int sales)
{
	if (sales >= 0)
		_sales = sales;
}

// toString
std::string Product::toString() const
{
	std::string output = _name + " (sales: " + std::to_string(_sales) + ")";
	return output;
}

// equality (==)
//
// Pre:
// Post:
bool operator==(const Product & left, const Product & right)
{
	return (left.getName() == right.getName() && left.getSales() == right.getSales());
}

// inequality (!=)
//
// Pre:
// Post:
bool operator!=(const Product & left, const Product & right)
{
	return !(left == right);
}

// operator<< (ostream,Product)
//
// Pre:
// Post:
std::ostream & operator<<(std::ostream & os, const Product & obj)
{
	os << obj.toString();
	return os;
}