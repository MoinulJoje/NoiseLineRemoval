#include <stdio.h>

#include <time.h>

/* The only leptonica header file you normally need to include: */

#include <allheaders.h>


#define LEPT_ERROR 1

#define LEPT_OK 0

#define   FILE_16BPP    "test16.tif"

#define   FILE_G3       "junkout_g3.tif"

#define   FILE_G4       "junkout_g4.tif"

#define   FILE_RLE      "junkout_rle.tif"

#define   FILE_PB       "junkout_packbits.tif"

#define   FILE_LZW      "junkout_lzw.tif"

#define   FILE_ZIP      "junkout_zip.tif"

#define   FILE_TIFF     "junkout.tif"

#define   FILE_1        "testproc1.tif"

#define   FILE_2        "testproc2.tif"

#define   FILE_3        "testproc3.tif"

#define   FILE_4        "testproc4.tif"

#define   FILE_5        "testproc5.tif"

#define   FILE_6        "testproc6.tif"

#define   FILE_7        "testproc7.tif"

#define   FILE_8        "testproc8.tif"

#define   FILE_9        "testproc9.tif"

#define   FILE_10       "testresult.tif"

#define   FILE_11       "testproc10.tif"



/*static const char *tempmtiff = "/tmp/junkmtiff";

static const char *tempnewmtiff = "/tmp/junknewmtiff";

*/

static char  mainName[] = "mtiflineremoval";



main(int argc, char **argv)

{

    char         *tempname;

    l_uint8      *data;

    l_int32      i, d, n, success, failure, same;

    l_int32      w, h, bps, spp;

    size_t       size, nbytes;

	char         *filein, *fileout;

    /* char         buffer[512]; */

    l_int32      count, npages, length;

    FILE         *fp1;

    /* NUMA        *naflags, *nasizes; */

    /* PIX          *pix1, *pix2, *pix4, *pix8, *pix16, *pix32; */

    PIX          *pixtif;

    /* PIXA         *pixa; */

    /* L_REGPARAMS  *rp;

	SARRAY      *savals, *satypes, *sa; */

	time_t startTime,endTime;
    double timeDiff;


	if (argc != 3)

    exit(ERROR_INT(" Syntax:  mtiflineremoval filein fileout", mainName, 1));

 

    filein = argv[1];

    fileout = argv[2];

	fprintf(stderr, "filein=%s fileout=%s\n", filein, fileout);



    time(&startTime);

    fprintf(stderr, " starting time is : %s\n",ctime(&startTime));



    /* read count of tiff multipage */

	fp1 = lept_fopen(filein, "rb");

    if (fileFormatIsTiff(fp1)) {

         tiffGetCount(fp1, &npages);

         fprintf(stderr, " Tiff: %d page\n", npages);

    }

    else

	{

		fp1 = NULL;

		exit(ERROR_INT(" file not tiff", mainName, 1));

	}

    lept_fclose(fp1);



	if (npages == 1)

	{

		/* read one beyond to catch error */

		pixtif = pixReadTiff(filein, 0);

		if (!pixtif) 

		{  

			fprintf(stderr, " Failed on reading Tiff: %d page\n", npages);

		}

		else

		{

			if (ioRemoveLineNoise(pixtif, fileout, npages)) success = FALSE; 

			/* success = FALSE; */

			if (success)

			{

				/* L_INFO("Processed Tiff page ", mainName); */

				fprintf(stderr, " Processed Tiff: %d page\n", npages); 	

			}

			else

			{

				/* L_INFO("Failed on processing Tiff page ", mainName); */

				fprintf(stderr, " Failed on processing Tiff: %d page\n", npages); 

			}

			pixDestroy(&pixtif);

	    

			if (!success) 

			{

				success = TRUE;

				failure = TRUE;

			}

		}

	}

	else

	{

		/* read in each page in file */

		for (i = 0; i < npages; i++) 

		{   

			 /* read one beyond to catch error */

			 /* fprintf(stderr, " Reading Tiff: %d page\n", i); */

			 /*if (i < npages)

			 {*/

				 pixtif = pixReadTiff(filein, i);

				 if (!pixtif) 

				 {  

					 fprintf(stderr, " Failed on reading Tiff: %d page\n", i);

					 break;

				 }

				 else

				 {

					/* fprintf(stderr, " Reading Tiff: %d page\n", i); */

					if ( i < 2)

					{

						/*pixWriteTiff(FILE_10, pixtif, IFF_TIFF_G4, "a"); */

						if (i == 0)

						{

							pixWriteTiff(fileout, pixtif, IFF_TIFF_G4, "w+");

						}

						else

						{

							pixWriteTiff(fileout, pixtif, IFF_TIFF_G4, "a");					

						}

						

					}

					else

					{						

		 				if (ioRemoveLineNoise(pixtif, fileout, npages)) success = FALSE; 

						if (success)

						{

							/* fprintf(stderr, " Processed Tiff: %d page\n", i); */

						}

						else

						{

							fprintf(stderr, " Failed on processing Tiff: %d page\n", i);

						}



						if (!success) 

						{

							success = TRUE;

							failure = TRUE;

						}

						

					}

					pixDestroy(&pixtif);

				 }

			/* } */

		}

	}

	time(&endTime);

    fprintf(stderr, " ending time is : %s\n",ctime(&endTime));
	timeDiff=difftime(endTime,startTime);
    printf("Time required to execute = %.3f seconds\n", timeDiff);

	exit(0); 

}



