#ifndef __HYDROBARBON_H__
#define __HYDROCARBONH__
#include "Molecule.h"
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
		void print(Element* curr); 

	public:
		HydroCarbon( int carbon, int hydrogen );

		int myIdh(); 
		void constructBackbone();
		void printMolecule(); 

};

//Constructor
HydroCarbon::HydroCarbon(  int carbon, int hydrogen )
	:doubleBond(0), tripleBond(0), ring(0), alternate(0)
{
	
	// Add elements 
	elements.push_back(pair<string, int>("C", carbon)); 
	elements.push_back(pair<string, int>("H", hydrogen)); 
	// Find number of elements
	numElements = carbon + hydrogen;
	this->carbon = carbon; 
	this->hydrogen = hydrogen; 
	// For now it is 0 
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
	
	//cout << *head << endl; 
}

// Used for inserting Carbon, to create the Carbon Backbone
void HydroCarbon::insertCarbon()
{
	Element* next = new Element("C");

	// If we want triple bonds and the previous bond was different. 
	if(tripleBond && alternate)
	{
		// current will equal to next
		current = current->bondTo(next, TRIPLE); 
		//valence -= 3; 
		alternate = false; 
	}
	else if(doubleBond && alternate)
	{
		current = current->bondTo(next, DOUBLE); 
		//valence -= 2; 
		alternate = false; 
	}
	else 
	{
		current = current->bondTo(next, SINGLE); 
		//valence -= 1; 
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

// Print Molecule 
void HydroCarbon::printMolecule()
{
	print(head); 
	return; 
}

// Recursively prints the whole molecule, curr is current pointer
void HydroCarbon::print( Element* curr)
{
	if(curr == NULL)
		return; 

	cout << "(" << curr->name << ") " <<	 endl ; 
	for (int i = 0; i < curr->bonds.size(); i++)
	{ 
		cout << "Bond " << i+1 << ": " << curr->bonds[i].type << " To  (" << curr->bonds[i].next->name << ")" << endl; 
		print(curr->bonds[i].next); 
	}

	cout << endl; 

	return; 
}
#endif