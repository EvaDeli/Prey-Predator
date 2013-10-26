#pragma once

class CAnimal{
protected:
	double _density;
	double _tempDensity;
public:
	CAnimal() : _density(0.0f), _tempDensity(0.0f){}
	inline void setDensity(double density){_density = density;}
	inline double getDensity() const{return _density;}
	virtual void calculateNewDensity(double northDensity, double southDensity, double eastDensity, double westDensity, double preyPredatorDensity, double delta_t, double birthRate, double deathRate, double fusionRate, int landArea) = 0;
	inline void update(){_density = _tempDensity; _tempDensity = 0.0f;}
};

class CPredator : public CAnimal{
public:
	virtual void calculateNewDensity(double northDensity, double southDensity, double eastDensity, double westDensity, double preyDensity, double delta_t, double birthRate, double deathRate, double fusionRate, int landArea);
};

class CPrey : public CAnimal{
public:
	virtual void calculateNewDensity(double northDensity, double southDensity, double eastDensity, double westDensity, double predatorDensity, double delta_t, double birthRate, double deathRate, double fusionRate, int landArea);
};
