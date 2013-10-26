#include "Animal.h"

void CPredator::calculateNewDensity(double northDensity, double southDensity, double eastDensity, double westDensity, double preyDensity, double delta_t, double birthRate, double deathRate, double fusionRate, int landArea){
	/*divide equation into multiple steps eg.. new density, fusion etc.*/
	double predatorDensity = _density;
	_tempDensity =
		predatorDensity + delta_t*
		(birthRate*preyDensity*predatorDensity - deathRate*predatorDensity + fusionRate*
		((northDensity+southDensity+westDensity+eastDensity)-landArea*predatorDensity));
}

void CPrey::calculateNewDensity(double northDensity, double southDensity, double eastDensity, double westDensity, double predatorDensity, double delta_t, double birthRate, double deathRate, double fusionRate, int landArea){
	double preyDensity = _density;
	_tempDensity =
		preyDensity+delta_t*
		(birthRate*preyDensity-deathRate*preyDensity*predatorDensity + 
		fusionRate*((northDensity+southDensity+westDensity+eastDensity)-landArea*preyDensity));
}
