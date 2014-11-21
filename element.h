#ifndef __ELEMENT_H__
#define __ELEMENT_H__

struct Bond; 
enum BondType { SINGLE, DOUBLE, TRIPLE }; 

class Element
{

	private: 
		Periodic_Table  table;
		

	public: 
		Element();							// Default constructor
		Element( string name);	// Name is always abbreviation. Not "Carbon" but "C"
		Element::Element( string name, int id);  // ID is used to tag each separate element

		//==   Variables  ================================================
		string name;													// Name is abbreviated es: "C" 
		string fullName;  											// Full name ex: "Carbon + #"
		int atomic_number;										// Atomic number = # protons
		double atomic_mass;									// Atomic mass
		int elementValence;										// How many electrons the elements has 
		vector<Bond > bonds;									// Vector of all bonds
		bool visited;													// Checks if element visisted for print functions
		// == Functions  ================================================
		int getValence();
		void bondTo(Element* bondTo , BondType type ); 
		friend ostream& operator<<(ostream& os, const Element& element);
};

struct Bond 
{
	Bond(Element* next,  BondType type )
	{
		this->type = type; 
		this->next = next; 
	}
	BondType type; 
	Element* next; 
}; 

Element::Element()
{
	this->atomic_number = 0; 
	this->elementValence = 0; 
	this->atomic_mass = 0.0;
	this->visited = false; 
}

// Constructor(name is abbreviation ex: "C")
Element::Element( string name)
{
	this->name = name; 
	this->fullName = table.getFullName(name) + " NoID"; 
	this->atomic_mass = table.getMass(name);
	this->elementValence = table.getValence(name);
	this->atomic_number = table.getNumber(name); 
	this->visited = false; 
}

// Constructor(name is abbreviation ex: "C")
// id is jus tused to tag the element by number
Element::Element( string name, int id)
{
	this->name = name; 
	this->fullName = table.getFullName(name) + to_string(id); 
	this->atomic_mass = table.getMass(name);
	this->elementValence = table.getValence(name);
	this->atomic_number = table.getNumber(name); 
	this->visited = false; 
}


int Element::getValence()
{
	return this->elementValence; 
}

ostream& operator<<(ostream& os, const Element& element)
{
	os << element.fullName << " (" << element.name << ")" << endl;
	os << "Valence: " << element.elementValence  << endl;
	os << "Atomic Mass: " << element.atomic_mass << endl; 
    return os;
}

// *bondTo is the pointer that points to the next element that you want to bond to
//  type is the type of bond: SINGLE DOUBLE TRIPLE 
void Element::bondTo(Element* bondTo , BondType type)
{
	int valenceWeight = 0; 
	if( type == SINGLE )
		valenceWeight  = 1; 
	else if( type == DOUBLE )
		valenceWeight = 2; 
	else if( type == TRIPLE )
		valenceWeight = 3; 

	this->bonds.push_back( Bond(bondTo, type));			// Document bond for this element 
	bondTo->bonds.push_back(Bond(this,type));				// Document bond for the element to bond to
	this->elementValence -= valenceWeight;					// Update valence of this element
	bondTo->elementValence -= valenceWeight;				// Update valence of element to bond to
}

/* This overload function allows to print out the bond type of BondType enum
* Example
*
*		BondType type = DOUBLE; 
*		cout << type; 
*      // This will print "Double"
*/
ostream& operator<<( ostream& os, const BondType type )
{
    if(type == SINGLE)
		os << "Single"; 
	else if(type == DOUBLE)
		os << "Double"; 
	else if(type == TRIPLE)
		os << "Triple"; 

    return os;
}
#endif