#ifndef __Manager_Observer_H
#define __Manager_Observer_H

//class AreaManager;
#include <iostream>
using namespace std;

class ManagerObserver
{
public:
	virtual void notifyAboutNewManager(const string& managerName) const = 0;
};

#endif // __Manager_Observer_H