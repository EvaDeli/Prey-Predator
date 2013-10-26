#pragma once

class CCell;
class CGrid{
	enum NEIGHBOR{NORTH, SOUTH, EAST, WEST};
	unsigned int _dim_x;
	unsigned int _dim_x_with_halo;
	unsigned int _dim_y;
	unsigned int _dim_y_with_halo;
	CCell* _cells;
	

	CGrid(const CGrid&);			// Disallow copy contructor.
	CGrid& operator=(const CGrid&); //Disallow assignment operator

	const CCell* getNeighbor(int cordX, int cordY, NEIGHBOR position);
	void updateCells();
	void printHareDensity();
	void printPumaDensity();
public:
	enum SIMULATION_ERROR{SUCCESS, UNABLE_TO_CREATE_FILE, UNABLE_TO_WRITE_TO_FILE};

	CGrid(unsigned int dim_x, unsigned int dim_y);
	bool setLayout(const unsigned int* layout);
	void setPumaDensity(const double* density);
	void setHareDensity(const double* density);
	SIMULATION_ERROR simulate(char* outfile, int steps, float delta_t, double pumaBirthRate, double pumaDeathRate, double pumaFusionRate, double hareBirthRate, double hareDeathRate, double hareFusionRate);
	~CGrid();
};
