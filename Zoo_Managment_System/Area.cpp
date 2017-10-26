#include "Area.h"

Area::Area()
{
}

void Area::initAttributes(const string& name, int maxNumberOfAnimals, int maxNumberOfWorkers, const AreaManager* areaManager) throw (const char*)
{
	this->setName(name);
	this->setMaxNumberOfAnimals(maxNumberOfAnimals);
	this->setMaxNumberOfWorkers(maxNumberOfWorkers);
	if (areaManager != nullptr)
		this->setAreaManager(*areaManager);
}

void Area::setMaxNumberOfAnimals(int maxNumberOfAnimals) throw(const char *)
{
	if (maxNumberOfAnimals <= 0)
		throw "Maximum number of animals per area must be positive";

	this->maxNumberOfAnimals = maxNumberOfAnimals;
}

void Area::setMaxNumberOfWorkers(int maxNumberOfWorkers) throw(const char *)
{
	if (maxNumberOfWorkers < 0)
		throw "Maximum number of worker in each area can not be negative";

	this->maxNumberOfWorkers = maxNumberOfWorkers;
}

void Area::setName(const string& name) throw(const char *)
{
	if (name.empty())
		throw "Area name can not be empty";

	this->name = name;
}

Area::Area(const string& name, int maxNumberOfAnimals, int maxNumberOfWorkers, AreaManager * areaManager)
	: numOfAnimals(0), numOfWorkers(0)
{
	setName(name);
	setMaxNumberOfAnimals(maxNumberOfAnimals);
	setMaxNumberOfWorkers(maxNumberOfWorkers);

	if (areaManager != nullptr)
		setAreaManager(*areaManager);
}

Area::~Area()
{}

const string& Area::getName() const
{
	return this->name;
}

inline int Area::getNumOfAnimals() const
{
	return this->numOfAnimals;
}

int Area::getMaxNumberOfAnimals() const
{
	return this->maxNumberOfAnimals;
}

inline int Area::getNumOfWorkers() const
{
	return this->numOfWorkers;
}

int Area::getMaxNumberOfWorkers() const
{
	return this->maxNumberOfWorkers;
}

const AreaManager& Area::getAreaManager() const
{
	return *(this->areaManager);
}

void Area::setAreaManager(const AreaManager& areaManager)
{
	if (this->areaManager == nullptr)
	{
		this->areaManager = (AreaManager*)&areaManager;
	}
	else if (this->areaManager != &areaManager)
	{
		(this->areaManager)->removeArea();
		this->areaManager = (AreaManager*)&areaManager;
	}

	// Notify all workers in this area about the new manager
	notifyWorkers();
}

// For observer Design Pattern 
void Area::notifyWorkers() const
{
	vector<const Worker*> workersVc = this->getAllworkers();
	vector<const Worker*>::const_iterator itr = workersVc.begin();
	vector<const Worker*>::const_iterator itrEnd = workersVc.end();

	for (; itr != itrEnd; ++itr)
		(*itr)->notifyAboutNewManager(this->getAreaManager().getName());
}

void Area::addAnimal(const Animal & animal) throw(const char *)
{
	if (numOfAnimals == maxNumberOfAnimals)
		throw "You can not add an animal to an area that's already full";

	this->animals.addToTail(&animal);
	numOfAnimals++;
}

void Area::addWorker(const Worker & worker) throw(const char *)
{
	if (numOfWorkers == maxNumberOfWorkers)
		throw "You can not add an worker to an area that's already full";

	this->workers.push_back(&worker);
	numOfWorkers++;
}


vector<const Worker *> Area::getAllworkers() const
{
	return workers;
}

const Area & Area::operator+=(const Animal & animal)
{
	addAnimal(animal);
	return *this;
}

bool Area::operator<(const Area & area) const
{
	return this->maxNumberOfAnimals < area.maxNumberOfAnimals;
}

bool Area::operator>(const Area & area) const
{
	return this->maxNumberOfAnimals < area.maxNumberOfAnimals;
}

bool Area::operator==(const Area & area) const
{
	return (this->getName() == area.getName());
}

ostream & operator<<(ostream & os, const Area & area)
{
	os << "name= " << area.name.data()
		<< ", numOfAnimals= " << area.numOfAnimals << " from " << area.maxNumberOfAnimals
		<< ", numOfWorkers= " << area.numOfWorkers << " from " << area.maxNumberOfWorkers
		<< ", areaManager= ";

	if (area.areaManager != nullptr)
		os << area.areaManager->getName().data();
	else
		os << "null";

	os << endl << endl << "Animals: " /*<< endl << "--------"*/;
	for (int i = 0; i < area.numOfAnimals; i++)
	{
		os << endl << *area.animals[i];
	}

	os << endl << endl << "Workers: " /*<< endl << "--------"*/;
	for (int i = 0; i < area.numOfWorkers; i++)
	{
		os << endl << *area.workers[i];
	}

	return os;
}
