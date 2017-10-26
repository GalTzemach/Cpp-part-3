//
//  Zoo.h
//  Zoo_Management_System
//
//  Created by Almog Segal on 18/08/2017.
//  Copyright © 2017 Almog Segal. All rights reserved.
//

#ifndef __ZOO_H
#define __ZOO_H

#include "Area.h"
#include "Worker.h"
#include "Animal.h"

#include <vector>

class Zoo
{
private:
	string name;
	int maxNumOfAreas;
	int numOfAreas;
	vector<Area*> areas;
	Area quarentineArea;

	// For singletone using
	static Zoo zoo;
	Zoo();

	void setMaxNumOfAreas(int maxNumOfAreas) throw (const char*);
	void setName(const string& name) throw (const char*);

public:
	// For singletone using
	static Zoo* getInstance();

	void updateProperties(const char* name, int maxNumOfAreas, Area* quarantineArea) throw (const char*);


	// Zoo(const string& name, int maxNumOfAreas, const Area& quarentineArea);  //singleton
	~Zoo();

	Zoo(const Zoo& other) = delete;
	const Zoo& operator=(const Zoo& zoo) = delete;

	const string& getName() const;

	int getMaxNumOfAreas() const;

	int getNumOfAreas() const;

	const Area& getQuarentineAreaArea() const;

	void addArea(Area& area)  throw (const char *);

	void addAnimal(Animal& animal, const string& areaName)  throw (const char*);

	void addWorker(Worker& worker, const string& areaName)  throw (const char*);

	/*vector<const Area*>*/ vector<Area*> getAllAreas() const;///

	const Zoo& operator+(Area& area);

	const Area& operator[](int index) const throw (const char*);

	friend ostream& operator<<(ostream& os, const Zoo& zoo);
};

#endif /* __ZOO_H */
