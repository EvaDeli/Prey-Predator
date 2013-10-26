#pragma once
#include "Animal.h"

typedef int LANDSCAPE_TYPE;

class CCell{
	enum TYPE{LAND, WATER};
	LANDSCAPE_TYPE _type; //land or water
	//double _pumaDensity;
	//double _hareDensity;
	CPredator _puma;
	CPrey	  _hare;
public:
	CCell() : _type(0){}
	bool setType(unsigned int);
	inline void setPumaDensity(double density){_puma.setDensity(density);}
	inline double getPumaDensity() const { return _puma.getDensity();}
	inline void setHareDensity(double density){_hare.setDensity(density);}
	inline double getHareDensity() const {return _hare.getDensity();}
	inline void calcNewPumaDensity(double northDensity, double southDensity, double eastDensity, double westDensity, double hareDensity, double delta_t, double birthRate, double deathRate, double fusionRate, int landArea)
	{ _puma.calculateNewDensity(northDensity, southDensity, eastDensity, westDensity, hareDensity, delta_t, birthRate, deathRate, fusionRate, landArea); }
	inline void calcNewHareDensity(double northDensity, double southDensity, double eastDensity, double westDensity, double pumaDensity, double delta_t, double birthRate, double deathRate, double fusionRate, int landArea)
	{ _hare.calculateNewDensity(northDensity, southDensity, eastDensity, westDensity, pumaDensity, delta_t, birthRate, deathRate, fusionRate, landArea); }
	inline void update(){_puma.update();_hare.update();}
	inline unsigned int isLand() const {return _type == 1;}
};
