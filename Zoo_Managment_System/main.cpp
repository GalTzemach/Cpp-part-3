// Gal & Tal Tzemach
#pragma warning( disable : 4290 )
#pragma warning( disable : 4018 )

#include <iostream>
using namespace std;

#include <vector>

#include "Zoo.h"
#include "Area.h"
#include "Animal.h"
#include "Worker.h"
#include "AreaManager.h"
#include "Veterinarian.h"
#include "Keeper.h"
#include "MaintenanceWorker.h"
#include "ManagerObserver.h"
#include "Elephant.h"
#include "Giraffe.h"
#include "Horse.h"
#include "Lion.h"
#include "Penguin.h"
#include "Zebra.h"
#include "Zebroid.h"

vector<Area*> createAllAreas(int& numOfAreas, vector<AreaManager*> managers, int& numOfManagers);
vector<AreaManager*> createAreaManagers(int& numOfManagers, int& numOfAreas);
void addAreasToZoo(Zoo& zoo, vector<Area*> areas);
vector<Animal*> createAnimals(int& numOfAnimals);
void addAllAnimalsToZoo(Zoo& myZoo, vector<Animal*> animals);
vector<Keeper*> createAllKeepers(int& numOfKeepers);
void addKeepersToZoo(Zoo& myZoo, vector<Keeper*> keepers);
vector<Veterinarian*> createAllVeterinarian(int& numOfVeterinarian);
void addAllVeterinarianToZoo(Zoo& myZoo, vector<Veterinarian*>vets);

template<class T>
void deleteAllVectorElement(vector<T> vec);


int main()
{
	static constexpr int NUM_OF_AREAS = 3;

	int numOfAreas = NUM_OF_AREAS;
	int numOfManagers;
	int numOfAnimals;
	int numOfKeepers;
	int numOfVeterinarian;

	try
	{
		AreaManager quarantineManager("Meny", 5468, 50000, 20);
		Area quarentineArea("quarentineArea", 4, 4, &quarantineManager);

		Zoo* myZoo = Zoo::getInstance();
		myZoo->updateProperties("My Zoo", 10, &quarentineArea);// Singleton

		vector<AreaManager*> managers = createAreaManagers(numOfManagers, numOfAreas);

		vector<Area*> areas = createAllAreas(numOfAreas, managers, numOfManagers);

		// add all areas
		addAreasToZoo(*myZoo, areas);

		vector<Animal*> animals = createAnimals(numOfAnimals);

		// add animals
		addAllAnimalsToZoo(*myZoo, animals);

		vector<Keeper*> keepers = createAllKeepers(numOfKeepers);

		// add all the keepers
		addKeepersToZoo(*myZoo, keepers);

		vector<Veterinarian*> vets = createAllVeterinarian(numOfVeterinarian);

		// add all vets
		addAllVeterinarianToZoo(*myZoo, vets);

		// print the whole zoo
		cout << " ========" << endl << "||My Zoo||" << endl << " ========" << "\n" << *myZoo << endl << endl;

		// For observer Design Pattern 
		cout << "Set a new manager to area A2 (observer Design Pattern):" << endl;
		(myZoo->getAllAreas()).at(1)->setAreaManager(*(new AreaManager("Tal", 12345, 12000, 10)));
		cout << endl;

		// free all memory
		deleteAllVectorElement(animals);
		deleteAllVectorElement(managers);
		deleteAllVectorElement(areas);
		deleteAllVectorElement(keepers);
		deleteAllVectorElement(vets);

	}
	catch (const char* message)
	{
		cout << message;
	}
	catch (...)
	{
		cout << "Something went wrong" << endl;
	}

	system("pause");
	return 0;
}

vector<AreaManager*> createAreaManagers(int& numOfManagers, int& numOfAreas)
{
	numOfManagers = 3;
	const string managersNames[] = { "Yogev", "Moshe", "Roie" };
	int managersId[] = { 31235, 51455, 84578 };
	int managersSalary[] = { 5000, 4500, 4800 };
	int managersYearsOfExperience[] = { 2, -3, 4 };

	vector<AreaManager*> managers;

	for (int i = 0; i < numOfManagers && i < numOfAreas; i++)
	{
		try
		{
			managers.push_back(new AreaManager(managersNames[i], managersId[i], managersSalary[i], managersYearsOfExperience[i]));
		}
		catch (const char* errMessage)
		{
			cout << "Could not create manager " << managersNames[i].data() << ":" << endl << errMessage << endl << endl;
		}
	}

	return managers;
}

vector<Area*> createAllAreas(int& numOfAreas, vector<AreaManager*> managers, int& numOfManagers)
{
	int maxNumberOfAnimals = 4, maxNumberOfWorkers = 4, wrongMaxNumberOfAnimals = -5;
	const string areasNames[] = { "A1", "A2", "A3" };

	vector<Area*> areas;

	for (int i = 0; i < numOfAreas; i++)
	{
		try
		{
			if (managers.size() > i)
			{
				areas.push_back(new Area(areasNames[i], maxNumberOfAnimals, maxNumberOfWorkers, managers.at(i)));///
			}
			else
				areas.push_back(new Area(areasNames[i], maxNumberOfAnimals, maxNumberOfWorkers, nullptr));

		}
		catch (const char* errMessage)
		{
			cout << "Could not create area " << areasNames[i].data() << ":" << endl << errMessage << endl << endl;
		}
	}

	return areas;
}

