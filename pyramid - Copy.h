#pragma once

//#include "colorspace.h"
//for my new class


class pyramid
{
public:

#include "IPlugin.h"


	pyramid(void)
	{	}

	virtual ~pyramid(void)
	{	}
	
};




/*
for (int x = 0; x < nWidth; x++)
{
	for (int y = 0; y < nHeight; y++)
	{
		int nIdx = x * 4 + y * 4 * nWidth;
	}
}*/




/// <summary> Used to print array to screen to see the state of the array. 
/// <para>*imageArray = image array to be printed.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float printArray(float *array, int ImageWidth, int ImageHeight)
{
	char sBuffer6[400];

	sprintf(sBuffer6,"ImageWidth = %d\n ImageHeight = %d"
	                 ,ImageWidth,       ImageHeight);
	MessageBox(NULL,sBuffer6,"Image Resolutions", MB_OK);

	for (int x = 0; x < ImageWidth; x++)
	{
		for (int y = 0; y < ImageHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * ImageWidth;

			float red = array[nIdx1 + CHANNEL_R];

			//if (xx > 120)
			{
				sprintf(sBuffer6,"x = %d\n y = %d\n\n red = %f\n\n"
					             ,x,       y,         red);
				MessageBox(NULL,sBuffer6,"X and Y", MB_OK);
			}
		}
	}
	return 0;
}

/// <summary> Round integer to next nearest power of 2.  i.e. 9 rounds up to 16,  however 16 stays at 16
/// <para>intergerToExpandToTheNearestPowerof2 = interger to round to next nearest power of 2</para>
/// </summary>
int powerOfTwo(int intergerToExpandToTheNearestPowerof2)
{
	return pow(2, ceil(log(intergerToExpandToTheNearestPowerof2)/log(2)));
}

/// <summary> Find out how many pyramid levels the input image can be shrunk to Assuming that the input number is a power of 2.
/// <para>powerOf2Interger = power of 2 number to be processed. MUST BE a power of 2.</para>
/// <para>lowestLevel = the lowest pyramid level you want to shrink the image to.  MUST BE a power of 2.</para>
/// <para>Returns the number of levels the image can be shrunk until the lowest level can be matched. </para>
/// </summary>
int howManyLevelsCanBeProcessed (int powerOf2Interger, int lowestLevel)
{
	char sBuffer6[400];

	if (powerOf2Interger == 0)
		return 0;

	int howManyLevels = 0;

	while (powerOf2Interger > lowestLevel)
	{
		howManyLevels ++;
		powerOf2Interger = powerOf2Interger / 2;

		/*sprintf(sBuffer6,"powerOf2Interger = %d\n\n howManyLevels = %d\n\n lowestLevel = %d\n"
	                 ,powerOf2Interger,         howManyLevels,         lowestLevel);
					   MessageBox(NULL,sBuffer6,"numbers during loop", MB_OK);*/
	}

	//sprintf(sBuffer6,"HALT");MessageBox(NULL,sBuffer6,"stop", MB_OK);


	/*sprintf(sBuffer6,"powerOf2Interger = %d\n\n howManyLevels = %d\n\n lowestLevel = %d\n"
	                 ,powerOf2Interger,         howManyLevels,         lowestLevel);
					   MessageBox(NULL,sBuffer6,"numbers after loop", MB_OK);*/

	return howManyLevels;
}


/// <summary> Copies an image from one array to another, the copy to array can be of any size. if copy to image is smaller, image will truncate. If copy to image is larger will have blank areas.
/// <para>copyFromImage = input image.</para>
/// <para>copyFromImageWidth = width of input image.</para>
/// <para>copyFromImageHeight = height of input image.</para>
/// <para>copyToImage = output image, must be initalized in calling routine.</para>
/// <para>copyToImageWidth = width of output image.</para>
/// <para>copyToImageHeight = height of output image.</para>
/// <para>Returns return *copyToImage </para>
/// </summary>
float copyImageToBottomPyramidLevel(float *copyFromImage, int copyFromImageWidth, int copyFromImageHeight, float *copyToImage, int copyToImageWidth, int copyToImageHeight)
{
	for (int x = 0; x < copyFromImageWidth; x++)
	{
		for (int y = 0; y < copyFromImageHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * copyFromImageWidth;
			//int nIdx2 = x * 4 + y * 4 * copyToImageWidth;

			float red = copyFromImage[nIdx1 + CHANNEL_R];
			float green = copyFromImage[nIdx1 + CHANNEL_G];
			float blue = copyFromImage[nIdx1 + CHANNEL_B];

			copyToImage[nIdx1 + CHANNEL_R] = red;
			copyToImage[nIdx1 + CHANNEL_R] = green;
			copyToImage[nIdx1 + CHANNEL_R] = blue;
		}
	}

	return *copyToImage;
}


/// <summary> Shifts image from the edge to 1/2 kernel input i.e. if using a kernel size of 3, the shift amount is 1.  The edges of the output image will be a reflected copy of the input image.
/// <para>originalImage = Input image.</para>
/// <para>originalImageWidth = Width of input image.</para>
/// <para>originalImage = Height of input image.</para>
/// <para>largerImageArray = Output image.</para>
/// <para>largerImageWidth = Width of output image.</para>
/// <para>largerImageHeight = Height of output image.</para>
/// <para>KernelSizeOddNumberGreaterThanOne = Kernel size to be used. MUST BE an ODD number greater than 1.  Kernel size is automatically cut in half in the routine</para>
/// <para>Returns return *largerImageArray </para>
/// </summary>
float shiftReflectOddKernel(float *originalImage, int originalImageWidth, int originalImageHeight, float *largerImageArray, int largerImageWidth, int largerImageHeight, int KernelSizeOddNumberGreaterThanOne)
{
	int shiftAmount = (KernelSizeOddNumberGreaterThanOne - 1) / 2;

	initalizeArrayNeutralGrey(largerImageArray,largerImageWidth,largerImageHeight);

	//performs a simple copy ignoring the edges for the larger image
	for (int x = 0; x < originalImageWidth; x++)
	{
		for (int y = 0; y < originalImageHeight; y++)
		{
			int xx = x + shiftAmount;
			int yy = y + shiftAmount;
			int nIdx1 = x * 4 + y * 4 * originalImageWidth;
			int nIdx2 = xx * 4 + yy * 4 * largerImageWidth;

			float red = originalImage[nIdx1 + CHANNEL_R];
			float green = originalImage[nIdx1 + CHANNEL_G];
			float blue = originalImage[nIdx1 + CHANNEL_B];

			largerImageArray[nIdx2 + CHANNEL_R] = red;
			largerImageArray[nIdx2 + CHANNEL_G] = green;
			largerImageArray[nIdx2 + CHANNEL_B] = blue;
		}
	}
	//performs a simple copy ignoring the edges for the larger image

	//reflect left border
	for (int x = 0; x < shiftAmount; x++)//width
	{
		for (int y = shiftAmount; y < largerImageHeight - shiftAmount; y++)//height
		{
			int xx = x + shiftAmount;
			int nIdx1 = x * 4 + y * 4 * largerImageWidth;
			int nIdx2 = xx * 4 + y * 4 * largerImageWidth;

			float red1 = largerImageArray[nIdx2 + CHANNEL_R];
			float green1 = largerImageArray[nIdx2 + CHANNEL_G];
			float blue1 = largerImageArray[nIdx2 + CHANNEL_B];

			//float red2 = largerImageArray[nIdx1 + CHANNEL_R];
			/*sprintf(sBuffer6,"x = %d\n y = %d\n\n xx = %d\n\n red1 = %f\n\n red2 = %f"
			                 ,x,       y,         xx,        red1,          red2);
			MessageBox(NULL,sBuffer6,"reflect left border", MB_OK);*/

			largerImageArray[nIdx1 + CHANNEL_R] = red1;
			largerImageArray[nIdx1 + CHANNEL_G] = green1;
			largerImageArray[nIdx1 + CHANNEL_B] = blue1;
		}
	}
	//reflect left border

	//reflect right border
	for (int x = largerImageWidth - shiftAmount; x < largerImageWidth; x++)//width
	{
		for (int y = shiftAmount; y < largerImageHeight - shiftAmount; y++)//height
		{
			int xx = x - shiftAmount;
			int nIdx1 = x * 4 + y * 4 * largerImageWidth;
			int nIdx2 = xx * 4 + y * 4 * largerImageWidth;

			float red1 = largerImageArray[nIdx2 + CHANNEL_R];
			float green1 = largerImageArray[nIdx2 + CHANNEL_G];
			float blue1 = largerImageArray[nIdx2 + CHANNEL_B];
			largerImageArray[nIdx1 + CHANNEL_R] = red1;
			largerImageArray[nIdx1 + CHANNEL_G] = green1;
			largerImageArray[nIdx1 + CHANNEL_B] = blue1;
		}
	}
	//reflect right border

	//reflect bottom border
	for (int y = 0; y < shiftAmount; y++)//height
	{
		for (int x = shiftAmount; x < largerImageWidth - shiftAmount; x++)//width
		{
			int yy = y + shiftAmount;
			int nIdx1 = x * 4 + y * 4 * largerImageWidth;
			int nIdx2 = x * 4 + yy * 4 * largerImageWidth;

			float red1 = largerImageArray[nIdx2 + CHANNEL_R];
			float green1 = largerImageArray[nIdx2 + CHANNEL_G];
			float blue1 = largerImageArray[nIdx2 + CHANNEL_B];

			largerImageArray[nIdx1 + CHANNEL_R] = red1;
			largerImageArray[nIdx1 + CHANNEL_G] = green1;
			largerImageArray[nIdx1 + CHANNEL_B] = blue1;
		}
	}
	//reflect bottom border

	//reflect top border
	for (int y = largerImageHeight - shiftAmount; y < largerImageHeight; y++)//height
	{
		for (int x = shiftAmount; x < largerImageWidth - shiftAmount; x++)//width
		{
			int yy = y - shiftAmount;
			int nIdx1 = x * 4 + y * 4 * largerImageWidth;
			int nIdx2 = x * 4 + yy * 4 * largerImageWidth;

			float red1 = largerImageArray[nIdx2 + CHANNEL_R];
			float green1 = largerImageArray[nIdx2 + CHANNEL_G];
			float blue1 = largerImageArray[nIdx2 + CHANNEL_B];

			largerImageArray[nIdx1 + CHANNEL_R] = red1;
			largerImageArray[nIdx1 + CHANNEL_G] = green1;
			largerImageArray[nIdx1 + CHANNEL_B] = blue1;
		}
	}
	//reflect top border

	return *largerImageArray;
}


