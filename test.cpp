#include <iostream>
#include <cassert>
#include <time.h>
#include <vector>

#include "StackAlloc.h"

#define ELEMS 1000000
#define REPS  50

int main(void)
{
	clock_t start;
	
	//对于int,使用默认的空间配置器
	StackAlloc<int,std::allocator<int> > stackdefault;
	start = clock();
	int i,j;
	for(i=0;i<REPS;i++)
	{
		assert(stackdefault.empty());
		for(j=0;j<ELEMS;j++)
		{
			stackdefault.push(i);
			stackdefault.push(i);
			stackdefault.push(i);
			stackdefault.push(i);
		}
		
		for(j = 0;j<ELEMS;j++)
		{
			stackdefault.pop();
			stackdefault.pop();
			stackdefault.pop();
			stackdefault.pop();
		}
	}
	std::cout <<"Default Allocator time:";
	std::cout << ((double)clock()-start)/CLOCKS_PER_SEC << "\n";
}
