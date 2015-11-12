
#include "allocation.h"

void allocation::output() {
	for(int i=0; i<tnum_; i++) {
		for(int j=0; j<rnum_; j++)
			std::cout<<alloc[i][j]<<'\t';
		std::cout<<std::endl;
	}
}
