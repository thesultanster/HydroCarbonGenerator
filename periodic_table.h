#ifndef __PERIODIC_TABLE_H__
#define __PERIODIC_TABLE_H__


class Periodic_Table
{
	struct Info
	{
		string name; 
		string full_name; 
		int atomic_number; 
		int valence; 
		double atomic_mass; 
	};

	map<string, Info> elementInfo; 

	public:
		Periodic_Table();
		Periodic_Table(string element);
		double getMass( string element); 
		int getNumber( string element); 
		int getValence( string element); 
		string getFullName( string element );
};

Periodic_Table::Periodic_Table()
{

	string name; 

	ifstream in;
	in.open("C:\\Users\\Sultan\\Documents\\GitHub\\organ\\elements.txt");
 
		// If we couldn't open the output file stream for reading
		if (!in.is_open())
		{
			// Print an error and exit
			cerr << "Cant open elements.txt file" << endl;
			exit(1);
		}

		Info temp_info; 
		while( in >> temp_info.name )
		{
			in >> temp_info.full_name; 
			in >> temp_info.atomic_number; 
			in >> temp_info.atomic_mass;
			in >> temp_info.valence; 

			// Add struct to map 
			elementInfo[temp_info.name] = temp_info; 
		}
		

	in.close(); 

}

double Periodic_Table::getMass(string name)
{
	return elementInfo[name].atomic_mass; 
}

int Periodic_Table::getValence(string name)
{
	return elementInfo[name].valence; 
}

int Periodic_Table::getNumber(string name)
{
	return elementInfo[name].atomic_number; 
}

string Periodic_Table::getFullName(string name)
{
	return elementInfo[name].full_name;
}

#endif