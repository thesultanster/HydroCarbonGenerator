#include <iostream>
#include <string>
#include <vector> 
#include <cctype>
#include <map>
#include <fstream> 
using namespace std; 
#include "PeriodicTable.h"
#include "Element.h"
#include "Molecule.h"
#include "HydroCarbon.h"



int main()
{
    string input; 

	//cin >>  input; 

	//Molecule molecule(input); 

	HydroCarbon my_hydro_carbon(6,6);
	//cout << my_hydro_carbon.myIdh() << endl;

	my_hydro_carbon.printMolecule();

	// TO STOP WINDOW FROM CLOSING
	cin >> input; 
}
