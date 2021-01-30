#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


int main(int argc, char *argv[])
{
    
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    
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

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE) ) % 4) % 4;
    
    bi.biWidth *= n;
    
	
    int padding2 = (4 - (bi.biWidth * sizeof(RGBTRIPLE) ) % 4) % 4;
    
    
    bi.biHeight *= n;
    
    bf.bfSize = bf.bfOffBits + (((bi.biWidth * sizeof(RGBTRIPLE)) + padding2) * bi.biHeight * -1);
    bi.biSizeImage = bf.bfSize - bf.bfOffBits;
    printf("%d",bf.bfSize);
    
    
    
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
   
	// input u okumak için tekrar eski deðerlere döndürdük
    bi.biHeight /= n;
    bi.biWidth  /= n;
    
    
    int height = 0;
	
    if (bi.biHeight < 0) height = bi.biHeight * -1;
    else height = bi.biHeight;
	
    int width = bi.biWidth;
	
	
    RGBTRIPLE triples[height][width];

   
    for (int i = 0 ; i< height ; i++)
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
    
    RGBTRIPLE triples2[height*n][width*n];
    
    for (int i = 0 ; i < height; i++)
    {
        
        for (int j  = 0; j < width; j++)
        {
            
			
            for (int k = 0; k < n ; k++)
            {
                for (int l=0; l<n; l++)
                {
                    triples2[(i*n)+k][(j*n)+l] = triples[i][j];
                }
            }
            
        }

    }
    
    for (int i = 0 ; i< height*n; i++)
    {
        
        for (int j = 0; j < width*n; j++)
        {
            
            
            RGBTRIPLE triple = triples2[i][j];
            
            fwrite(&triple,sizeof(RGBTRIPLE),1,outptr);
            
        }
        
        for (int k=0; k<padding2; k++)
            fputc(0x00,outptr);

    }

    
    fclose(inptr);

    
    fclose(outptr);

    
    return 0;
}
