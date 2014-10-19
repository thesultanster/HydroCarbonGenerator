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
		bool alternate; 

		void prompt();
		void insertCarbon(); 

	public:
		HydroCarbon( int carbon, int hydrogen );

		int myIdh(); 
		void constructBackbone();

};

//Constructor
HydroCarbon::HydroCarbon(  int carbon, int hydrogen )
{
	
	elements.push_back(pair<string, int>("C", carbon)); 
	elements.push_back(pair<string, int>("H", hydrogen)); 
	this->carbon = carbon; 
	this->hydrogen = hydrogen; 
	this->alternate = true; 
	this->valence = 0;
	this->idh = ((2*carbon + 2) - hydrogen)/2;
	prompt(); 
	constructBackbone();
}


void HydroCarbon::constructBackbone()
{
	// Initialize head as first element ex: head -> (C) [->, ->, ->, ->] 
	head = new Element(elements[0].first);
	current = head; 

	for (int i = 1; i < carbon; i++)
	{
		insertCarbon(); 
	}
	
	cout << *head << endl; 
}

void HydroCarbon::insertCarbon()
{
	Element* next = new Element("C");

	if(tripleBond && alternate)
	{
		// current will equal to next
		current = current->bondTo(next, 3); 
		alternate = false; 
	}
	else if(doubleBond && alternate)
	{
		current = current->bondTo(next, 2); 
		alternate = false; 
	}
	else if(!alternate)
	{
		 current = current->bondTo(next,1); 
		alternate = true; 
	}
}

int HydroCarbon::myIdh()
{
	return idh; 
}

void HydroCarbon::prompt()
{
	string input; 

	if( idh >= 2)
	{

		do
		{
			cout << "Do you want a ring? (y/n)"; 
			cin >> input;

			if(input == "y") 
				ring = true; 
			else if(input == "n")
				ring = false; 
			else 
				continue; 

			break;
		} while( true); 

		do
		{
			cout << "Do you want a double bond? (y/n)";
			cin >> input;

			if(input == "y") 
				doubleBond = true; 
			else if(input == "n")
				doubleBond = false; 
			else 
				continue; 

			break;
		} while( true  ); 
	}
	
	if( idh >=3 )
	{
		do
		{
			cout << "Do you want a triple bond? (y/n)";
			cin >> input;

			if(input == "y") 
				tripleBond = true; 
			else if(input == "n")
				tripleBond = false; 
			else 
				continue; 

			break; 
		} while( true ); 
	}
	
};

#endif