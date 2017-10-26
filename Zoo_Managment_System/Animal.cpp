#pragma warning( disable : 4996 ) // localtime

#include "Animal.h"

void Animal::setName(const string& name) throw(const char *)
{
	if (name.empty() )
		throw "Animal name can not be empty";

	this->name = name;
}

void Animal::setWeight(float weight) throw(const char *)
{
	if (weight <= 0)
		throw "The weight of the animal must be positive";

	this->weight = weight;
}

void Animal::setBirthYear(int birthYear) throw(const char *)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	if (birthYear < 0 || birthYear > 1970 + ltm->tm_year)
		throw "The year of birth of an animal must be positive and smaller than the current year";

	this->birthYear = birthYear;
}

Animal::Animal(const string& name, float weight, int birthYear, const Area * area)
{
	setName(name);
	setWeight(weight);
	setBirthYear(birthYear);
}

Animal::~Animal()
{}

inline const string& Animal::getName() const
{
	return this->name;
}

inline float Animal::getWeight() const
{
	return this->weight;
}

inline int Animal::getBirthYear() const
{
	return this->birthYear;
}

ostream & operator<<(ostream & os, const Animal & animal)
{
	os << "name= " << animal.name.data() << ", weight= " << animal.weight << ", birthYear= " << animal.birthYear;
	animal.toOs(os);
	return os;
}
