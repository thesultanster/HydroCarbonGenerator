#ifndef __HYDROBARBON_H__
#define __HYDROCARBONH__
#include "Molecule.h"
class HydroCarbon : protected Molecule
{
	private:
		int idh;						// Index deficiency of hydrogen 
		int carbon;					// Number of carbon atoms
		int hydrogen;				// Number of Hydrogen Atoms
		int hydroCounter;    // Temp

		bool doubleBond;   
		bool tripleBond; 
		bool ring; 
		bool alternate; 

		vector<vector<BondType>  > bondTable; 

		void prompt();
		void bondCarbon(Element* & next);
		void print(Element* curr); 
		void constructBackbone();
		void fillHydrogen(); 
		void formRing();
		vector<vector<BondType>  > createBondTable(); 

	public:
		HydroCarbon( int carbon, int hydrogen );

		int myIdh(); 
		void printMolecule(); 

};

//Constructor( number of carbons, number of hydrogens)
HydroCarbon::HydroCarbon(  int carbon, int hydrogen )
	:doubleBond(0), tripleBond(0), ring(0), alternate(0),  hydroCounter(1)
{
	
	numElements = carbon + hydrogen;				// Find number of elements
	this->carbon = carbon;										// Set number value
	this->hydrogen = hydrogen;								// Set number value
	this->valence = carbon*4;									// valence = number of carbons*4. vari from Molecule.h
	this->idh = ((2*carbon + 2) - hydrogen)/2;

	if(carbon%2 == 0 && hydrogen%2 == 0 && hydrogen > 2	)		
		bondTable = createBondTable();					// Construct Bond table
	prompt();																// prompt for ring and properties
	constructBackbone();											// Construct carbon backbone
	fillHydrogen(); 
}


void HydroCarbon::constructBackbone()
{
	// Initialize head as first element ex: head -> (C) [->, ->, ->, ->] 
	head = new Element("C", 1);
	elements["C"].push_back(head);					// Document the pointer 
	current = head;

	if(carbon%2 == 0 && hydrogen%2 == 0 && hydrogen > 2 &&  !ring )	// If stable 
		cout << endl << "Stable Molecule Detected" << endl << endl; 

	for (int i = 1, j = 0; i < carbon; i++)
	{
		
		Element* next = new Element("C", i+1);
		elements["C"].push_back(next);				   // Document the pointer to the Carbon element
 
		 // If this molecule is compatible with our lookup table
		if(carbon%2 == 0 && hydrogen%2 == 0 && hydrogen > 2 && !ring )   // Then create backbone according to table	
		{
			//iterate through bondtypes
			current->bondTo(next, bondTable[j][hydrogen/2-2]);
			current = next; 

			if(bondTable[j][hydrogen/2-2] == DOUBLE)
				valence -= 2; 
			else 
				valence -= 1; 
			j++; 
		}
		else																	// Else Freely bond the elements
			bondCarbon(next);									// It forms a bond by attaching the current C Element to new C Element
	}
	
	// At this point, pointer var current is pointing to last Carbon of  backbone
	// If we want ring, then create approprate connection 
	// It forms a ring by attaching the current Carbon Element (last one) to first 
	if(ring)
	{
		Element* next = head; 
		bondCarbon(next); 
	}

	
}

// Fill hydrogen for remaining valence of every carbon element
void HydroCarbon::fillHydrogen()
{
	// For all carbon elements 
	for(int i = 0; i < elements["C"].size(); i++)
	{
		// Fill their valence
		int tempValence = elements["C"][i]->elementValence;  // Use temp variable because we change valence in bondTo()
		for(int j = 0; j < tempValence ; j++)
		{
			Element* newHydrogen = new Element("H", hydroCounter);
			hydroCounter++; 
			elements["C"][i]->bondTo(newHydrogen, SINGLE); 
		}
	}
}

// Used for inserting Carbon, to create the Carbon Backbone
void HydroCarbon::bondCarbon(Element* & next)
{
	// If we want triple bonds and the previous bond was different.
	// This will alternate between single and double/triple bonds
	// bondTo creates bond, Current will equal to next element 
	// Valence will be updated
	if(tripleBond && alternate)
	{
		current->bondTo(next, TRIPLE); 
		current = next; 
		valence -= 3; 
		alternate = false; 
	}
	else if(doubleBond && alternate)
	{
		current->bondTo(next, DOUBLE);
		current = next; 
		valence -= 2; 
		alternate = false; 
	}
	else 
	{
		current->bondTo(next, SINGLE); 
		current = next; 
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

vector<vector<BondType>  > HydroCarbon::createBondTable()
{
	vector<vector<BondType>  > format(carbon);
	// Fill first half with 0 
	for (int i = 0; i < carbon/2; i++)
	{
		format[0].push_back(DOUBLE); 
	}

	// Fill second half with 1
	for (int i = 0; i < carbon/2; i++)
	{
		format[0].push_back(SINGLE); 
	}

	// Swap half the rows
	int index = carbon/2;  
	for (int i = 1; i < carbon/2; i++)
	{
		//Set next array to last one
		format[i] = format[i-1];

		int tempIndex = index; 
		//Do this i times. i is number of swaps
		for (int j = 0; j < i; j++)
		{
			swap(format[i][tempIndex-1], format[i][tempIndex]); 
			tempIndex+=2; 
		}
		index--; 
	}

	// Fill the rest with the same copies
	for (int i = carbon/2,  j = 1; i < carbon-1; i++, j++)
	{
		format[i] = format[i-2*j]; 
	}

	
	/*	for (int j = 0; j < carbon-1; j++)
		{
			cout << format[j][carbon/2-2]; 
		}
		cout << endl; */

	return format; 
}

// Print Molecule 
void HydroCarbon::printMolecule()
{
	print(head); 
	return; 
}

// Recursively prints the whole molecule, curr is temp current pointer
void HydroCarbon::print( Element* curr)
	// TODO PRINT BACKBONE? OR ALL
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