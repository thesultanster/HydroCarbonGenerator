#ifndef __ELEMENT_H__
#define __ELEMENT_H__


class Element
{
		// Abreviation 
	string name; 
	// Full name 
	string full_name; 
	int atomic_number; 
	double atomic_mass; 
	int valence; 
	// Checks if element visisted for...
	bool visited; 

	vector<Element* > bond; 

public: 

	Element(); 
	// Default constructor name is always abbreviation. Not "Carbon" but "C"
	Element( string name, Periodic_Table & table );
	friend ostream& operator<<(ostream& os, const Element& element);
};

Element::Element()
{
	atomic_number = 0; 
	valence = 0; 
	atomic_mass = 0.0;
	visited = false; 
}

// The name should be the abbreviation
Element::Element( string name, Periodic_Table & table)
{
	this->name = name; 
	this->full_name = table.getFullName(name); 
	this->atomic_mass = table.getMass(name);
	this->valence = table.getValence(name);
	this->atomic_number = table.getNumber(name); 
	this->bond.resize(this->valence); 
}

ostream& operator<<(ostream& os, const Element& element)
{
	os << element.full_name << "(" << element.name << ")" << endl;
	os << "Valence: " << element.valence  << endl;
    return os;
}

#endif