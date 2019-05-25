
#include "dictionar.h"



int main()
{
	dictionar <int,int> d;
	d.setWithKey(3, 5); 
	d.setWithKey(5, 6);
	d.setWithKey(4, 1);
	d.setWithKey(7, 11);
	d.setWithKey(1, 3);
	assert(d.search(3)==5);
	assert(d.search(5)==6);
	assert(d.search(8)==1);
	assert(d.getNrElem()==5);

	dictionar <int, int> x;
	x = d;
	assert(x.getNrElem()==5);
	assert(x.search(5)==6);
	assert(x.search(8) == 1);
	x.erase(5);
	assert(x.search(5) == 1);
	x.empty();
	assert(x.getNrElem() == 0);

	assert(d[3] == 5);
	
	d.setWithKey(1, 66);
	assert(d[1] == 66);
	
	system("pause");
	return 0;
}
