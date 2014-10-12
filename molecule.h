#ifndef __MOLECULE_H__
#define __MOLECULE_H__

class Molecule
{
	int valence; 
	
public:
	Molecule();
	Molecule( string input );
};

Molecule::Molecule()
{
	valence = 0;
}

Molecule::Molecule( string input )
{
	valence = 0;
	cout << input << endl; 
}

#endif
