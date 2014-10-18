#ifndef __HYDROBARBON_H__
#define __HYDROCARBONH__
#include "molecule.h"
class HydroCarbon : protected Molecule
{
	private:
		// Index deficiency of hydrogen 
		int idh; 
		int carbon; 
		int hydrogen; 

		bool doubleBond; 
		bool tripleBond; 
		bool ring; 

		void prompt();

	public:
		HydroCarbon( int carbon, int hydrogen );
		void constructMolecule();
};

//Constructor
HydroCarbon::HydroCarbon(  int carbon, int hydrogen )
{
	
	elements.push_back(pair<string, int>("carbon", carbon)); 
	elements.push_back(pair<string, int>("hydrogen", hydrogen)); 
	this->carbon = carbon; 
	this->hydrogen = hydrogen; 
	valence = 0;
	idh = ((2*carbon + 2) - 4)/2;
	prompt(); 
	constructMolecule();
}


void HydroCarbon::constructMolecule()
{

	// Initialize head, pass in name of element in element and the table for setup info
	cerr << elements.size(); 
	head = new Element(elements[0].first); 
	
	cout << *head << endl; 
}

void HydroCarbon::prompt()
{
	string input; 

	if( idh >= 2)
	{
		cout << "Do you want a ring? (y/n)"; 
		cin >> input;
		do
		{
			if(input == "y") 
				ring = true; 
			else if(input == "n")
				ring = false; 
			else 
				continue; 
		} while( false ); 

		cout << "Do you want a double bond? (y/n)";
		cin >> input;
		do
		{
			if(input == "y") 
				doubleBond = true; 
			else if(input == "n")
				doubleBond = false; 
			else 
				continue; 
		} while( false ); 
	}
	
	if( idh >=3 )
	{
		cout << "Do you want a triple bond? (y/n)";
		cin >> input;
		do
		{
			if(input == "y") 
				tripleBond = true; 
			else if(input == "n")
				tripleBond = false; 
			else 
				continue; 
		} while( false ); 
	}
	
};
#endif