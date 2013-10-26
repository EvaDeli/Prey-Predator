#include "Animal.h"
#include "Cell.h"
#include "Grid.h"
#include <assert.h>
#include <new.h> //for no throw
#include <iostream>


CGrid::CGrid(unsigned int dim_x, unsigned int dim_y):
	_dim_x(dim_x), _dim_y(dim_y), _dim_x_with_halo(dim_x+2), _dim_y_with_halo(dim_y+2), _cells(0){
	assert(dim_x > 0 && dim_y > 0 && "Both grid dimensions need to be greater than 0");
	_cells = new(std::nothrow) CCell[_dim_y_with_halo*_dim_x_with_halo];
	assert(_cells != 0);
	for(int i = 0; i < _dim_y_with_halo; ++i){
		for(int j=0; j < _dim_x_with_halo; ++j){
			_cells[i*_dim_x_with_halo+j].setType(0);
			_cells[i*_dim_x_with_halo+j].setPumaDensity(0.0f);
			_cells[i*_dim_x_with_halo+j].setHareDensity(0.0f);
		}
	}
	
}

bool CGrid::setLayout(const unsigned int* layout){
	//assumption: layout size=landscape size
	assert(layout != 0 && "Invalid pointer for layout input");

	for(int i = 0; i < _dim_y; ++i){
		for(int j = 0; j < _dim_x; ++j){
			bool status = _cells[(i+1)*_dim_x_with_halo + (j+1)].setType(layout[i*_dim_x+j]);
			if(!status){
				std::cout << "Invalid layout type at row " << i << " column " << j << std::endl;
				return false;
			}
		}
	}
	return true;
}

void CGrid::setPumaDensity(const double* density){
	assert(0 != density && "Invalid pointer for density input");
	for(int i = 0; i < _dim_y; ++i){
		for(int j = 0; j < _dim_x; ++j){
			_cells[(i+1)*_dim_x_with_halo + (j+1)].setPumaDensity(density[i*_dim_x+j]);
		}
	}
}

void CGrid::setHareDensity(const double* density){
	assert(0 != density && "Invalid pointer for density input");
	for(int i = 0; i < _dim_y; ++i){
		for(int j = 0; j < _dim_x; ++j){
			_cells[(i+1)*_dim_x_with_halo + (j+1)].setHareDensity(density[i*_dim_x+j]);
		}
	}
}

void CGrid::updateCells(){
	for(int i = 0; i < _dim_y; ++i){
		for(int j = 0; j < _dim_x; ++j){
			_cells[(i+1)*_dim_x_with_halo+(j+1)].update();
		}
	}
}

void CGrid::printHareDensity(){
	std::cout << "Printing Hare Density...\n";
	for(int i = 0; i < _dim_y; ++i){
		for(int j = 0; j < _dim_x; ++j){
			std::cout << _cells[(i+1)*_dim_x_with_halo+(j+1)].getHareDensity() << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "Done." << std::endl << std::endl;
}

void CGrid::printPumaDensity(){
	std::cout << "Printing Puma Density...\n";
	for(int i = 0; i < _dim_y; ++i){
		for(int j = 0; j < _dim_x; ++j){
			std::cout << _cells[(i+1)*_dim_x_with_halo+(j+1)].getPumaDensity() << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "Done." << std::endl << std::endl;
}

const CCell* CGrid::getNeighbor(int cordX, int cordY, CGrid::NEIGHBOR position){
	
	CCell* Neighbor = 0;

	if(cordX*cordY > 0 || cordX*cordY < (_dim_x*_dim_y)) {
		switch(position){
		case NORTH:
			Neighbor = _cells+(cordY-1)*_dim_x_with_halo+cordX;
			break;
		case SOUTH:
			Neighbor = _cells+(cordY+1)*_dim_x_with_halo+cordX;
			break;
		case EAST:
			Neighbor = _cells+cordY*_dim_x_with_halo+(cordX+1);
			break;
		case WEST:
			Neighbor = _cells+cordY*_dim_x_with_halo+(cordX-1);
			break;
		}
	}
	
	return Neighbor;
}

CGrid::SIMULATION_ERROR CGrid::simulate(char* outfile, int steps, float delta_t, double pumaBirthRate, double pumaDeathRate, double pumaFusionRate, double hareBirthRate, double hareDeathRate, double hareFusionRate){
	assert(0 != outfile && "Invalid pointer for density input");
	for(float T=0; T<steps; T=T+delta_t){
		for(int i = 0; i < _dim_y; ++i){
			for(int j = 0; j < _dim_x; ++j){
				if(_cells[(i+1)*_dim_x_with_halo + (j+1)].isLand()){
					const CCell* northCell = getNeighbor(i+1,j+1,NORTH);
					assert(northCell != 0);
					const CCell* southCell = getNeighbor(i+1,j+1,SOUTH);
					assert(southCell != 0);
					const CCell* eastCell  = getNeighbor(i+1,j+1,EAST);
					assert(eastCell != 0);
					const CCell* westCell  = getNeighbor(i+1,j+1,WEST);
					assert(westCell != 0);
					CCell* currentCell	   = _cells+(i+1)*_dim_x_with_halo+(j+1);

					unsigned int surroundingLandCells = 
						northCell->isLand()+southCell->isLand()+eastCell->isLand()+westCell->isLand();

					currentCell->calcNewPumaDensity(northCell->getPumaDensity(),southCell->getPumaDensity(),
										eastCell->getPumaDensity(), westCell->getPumaDensity(),
										currentCell->getHareDensity(), delta_t, pumaBirthRate, pumaDeathRate, pumaFusionRate, surroundingLandCells);

					currentCell->calcNewHareDensity(northCell->getHareDensity(),southCell->getHareDensity(),
										eastCell->getHareDensity(), westCell->getHareDensity(),
										currentCell->getPumaDensity(), delta_t, hareBirthRate, hareDeathRate, hareFusionRate, surroundingLandCells);
				}
			}
		}
		updateCells();
		printHareDensity();
		printPumaDensity();
	 }
	return SUCCESS;
}

CGrid::~CGrid(){
	delete [] _cells;
}
