#include <osbind.h>
#include "raster.h"
#include "constant.h"

int main()
{	
	UNIT16 *base_16 = (UNIT16 *)Physbase();
	unsigned long *base_32 = (unsigned long *)Physbase();


	plot_something_1(base, 100, 100);
	plot_something_2(base, 200, 200);

	return 0;
}
