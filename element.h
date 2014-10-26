#ifndef __ELEMENT_H__
#define __ELEMENT_H__

struct Bond; 
enum BondType { SINGLE, DOUBLE, TRIPLE }; 

class Element
{

	private: 
		Periodic_Table  table;
		// Checks if element visisted for...
		bool visited; 

	public: 
		// Default constructor
		Element(); 
		// Name is always abbreviation. Not "Carbon" but "C"
		Element( string name);

		//==   Variables  ===========================================  
		string name;													// name is abbreviated es: "C" 
		string full_name;  											// Full name ex: "Carbon"
		int atomic_number;										// atomic number = # protons
		double atomic_mass; 
		int valence;													// How many electrons the elements has 
		// Vector of all bonds
		vector<Bond > bonds; 
	
		// == Functions  ===========================================
		int getValence();
		Element* bondTo(Element* bondTo , BondType type ); 
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
	this->valence = 0; 
	this->atomic_mass = 0.0;
	this->visited = false; 
}

// The name should be the abbreviation
Element::Element( string name)
{
	this->name = name; 
	this->full_name = table.getFullName(name); 
	this->atomic_mass = table.getMass(name);
	this->valence = table.getValence(name);
	this->atomic_number = table.getNumber(name); 
}

int Element::getValence()
{
	return this->valence; 
}

ostream& operator<<(ostream& os, const Element& element)
{
	os << element.full_name << " (" << element.name << ")" << endl;
	os << "Valence: " << element.valence  << endl;
	os << "Atomic Mass: " << element.atomic_mass << endl; 
    return os;
}

// *bondTo is the pointer that points to the next element that you want to bond to
//  type is the type of bond: SINGLE DOUBLE TRIPLE
Element* Element::bondTo(Element* bondTo , BondType type)
{
	this->bonds.push_back( Bond(bondTo, type)); 
	this->valence -= type; 
	return bondTo; 
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