/* Emotic EPOC daemon that decrypt stream using ECB and RIJNDAEL-128 cipher
 * (well, not yet a daemon...)
 * 
 * Usage: epocd (consumer/research) /dev/emotiv/encrypted output_file
 * 
 * Make sure to pick the right type of device, as this determins the key
 * */

#include <stdio.h>
#include <string.h>

#include "emokit/emokit.h"
   

int main(int argc, char **argv)
{
	struct emokit_device* d;
  
	d = emokit_create();
	printf("Current epoc devices connected: %d\n", emokit_get_count(d, EMOKIT_VID, EMOKIT_PID));
	int r = emokit_open(d, EMOKIT_VID, EMOKIT_PID, 0);
	if(r != 0)
	{
		printf("CANNOT CONNECT: %d\n", r);
		return 1;
	}
	printf("Connected\n");
	while(1)
	{
		printf("Starting read\n");
		if(emokit_read_data(d) > 0)
		{
			printf("Read data!\n");
			struct emokit_frame c;
			c = emokit_get_next_frame(d);
			printf("%d %d %d %d %d %d\n", c.counter, c.gyroX, c.gyroY, c.F3, c.FC6, c.P7);
		  
			fflush(stdout);
		}
	}

	emokit_close(d);
	emokit_delete(d);
	return 0;
}
