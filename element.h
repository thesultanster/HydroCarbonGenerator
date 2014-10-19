#ifndef __ELEMENT_H__
#define __ELEMENT_H__
struct Bond; 

class Element
{

	Periodic_Table  table;

	// Abreviation 
	string name; 
	// Full name 
	string full_name; 
	int atomic_number; 
	double atomic_mass; 
	int valence; 
	// Checks if element visisted for...
	bool visited; 

	// Vector of all bonds
	vector<Bond > bonds; 

public: 

	Element(); 
	// Default constructor name is always abbreviation. Not "Carbon" but "C"
	Element( string name);
	int getValence();
	Element* bondTo(Element* bondTo , int bondNum ); 
	friend ostream& operator<<(ostream& os, const Element& element);
};

struct Bond 
{
	Bond(Element* bond,  int weight )
	{
		this->weight = weight; 
		this->bond = bond; 
	}

	int weight; 
	Element* bond; 
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

Element* Element::bondTo(Element* bondTo , int bondNum)
{
	this->bonds.push_back( Bond(bondTo, bondNum)); 
	this->valence -= bondNum; 
	return bondTo; 
}

#endif