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

	cout << "Making Propane" << endl;
	cout << "===========================================" << endl; 

	HydroCarbon my_hydro_carbon1(3,8);
	my_hydro_carbon1.printMolecule();
	
	cout << "Making Benzene  Isomer" << endl;
	cout << "===========================================" << endl; 

	HydroCarbon my_hydro_carbon2(6,6);
	my_hydro_carbon2.printMolecule();
	
	// TO STOP WINDOW FROM CLOSING
	cin >> input; 
}
