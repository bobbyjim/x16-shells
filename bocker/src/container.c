
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "container.h"
#include "universal.h"
#include "image.h"

typedef struct 
{
	char container_id[21];
	char image[17];
	unsigned int createdOnYear;
	int  createdOnMonth : 4;
	int  createdOnDay   : 5;
	int  createdOnHour  : 5;
	int  createdOnMin   : 6;
	unsigned char status;
} Container;

Container container[16];
unsigned char containerCount = 0;

extern char *argv[40];
extern unsigned char argc;

char* translateStatus( unsigned char status )
{
	switch(status)
	{
		case 0: return "ok";
		default: return "dead";
	}
	return "dead";
}

void container_root()
{
   if (argc > 2) // wait, there's more
   {
      if (!strcmp(argv[1], "create"))
	     container_create( argv[2] );
	  return;
   }
}

void container_ps()
{
   unsigned char i;

   wipeScreen();
   cputs("container id        image               created             status\r\n");
   cputs("------------------- ------------------- ------------------- ------\r\n");
   for(i=0; i<containerCount; ++i)
      cprintf("%-20s%-20s%4d/%02d/%02d %02d:%02d    %s\r\n", 
	  	container[i].container_id,
		container[i].image,

		container[i].createdOnYear,
		container[i].createdOnMonth,
		container[i].createdOnDay,
		container[i].createdOnHour,
		container[i].createdOnMin,

		translateStatus(container[i].status));
}

void container_create( char *imageId )
{
	unsigned char id = image_exists( imageId );
	if (id == 255)
	{
		cputs("image does not exist.\r\n");
		return;
	}
	// image exists
	strncpy(container[containerCount].container_id, generateName(), 20 );
	strncpy(container[containerCount].image, imageId, 16);

	container[containerCount].createdOnYear  = 1970 + rand() % 100;
	container[containerCount].createdOnMonth = 1 + rand() % 12;
	container[containerCount].createdOnDay   = 1 + rand() % 30;
	container[containerCount].createdOnHour  = rand() % 24;
	container[containerCount].createdOnMin   = 1 + rand() % 60;

	container[containerCount].status = 0;

	// done!
    cprintf("container [%s] created\r\n", container[containerCount].container_id);
	++containerCount;
}