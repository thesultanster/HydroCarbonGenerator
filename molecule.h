#ifndef __MOLECULE_H__
#define __MOLECULE_H__

class Molecule
{
	protected: 	
		string type;									// Molecule type, ex: HydroCarbon 
		int valence;								// How many electrons open for each molecule 
		int numElements;						// Number of Elements in molecule
		map<string, vector<Element* > > elements;		// Splits molecule into elements and pointers to all of themt 
																							// ex: ( <"C", [-> -> -> ] >   |  <"H", [-> ] >    |  <"Cl",[ -> ->] > )
		
		// Element pointers of backbone ex:  (head)-->  C => C -> C => C   <--(current)
		Element* head;							// Head pointer points to first added element (a carbon)
		Element* current;						// Temp pointer points to last added element 
		Periodic_Table table;				// Periodic Table used for information lookup

	public:
		Molecule();
		~Molecule();

};

// Constructor
Molecule::Molecule()
	: valence(0), numElements(0) {}


// Destructor
Molecule::~Molecule()
{
	// Iterate through all element types, and then delete all pointers 
	typedef map<string, vector<Element* > >::iterator it;
	for(it iterator = elements.begin(); iterator != elements.end(); iterator++) 
		for (int i = 0; i < iterator->second.size(); i++)
			delete iterator->second[i]; 

}
#endif
