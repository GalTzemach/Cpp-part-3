#pragma warning( disable : 4996 )
#include "Worker.h"
#include "AreaManager.h"

void Worker::setIdNumber(long idNumber) throw(const char *)
{
	if (idNumber <= 0)
		throw "idNumber can not be empty";

	this->idNumber = idNumber;
}

Worker::Worker(const string& name, long idNumber, int salary, Area * area)
{
	setName(name);
	setIdNumber(idNumber);
	setSalary(salary);

	if (area != nullptr)
		setArea(*area);
}

Worker::~Worker()
{}

// Notifies workers about their new manager
void Worker::notifyAboutNewManager(const string& managerName) const
{
	cout << this->getName().data() << " -  your new manager is: " << managerName.data() << endl;
}

const string& Worker::getName() const
{
	return this->name;
}

void Worker::setName(const string& name) throw(const char *)
{
	if (name.empty())
		throw "Worker name can not be empty";

	this->name = name;
}

inline long Worker::getIdNumber() const
{
	return this->idNumber;
}

inline int Worker::getSalary() const
{
	return this->salary;
}

void Worker::setSalary(int salary) throw(const char *)
{
	if (salary < 0) // 0 for a volunteer
		throw "Salary can not be negative";

	this->salary = salary;
}

inline const Area& Worker::getArea() const
{
	return *(this->area);
}

void Worker::setArea(Area & area)
{
	if (this->area != &area) // If not same area
		this->area = &area;
}

void Worker::removeArea()
{
	this->area = nullptr;
}

ostream & operator<<(ostream & os, const Worker & worker)
{
	os << "name= " << worker.name.data() << ", idNumber= " << worker.idNumber << ", salary= " << worker.salary;
	worker.toOs(os);
	return os;
}
