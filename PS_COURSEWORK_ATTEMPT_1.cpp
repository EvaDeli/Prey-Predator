// PS_COURSEWORK_ATTEMPT_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Grid.h"
#include <iostream>



int _tmain(int argc, _TCHAR* argv[])
{
	using namespace std;
	unsigned int layout[4] = {0,1,1,1};
	double pumaDensity[4] = {0, 4.77f, 2.669f, 0.904f};
	double hareDensity[4] = {0, 1.329f, 4.14f, 4.312f};

	double hareBirthRate		= 0.08f;
	double predationRate		= 0.04f;
	double pumaBirthRate		= 0.02f;
	double pumaDifusionRate		= 0.20f;
	double pumaMortalityRate	= 0.06f;
	double hareDiffusionRate	= 0.20f;
	double delta_t				= 0.40f;

	int gridX = 2;
	int gridY = 2;

	CGrid landscape(gridX,gridY);

	cout << "Program description here" << endl;
	
	//use gopt

	/*CFile* file;
	cout << "Opening file " << "layout.dat" << "..." << endl;
	file.open("layout.dat");
	file.read(layout);
	file.close();
	cout << "Done" << endl;
	
	cout << "Opening file " << "puma.dat" << "..." << endl;
	file.open("puma.dat");
	file.read(pumaDensity);
	file.close();
	cout << "Done" << endl;

	cout << "Opening file " << "hare.dat" << "..." << endl;
	file.open("hare.dat");
	file.read(hareDensity);
	file.close();
	cout << "Done" << endl;*/

	bool status = landscape.setLayout(layout);
	if(!status){
		cout << "Invalid landscape type." << endl;
		cout << "acceptable values are 0 = WATER or 1 == LAND" << endl;
		cout << "Aborting program." << endl;
		return 0;
	}

	landscape.setPumaDensity(pumaDensity);
	landscape.setHareDensity(hareDensity);

	//cout << "Creating output file..." << endl;	
	//cout << "Done" << endl;

	cout << "Begin simulation..." << endl;
	landscape.simulate("out.dat", 1, delta_t, pumaBirthRate, pumaMortalityRate, pumaDifusionRate, hareBirthRate, predationRate, hareDiffusionRate);
	cout << "Done" << endl;
	cout << "Program exit" << endl;
	return 0;
}

