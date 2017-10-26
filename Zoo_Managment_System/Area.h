//
//  Area.h
//  Zoo_Management_System
//
//  Created by Almog Segal on 01/08/2017.
//  Copyright © 2017 Almog Segal. All rights reserved.
//

#ifndef __AREA_H
#define __AREA_H

#include <iostream>
using namespace std;

#include<vector>

#include "AreaManager.h"
#include "Worker.h"
#include "Animal.h"
#include "MyLinkedList.h"


class Area
{

private:
	string name;
	int numOfAnimals;
	int maxNumberOfAnimals;
	int numOfWorkers;
	int maxNumberOfWorkers;
	AreaManager* areaManager;
	vector<const Worker*> workers;
	
	// Using MyLinkedList
	MyLinkedList<const Animal*> animals;



	void setMaxNumberOfAnimals(int maxNumberOfAnimals) throw (const char*);
	void setMaxNumberOfWorkers(int maxNumberOfWorkers) throw (const char*);
	void setName(const string& name) throw (const char*);

public:
	// For singletone using
	Area();
	void initAttributes(const string& name, int maxNumberOfAnimals, int maxNumberOfWorkers, const AreaManager* areaManager = nullptr) throw (const char*);

	// For observer Design Pattern 
	void notifyWorkers() const;

	Area(const string& name, int maxNumberOfAnimals, int maxNumberOfWorkers, AreaManager* areaManager = nullptr);
	~Area();

	Area(const Area& area) = delete;
	const Area& operator=(const Area& area) = delete;

	const string& getName() const;

	inline int getNumOfAnimals() const;
	int getMaxNumberOfAnimals() const;

	inline int getNumOfWorkers() const;
	int getMaxNumberOfWorkers() const;

	const AreaManager& getAreaManager() const;
	void setAreaManager(const AreaManager& areaManager);

	void addAnimal(const Animal& animal) throw (const char*);

	void addWorker(const Worker& worker) throw (const char*);

	vector<const Worker*> getAllworkers() const;

	const Area& operator+=(const Animal& animal) throw (const char*);

	bool operator<(const Area& area) const;

	bool operator>(const Area& area) const;

	bool operator==(const Area& area) const;

	friend ostream& operator<<(ostream& os, const Area& area);
};

#endif /* __AREA_H */
