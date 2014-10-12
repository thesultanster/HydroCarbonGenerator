#ifndef __MOLECULE_H__
#define __MOLECULE_H__

class Molecule
{
	int valence; 
	vector<pair<string, int> > elements; 
public:
	Molecule();
	Molecule( string input );
	
	void addElement( string & element, string & amount);
	void printElementsSimple(); 
private:
	vector<pair<string, int> > parser( string input ); 

};

Molecule::Molecule()
{
	valence = 0;
}

Molecule::Molecule( string input )
{
	valence = 0;
	parser(input); 
}

vector<pair<string, int> > Molecule::parser( string input )
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

	printElementsSimple();
	return elements;
}

void Molecule::addElement( string & element, string & amount)
{
	pair<string, int> my_pair;
	my_pair.first  = element; 
	my_pair.second = atoi(amount.c_str());

	element = ""; 
	amount = ""; 

	elements.push_back(my_pair); 
}

void Molecule::printElementsSimple()
{
	for (int i = 0; i < elements.size(); i++)
	{
		cout << "Element: " << elements[i].first << " Amount: " << elements[i].second << endl; 
	}
}

#endif
