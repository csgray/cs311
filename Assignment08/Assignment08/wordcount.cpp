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
		<< "Word Count" << endl
		<< "Enter a file name and this program will print the number of distinct words that appear in the file" << endl
		<< "followed by a list of each individual word and the number of times it appears in the file." << endl
		<< endl
		<< "Type your filename: ";

	string filename;
	getline(cin, filename);
	ifstream input(filename);
	if (!input)
	{
		cout << "ERROR: Bad input!" << endl;
		cout << "Please try again with a proper filename." << endl;
		cout << "Press ENTER to quit.";
		while (cin.get() != '\n');
		return -1;
	}

	if (input.is_open())
	{
		cout << "Counting " << filename << "..." << endl << endl;
		map<string, int> counts;

		string word;
		while (input >> word)
			counts[word]++;
		input.close();

		cout << "Number of distinct words: " << counts.size() << endl << endl;
		for (const auto & kvpair : counts)
			cout << kvpair.first << " " << kvpair.second << endl;
	}
	
	cout << endl << "Press ENTER to quit.";
	while (cin.get() != '\n');

	return 0;
}