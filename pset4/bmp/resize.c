/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
		// ensure proper usage
		if (argc != 4)
		{
				printf("Usage: resize n infile outfile\n");
				return 1;
		}

		// Check the factor
		int factor = atoi(argv[1]);
		if(factor < 0 || factor > 100)
		{
				printf("The resize factor should lie between 0 and 100\n");
				return 2;
		}

		char* infile = argv[2];
		char* outfile = argv[3];

		// open input file 
		FILE* inptr = fopen(infile, "r");
		if (inptr == NULL)
		{
				printf("Could not open %s.\n", infile);
				return 3;
		}

		// open output file
		FILE* outptr = fopen(outfile, "w");
		if (outptr == NULL)
		{
				fclose(inptr);
				fprintf(stderr, "Could not create %s.\n", outfile);
				return 4;
		}

		// read infile's BITMAPFILEHEADER
		BITMAPFILEHEADER bf;
		fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

		// read infile's BITMAPINFOHEADER
		BITMAPINFOHEADER bi;
		fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

		// ensure infile is (likely) a 24-bit uncompressed BMP 4.0
		if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
						bi.biBitCount != 24 || bi.biCompression != 0)
		{
				fclose(outptr);
				fclose(inptr);
				fprintf(stderr, "Unsupported file format.\n");
				return 4;
		}

		// construct bitmap headers for the outfile
		BITMAPFILEHEADER new_bf;
		BITMAPINFOHEADER new_bi;
		
		//new structs	
		new_bf = bf;
		new_bi = bi;
		
		// update height and width
		new_bi.biHeight = bi.biHeight * factor;
		new_bi.biWidth = bi.biWidth * factor;

		// determine padding
		int old_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
		
		int new_padding =  (4 - (new_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

		// Calculate file and image size
		new_bf.bfSize = 54 + new_bi.biWidth * abs(new_bi.biHeight) * 3 + abs(new_bi.biHeight) *  new_padding;
		
		// Formula taken from web
		new_bi.biSizeImage = ((((new_bi.biWidth * new_bi.biBitCount) + 31) & ~31) / 8) * abs(new_bi.biHeight);


		fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

		fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);


        // iterate over the height of the image
		for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
		{
				// Write each line factor no of times
				for (int n = 0; n < factor; n++)
				{
						// iterate over line
						for (int x = 0; x < bi.biWidth; x++)
						{
								RGBTRIPLE triple;

								// read RGB triple from infile
								fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

								// write RGB triple to outfile
								for (int z = 0; z < factor; z++) 
								{
										fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
								}
						}

						// skip over padding in infile
						fseek(inptr, old_padding, SEEK_CUR);

						// then add it to outfile
						for (int k = 0; k < new_padding; k++)
								fputc(0x00, outptr);
        
                        // go back to the beginning of the line
						fseek(inptr, -(bi.biWidth * 3 + old_padding ), SEEK_CUR);

				}
				
				fseek(inptr, bi.biWidth * 3 + old_padding, SEEK_CUR);
		}

		// close infile
		fclose(inptr);

		// close outfile
		fclose(outptr);

		// that's all folks
		return 0;
}
