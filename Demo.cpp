#include "Demo.h"


Demo::Demo(const std::string& name) : name(name)
{
	getDemos().push_back(this);
}



std::list<Demo*> &Demo::getDemos()
{
	static std::list<Demo*> demos;
	return demos;
}