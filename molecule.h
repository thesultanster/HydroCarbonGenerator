#ifndef __MOLECULE_H__
#define __MOLECULE_H__

class Molecule
{
	protected: 	
		string type;									// Molecule type, ex: HydroCarbon 
		int valence;								// How many electrons open for each molecule 
		int numElements;						// Number of Elements in molecule
		vector<pair<string, int> > elements;		// Splits molecule into elements and amount ex: [ <"C", 6> | <"H", 6 > | <"Cl", 2 > ]
		
		// Element pointers of backbone ex:  (head)-->  C => C -> C => C   <--(current)
		Element* head;							// Head pointer points to first added element (a carbon)
		Element* current;						// Temp pointer points to last added element 
		Periodic_Table table;				// Periodic Table used for information lookup

	private:
		void parseSingleMolecule( string input ); 
		void constructMolecule(); 
		void findType(); 

	public:
		Molecule();
		Molecule( string input );
		~Molecule();
		void addElement( string  element, string amount);
		void printElementsSimple(); 

};

Molecule::Molecule()
{
}

// For now, this only parses Single Molecules. 
Molecule::Molecule( string input )
{
	parseSingleMolecule(input); 
	findType(); 
}

// Parses single molecule input 
void Molecule::parseSingleMolecule( string input )
{
	string element; 
	string amount; 
	pair<string, int> my_pair;

	bool two_char = false; 
	bool found_number = false; 

	for (int i = 0; i < input.size(); i++)
	{
		// If char
		if( isalpha(input[i]) )
		{
			// If last element was a number
			if(found_number)
			{
				found_number = false; 

				// save the last Element of molecule 
				addElement(element,amount);
				element = ""; 
				amount = ""; 
			}

			if(isupper( input[i] ) )
			{
				element = input[i]; 
			}
			else if (islower( input[i] ))
			{
				element += input[i];
			}
		}

		// If number
		else if( isdigit(input[i]) )
		{
			found_number = true; 
			amount += input[i]; 
		}
	}

	// save the last Element of molecule 
	addElement(element,amount);
	element = ""; 
	amount = ""; 
	printElementsSimple();

}


void Molecule::addElement( string  element, string  amount)
{
	pair<string, int> my_pair;
	my_pair.first  = element; 
	my_pair.second = atoi(amount.c_str());

	this->elements.push_back(my_pair); 
}

void Molecule::printElementsSimple()
{
	for (int i = 0; i < this->elements.size(); i++)
	{
		cout << "Element: " << this->elements[i].first << " Amount: " << this->elements[i].second << endl; 
	}
}

void Molecule::findType()
{
	if(elements[0].first == "C" && elements[1].first == "H"  ||  elements[0].first == "H" && elements[1].first == "C")
		type = "HydroCarbon"; 
}

Molecule::~Molecule()
{
	for (int i = 0; i < numElements; i++)
	{

	}
}
#endif
