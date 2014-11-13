#ifndef __HYDROBARBON_H__
#define __HYDROCARBONH__
#include "Molecule.h"
class HydroCarbon : protected Molecule
{
	private:
		int idh;						// Index deficiency of hydrogen 
		int carbon;					// Number of carbon atoms
		int hydrogen;				// Number of Hydrogen Atoms

		bool doubleBond;   
		bool tripleBond; 
		bool ring; 
		bool alternate; 

		void prompt();
		void bondCarbon(Element* & next);
		void print(Element* curr); 
		void constructBackbone();
		void formRing();

	public:
		HydroCarbon( int carbon, int hydrogen );

		int myIdh(); 
		void printMolecule(); 

};

//Constructor( number of carbons, number of hydrogens)
HydroCarbon::HydroCarbon(  int carbon, int hydrogen )
	:doubleBond(0), tripleBond(0), ring(0), alternate(0)
{
	// Add elements to elements array (from Molecule.h)
	elements.push_back(pair<string, int>("C", carbon)); 
	elements.push_back(pair<string, int>("H", hydrogen)); 
	
	numElements = carbon + hydrogen;				// Find number of elements
	this->carbon = carbon;										// Set number value
	this->hydrogen = hydrogen;								// Set number value
	this->valence = elements[0].second*4;			    // valence = number of carbons*4
	this->idh = ((2*carbon + 2) - hydrogen)/2;
	prompt(); 
	constructBackbone();
}


void HydroCarbon::constructBackbone()
{
	// Initialize head as first element ex: head -> (C) [->, ->, ->, ->] 
	head = new Element(elements[0].first, 1);
	current = head; 

	for (int i = 1; i < carbon; i++)
	{
		// It forms a bond by attaching the current C Element to new C Element
		Element* next = new Element("C", i+1);
		bondCarbon(next); 
	}
	
	// At this point, pointer var current is pointing to last Carbon of  backbone
	// If we want ring, then create approprate connection 
	// It forms a ring by attaching the current Carbon Element (last one) to first 
	if(ring)
	{
		Element* next = head; 
		bondCarbon(next); 
	}

	
	//cout << *head << endl; 
}

// Used for inserting Carbon, to create the Carbon Backbone
void HydroCarbon::bondCarbon(Element* & next)
{
	// If we want triple bonds and the previous bond was different.
	// This will alternate between single and double/triple bonds
	// Current will equal to next element, bondTo creates bond and returns pointer to the element
	//  Valence will be updated
	if(tripleBond && alternate)
	{
		current = current->bondTo(next, TRIPLE); 
		valence -= 3; 
		alternate = false; 
	}
	else if(doubleBond && alternate)
	{
		current = current->bondTo(next, DOUBLE); 
		valence -= 2; 
		alternate = false; 
	}
	else 
	{
		current = current->bondTo(next, SINGLE); 
		valence -= 1; 
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

// Recursively prints the whole molecule, curr is temp current pointer
void HydroCarbon::print( Element* curr)
{
	// Base case: if no more neighbors, or if molecule has been visited
	if(curr == NULL || curr->visited == true)	
		return; 

	curr->visited = true;															
	//cout << "(" << curr->fullName << ") " <<	 endl ; 
	cout << *curr; 
	for (int i = 0; i < curr->bonds.size(); i++)
	{ 
		cout << "Bond " << i+1 << ": " << curr->bonds[i].type << " To  (" << curr->bonds[i].next->fullName << ")" << endl; 
	}
	cout << endl; 
	for (int i = 0; i < curr->bonds.size(); i++)
	{ 
		print(curr->bonds[i].next); 
	}
	

	return; 
}
#endif