/*---------------------------------------------------------------------*

  *             Test function for I/O with different formats            *

  *---------------------------------------------------------------------*/

 #ifdef HAVE_CONFIG_H

 #include "config_auto.h"

 #endif  /* HAVE_CONFIG_H */

 

 l_int32

 ioRemoveLineNoise(PIX  *pixs, const char  *filename1, l_int32 pgcount)

 {

 l_int32   d1, problems1, w1, h1, d2;

 l_float32 angle, conf, deg2rad;

 /* char c1 = ' '; */

 PIX      *pix0, *pix1, *pix2, *pix3, *pix4, *pix5;

 PIX      *pixd, *pix6, *pix7, *pix8, *pix9, *pix10, *pix11, *pix12, *pix13, *pix14, *pix15, *pix16, *pixn;

 PIXCMAP  *cmap1;

 l_int32 status=LEPT_ERROR;




     PROCNAME("ioRemoveLineNoise");

     /*

     if (!filename1)

         return ERROR_INT("filename not defined", procName, 1);

 

     if ((pix0 = pixRead(filename1)) == NULL)

         return ERROR_INT("pix0 not made", procName, 1);

	 */

     pixd = pixClone(pixs);  /* laziness */

     cmap1 = pixGetColormap(pixd);  /* colormap; can be NULL */

      

     pix10 = pixUnpackBinary(pixd, 8, 1);

	 d1 = pixGetDepth(pix10);

	 if (d1 != 8)

	 {

		 /* L_INFO("Depth = 8 ", procName); */

		 pixDestroy(&pix10);

		 pixDestroy(&pixd);

		 return TRUE;

	 }

	 if (pix10 == NULL)

	 {

        /*L_INFO("pix10 is null ", procName); */

		 pixDestroy(&pixd);

		 return TRUE; 

	 }



	 deg2rad = 3.14159 / 180.;



 #if HAVE_LIBTIFF    

	 /*First threshold to binary, extracting enough of the lines 

      *to make a good measurement */ 

	 /*pixGetDimensions(pixd, &w1, &h1, &d2);

	 if (d2 == 4)

	 {

	     L_INFO("d2=4", procName);

	 }

	 if (d2 == 8)

	 {

	     L_INFO("d2=8", procName);

	 }

	 */

	 /* printf("\nd2=%d c1=%c", d2, c1);*/

	 pix1 = pixThresholdToBinary(pix10, 180);  /* 170 */

	 if (pix1 == NULL)

	 {

         L_INFO("pix1 is null ", procName);

		 pixDestroy(&pix10);

		 pixDestroy(&pixd);

		 return TRUE; 

	 }



	 /*compute the skew angle, which turns out to be 0.66 degrees clockwise, 

	   and deskew using an interpolated rotator for anti-aliasing */

	 pixFindSkew(pix1, &angle, &conf); 

     pix2 = pixRotateAMGray(pix10, deg2rad * angle, 255);  /* for 8bpp only */

	 if (pix2 == NULL)

	 {

         L_INFO("pix2 is null ", procName);

		

		 pixDestroy(&pix1);

		 pixDestroy(&pix10);

		 pixDestroy(&pixd);

		 return TRUE; 

	 }



     /* extract the lines to be removed, trying not to get too much else in the process. Unfortunately, 

        we get a lot of light background stuff that we're going to eventually want to save. This is done

		with a grayscale morphological closing with a large horizontal structuring element. */	 

	 pix3 = pixCloseGray(pix2, 23, 1);   /* 51, HORIZ=1 */

	 if (pix3 == NULL)

	 {

         L_INFO("pix3 is null ", procName);



		 pixDestroy(&pix2);

		 pixDestroy(&pix1);

		 pixDestroy(&pix10);

		 pixDestroy(&pixd);

		 return TRUE; 

	 }



     /* We need to solidify them in the vertical direction, and do this with a small grayscale 

        vertical erosion.   */

	 pix4 = pixErodeGray(pix3, 5, 1);  /* VERT=1 */

	 if (pix4 == NULL)

	 {

         L_INFO("pix4 is null ", procName);



		 pixDestroy(&pix3);

		 pixDestroy(&pix2);

		 pixDestroy(&pix1);

		 pixDestroy(&pix10);

		 pixDestroy(&pixd);

		 return TRUE; 

	 }

	 

	 pix5 = pixThresholdToValue(NULL, pix4, 210, 255);

	 if (pix5 == NULL)

	 {

         L_INFO("pix5 is null ", procName);



		 pixDestroy(&pix4);

		 pixDestroy(&pix3);

		 pixDestroy(&pix2);

		 pixDestroy(&pix1);

		 pixDestroy(&pix10);

		 pixDestroy(&pixd);

		 return TRUE; 

	 }

     

	 pix6 = pixThresholdToValue(NULL, pix5, 200, 0);

	 if (pix6 == NULL)

	 {

         L_INFO("pix6 is null ", procName);



		 pixDestroy(&pix5);

		 pixDestroy(&pix4);

		 pixDestroy(&pix3);

		 pixDestroy(&pix2);

		 pixDestroy(&pix1);

		 pixDestroy(&pix10);

		 pixDestroy(&pixd);

		 return TRUE; 

	 }

 

	 pix7 = pixThresholdToBinary(pix6, 210);

	 if (pix7 == NULL)

	 {

         L_INFO("pix7 is null ", procName);



		 pixDestroy(&pix6);

		 pixDestroy(&pix5);

		 pixDestroy(&pix4);

		 pixDestroy(&pix3);

		 pixDestroy(&pix2);

		 pixDestroy(&pix1);

		 pixDestroy(&pix10);

		 pixDestroy(&pixd);

		 return TRUE; 

	 }



	 pixInvert(pix6, pix6); 

     pix8 = pixAddGray(NULL, pix2, pix6);

	 if (pix8 == NULL)

	 {

         L_INFO("pix8 is null ", procName);

		 

		 pixDestroy(&pix7);

		 pixDestroy(&pix6);

		 pixDestroy(&pix5);

		 pixDestroy(&pix4);

		 pixDestroy(&pix3);

		 pixDestroy(&pix2);

		 pixDestroy(&pix1);

		 pixDestroy(&pix10);

		 pixDestroy(&pixd);

		 return TRUE;

	 }



 	 pixDestroy(&pix1);

     pixDestroy(&pix2); 

	 pixDestroy(&pix3);

     pixDestroy(&pix4);      

	 pixDestroy(&pix5);

     pixDestroy(&pix6);      

	 

     pix9 = pixOpenGray(pix8, 9, 1);   /* VERT=1 */

	 if (pix9 == NULL)

	 {

         L_INFO("pix9 is null ", procName);

		 

		 pixDestroy(&pix8);

		 pixDestroy(&pix7);

		 pixDestroy(&pix10);

		 pixDestroy(&pixd);

		 return TRUE;

	 }

	 

	 pixCombineMasked(pix8, pix9, pix7);

	 if (pix8 == NULL)

	 {

         L_INFO("pix8 is null ", procName);

	 }

	 else

	 {

		 pixn = pixConvertTo1(pix8, 180);

		 if (pixn == NULL)

		 {			 

			 L_INFO("pixn is null ", procName);

		 }

		 else

		 {

             pix11=pixConvertTo8(pixn,50);
			 pix12=pixCloseGray(pix11,3,3);
pix13=pixConvertRGBToValue(pix12);
			 pix14=pixBlockconv(pix13,1,1);
			 pix15=pixCloseGray(pix14,3,3);
			 pix16=pixBlockconv(pix15,1,1);
			 status=pixOtsuAdaptiveThreshold(pix16,2000,2000,0,0, 0.0f,NULL,&pix16); //binarization

			 if (pgcount == 1)

			 {

			     pixWrite(filename1, pix16, IFF_TIFF_G4); 

				 L_INFO("Write pg 1 testresult.tif ", procName);

			 }

			 else

			 {

				pixWriteTiff(filename1, pix16, IFF_TIFF_G4, "a");

				/* L_INFO("Write pg n testresult.tif ", procName); */

			 }

			 

		 }

		 pixDestroy(&pixn);
		 pixDestroy(&pix11);
		 pixDestroy(&pix12);
		 pixDestroy(&pix13);
		 pixDestroy(&pix14);
		 pixDestroy(&pix15);
		 pixDestroy(&pix16);
	 }

     problems1 = FALSE;

	 /* L_INFO("before destroy procedure", procName); */

 #endif  /* HAVE_LIBTIFF */



	 pixDestroy(&pix7);

     pixDestroy(&pix8);      

	 pixDestroy(&pix9); 

	 pixDestroy(&pix10);

     pixDestroy(&pixd);

	 /* pixDestroy(&pix0); */



     /* L_INFO("before exit procedure", procName); */

     return problems1;

 }
 
 
