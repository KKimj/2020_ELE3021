#include "types.h"
#include "stat.h"
#include "user.h"


int main(int argc, char *argv[])
{
    printf(1, "start\n");
    int i;
    for(;;)
    {
	    i = 0;
	    while(i<1000)
	    {
		printf(1, "time : %d", uptime());
		    i++;
	    }
   	
    }
    
    
    exit();
}
