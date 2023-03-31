
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "universal.h"

typedef struct {
	char repository[16];
	char repository_id[16];
	unsigned int createdOnYear;
	int  createdOnMonth : 4;
	int  createdOnDay   : 5;
	int  createdOnHour  : 5;
	int  createdOnMin   : 6;
	unsigned char size_kb;
} Image;

Image image[16];
unsigned char imageCount = 0;
#define	MAX_IMAGES	16

extern char *argv[40];
extern unsigned char argc;

unsigned char image_exists(char *id)
{
	unsigned char i;
	for (i=0; i<imageCount; ++i)
	{
		if (!strcmp(image[i].repository_id, id))
			return i;
		if (!strcmp(image[i].repository, id))
			return i;
	}
	return 255;
}

void image_root()
{
   int i;

   if (argc > 2) // wait, there's more
   {
	  cprintf("[%s]\r\n", argv[1]);
      if (!strcmp(argv[1], "pull"))
	     image_pull( argv[2] );
	  return;
   }

   wipeScreen();
   cputs("repository      image id     created on         size\r\n");
   cputs("--------------- --------     ----------------   ------\r\n");
   for (i=0; i<imageCount; ++i)
   {
      cprintf("%-16s%-10s   %4d/%02d/%02d %02d:%02d   %d kb\r\n",
         image[i].repository,
		 image[i].repository_id,

		 image[i].createdOnYear,
		 image[i].createdOnMonth,
		 image[i].createdOnDay,
		 image[i].createdOnHour,
		 image[i].createdOnMin,

		 image[i].size_kb
	  );
   }
}

void image_pull(char *name)
{
	cprintf("attempting to pull %s\r\n", name);
	if (imageCount == MAX_IMAGES)
	{
		cputs("sorry, at max images\r\n");
	    return;
	}

	if (name == NULL)
	{
		cputs("synopsis: image pull <name>\r\n");
		return;
	}

	strncpy(image[imageCount].repository, name, 15);
	sprintf(image[imageCount].repository_id, "%-10x", rand());
	image[imageCount].createdOnYear  = 1970 + rand() % 100;
	image[imageCount].createdOnMonth = 1 + rand() % 12;
	image[imageCount].createdOnDay   = 1 + rand() % 30;
	image[imageCount].createdOnHour  = rand() % 24;
	image[imageCount].createdOnMin   = 1 + rand() % 60;
	image[imageCount].size_kb        = 1 + rand() % 255;

	// done!
	++imageCount; 
}
