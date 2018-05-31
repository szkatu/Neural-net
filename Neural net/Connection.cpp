#include "Connection.h"
#include<cstdlib>




Connection::Connection()
{
	weight = (rand() / double(RAND_MAX));//
}


Connection::~Connection()
{
}