/// <summary> Strips off the edge of a reflected kernel to place an image back to its original width and height
/// <para>smallerImage = Original Image.</para>
/// <para>smallerImageWidth = Width of Original image.</para>
/// <para>smallerImageHeight = Height of Original image.</para>
/// <para>largerImageArray = Larger image with reflected edges.</para>
/// <para>largerImageWidth = Width of Larger image.</para>
/// <para>largerImageHeight = Height of Larger image.</para>
/// <para>KernelSizeOddNumberGreaterThanOne = Kernel size to be used. MUST BE an ODD number greater than 1.  Kernel size is automatically cut in half in the routine</para>
/// <para>Returns return *smallerImageArray </para>
/// </summary>
float stripReflectedOddKernelAndMove(float *smallerImageArray, int smallerImageWidth, int smallerImageHeight, float *largerImageArray, int largerImageWidth, int largerImageHeight, int KernelSizeOddNumberGreaterThanOne)
{
	int shiftAmount = (KernelSizeOddNumberGreaterThanOne - 1) / 2;
	char sBuffer6[400];

	//performs a simple copy ignoring the edges for the larger image
	for (int x = shiftAmount; x < largerImageWidth - shiftAmount; x++)
	{
		for (int y = shiftAmount; y < largerImageHeight - shiftAmount; y++)
		{
			int xx = x - shiftAmount;
			int yy = y - shiftAmount;

			int nIdx1 = x * 4 + y * 4 * largerImageWidth;
			int nIdx2 = xx * 4 + yy * 4 * smallerImageWidth;

			float red = largerImageArray[nIdx1 + CHANNEL_R];
			float green = largerImageArray[nIdx1 + CHANNEL_G];
			float blue = largerImageArray[nIdx1 + CHANNEL_B];

			smallerImageArray[nIdx2 + CHANNEL_R] = red;
			smallerImageArray[nIdx2 + CHANNEL_G] = green;
			smallerImageArray[nIdx2 + CHANNEL_B] = blue;

			//just to check results
			/*
			float red1 = smallerImageArray[nIdx2 + CHANNEL_R];

			sprintf(sBuffer6,"x = %d\n y = %d\n\n largerImageWidth = %d\n largerImageHeight = %d\n\n\n red = %f\n\n red1 = %f\n\n"
			                 ,x,        y,        largerImageWidth,       largerImageHeight,           red,         red1);
			MessageBox(NULL,sBuffer6,"Image Resolutions", MB_OK);*/
		}
	}
	//performs a simple copy ignoring the edges for the larger image

	return *smallerImageArray;
}

/// <summary> Strips off the edge of a reflected kernel to place an image back to its original width and height
/// <para>largerImageArray = Larger image with reflected edges.</para>
/// <para>largerImageWidth = Width of Larger image.</para>
/// <para>largerImageHeight = Height of Larger image.</para>
/// <para>KernelSizeOddNumberGreaterThanOne = Kernel size to be used. MUST BE an ODD number greater than 1.  Kernel size is automatically cut in half in the routine</para>
/// <para>Returns return *smallerImageArray </para>
/// </summary>
/*
float stripReflectedOddKernel(float *imageArray, int largerImageWidth, int largerImageHeight, int KernelSizeOddNumberGreaterThanOne)
{
	int shiftAmount = (KernelSizeOddNumberGreaterThanOne - 1) / 2;
	char sBuffer6[400];

	//performs a simple copy ignoring the edges for the larger image
	for (int x = shiftAmount; x < largerImageWidth - shiftAmount; x++)
	{
		for (int y = shiftAmount; y < largerImageHeight - shiftAmount; y++)
		{
			int xx = x - shiftAmount;
			int yy = y - shiftAmount;

			int nIdx1 = x * 4 + y * 4 * largerImageWidth;
			int nIdx2 = xx * 4 + yy * 4 * smallerImageWidth;

			float red = largerImageArray[nIdx1 + CHANNEL_R];
			float green = largerImageArray[nIdx1 + CHANNEL_G];
			float blue = largerImageArray[nIdx1 + CHANNEL_B];

			smallerImageArray[nIdx2 + CHANNEL_R] = red;
			smallerImageArray[nIdx2 + CHANNEL_G] = green;
			smallerImageArray[nIdx2 + CHANNEL_B] = blue;

			//just to check results
			
			float red1 = smallerImageArray[nIdx2 + CHANNEL_R];

			//sprintf(sBuffer6,"x = %d\n y = %d\n\n largerImageWidth = %d\n largerImageHeight = %d\n\n\n red = %f\n\n red1 = %f\n\n"
			//                 ,x,        y,        largerImageWidth,       largerImageHeight,           red,         red1);
			//MessageBox(NULL,sBuffer6,"Image Resolutions", MB_OK);
		}
	}
	//performs a simple copy ignoring the edges for the larger image

	return *smallerImageArray;
}
*/


