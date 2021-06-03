#include "Demo.h"
#include <algorithm>


Demo::Demo(const std::string& name) : name(name)
{
	getDemos().push_back(this);
	getDemos().sort([](Demo* a, Demo* b) { return a->name < b->name;  });
}



std::list<Demo*> &Demo::getDemos()
{
	static std::list<Demo*> demos;
	return demos;
}