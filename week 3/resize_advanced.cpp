#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
	
	if (argc != 4)
	{
		fprintf(stderr, "Usage: copy infile outfile\n");
		return 1;
	}

	
	char *eptr = NULL;
	double n = strtod(argv[1], &eptr);
	int a = (int)(1 / n);
	char *infile = argv[2];
	char *outfile = argv[3];
	bool makeSmall = false;
	bool makeBigger = false;
	if (a < 1) makeBigger = true;
	else makeSmall = true;

	
	FILE *inptr = fopen(infile, "r");
	if (inptr == NULL)
	{
		fprintf(stderr, "Could not open %s.\n", infile);
		return 2;
	}

	
	FILE *outptr = fopen(outfile, "w");
	if (outptr == NULL)
	{
		fclose(inptr);
		fprintf(stderr, "Could not create %s.\n", outfile);
		return 3;
	}

	
	BITMAPFILEHEADER bf;
	fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

	
	BITMAPINFOHEADER bi;
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

	
	if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
		bi.biBitCount != 24 || bi.biCompression != 0)
	{
		fclose(outptr);
		fclose(inptr);
		fprintf(stderr, "Unsupported file format.\n");
		return 4;
	}

	int padding = (4 - (bi.biWidth* sizeof(RGBTRIPLE)) % 4) % 4;

	if (makeBigger)
		bi.biWidth *= n;
	else
		bi.biWidth /= a;
	
	int padding2 = (4 - (bi.biWidth* sizeof(RGBTRIPLE)) % 4) % 4;

	if (makeBigger)
		bi.biHeight *= n;
	else
		bi.biHeight /= a;

	bf.bfSize = bf.bfOffBits + (((bi.biWidth* sizeof(RGBTRIPLE)) + padding2) *bi.biHeight *-1);
	bi.biSizeImage = bf.bfSize - bf.bfOffBits;
	printf("%d", bf.bfSize);

	fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

	fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

	
	if (makeBigger)
	{
		bi.biHeight /= n;
		bi.biWidth /= n;
	}
	else
	{
		bi.biHeight *= a;
		bi.biWidth *= a;
	}

	int height = 0;

	if (bi.biHeight < 0) height = bi.biHeight *-1;
	else height = bi.biHeight;

	int width = bi.biWidth;

	RGBTRIPLE triples[height][width];

	for (int i = 0; i < height; i++)
	{

		for (int j = 0; j < width; j++)
		{

			RGBTRIPLE triple;

			fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

			triples[i][j].rgbtBlue = triple.rgbtBlue;
			triples[i][j].rgbtRed = triple.rgbtRed;
			triples[i][j].rgbtGreen = triple.rgbtGreen;
		}

		fseek(inptr, padding, SEEK_CUR);
	}

	int height2 = (int)(height *n);
	int width2 = (int)(width *n);

	RGBTRIPLE triples2[height2][width2];

	if (makeBigger)
	{
		for (int i = 0; i < height; i++)
		{

			for (int j = 0; j < width; j++)
			{

				
				for (int k = 0; k < n; k++)
				{
					for (int l = 0; l < n; l++)
					{
						triples2[((int)(i *n)) + k][((int)(j *n)) + l] = triples[i][j];
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0, k = 0; i < height; i += a, k++)
		{

			for (int j = 0, l = 0; j < width; j += a, l++)
			{

				triples2[k][l] = triples[i][j];
			}
		}
	}

	for (int i = 0; i < height2; i++)
	{

		for (int j = 0; j < width2; j++)
		{

			RGBTRIPLE triple = triples2[i][j];

			fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
		}

		for (int k = 0; k < padding2; k++)
			fputc(0x00, outptr);
	}


    
    fclose(inptr);

   
    fclose(outptr);

    
    return 0;
}
