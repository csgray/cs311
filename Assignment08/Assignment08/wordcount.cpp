// wordcount.cpp
// Corey S. Gray
// 05 Dec 2017
//
// For CS 311 Fall 2017
// Source for Assignment 8: Word count using a STL table implementation

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;
using std::getline;
#include <fstream>
using std::ifstream;
#include <map>
using std::map;

int main()
{
	cout
		<< "'Word Count' by C. S. Gray" << endl
		<< "Enter a file name and this program will print the number of distinct words that appear in the file" << endl
		<< "followed by a list of each individual word and the number of times it appears in the file." << endl
		<< endl;	

	// Global variables
	string filename;			// User-specified file
	ifstream input;				// Input stream for said file
	map<string, int> counts;	// STL Table of <word, count> pairs
	string word;				// Word read from file and added to map

	// Repeatedly prompts the user for a filename until a file is successfully opened
	while (true)
	{
		cout << "Type your filename: ";
		getline(cin, filename);
		input.open(filename);
		if (input.is_open())	// only exits the loop if the file was successfully opened
			break;
		cout << "That cannot be opened. Please try again with another filename." << endl;
	}

	cout << "Counting '" << filename << "'..." << endl << endl;
	// Adds each word to the map as a key or increments its value if already present
	while (input >> word)
		counts[word]++;
	input.close();

	// Outputs the results by printing the map's size then iterating over it
	cout << "Number of distinct words: " << counts.size() << endl << endl;
	for (const auto & kvpair : counts)
		cout << kvpair.first << " " << kvpair.second << endl;
	
	// Wait for user then exit
	cout << endl << "Press ENTER to quit.";
	while (cin.get() != '\n');
	return 0;
}