/// <summary> Shifts image from the edge to 1/2 kernel input i.e. if using a kernel size of 3, the shift amount is 1.  The edges of the output image will be a reflected copy of the input image.
/// <para>largerPyramidLevelArray = Input image.</para>
/// <para>largerPyramidLevelWidth = Width of input image.</para>
/// <para>largerPyramidLevelHeight = Height of input image.</para>
/// <para>smallerPyramidLevelArray = Output image.</para>
/// <para>smallerPyramidLevelWidth = Width of output image.</para>
/// <para>smallerPyramidLevelHeight = Height of output image.</para>
/// <para>Returns return *smallerPyramidLevelArray </para>
/// <para> SEE http://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html or details</para>
/// </summary>
float gaussianReducepyramid(float *largerPyramidLevelArray, int largerPyramidLevelWidth, int largerPyramidLevelHeight, float *smallerPyramidLevelArray, int smallerPyramidLevelWidth, int smallerPyramidLevelHeight)
{
	char sBuffer6[400];

	//each pyramid level 1/2 the height and width of the prior pyramid


	/*sprintf(sBuffer6,"largerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
	                 ,largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
					   MessageBox(NULL,sBuffer6,"Pyramid Resolutions", MB_OK);*/


	//for a fast routine, we will be using the recursive gaussian method

	int radius = 5;

	float wnR, wn1R, wn2R, wn3R;
	float wnG, wn1G, wn2G, wn3G;
	float wnB, wn1B, wn2B, wn3B;

	float b3 = max(radius - 4, radius * 2 / 3) / 4.0; 
	float b0 = 1.57825 + b3 * (2.44413 + b3 * (1.4281 + 0.422205 * b3));
	float b1 = b3 * (2.44413 + b3 * (2.85619 + 1.26661 * b3)) / b0;
	float b2 = (-1.4281 - 1.26661 * b3) * b3 * b3 / b0;
	b3 = 0.422205 * b3 * b3 * b3 / b0;
	b0 = 1.0 - (b1 + b2 + b3);


	float* horizontal = new float[largerPyramidLevelWidth * largerPyramidLevelHeight * 4]; // this is our temporary buffer to store image blurred horizontally
	float* temp = new float[largerPyramidLevelWidth * largerPyramidLevelHeight * 4];

	float* putR = new float[radius];
	float* putG = new float[radius];
	float* putB = new float[radius];

	int widthminus = largerPyramidLevelWidth - 1;
	int heightminus = largerPyramidLevelHeight - 1;


	//blur horizontal
	for (int y = 0; y < largerPyramidLevelHeight; ++y)
	{
		unsigned int nIdx1 = widthminus * 4 + y * 4 * largerPyramidLevelWidth;
		unsigned int nIdx2 = 0 * 4 + y * 4 * largerPyramidLevelWidth;

		float pR = largerPyramidLevelArray[nIdx1 + CHANNEL_R];//redEdgePixel
		float pG = largerPyramidLevelArray[nIdx1 + CHANNEL_G];
		float pB = largerPyramidLevelArray[nIdx1 + CHANNEL_B];

		float red = largerPyramidLevelArray[nIdx2 + CHANNEL_R];//redEdgePixel
		float green = largerPyramidLevelArray[nIdx2 + CHANNEL_G];
		float blue = largerPyramidLevelArray[nIdx2 + CHANNEL_B];

		wn1R = wn2R = wn3R = red;
		wn1G = wn2G = wn3G = green;
		wn1B = wn2B = wn3B = blue;

		for(int x = 0; x < largerPyramidLevelWidth; x++)// real forward pass
		{   
			unsigned int nIdx2 = x * 4 + y * 4 * largerPyramidLevelWidth;

			red = largerPyramidLevelArray[nIdx2 + CHANNEL_R];
			green = largerPyramidLevelArray[nIdx2 + CHANNEL_G];
			blue = largerPyramidLevelArray[nIdx2 + CHANNEL_B];
				
			wnR = b0 * red + b1 * wn1R + b2 * wn2R + b3 * wn3R;
			wnG = b0 * green + b1 * wn1G + b2 * wn2G + b3 * wn3G;
			wnB = b0 * blue + b1 * wn1B + b2 * wn2B + b3 * wn3B;

			temp[nIdx2 + CHANNEL_R] = wnR;
			temp[nIdx2 + CHANNEL_G] = wnG;
			temp[nIdx2 + CHANNEL_B] = wnB;

			wn3R = wn2R; wn2R = wn1R; wn1R = wnR;
			wn3G = wn2G; wn2G = wn1G; wn1G = wnG;
			wn3B = wn2B; wn2B = wn1B; wn1B = wnB;
		} // end real forward pass

		int xx = 0;

		for (int x = largerPyramidLevelWidth; x < largerPyramidLevelWidth + radius; x++)  // post process forward
		{
			wnR = b0 * pR + b1 * wn1R + b2 * wn2R + b3 * wn3R;
			wnG = b0 * pG + b1 * wn1G + b2 * wn2G + b3 * wn3G;
			wnB = b0 * pB + b1 * wn1B + b2 * wn2B + b3 * wn3B;

			putR[xx] = wnR;
			putG[xx] = wnG;
			putB[xx] = wnB;

			wn3R = wn2R; wn2R = wn1R; wn1R = wnR;
			wn3G = wn2G; wn2G = wn1G; wn1G = wnG;
			wn3B = wn2B; wn2B = wn1B; wn1B = wnB;

			xx++;
		}
		xx--;

		wn1R = wn2R = wn3R = pR;
		wn1G = wn2G = wn3G = pG;
		wn1B = wn2B = wn3B = pB;

		for (int x = xx; x > 0; x--)// initialize backward
		{
			float pRR = putR[x];
			float pGG = putG[x];
			float pBB = putB[x];

			wnR = b0 * pRR + b1 * wn1R + b2 * wn2R + b3 * wn3R;
			wnG = b0 * pGG + b1 * wn1G + b2 * wn2G + b3 * wn3G;
			wnB = b0 * pBB + b1 * wn1B + b2 * wn2B + b3 * wn3B;

			wn3R = wn2R; wn2R = wn1R; wn1R = wnR;
			wn3G = wn2G; wn2G = wn1G; wn1G = wnG;
			wn3B = wn2B; wn2B = wn1B; wn1B = wnB;
		}// end initialize backward

		for (int x = widthminus; x > -1; x--) // real backward pass
		{
			unsigned int nIdx1 = x * 4 + y * 4 * largerPyramidLevelWidth;

			red = temp[nIdx1 + CHANNEL_R];
			green = temp[nIdx1 + CHANNEL_G];
			blue = temp[nIdx1 + CHANNEL_B];

			wnR = b0 * red + b1 * wn1R + b2 * wn2R + b3 * wn3R;
			wnG = b0 * green + b1 * wn1G + b2 * wn2G + b3 * wn3G;
			wnB = b0 * blue + b1 * wn1B + b2 * wn2B + b3 * wn3B;

			horizontal[nIdx1 + CHANNEL_R] = wnR;
			horizontal[nIdx1 + CHANNEL_G] = wnG;
			horizontal[nIdx1 + CHANNEL_B] = wnB;

			wn3R = wn2R; wn2R = wn1R; wn1R = wnR;
			wn3G = wn2G; wn2G = wn1G; wn1G = wnG;
			wn3B = wn2B; wn2B = wn1B; wn1B = wnB;
		}// end real backward pass
	}//end y

	float* vertical = new float[largerPyramidLevelWidth * largerPyramidLevelHeight * 4];	

	//blur vertical
	for(int x = 0; x < largerPyramidLevelWidth; x++)
	{
		unsigned int nIdx1 = x * 4 + heightminus * 4 * largerPyramidLevelWidth;
		unsigned int nIdx2 = x * 4 + 0 * 4 * largerPyramidLevelWidth;

		float pR = horizontal[nIdx1 + CHANNEL_R];
		float pG = horizontal[nIdx1 + CHANNEL_G];
		float pB = horizontal[nIdx1 + CHANNEL_B];

		float red = horizontal[nIdx2 + CHANNEL_R];
		float green = horizontal[nIdx2 + CHANNEL_G];
		float blue = horizontal[nIdx2 + CHANNEL_B];

		wn1R = wn2R = wn3R = red;
		wn1G = wn2G = wn3G = green;
		wn1B = wn2B = wn3B = blue;

		for (int y = 0; y < largerPyramidLevelHeight; ++y)
		{   
			unsigned int nIdx2 = x * 4 + y * 4 * largerPyramidLevelWidth;

			red = horizontal[nIdx2 + CHANNEL_R];
			green = horizontal[nIdx2 + CHANNEL_G];
			blue = horizontal[nIdx2 + CHANNEL_B];

			wnR = b0 * red + b1 * wn1R + b2 * wn2R + b3 * wn3R;
			wnG = b0 * green + b1 * wn1G + b2 * wn2G + b3 * wn3G;
			wnB = b0 * blue + b1 * wn1B + b2 * wn2B + b3 * wn3B;

			temp[nIdx2 + CHANNEL_R] = wnR;
			temp[nIdx2 + CHANNEL_G] = wnG;
			temp[nIdx2 + CHANNEL_B] = wnB;

			wn3R = wn2R; wn2R = wn1R; wn1R = wnR;
			wn3G = wn2G; wn2G = wn1G; wn1G = wnG;
			wn3B = wn2B; wn2B = wn1B; wn1B = wnB;
		}

		int yy = 0;
		for (int y = largerPyramidLevelHeight; y < largerPyramidLevelHeight + radius; y++)  // post process forward
		{
			wnR = b0 * pR + b1 * wn1R + b2 * wn2R + b3 * wn3R;
			wnG = b0 * pG + b1 * wn1G + b2 * wn2G + b3 * wn3G;
			wnB = b0 * pB + b1 * wn1B + b2 * wn2B + b3 * wn3B;

			putR[yy] = wnR;
			putG[yy] = wnG;
			putB[yy] = wnB;

			wn3R = wn2R; wn2R = wn1R; wn1R = wnR;
			wn3G = wn2G; wn2G = wn1G; wn1G = wnG;
			wn3B = wn2B; wn2B = wn1B; wn1B = wnB;

			yy++;
		}
		yy--;

		wn1R = wn2R = wn3R = pR;
		wn1G = wn2G = wn3G = pG;
		wn1B = wn2B = wn3B = pB;

		for (int y = yy; y > 0; y--)// initialize backward
		{
			float pRR = putR[y];
			float pGG = putG[y];
			float pBB = putB[y];

			wnR = b0 * pRR + b1 * wn1R + b2 * wn2R + b3 * wn3R;
			wnG = b0 * pGG + b1 * wn1G + b2 * wn2G + b3 * wn3G;
			wnB = b0 * pBB + b1 * wn1B + b2 * wn2B + b3 * wn3B;

			wn3R = wn2R; wn2R = wn1R; wn1R = wnR;
			wn3G = wn2G; wn2G = wn1G; wn1G = wnG;
			wn3B = wn2B; wn2B = wn1B; wn1B = wnB;
		}// end initialize backward

		for (int y = heightminus; y > 1; y--) // real backward pass
		{
			unsigned int nIdx2 = x * 4 + y * 4 * largerPyramidLevelWidth;

			red = temp[nIdx2 + CHANNEL_R];
			green = temp[nIdx2 + CHANNEL_G];
			blue = temp[nIdx2 + CHANNEL_B];

			wnR = b0 * red + b1 * wn1R + b2 * wn2R + b3 * wn3R;
			wnG = b0 * green + b1 * wn1G + b2 * wn2G + b3 * wn3G;
			wnB = b0 * blue + b1 * wn1B + b2 * wn2B + b3 * wn3B;

			vertical[nIdx2 + CHANNEL_R] = wnR;
			vertical[nIdx2 + CHANNEL_G] = wnG;
			vertical[nIdx2 + CHANNEL_B] = wnB;

			wn3R = wn2R; wn2R = wn1R; wn1R = wnR;
			wn3G = wn2G; wn2G = wn1G; wn1G = wnG;
			wn3B = wn2B; wn2B = wn1B; wn1B = wnB;
		}//end backward pass
	}//end vertical


	delete [] temp;// delete array to prevent memory leaks
	delete [] horizontal;// delete array to prevent memory leaks
	delete [] putR;// delete array to prevent memory leaks
	delete [] putG;// delete array to prevent memory leaks
	delete [] putB;// delete array to prevent memory leaks

	// larger pyramid array is now blurred recursively



	//float gaussianReducepyramid(float *largerPyramidLevelArray, int largerPyramidLevelWidth, int largerPyramidLevelHeight, float *smallerPyramidLevelArray, int smallerPyramidLevelWidth, int smallerPyramidLevelHeight)
	// SEE http://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html or details 

	// open CV explains it this way
	// The function performs the downsampling step of the Gaussian pyramid construction. First, it convolves the source image with the kernel: 5x5 gaussian kernel
	// Then, it downsamples the image by rejecting even rows and columns.

	int xx = 0;
	int yy = 0;

	for(int x = 0; x < largerPyramidLevelWidth; x++)// scan the larger image width
	{
		//if x is not divisible by 2 (means an odd number), increment xx by 1
		if (x%2 != 0){xx ++;}

		for(int y = 0; y < largerPyramidLevelHeight; y++)// scan the larger image height
		{
			//if y is not divisible by 2 (means an odd number), increment yy by 1
			if (y%2 != 0){yy ++;}

			//for the larger image
			int nIdx1 = x * 4 + y * 4 * largerPyramidLevelWidth; //center
			//for the larger image

			//for the smaller image
			int nIdx2 = xx * 4 + yy * 4 * smallerPyramidLevelWidth; //center
			//for the smaller image



			sprintf(sBuffer6,"x = %d\n y = %d\n\n xx = %d\n yy = %d\n\n largerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
			                 ,x,       y,         xx,       yy,         largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
			MessageBox(NULL,sBuffer6,"X and Y", MB_OK);
		}
	}





	delete [] vertical;// delete array to prevent memory leaks




	/*
	for(int x = 0; x < smallerPyramidLevelWidth; x++)// scan the larger image width
	{
		for(int y = 0; y < smallerPyramidLevelHeight; y++)// scan the larger image height
		{
			int nIdx = x * 4 + y * 4 * smallerPyramidLevelWidth; //center

			float red = smallerPyramidLevelArray[nIdx + CHANNEL_R];
			float green = smallerPyramidLevelArray[nIdx + CHANNEL_R];
			float blue = smallerPyramidLevelArray[nIdx + CHANNEL_R];
			
			//sprintf(sBuffer6,"x = %d\n y = %d\n\n red = %f\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
			//                 ,x,       y,         red,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
			//MessageBox(NULL,sBuffer6,"X and Y", MB_OK);
		}
	}
	*/



	//printArray(smallerPyramidLevelArray, smallerPyramidLevelWidth, smallerPyramidLevelHeight);

	//sprintf(sBuffer6,"HALT");MessageBox(NULL,sBuffer6,"stop", MB_OK);

	return *largerPyramidLevelArray;
	//return *smallerPyramidLevelArray;
}




/// <summary> Shifts image from the edge to 1/2 kernel input i.e. if using a kernel size of 3, the shift amount is 1.  The edges of the output image will be a reflected copy of the input image.
/// <para>largerPyramidLevelArray = Input image.</para>
/// <para>largerPyramidLevelWidth = Width of input image.</para>
/// <para>largerPyramidLevelHeight = Height of input image.</para>
/// <para>smallerPyramidLevelArray = Output image.</para>
/// <para>smallerPyramidLevelWidth = Width of output image.</para>
/// <para>smallerPyramidLevelHeight = Height of output image.</para>
/// <para>Returns return *smallerPyramidLevelArray </para>
/// </summary>
float gaussianReducepyramid2(float *largerPyramidLevelArray, int largerPyramidLevelWidth, int largerPyramidLevelHeight, float *smallerPyramidLevelArray, int smallerPyramidLevelWidth, int smallerPyramidLevelHeight)
{
	char sBuffer6[400];

	//each pyramid level 1/2 the height and width of the prior pyramid


	/*sprintf(sBuffer6,"largerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
	                 ,largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
					   MessageBox(NULL,sBuffer6,"Pyramid Resolutions", MB_OK);*/
		

	int largerPyramidLevelHeightMinus = largerPyramidLevelHeight - 1;
	int largerPyramidLevelWidthMinus = largerPyramidLevelWidth - 1;
	
	//since a gaussian pyramid level is 1/2 the size of the prior level
	//we cannot use the x / y loops directly for the smaller image.
	//We recalcuate the position for the smaller image by checking if the numbers of the
	//x / y loop is even, if so we increment xx and yy by 1

	int xx = 0;
	int yy = 0;

	for(int x = 1; x < largerPyramidLevelWidthMinus; x++)// scan the larger image width
	{
		for(int y = 1; y < largerPyramidLevelHeightMinus; y++)// scan the larger image height
		{
			int xplus = x + 1;
			int xminus = x - 1;
			int yplus = y + 1;
			int yminus = y - 1;

			//this is for the larger image
			//prevent kernel from exceeding the edges of larger image
			if (xminus < 1) xminus = 1;
			if (yminus < 1) yminus = 1;
			if (xplus > largerPyramidLevelWidthMinus) xplus = largerPyramidLevelWidthMinus;
			if (yplus > largerPyramidLevelHeightMinus) yplus = largerPyramidLevelHeightMinus;
			//prevent kernel from exceeding the edges

			//   x-   ◄◄◄◄X►►►►   x+
			//________________________
			//| nIdx1 | nidx2 | nidx3 | y+
			//|_______________________| ▲
			//| nIdx4 | nidx5 | nidx6 | Y
			//|_______________________| ▼
			//| nIdx7 | nidx8 | nidx9 | y-
			//|_______________________| 

			//Index for the larger image
#pragma region
			int nIdx1 = xminus * 4 + yplus  * 4 * largerPyramidLevelWidth;//left above center
			int nIdx2 = x      * 4 + yplus  * 4 * largerPyramidLevelWidth;//above center
			int nIdx3 = xplus  * 4 + yplus  * 4 * largerPyramidLevelWidth;//right above center
			int nIdx4 = xminus * 4 + y      * 4 * largerPyramidLevelWidth;//left center
			int nIdx5 = x      * 4 + y      * 4 * largerPyramidLevelWidth; //center
			int nIdx6 = xplus  * 4 + y      * 4 * largerPyramidLevelWidth;//right center
			int nIdx7 = xminus * 4 + yminus * 4 * largerPyramidLevelWidth;//left below center
			int nIdx8 = x      * 4 + yminus * 4 * largerPyramidLevelWidth;//below center
			int nIdx9 = xplus  * 4 + yminus * 4 * largerPyramidLevelWidth;//right below center
			//for the larger image

			float red1 = largerPyramidLevelArray[nIdx1 + CHANNEL_R];//upper left
			float red2 = largerPyramidLevelArray[nIdx2 + CHANNEL_R];//upper center
			float red3 = largerPyramidLevelArray[nIdx3 + CHANNEL_R];//upper right
			float red4 = largerPyramidLevelArray[nIdx4 + CHANNEL_R];//left center
			float red5 = largerPyramidLevelArray[nIdx5 + CHANNEL_R];//center
			float red6 = largerPyramidLevelArray[nIdx6 + CHANNEL_R];//right center
			float red7 = largerPyramidLevelArray[nIdx7 + CHANNEL_R];//lower left
			float red8 = largerPyramidLevelArray[nIdx8 + CHANNEL_R];//lower center
			float red9 = largerPyramidLevelArray[nIdx9 + CHANNEL_R];//lower right

			float green1 = largerPyramidLevelArray[nIdx1 + CHANNEL_G];//upper left
			float green2 = largerPyramidLevelArray[nIdx2 + CHANNEL_G];//upper center
			float green3 = largerPyramidLevelArray[nIdx3 + CHANNEL_G];//upper right
			float green4 = largerPyramidLevelArray[nIdx4 + CHANNEL_G];//left center
			float green5 = largerPyramidLevelArray[nIdx5 + CHANNEL_G];//center
			float green6 = largerPyramidLevelArray[nIdx6 + CHANNEL_G];//right center
			float green7 = largerPyramidLevelArray[nIdx7 + CHANNEL_G];//lower left
			float green8 = largerPyramidLevelArray[nIdx8 + CHANNEL_G];//lower center
			float green9 = largerPyramidLevelArray[nIdx9 + CHANNEL_G];//lower right

			float blue1 = largerPyramidLevelArray[nIdx1 + CHANNEL_B];//upper left
			float blue2 = largerPyramidLevelArray[nIdx2 + CHANNEL_B];//upper center
			float blue3 = largerPyramidLevelArray[nIdx3 + CHANNEL_B];//upper right
			float blue4 = largerPyramidLevelArray[nIdx4 + CHANNEL_B];//left center
			float blue5 = largerPyramidLevelArray[nIdx5 + CHANNEL_B];//center
			float blue6 = largerPyramidLevelArray[nIdx6 + CHANNEL_B];//right center
			float blue7 = largerPyramidLevelArray[nIdx7 + CHANNEL_B];//lower left
			float blue8 = largerPyramidLevelArray[nIdx8 + CHANNEL_B];//lower center
			float blue9 = largerPyramidLevelArray[nIdx9 + CHANNEL_B];//lower right
#pragma endregion
			//Index for the larger image


			//calculate 3x3 gaussian kernel for the larger image
#pragma region
			//   3X3 Gaussian Kernel
			//        -◄◄◄X►►►+
			//______________________
			//| 1/16 | 1/8  | 1/16 | +
			//|____________________| ▲
			//| 1/8  | 1/4  | 1/8  | Y
			//|____________________| ▼
			//| 1/16 | 1/8  | 1/16 | -
			//|____________________| 

			//   3X3 Gaussian Kernel
			//        -◄◄◄X►►►+                         -◄◄◄X►►►+
			//________________________              ___________________
			//| .0625 | .1250 | .0625 | +           | rr1 | rr2 | rr3 | +
			//|_______________________| ▲           |_________________| ▲
			//| .1250 | .2500 | .1250 | Y           | rr4 | rr5 | rr6 | Y
			//|_______________________| ▼           |_________________| ▼
			//| .0625 | .1250 | .0625 | -           | rr7 | rr8 | rr9 | -
			//|_______________________|             |_________________| 


			float rr1 = .0625 * red1;
			float rr2 = .1250 * red2;
			float rr3 = .0625 * red3;
			float rr4 = .1250 * red4;
			float rr5 = .2500 * red5;
			float rr6 = .1250 * red6;
			float rr7 = .0625 * red7;
			float rr8 = .1250 * red8;
			float rr9 = .0625 * red9;

			float gg1 = .0625 * green1;
			float gg2 = .1250 * green2;
			float gg3 = .0625 * green3;
			float gg4 = .1250 * green4;
			float gg5 = .2500 * green5;
			float gg6 = .1250 * green6;
			float gg7 = .0625 * green7;
			float gg8 = .1250 * green8;
			float gg9 = .0625 * green9;

			float bb1 = .0625 * blue1;
			float bb2 = .1250 * blue2;
			float bb3 = .0625 * blue3;
			float bb4 = .1250 * blue4;
			float bb5 = .2500 * blue5;
			float bb6 = .1250 * blue6;
			float bb7 = .0625 * blue7;
			float bb8 = .1250 * blue8;
			float bb9 = .0625 * blue9;
#pragma endregion

			//combine the kernel for gaussian
			float red = rr1 + rr2 + rr3 + rr4 + rr5 + rr6 + rr7 + rr8 + rr9;
			float green = gg1 + gg2 + gg3 + gg4 + gg5 + gg6 + gg7 + gg8 + gg9;
			float blue = bb1 + bb2 + bb3 + bb4 + bb5 + bb6 + bb7 + bb8 + bb9;
			//calculate gaussian formula

			//        ◄◄◄◄X►►►►
			//_______________________________________
			//|   top left  |   top  |   top right  | ▲
			//|_____________________________________| ▲
			//|    left     |  nidx  |     right    | Y
			//|_____________________________________| ▼
			//| bottom left | bottom | bottom right | ▼
			//|_____________________________________| 

			if (y%2 == 0)
			{//for the smaller image				
				int nIdx = xx * 4 + yy * 4 * smallerPyramidLevelWidth; //center
				//for the smaller image
				//smallerPyramidLevelArray[nIdx + CHANNEL_R] = red;
				//smallerPyramidLevelArray[nIdx + CHANNEL_G] = green;
				//smallerPyramidLevelArray[nIdx + CHANNEL_B] = blue;

				yy ++;// increment yy if y is even
			}

		}//end y
		if (x%2 == 0)
		{xx ++;}// increment xx if x is even
		yy = 0;//reset yy back to 0 to follow the y loop
	}//end x

	///////////////////////////////////////////////////////////////////
	//                     NOT  OK to this point                        //
	///////////////////////////////////////////////////////////////////

	for(int x = 0; x < smallerPyramidLevelWidth; x++)// scan the larger image width
	{
		for(int y = 0; y < smallerPyramidLevelHeight; y++)// scan the larger image height
		{
			int nIdx = x * 4 + y * 4 * smallerPyramidLevelWidth; //center

			float red = smallerPyramidLevelArray[nIdx + CHANNEL_R];
			float green = smallerPyramidLevelArray[nIdx + CHANNEL_R];
			float blue = smallerPyramidLevelArray[nIdx + CHANNEL_R];
			
			/*sprintf(sBuffer6,"x = %d\n y = %d\n\n red = %f\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
			                 ,x,       y,         red,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
			MessageBox(NULL,sBuffer6,"X and Y", MB_OK);*/
		}
	}




	//printArray(smallerPyramidLevelArray, smallerPyramidLevelWidth, smallerPyramidLevelHeight);

	//sprintf(sBuffer6,"HALT");MessageBox(NULL,sBuffer6,"stop", MB_OK);


	/*

	//!!!!!!!!!!!!!!!!!!!!!!!
	// see a problem with routine below
	// at end of x, (x = 127 & y = 0)
	// reads red = 95 which is at 
	// x = 1 && y = 253, which over the course of an image will create a sheer

	//copy smaller pyramid back to larger one to return to main loop
	yy = 0;
	xx = 0;

	for (int x = 0; x < smallerPyramidLevelWidth; x++)
	{
		for (int y = 0; y < smallerPyramidLevelHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * smallerPyramidLevelWidth;
			int nIdx2 = xx * 4 + y * 4 * largerPyramidLevelWidth;
			float red = smallerPyramidLevelArray[nIdx1 + CHANNEL_R];
			float green = smallerPyramidLevelArray[nIdx1 + CHANNEL_G];
			float blue = smallerPyramidLevelArray[nIdx1 + CHANNEL_B];


			sprintf(sBuffer6,"x = %d\n y = %d\n\n xx = %d\n yy = %d\n\n red = %f\n\nlargerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
				             ,x,       y,         xx,       yy,         red,        largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
			MessageBox(NULL,sBuffer6,"X and Y", MB_OK);


			//largerPyramidLevelArray[nIdx2 + CHANNEL_R] = red;
			//largerPyramidLevelArray[nIdx2 + CHANNEL_G] = green;
			//largerPyramidLevelArray[nIdx2 + CHANNEL_B] = blue;
			xx++;
		}
		xx = 0;
	}
	*/



	//sprintf(sBuffer6,"HALT2");MessageBox(NULL,sBuffer6,"end copy", MB_OK);

	return *smallerPyramidLevelArray;
}












	//calculate LaPlacian formula

	//   3X3 LaPlacian Kernel 4 neighbors
	//        ◄◄◄◄X►►►►
	//___________________
	//| 0   | -1/4 | 0   | ▲
	//|------------------| ▲
	//|-1/4 |  1   |-1/4 | Y
	//|------------------| ▼
	//| 0   | -1/4 | 0   | ▼
	//|__________________| 

	//   3X3 LaPlacian Kernel 8 neighbors
	//        ◄◄◄◄X►►►►
	//_____________________
	//| -1/8 | -1/8 | -1/8 | ▲
	//|--------------------| ▲
	//| -1/8 |  1   |-1/8  | Y
	//|--------------------| ▼
	//| -1/8 | -1/8 | -1/8 | ▼
	//|____________________| 










/*
float gaussianReducepyramid_orig(float *largerPyramidLevelArray, int largerPyramidLevelWidth, int largerPyramidLevelHeight)
{
	char sBuffer6[400];

	//each pyramid level 1/2 the height and width of the prior pyramid
	int smallerPyramidLevelWidth = largerPyramidLevelWidth / 2;
	int smallerPyramidLevelHeight = largerPyramidLevelHeight / 2;
	int pyramidLevelSize = (smallerPyramidLevelWidth * smallerPyramidLevelHeight) * 4;

	//create the array
	float* smallerPyramidLevelArray = new float[pyramidLevelSize];
	memset( smallerPyramidLevelArray, 0, sizeof(pyramidLevelSize) );

		
	//sprintf(sBuffer6,"largerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
	//                   ,largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
	//				   MessageBox(NULL,sBuffer6,"Pyramid Resolutions", MB_OK);
		

	int largerPyramidLevelHeightMinus = largerPyramidLevelHeight - 1;
	int largerPyramidLevelWidthMinus = largerPyramidLevelWidth - 1;

	int smallerPyramidWidthMinus = smallerPyramidLevelWidth - 1;
	int smallerPyramidHeightMinus = smallerPyramidLevelHeight - 1;



		
		
	//since a gaussian pyramid level is 1/2 the size of the prior level
	//we cannot use the x / y loops directly for the smaller image.
	//We recalcuate the position for the smaller image by checking if the numbers of the
	//x / y loop is even, if so we increment xx and yy by 1

	

	//currently kernel goes too far right and too far up
	int xx = 0;
	int yy = 0;
	for(int x = 1; x < largerPyramidLevelWidthMinus; x++)// scan the larger image width
	{
		//if x is divisible by 2, increment xx by 1
		if (x%2 == 0){xx ++;}

		for(int y = 1; y < largerPyramidLevelHeightMinus; y++)// scan the larger image height
		{
			//if y is divisible by 2, increment yy by 1
			if (y%2 == 0){yy ++;}

			int xplus = x + 1;
			int xminus = x - 1;
			int yplus = y + 1;
			int yminus = y - 1;

			int xxplus = xx + 1;
			int xxminus = xx - 1;
			int yyplus = yy + 1;
			int yyminus = yy - 1;

			//this is for the larger image

			//prevent kernel from exceeding the edges of larger image
			if (xminus < 1) xminus = 1;
			if (yminus < 1) yminus = 1;
			if (xplus > largerPyramidLevelWidthMinus) xplus = largerPyramidLevelWidthMinus;
			if (yplus > largerPyramidLevelHeightMinus) yplus = largerPyramidLevelHeightMinus;
			//prevent kernel from exceeding the edges

			//   -    ◄◄◄◄X►►►►   +
			//________________________
			//| nIdx1 | nidx2 | nidx3 | +
			//|_______________________| ▲
			//| nIdx4 | nidx5 | nidx6 | Y
			//|_______________________| ▼
			//| nIdx7 | nidx8 | nidx9 | -
			//|_______________________| 

			//for the larger image
#pragma region
			int nIdx1 = xminus * 4 + yplus * 4 * largerPyramidLevelWidth;//left above center
			int nIdx2 = x * 4 + yplus * 4 * largerPyramidLevelWidth;//above center
			int nIdx3 = xplus * 4 + yplus * 4 * largerPyramidLevelWidth;//right above center
			int nIdx4 = xminus * 4 + y * 4 * largerPyramidLevelWidth;//left center
			int nIdx5 = x * 4 + y * 4 * largerPyramidLevelWidth; //center
			int nIdx6 = xplus * 4 + y * 4 * largerPyramidLevelWidth;//right center
			int nIdx7 = xminus * 4 + yminus * 4 * largerPyramidLevelWidth;//left below center
			int nIdx8 = x * 4 + yminus * 4 * largerPyramidLevelWidth;//below center
			int nIdx9 = xplus * 4 + yminus * 4 * largerPyramidLevelWidth;//right below center
			//for the larger image

			//for the smaller image
			unsigned int nIdx = xx * 4 + yy * 4 * smallerPyramidLevelWidth; //center
			//for the smaller image

			float red1 = largerPyramidLevelArray[nIdx1 + CHANNEL_R];//upper left
			float red2 = largerPyramidLevelArray[nIdx2 + CHANNEL_R];//upper center
			float red3 = largerPyramidLevelArray[nIdx3 + CHANNEL_R];//upper right
			float red4 = largerPyramidLevelArray[nIdx4 + CHANNEL_R];//left center
			float red5 = largerPyramidLevelArray[nIdx5 + CHANNEL_R];//center
			float red6 = largerPyramidLevelArray[nIdx6 + CHANNEL_R];//right center
			float red7 = largerPyramidLevelArray[nIdx7 + CHANNEL_R];//lower left
			float red8 = largerPyramidLevelArray[nIdx8 + CHANNEL_R];//lower
			float red9 = largerPyramidLevelArray[nIdx9 + CHANNEL_R];//lower right

			float green1 = largerPyramidLevelArray[nIdx1 + CHANNEL_G];
			float green2 = largerPyramidLevelArray[nIdx2 + CHANNEL_G];
			float green3 = largerPyramidLevelArray[nIdx3 + CHANNEL_G];
			float green4 = largerPyramidLevelArray[nIdx4 + CHANNEL_G];
			float green5 = largerPyramidLevelArray[nIdx5 + CHANNEL_G];
			float green6 = largerPyramidLevelArray[nIdx6 + CHANNEL_G];
			float green7 = largerPyramidLevelArray[nIdx7 + CHANNEL_G];
			float green8 = largerPyramidLevelArray[nIdx8 + CHANNEL_G];
			float green9 = largerPyramidLevelArray[nIdx9 + CHANNEL_G];

			float blue1 = largerPyramidLevelArray[nIdx1 + CHANNEL_B];
			float blue2 = largerPyramidLevelArray[nIdx2 + CHANNEL_B];
			float blue3 = largerPyramidLevelArray[nIdx3 + CHANNEL_B];
			float blue4 = largerPyramidLevelArray[nIdx4 + CHANNEL_B];
			float blue5 = largerPyramidLevelArray[nIdx5 + CHANNEL_B];
			float blue6 = largerPyramidLevelArray[nIdx6 + CHANNEL_B];
			float blue7 = largerPyramidLevelArray[nIdx7 + CHANNEL_B];
			float blue8 = largerPyramidLevelArray[nIdx8 + CHANNEL_B];
			float blue9 = largerPyramidLevelArray[nIdx9 + CHANNEL_B];
#pragma endregion
			//this is for the larger image


			//calculate 3x3 gaussian kernel
#pragma region
			//   3X3 Gaussian Kernel
			//        -◄◄◄X►►►+
			//______________________
			//| 1/16 | 1/8  | 1/16 | +
			//|____________________| ▲
			//| 1/8  | 1/4  | 1/8  | Y
			//|____________________| ▼
			//| 1/16 | 1/8  | 1/16 | -
			//|____________________| 

			//   3X3 Gaussian Kernel
			//        -◄◄◄X►►►+                         -◄◄◄X►►►+
			//________________________              ___________________
			//| .0625 | .1250 | .0625 | +           | rr1 | rr2 | rr3 | +
			//|_______________________| ▲           |_________________| ▲
			//| .1250 | .2500 | .1250 | Y           | rr4 | rr5 | rr6 | Y
			//|_______________________| ▼           |_________________| ▼
			//| .0625 | .1250 | .0625 | -           | rr7 | rr8 | rr9 | -
			//|_______________________|             |_________________| 


			float rr1 = .0625 * red1;
			float rr2 = .1250 * red2;
			float rr3 = .0625 * red3;
			float rr4 = .1250 * red4;
			float rr5 = .2500 * red5;
			float rr6 = .1250 * red6;
			float rr7 = .0625 * red7;
			float rr8 = .1250 * red8;
			float rr9 = .0625 * red9;

			float gg1 = .0625 * green1;
			float gg2 = .1250 * green2;
			float gg3 = .0625 * green3;
			float gg4 = .1250 * green4;
			float gg5 = .2500 * green5;
			float gg6 = .1250 * green6;
			float gg7 = .0625 * green7;
			float gg8 = .1250 * green8;
			float gg9 = .0625 * green9;

			float bb1 = .0625 * blue1;
			float bb2 = .1250 * blue2;
			float bb3 = .0625 * blue3;
			float bb4 = .1250 * blue4;
			float bb5 = .2500 * blue5;
			float bb6 = .1250 * blue6;
			float bb7 = .0625 * blue7;
			float bb8 = .1250 * blue8;
			float bb9 = .0625 * blue9;
#pragma endregion

			//combine the kernel for gaussian
			float red = red5;//this is temp only
			//float red = rr1 + rr2 + rr3 + rr4 + rr5 + rr6 + rr7 + rr8 + rr9;
			float green = gg1 + gg2 + gg3 + gg4 + gg5 + gg6 + gg7 + gg8 + gg9;
			float blue = bb1 + bb2 + bb3 + bb4 + bb5 + bb6 + bb7 + bb8 + bb9;

			//calculate gaussian formula

			//this is for the smaller image

			//prevent kernel from exceeding the edges
			if (xxminus < 1) xxminus = 1;
			if (yyminus < 1) yyminus = 1;
			if (xxplus > smallerPyramidWidthMinus) xxplus = smallerPyramidWidthMinus;
			if (yyplus > smallerPyramidHeightMinus) yyplus = smallerPyramidHeightMinus;
			//prevent kernel from exceeding the edges

			//        ◄◄◄◄X►►►►
			//_______________________________________
			//|   top left  |   top  |   top right  | ▲
			//|_____________________________________| ▲
			//|    left     |  nidx  |     right    | Y
			//|_____________________________________| ▼
			//| bottom left | bottom | bottom right | ▼
			//|_____________________________________| 



			//this is for the smaller image

			//sprintf(sBuffer6,"x = %d\n y = %d\n\n xx = %d\n yy = %d\n\n largerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
			//                   ,x,       y,         xx,       yy,         largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
			//				   MessageBox(NULL,sBuffer6,"X and Y", MB_OK);

				
			//if (xx > 120)
			{
			//sprintf(sBuffer6,"x = %d\n y = %d\n\n xx = %d\n yy = %d\n\n red = %f\n\nlargerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
			//,x,       y,         xx,       yy,         red,        largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
			//MessageBox(NULL,sBuffer6,"X and Y", MB_OK);
			}


			smallerPyramidLevelArray[nIdx + CHANNEL_R] = red;
			smallerPyramidLevelArray[nIdx + CHANNEL_G] = green;
			smallerPyramidLevelArray[nIdx + CHANNEL_B] = blue;

		}//end y
		yy = 0;//reset xx back to 0 to follow the x loop
	}//end x

	//sprintf(sBuffer6,"HALT");MessageBox(NULL,sBuffer6,"stop", MB_OK);



	//!!!!!!!!!!!!!!!!!!!!!!!
	// see a problem with routine below
	// at end of x, (x = 127 & y = 0)
	// reads red = 95 which is at 
	// x = 1 && y = 253, which over the course of an image will create a sheer

	//copy smaller pyramid back to larger one to return to main loop
		
	yy = 0;
	xx = 0;

	for (int x = 0; x < smallerPyramidLevelWidth; x++)
	{
		for (int y = 0; y < smallerPyramidLevelHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * smallerPyramidLevelWidth;
			int nIdx2 = xx * 4 + y * 4 * largerPyramidLevelWidth;
			float red = smallerPyramidLevelArray[nIdx1 + CHANNEL_R];
			float green = smallerPyramidLevelArray[nIdx1 + CHANNEL_G];
			float blue = smallerPyramidLevelArray[nIdx1 + CHANNEL_B];


			sprintf(sBuffer6,"x = %d\n y = %d\n\n xx = %d\n yy = %d\n\n red = %f\n\nlargerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
				             ,x,       y,         xx,       yy,         red,        largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
			MessageBox(NULL,sBuffer6,"X and Y", MB_OK);


			//largerPyramidLevelArray[nIdx2 + CHANNEL_R] = red;
			//largerPyramidLevelArray[nIdx2 + CHANNEL_G] = green;
			//largerPyramidLevelArray[nIdx2 + CHANNEL_B] = blue;
			xx++;
		}
		xx = 0;
	}



	//just for printing results
	for (int x = 0; x < smallerPyramidLevelWidth; x++)
	{
		for (int y = 0; y < smallerPyramidLevelHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * smallerPyramidLevelWidth;
			int nIdx2 = x * 4 + y * 4 * largerPyramidLevelWidth;

			float red = largerPyramidLevelArray[nIdx2 + CHANNEL_R];
			float green = largerPyramidLevelArray[nIdx2 + CHANNEL_G];
			float blue = largerPyramidLevelArray[nIdx2 + CHANNEL_B];
			//if (x > 120)
			{
				sprintf(sBuffer6,"x = %d\n y = %d\n\n red = %f\n\nlargerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
			                     ,x,       y,         red,        largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
				MessageBox(NULL,sBuffer6,"X and Y", MB_OK);
			}

		}
	}

	//sprintf(sBuffer6,"HALT2");MessageBox(NULL,sBuffer6,"end copy", MB_OK);


	delete [] smallerPyramidLevelArray;

	return *largerPyramidLevelArray;
}
*/



/*
float gaussianReducepyramid1(float *largerPyramidLevelArray, int largerPyramidLevelWidth, int largerPyramidLevelHeight, float *smallerPyramidLevelArray, int smallerPyramidLevelWidth, int smallerPyramidLevelHeight)
{
	char sBuffer6[400];

	//each pyramid level 1/2 the height and width of the prior pyramid


	//sprintf(sBuffer6,"largerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
	//                   ,largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
	//				   MessageBox(NULL,sBuffer6,"Pyramid Resolutions", MB_OK);
		

	int largerPyramidLevelHeightMinus = largerPyramidLevelHeight - 1;
	int largerPyramidLevelWidthMinus = largerPyramidLevelWidth - 1;

	int smallerPyramidWidthMinus = smallerPyramidLevelWidth - 1;
	int smallerPyramidHeightMinus = smallerPyramidLevelHeight - 1;



		
		
	//since a gaussian pyramid level is 1/2 the size of the prior level
	//we cannot use the x / y loops directly for the smaller image.
	//We recalcuate the position for the smaller image by checking if the numbers of the
	//x / y loop is even, if so we increment xx and yy by 1

	

	//currently kernel goes too far right and too far up
	int xx = 0;
	int yy = 0;
	for(int x = 1; x < largerPyramidLevelWidthMinus; x++)// scan the larger image width
	{
		//if x is divisible by 2, increment xx by 1
		if (x%2 == 0){xx ++;}

		for(int y = 1; y < largerPyramidLevelHeightMinus; y++)// scan the larger image height
		{
			//if y is divisible by 2, increment yy by 1
			if (y%2 == 0){yy ++;}

			int xplus = x + 1;
			int xminus = x - 1;
			int yplus = y + 1;
			int yminus = y - 1;

			int xxplus = xx + 1;
			int xxminus = xx - 1;
			int yyplus = yy + 1;
			int yyminus = yy - 1;

			//this is for the larger image

			//prevent kernel from exceeding the edges of larger image
			if (xminus < 1) xminus = 1;
			if (yminus < 1) yminus = 1;
			if (xplus > largerPyramidLevelWidthMinus) xplus = largerPyramidLevelWidthMinus;
			if (yplus > largerPyramidLevelHeightMinus) yplus = largerPyramidLevelHeightMinus;
			//prevent kernel from exceeding the edges

			//   -    ◄◄◄◄X►►►►   +
			//________________________
			//| nIdx1 | nidx2 | nidx3 | +
			//|_______________________| ▲
			//| nIdx4 | nidx5 | nidx6 | Y
			//|_______________________| ▼
			//| nIdx7 | nidx8 | nidx9 | -
			//|_______________________| 

			//for the larger image
#pragma region
			int nIdx1 = xminus * 4 + yplus * 4 * largerPyramidLevelWidth;//left above center
			int nIdx2 = x * 4 + yplus * 4 * largerPyramidLevelWidth;//above center
			int nIdx3 = xplus * 4 + yplus * 4 * largerPyramidLevelWidth;//right above center
			int nIdx4 = xminus * 4 + y * 4 * largerPyramidLevelWidth;//left center
			int nIdx5 = x * 4 + y * 4 * largerPyramidLevelWidth; //center
			int nIdx6 = xplus * 4 + y * 4 * largerPyramidLevelWidth;//right center
			int nIdx7 = xminus * 4 + yminus * 4 * largerPyramidLevelWidth;//left below center
			int nIdx8 = x * 4 + yminus * 4 * largerPyramidLevelWidth;//below center
			int nIdx9 = xplus * 4 + yminus * 4 * largerPyramidLevelWidth;//right below center
			//for the larger image

			//for the smaller image
			unsigned int nIdx = xx * 4 + yy * 4 * smallerPyramidLevelWidth; //center
			//for the smaller image

			float red1 = largerPyramidLevelArray[nIdx1 + CHANNEL_R];//upper left
			float red2 = largerPyramidLevelArray[nIdx2 + CHANNEL_R];//upper center
			float red3 = largerPyramidLevelArray[nIdx3 + CHANNEL_R];//upper right
			float red4 = largerPyramidLevelArray[nIdx4 + CHANNEL_R];//left center
			float red5 = largerPyramidLevelArray[nIdx5 + CHANNEL_R];//center
			float red6 = largerPyramidLevelArray[nIdx6 + CHANNEL_R];//right center
			float red7 = largerPyramidLevelArray[nIdx7 + CHANNEL_R];//lower left
			float red8 = largerPyramidLevelArray[nIdx8 + CHANNEL_R];//lower center
			float red9 = largerPyramidLevelArray[nIdx9 + CHANNEL_R];//lower right

			float green1 = largerPyramidLevelArray[nIdx1 + CHANNEL_G];//upper left
			float green2 = largerPyramidLevelArray[nIdx2 + CHANNEL_G];//upper center
			float green3 = largerPyramidLevelArray[nIdx3 + CHANNEL_G];//upper right
			float green4 = largerPyramidLevelArray[nIdx4 + CHANNEL_G];//left center
			float green5 = largerPyramidLevelArray[nIdx5 + CHANNEL_G];//center
			float green6 = largerPyramidLevelArray[nIdx6 + CHANNEL_G];//right center
			float green7 = largerPyramidLevelArray[nIdx7 + CHANNEL_G];//lower left
			float green8 = largerPyramidLevelArray[nIdx8 + CHANNEL_G];//lower center
			float green9 = largerPyramidLevelArray[nIdx9 + CHANNEL_G];//lower right

			float blue1 = largerPyramidLevelArray[nIdx1 + CHANNEL_B];//upper left
			float blue2 = largerPyramidLevelArray[nIdx2 + CHANNEL_B];//upper center
			float blue3 = largerPyramidLevelArray[nIdx3 + CHANNEL_B];//upper right
			float blue4 = largerPyramidLevelArray[nIdx4 + CHANNEL_B];//left center
			float blue5 = largerPyramidLevelArray[nIdx5 + CHANNEL_B];//center
			float blue6 = largerPyramidLevelArray[nIdx6 + CHANNEL_B];//right center
			float blue7 = largerPyramidLevelArray[nIdx7 + CHANNEL_B];//lower left
			float blue8 = largerPyramidLevelArray[nIdx8 + CHANNEL_B];//lower center
			float blue9 = largerPyramidLevelArray[nIdx9 + CHANNEL_B];//lower right
#pragma endregion
			//this is for the larger image


			//calculate 3x3 gaussian kernel
#pragma region
			//   3X3 Gaussian Kernel
			//        -◄◄◄X►►►+
			//______________________
			//| 1/16 | 1/8  | 1/16 | +
			//|____________________| ▲
			//| 1/8  | 1/4  | 1/8  | Y
			//|____________________| ▼
			//| 1/16 | 1/8  | 1/16 | -
			//|____________________| 

			//   3X3 Gaussian Kernel
			//        -◄◄◄X►►►+                         -◄◄◄X►►►+
			//________________________              ___________________
			//| .0625 | .1250 | .0625 | +           | rr1 | rr2 | rr3 | +
			//|_______________________| ▲           |_________________| ▲
			//| .1250 | .2500 | .1250 | Y           | rr4 | rr5 | rr6 | Y
			//|_______________________| ▼           |_________________| ▼
			//| .0625 | .1250 | .0625 | -           | rr7 | rr8 | rr9 | -
			//|_______________________|             |_________________| 


			float rr1 = .0625 * red1;
			float rr2 = .1250 * red2;
			float rr3 = .0625 * red3;
			float rr4 = .1250 * red4;
			float rr5 = .2500 * red5;
			float rr6 = .1250 * red6;
			float rr7 = .0625 * red7;
			float rr8 = .1250 * red8;
			float rr9 = .0625 * red9;

			float gg1 = .0625 * green1;
			float gg2 = .1250 * green2;
			float gg3 = .0625 * green3;
			float gg4 = .1250 * green4;
			float gg5 = .2500 * green5;
			float gg6 = .1250 * green6;
			float gg7 = .0625 * green7;
			float gg8 = .1250 * green8;
			float gg9 = .0625 * green9;

			float bb1 = .0625 * blue1;
			float bb2 = .1250 * blue2;
			float bb3 = .0625 * blue3;
			float bb4 = .1250 * blue4;
			float bb5 = .2500 * blue5;
			float bb6 = .1250 * blue6;
			float bb7 = .0625 * blue7;
			float bb8 = .1250 * blue8;
			float bb9 = .0625 * blue9;
#pragma endregion

			//combine the kernel for gaussian
			float red = red5;//this is temp only
			//float red = rr1 + rr2 + rr3 + rr4 + rr5 + rr6 + rr7 + rr8 + rr9;
			float green = gg1 + gg2 + gg3 + gg4 + gg5 + gg6 + gg7 + gg8 + gg9;
			float blue = bb1 + bb2 + bb3 + bb4 + bb5 + bb6 + bb7 + bb8 + bb9;

			//calculate gaussian formula

			//this is for the smaller image

			//prevent kernel from exceeding the edges
			if (xxminus < 1) xxminus = 1;
			if (yyminus < 1) yyminus = 1;
			if (xxplus > smallerPyramidWidthMinus) xxplus = smallerPyramidWidthMinus;
			if (yyplus > smallerPyramidHeightMinus) yyplus = smallerPyramidHeightMinus;
			//prevent kernel from exceeding the edges

			//        ◄◄◄◄X►►►►
			//_______________________________________
			//|   top left  |   top  |   top right  | ▲
			//|_____________________________________| ▲
			//|    left     |  nidx  |     right    | Y
			//|_____________________________________| ▼
			//| bottom left | bottom | bottom right | ▼
			//|_____________________________________| 



			//this is for the smaller image

			//sprintf(sBuffer6,"x = %d\n y = %d\n\n xx = %d\n yy = %d\n\n largerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
			//                   ,x,       y,         xx,       yy,         largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
			//				   MessageBox(NULL,sBuffer6,"X and Y", MB_OK);

				
			//if (xx > 120)
			{
			//sprintf(sBuffer6,"x = %d\n y = %d\n\n xx = %d\n yy = %d\n\n red = %f\n\nlargerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
			//,x,       y,         xx,       yy,         red,        largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
			//MessageBox(NULL,sBuffer6,"X and Y", MB_OK);
			}


			smallerPyramidLevelArray[nIdx + CHANNEL_R] = red;
			smallerPyramidLevelArray[nIdx + CHANNEL_G] = green;
			smallerPyramidLevelArray[nIdx + CHANNEL_B] = blue;

		}//end y
		yy = 0;//reset xx back to 0 to follow the x loop
	}//end x

	//sprintf(sBuffer6,"HALT");MessageBox(NULL,sBuffer6,"stop", MB_OK);



	//!!!!!!!!!!!!!!!!!!!!!!!
	// see a problem with routine below
	// at end of x, (x = 127 & y = 0)
	// reads red = 95 which is at 
	// x = 1 && y = 253, which over the course of an image will create a sheer

	//copy smaller pyramid back to larger one to return to main loop
		
	yy = 0;
	xx = 0;

	for (int x = 0; x < smallerPyramidLevelWidth; x++)
	{
		for (int y = 0; y < smallerPyramidLevelHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * smallerPyramidLevelWidth;
			int nIdx2 = xx * 4 + y * 4 * largerPyramidLevelWidth;
			float red = smallerPyramidLevelArray[nIdx1 + CHANNEL_R];
			float green = smallerPyramidLevelArray[nIdx1 + CHANNEL_G];
			float blue = smallerPyramidLevelArray[nIdx1 + CHANNEL_B];


			sprintf(sBuffer6,"x = %d\n y = %d\n\n xx = %d\n yy = %d\n\n red = %f\n\nlargerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
				             ,x,       y,         xx,       yy,         red,        largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
			MessageBox(NULL,sBuffer6,"X and Y", MB_OK);


			//largerPyramidLevelArray[nIdx2 + CHANNEL_R] = red;
			//largerPyramidLevelArray[nIdx2 + CHANNEL_G] = green;
			//largerPyramidLevelArray[nIdx2 + CHANNEL_B] = blue;
			xx++;
		}
		xx = 0;
	}

	//for (int y = 0; y < smallerPyramidLevelHeight; y++)
	//{
	//for (int x = 0; x < smallerPyramidLevelWidth; x++)
	//{
	//int nIdx1 = x * 4 + y * 4 * smallerPyramidLevelWidth;
	//int nIdx2 = x * 4 + y * 4 * largerPyramidLevelWidth;
	//float red = smallerPyramidLevelArray[nIdx1 + CHANNEL_R];
	//float green = smallerPyramidLevelArray[nIdx1 + CHANNEL_G];
	//float blue = smallerPyramidLevelArray[nIdx1 + CHANNEL_B];
	//largerPyramidLevelArray[nIdx2 + CHANNEL_R] = red;
	//largerPyramidLevelArray[nIdx2 + CHANNEL_G] = green;
	//largerPyramidLevelArray[nIdx2 + CHANNEL_B] = blue;
	//}
	//}

	//just for printing results
	for (int x = 0; x < smallerPyramidLevelWidth; x++)
	{
		for (int y = 0; y < smallerPyramidLevelHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * smallerPyramidLevelWidth;
			int nIdx2 = x * 4 + y * 4 * largerPyramidLevelWidth;

			float red = largerPyramidLevelArray[nIdx2 + CHANNEL_R];
			float green = largerPyramidLevelArray[nIdx2 + CHANNEL_G];
			float blue = largerPyramidLevelArray[nIdx2 + CHANNEL_B];
			//if (x > 120)
			{
				sprintf(sBuffer6,"x = %d\n y = %d\n\n red = %f\n\nlargerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
			                     ,x,       y,         red,        largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
				MessageBox(NULL,sBuffer6,"X and Y", MB_OK);
			}

		}
	}

	//sprintf(sBuffer6,"HALT2");MessageBox(NULL,sBuffer6,"end copy", MB_OK);

	return *smallerPyramidLevelArray;
}
*/







