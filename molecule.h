#ifndef __MOLECULE_H__
#define __MOLECULE_H__

class Molecule
{
	// Molecule type, ex: Hydro-carbon 
	string type; 
	// How many total electrons open 
	int valence; 
	// Index deficiency of hydrogen 
	int idh; 
	// Splits molecule into elements and amount 
	vector<pair<string, int> > elements; 
	// Pointer to first elemetn
	Element* head; 
	
public:
	Molecule();
	Molecule( string input );
	~Molecule();
	void addElement( string  element, string amount);
	void printElementsSimple(); 

private:
	void parseSingleMolecule( string input ); 
	void constructMolecule(); 

};

Molecule::Molecule()
{
	valence = 0;
}

// For now, this only parses Single Molecules. 
Molecule::Molecule( string input )
{
	valence = 0;
	parseSingleMolecule(input); 
	constructMolecule(); 
	// Calculate idh 
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

void Molecule::constructMolecule()
{

	// Initialize head, pass in name of element in element
	head = new Element(elements[0].first); 
	
	cout << *head << endl; 
}

void Molecule::addElement( string  element, string  amount)
{
	pair<string, int> my_pair;
	my_pair.first  = element; 
	my_pair.second = atoi(amount.c_str());

	elements.push_back(my_pair); 
}

void Molecule::printElementsSimple()
{
	for (int i = 0; i < elements.size(); i++)
	{
		cout << "Element: " << elements[i].first << " Amount: " << elements[i].second << endl; 
	}
}

Molecule::~Molecule()
{
		
}
#endif
