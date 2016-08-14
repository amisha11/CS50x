/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
		FILE* file = fopen("card.raw", "r");	

		if(file == NULL)
		{	
				fclose(file);
				fprintf(stderr, "Couldn't open the file\n");
				return 1;
		}

		// Starting bytes of a jpeg file.
		uint8_t jpg_id1[4] = {0xff, 0xd8, 0xff, 0xe0};
		uint8_t jpg_id2[4] = {0xff, 0xd8, 0xff, 0xe1};

		// jpeg count
		int count = 0;

		// file open indicator
		int open = 0;
		FILE* outp;

	    // Read 512 blocks buffer from file.
		uint8_t buffer[512];
		uint8_t id[4];
		fread(buffer, 512, 1, file);	

        // As long as the file has content
		while(fread(buffer, 512, 1, file) > 0)
		{
				// Add first four bytes into the check buffer
				for(int j = 0; j < 4; j++)
				{
						id[j] = buffer[j];
				}

				// Check for a jpeg signature
				if((memcmp(jpg_id1, id, 4) == 0 ) || (memcmp(jpg_id2, id, 4) == 0))
				{
						// output filename
						char filename[8];
						sprintf(filename, "%03d.jpg", count);

                        if(open == 1)
						{
								fclose(outp);
								outp = fopen(filename, "w");
								fwrite(buffer, sizeof(buffer), 1, outp);
								count++;
						}
						
						if(open == 0)
						{
								outp = fopen(filename, "w");
								fwrite(buffer, sizeof(buffer), 1, outp);
								open = 1;
								count++;
						}
						
				}
				// Till signature not encountered, copy content
				else
				{
						if(open == 1)
						{
								fwrite(buffer, sizeof(buffer), 1, outp);
						}
				}
		}
    
		// Close filehandles, be a good citizen and exit.
    if(outp)
    {
      fclose(outp);
    }

		fclose(file);
		return 0;
}