void addAreasToZoo(Zoo& zoo, vector<Area*> areas)
{
	for (int i = 0; i < areas.size(); i++)
	{
		try
		{
			zoo.addArea(*areas.at(i));
		}
		catch (const char* errMessage)
		{
			cout << "Area " << areas.at(i)->getName().data() << " was not added to the zoo:" << endl << errMessage << endl << endl;
		}
	}
}

vector<Animal*> createAnimals(int& numOfAnimals)
{
	numOfAnimals = 4;
	const string names[] = { "Horsy", "Pini", "Eli", "Zeze" };

	vector<Animal*> animals;

	for (int i = 0; i < numOfAnimals; i++)
	{
		try
		{
			switch (i%numOfAnimals)
			{
			case 0:
			{
				animals.push_back(new Horse(names[i], 208.5f, 1998, 40.2f));
				break;
			}
			case 1:
			{
				animals.push_back(new Penguin(names[i], 1.2f, 2005, Penguin::CRAB));
				break;
			}
			case 2:
			{
				animals.push_back(new Elephant(names[i], 2.5f, 1752, 1.35f, 2.75f));
				break;
			}
			case 3:
			{
				animals.push_back(new Zebroid(names[i], 1.45f, 2010, 128, 38.6f));
				break;
			}
			}
		}
		catch (const char *errMessage)
		{
			cout << "Could not create animal " << names[i].data() << ":" << endl << errMessage << endl << endl;
		}
	}
	return animals;
}

void addAllAnimalsToZoo(Zoo& myZoo, vector<Animal*> animals)
{
	int numOfAreas = myZoo.getNumOfAreas();

	vector<Area*> areas = myZoo.getAllAreas();

	for (int i = 0; i < animals.size() && i < numOfAreas; i++)
	{
		try
		{
			myZoo.addAnimal(*animals.at(i), areas.at(i)->getName().data());///
		}
		catch (const char* errMessage)
		{
			cout << "Could not add " << animals.at(i)->getName().data() << ":" << endl << errMessage << endl << endl;
		}
	}

	// another animal to the last area
	myZoo.addAnimal(*animals.at(3), areas.at(2)->getName().data());
}

vector<Keeper*> createAllKeepers(int& numOfKeepers)
{
	numOfKeepers = 3;
	const string  keepersNames[] = { "Kipi", "Keepi", "Keepee" };
	int keepersId[] = { 312542, 387542, 955642 }, keeperSalary = 7500;
	Keeper::eAnimal animals[] = { Keeper::PENGUIN, Keeper::ELEPHANT, Keeper::HORSE };

	vector<Keeper*> keepers;

	for (int i = 0; i < numOfKeepers; i++)
	{
		try
		{
			keepers.push_back(new Keeper(keepersNames[i], keepersId[i], keeperSalary, animals[i]));
		}
		catch (const char* errMessage)
		{
			cout << "Could not create keeper " << keepers[i]->getName().data() << endl << ":" << errMessage << endl << endl;
		}
	}

	return keepers;
}

void addKeepersToZoo(Zoo& myZoo, vector<Keeper*> keepers)
{
	int numOfAreas = myZoo.getNumOfAreas();

	vector<Area*> areas = myZoo.getAllAreas();

	for (int i = 0; i < keepers.size() && i < numOfAreas; i++)
	{
		try
		{
			myZoo.addWorker(*keepers.at(i), areas.at(i)->getName().data());
		}
		catch (const char* errMessage)
		{
			cout << "Could not add keeper " << keepers[i]->getName().data() << " to the zoo:" << endl << errMessage << endl << endl;
		}
	}
}

vector<Veterinarian*> createAllVeterinarian(int& numOfVeterinarian)
{
	numOfVeterinarian = 3;
	const string vetsNames[] = { "Dr. Vivi", "Dr. Vuvu", "Dr. Kobi" };
	int vetsId[] = { 45875, 87457, 26584 }, vetsSalary = 10000, vetsLicenseNumbers[] = { 5, 8, 10 };

	vector<Veterinarian*> vets;

	for (int i = 0; i < numOfVeterinarian; i++)
	{
		try
		{
			vets.push_back(new Veterinarian(vetsNames[i], vetsId[i], vetsSalary, vetsLicenseNumbers[i]));
		}
		catch (const char* errMessage)
		{
			cout << "Could not create Veterinarian " << vets[i]->getName().data() << ":" << endl << errMessage << endl << endl;
		}
	}

	return vets;
}

void addAllVeterinarianToZoo(Zoo& myZoo, vector<Veterinarian*>vets)
{
	int numOfAreas = myZoo.getNumOfAreas();
	vector<Area*> areas = myZoo.getAllAreas();

	for (int i = 0; i < vets.size() && i < numOfAreas; i++)
	{
		try
		{
			myZoo.addWorker(*vets.at(i), areas.at(i)->getName().data());
		}
		catch (const char* errMessage)
		{
			cout << "Could not add Veterinarian " << vets.at(i)->getName().data() << " to the zoo:" << endl << errMessage << endl << endl;
		}
	}
}

template<class T>
void deleteAllVectorElement(vector<T> vec)
{
	vector<T>::iterator  itr = vec.begin();
	vector<T>::iterator  itrEnd = vec.end();

	for (; itr != itrEnd; ++itr)
		delete *itr;
}

