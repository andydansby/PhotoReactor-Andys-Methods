#pragma once

//#include "colorspace.h"
//for my new class


class smallKernels
{
public:

#include "IPlugin.h"


	smallKernels(void)
	{	}

	virtual ~smallKernels(void)
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

float clamp0to1(float *inputArray, int ImageWidth, int ImageHeight)
{
	for (int x = 0; x < ImageWidth; x++)
	{
		for (int y = 0; y < ImageHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * ImageWidth;
			float red = inputArray[nIdx1 + CHANNEL_R];
			float green = inputArray[nIdx1 + CHANNEL_G];
			float blue = inputArray[nIdx1 + CHANNEL_B];

			float red1 = max(0, min(red, 1.0));
			float green1 = max(0, min(green, 1.0));
			float blue1 = max(0, min(blue, 1.0));

			inputArray[nIdx1 + CHANNEL_R] = red1;
			inputArray[nIdx1 + CHANNEL_G] = green1;
			inputArray[nIdx1 + CHANNEL_B] = blue1;
		}
	}

	return *inputArray;
}

float LaPlacian3x3x8(float *inputArray, int ImageWidth, int ImageHeight)
{
	//create a temp array
	float* tempArray=new float[ImageWidth * ImageHeight * 4];
	
	//copy input to tempArray
	for (int x = 0; x < ImageWidth; x++)
	{
		for (int y = 0; y < ImageHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * ImageWidth;

			float red = inputArray[nIdx1 + CHANNEL_R];
			float green = inputArray[nIdx1 + CHANNEL_G];
			float blue = inputArray[nIdx1 + CHANNEL_B];

			tempArray[nIdx1 + CHANNEL_R] = red;
			tempArray[nIdx1 + CHANNEL_G] = green;
			tempArray[nIdx1 + CHANNEL_B] = blue;
		}
	}


	for (int x = 1; x < ImageWidth - 1; x++)
	{
		for (int y = 1; y < ImageHeight - 1; y++)
		{

			int xplus = x + 1;
			int xminus = x - 1;
			int yplus = y + 1;
			int yminus = y - 1;
			
			//   x-   ◄◄◄◄X►►►►   x+
			//________________________
			//| nIdx1 | nidx2 | nidx3 | y+
			//|_______________________| ▲
			//| nIdx4 | nidx5 | nidx6 | Y
			//|_______________________| ▼
			//| nIdx7 | nidx8 | nidx9 | y-
			//|_______________________| 
			
			//Index for the input image
#pragma region
			int nIdx1 = xminus * 4 + yplus * 4 * ImageWidth;//left above center
			int nIdx2 = x * 4 + yplus * 4 * ImageWidth;//above center
			int nIdx3 = xplus * 4 + yplus * 4 * ImageWidth;//right above center
			int nIdx4 = xminus * 4 + y * 4 * ImageWidth;//left center
			int nIdx5 = x * 4 + y * 4 * ImageWidth; //center
			int nIdx6 = xplus * 4 + y * 4 * ImageWidth;//right center
			int nIdx7 = xminus * 4 + yminus * 4 * ImageWidth;//left below center
			int nIdx8 = x * 4 + yminus * 4 * ImageWidth;//below center
			int nIdx9 = xplus * 4 + yminus * 4 * ImageWidth;//right below center
			//for the larger image

			float red1 = inputArray[nIdx1 + CHANNEL_R];//upper left
			float red2 = inputArray[nIdx2 + CHANNEL_R];//upper center
			float red3 = inputArray[nIdx3 + CHANNEL_R];//upper right
			float red4 = inputArray[nIdx4 + CHANNEL_R];//left center
			float red5 = inputArray[nIdx5 + CHANNEL_R];//center
			float red6 = inputArray[nIdx6 + CHANNEL_R];//right center
			float red7 = inputArray[nIdx7 + CHANNEL_R];//lower left
			float red8 = inputArray[nIdx8 + CHANNEL_R];//lower center
			float red9 = inputArray[nIdx9 + CHANNEL_R];//lower right

			float green1 = inputArray[nIdx1 + CHANNEL_G];//upper left
			float green2 = inputArray[nIdx2 + CHANNEL_G];//upper center
			float green3 = inputArray[nIdx3 + CHANNEL_G];//upper right
			float green4 = inputArray[nIdx4 + CHANNEL_G];//left center
			float green5 = inputArray[nIdx5 + CHANNEL_G];//center
			float green6 = inputArray[nIdx6 + CHANNEL_G];//right center
			float green7 = inputArray[nIdx7 + CHANNEL_G];//lower left
			float green8 = inputArray[nIdx8 + CHANNEL_G];//lower center
			float green9 = inputArray[nIdx9 + CHANNEL_G];//lower right

			float blue1 = inputArray[nIdx1 + CHANNEL_B];//upper left
			float blue2 = inputArray[nIdx2 + CHANNEL_B];//upper center
			float blue3 = inputArray[nIdx3 + CHANNEL_B];//upper right
			float blue4 = inputArray[nIdx4 + CHANNEL_B];//left center
			float blue5 = inputArray[nIdx5 + CHANNEL_B];//center
			float blue6 = inputArray[nIdx6 + CHANNEL_B];//right center
			float blue7 = inputArray[nIdx7 + CHANNEL_B];//lower left
			float blue8 = inputArray[nIdx8 + CHANNEL_B];//lower center
			float blue9 = inputArray[nIdx9 + CHANNEL_B];//lower right
#pragma endregion
			//Index for the input image
			
#pragma region
			//   3X3 LaPlacian Kernel 8 neighbors
			//        -◄◄◄X►►►+
			//______________________
			//| -1/8 | -1/8 | -1/8 | +
			//|____________________| ▲
			//| -1/8 |  1   | -1/8 | Y
			//|____________________| ▼
			//| -1/8 | -1/8 | -1/8 | -
			//|____________________| 

			//   3X3 LaPlacian Kernel
			//        -◄◄◄X►►►+                         -◄◄◄X►►►+
			//______________________              ___________________
			//| -1.0 | -1.0 | -1.0 | +           | rr1 | rr2 | rr3 | +
			//|____________________| ▲           |_________________| ▲
			//| -1.0 |  8.0 | -1.0 | Y           | rr4 | rr5 | rr6 | Y
			//|____________________| ▼           |_________________| ▼
			//| -1.0 | -1.0 | -1.0 | -           | rr7 | rr8 | rr9 | -
			//|____________________|             |_________________| 
			
			
			float rr1 = -1.0 * red1;
			float rr2 = -1.0 * red2;
			float rr3 = -1.0 * red3;
			float rr4 = -1.0 * red4;
			float rr5 = 8.0 * red5;
			float rr6 = -1.0 * red6;
			float rr7 = -1.0 * red7;
			float rr8 = -1.0 * red8;
			float rr9 = -1.0 * red9;

			float gg1 = -1.0 * green1;
			float gg2 = -1.0 * green2;
			float gg3 = -1.0 * green3;
			float gg4 = -1.0 * green4;
			float gg5 = 8.0 * green5;
			float gg6 = -1.0 * green6;
			float gg7 = -1.0 * green7;
			float gg8 = -1.0 * green8;
			float gg9 = -1.0 * green9;

			float bb1 = -1.0 * blue1;
			float bb2 = -1.0 * blue2;
			float bb3 = -1.0 * blue3;
			float bb4 = -1.0 * blue4;
			float bb5 = 8.0 * blue5;
			float bb6 = -1.0 * blue6;
			float bb7 = -1.0 * blue7;
			float bb8 = -1.0 * blue8;
			float bb9 = -1.0 * blue9;
#pragma endregion
			
			//combine the kernel for gaussian
			float red = rr1 + rr2 + rr3 + rr4 + rr5 + rr6 + rr7 + rr8 + rr9;
			float green = gg1 + gg2 + gg3 + gg4 + gg5 + gg6 + gg7 + gg8 + gg9;
			float blue = bb1 + bb2 + bb3 + bb4 + bb5 + bb6 + bb7 + bb8 + bb9;
			
			tempArray[nIdx5 + CHANNEL_R] = red;
			tempArray[nIdx5 + CHANNEL_G] = green;
			tempArray[nIdx5 + CHANNEL_B] = blue;
			
		}
	}

	//copy tempArray to input
	for (int x = 0; x < ImageWidth; x++)
	{
		for (int y = 0; y < ImageHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * ImageWidth;

			float red = tempArray[nIdx1 + CHANNEL_R];
			float green = tempArray[nIdx1 + CHANNEL_G];
			float blue = tempArray[nIdx1 + CHANNEL_B];

			inputArray[nIdx1 + CHANNEL_R] = red;
			inputArray[nIdx1 + CHANNEL_G] = green;
			inputArray[nIdx1 + CHANNEL_B] = blue;
		}
	}

	delete [] tempArray;

	return *inputArray;
}

float LaPlacian3x3x4(float *inputArray, int ImageWidth, int ImageHeight)
{
	//create a temp array
	float* tempArray=new float[ImageWidth * ImageHeight * 4];
	
	//copy input to tempArray
	for (int x = 0; x < ImageWidth; x++)
	{
		for (int y = 0; y < ImageHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * ImageWidth;

			float red = inputArray[nIdx1 + CHANNEL_R];
			float green = inputArray[nIdx1 + CHANNEL_G];
			float blue = inputArray[nIdx1 + CHANNEL_B];

			tempArray[nIdx1 + CHANNEL_R] = red;
			tempArray[nIdx1 + CHANNEL_G] = green;
			tempArray[nIdx1 + CHANNEL_B] = blue;
		}
	}


	for (int x = 1; x < ImageWidth - 1; x++)
	{
		for (int y = 1; y < ImageHeight - 1; y++)
		{

			int xplus = x + 1;
			int xminus = x - 1;
			int yplus = y + 1;
			int yminus = y - 1;
			
			//   x-   ◄◄◄◄X►►►►   x+
			//________________________
			//| nIdx1 | nidx2 | nidx3 | y+
			//|_______________________| ▲
			//| nIdx4 | nidx5 | nidx6 | Y
			//|_______________________| ▼
			//| nIdx7 | nidx8 | nidx9 | y-
			//|_______________________| 
			
			//Index for the input image
#pragma region
			int nIdx1 = xminus * 4 + yplus * 4 * ImageWidth;//left above center
			int nIdx2 = x * 4 + yplus * 4 * ImageWidth;//above center
			int nIdx3 = xplus * 4 + yplus * 4 * ImageWidth;//right above center
			int nIdx4 = xminus * 4 + y * 4 * ImageWidth;//left center
			int nIdx5 = x * 4 + y * 4 * ImageWidth; //center
			int nIdx6 = xplus * 4 + y * 4 * ImageWidth;//right center
			int nIdx7 = xminus * 4 + yminus * 4 * ImageWidth;//left below center
			int nIdx8 = x * 4 + yminus * 4 * ImageWidth;//below center
			int nIdx9 = xplus * 4 + yminus * 4 * ImageWidth;//right below center
			//for the larger image

			float red1 = inputArray[nIdx1 + CHANNEL_R];//upper left
			float red2 = inputArray[nIdx2 + CHANNEL_R];//upper center
			float red3 = inputArray[nIdx3 + CHANNEL_R];//upper right
			float red4 = inputArray[nIdx4 + CHANNEL_R];//left center
			float red5 = inputArray[nIdx5 + CHANNEL_R];//center
			float red6 = inputArray[nIdx6 + CHANNEL_R];//right center
			float red7 = inputArray[nIdx7 + CHANNEL_R];//lower left
			float red8 = inputArray[nIdx8 + CHANNEL_R];//lower center
			float red9 = inputArray[nIdx9 + CHANNEL_R];//lower right

			float green1 = inputArray[nIdx1 + CHANNEL_G];//upper left
			float green2 = inputArray[nIdx2 + CHANNEL_G];//upper center
			float green3 = inputArray[nIdx3 + CHANNEL_G];//upper right
			float green4 = inputArray[nIdx4 + CHANNEL_G];//left center
			float green5 = inputArray[nIdx5 + CHANNEL_G];//center
			float green6 = inputArray[nIdx6 + CHANNEL_G];//right center
			float green7 = inputArray[nIdx7 + CHANNEL_G];//lower left
			float green8 = inputArray[nIdx8 + CHANNEL_G];//lower center
			float green9 = inputArray[nIdx9 + CHANNEL_G];//lower right

			float blue1 = inputArray[nIdx1 + CHANNEL_B];//upper left
			float blue2 = inputArray[nIdx2 + CHANNEL_B];//upper center
			float blue3 = inputArray[nIdx3 + CHANNEL_B];//upper right
			float blue4 = inputArray[nIdx4 + CHANNEL_B];//left center
			float blue5 = inputArray[nIdx5 + CHANNEL_B];//center
			float blue6 = inputArray[nIdx6 + CHANNEL_B];//right center
			float blue7 = inputArray[nIdx7 + CHANNEL_B];//lower left
			float blue8 = inputArray[nIdx8 + CHANNEL_B];//lower center
			float blue9 = inputArray[nIdx9 + CHANNEL_B];//lower right
#pragma endregion
			//Index for the input image
			
#pragma region
			//   3X3 LaPlacian Kernel 8 neighbors
			//        -◄◄◄X►►►+
			//______________________
			//| -1/8 | -1/8 | -1/8 | +
			//|____________________| ▲
			//| -1/8 |  1   | -1/8 | Y
			//|____________________| ▼
			//| -1/8 | -1/8 | -1/8 | -
			//|____________________| 

			//   3X3 LaPlacian Kernel
			//        -◄◄◄X►►►+                         -◄◄◄X►►►+
			//_____________________              ___________________
			//| 0.0  | -1.0 | 0.0 | +           | rr1 | rr2 | rr3 | +
			//|___________________| ▲           |_________________| ▲
			//| -1.0 | 4.0  |-1.0 | Y           | rr4 | rr5 | rr6 | Y
			//|___________________| ▼           |_________________| ▼
			//| 0.0  | -1.0 | 0.0 | -           | rr7 | rr8 | rr9 | -
			//|___________________|             |_________________| 
			
			
			float rr1 = 0.0 * red1;
			float rr2 = -1.0 * red2;
			float rr3 = 0.0 * red3;
			float rr4 = -1.0 * red4;
			float rr5 = 4.0 * red5;
			float rr6 = -1.0 * red6;
			float rr7 = 0.0 * red7;
			float rr8 = -1.0 * red8;
			float rr9 = 0.0 * red9;

			float gg1 = 0.0 * green1;
			float gg2 = -1.0 * green2;
			float gg3 = 0.0 * green3;
			float gg4 = -1.0 * green4;
			float gg5 = 4.0 * green5;
			float gg6 = -1.0 * green6;
			float gg7 = 0.0 * green7;
			float gg8 = -1.0 * green8;
			float gg9 = 0.0 * green9;

			float bb1 = 0.0 * blue1;
			float bb2 = -1.0 * blue2;
			float bb3 = 0.0 * blue3;
			float bb4 = -1.0 * blue4;
			float bb5 = 4.0 * blue5;
			float bb6 = -1.0 * blue6;
			float bb7 = 0.0 * blue7;
			float bb8 = -1.0 * blue8;
			float bb9 = 0.0 * blue9;
#pragma endregion
			
			//combine the kernel for laplacian
			float red = rr1 + rr2 + rr3 + rr4 + rr5 + rr6 + rr7 + rr8 + rr9;
			float green = gg1 + gg2 + gg3 + gg4 + gg5 + gg6 + gg7 + gg8 + gg9;
			float blue = bb1 + bb2 + bb3 + bb4 + bb5 + bb6 + bb7 + bb8 + bb9;
			
			tempArray[nIdx5 + CHANNEL_R] = abs(red);
			tempArray[nIdx5 + CHANNEL_G] = abs(green);
			tempArray[nIdx5 + CHANNEL_B] = abs(blue);
			
		}
	}

	//copy tempArray to input
	for (int x = 0; x < ImageWidth; x++)
	{
		for (int y = 0; y < ImageHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * ImageWidth;

			float red = tempArray[nIdx1 + CHANNEL_R];
			float green = tempArray[nIdx1 + CHANNEL_G];
			float blue = tempArray[nIdx1 + CHANNEL_B];

			inputArray[nIdx1 + CHANNEL_R] = red;
			inputArray[nIdx1 + CHANNEL_G] = green;
			inputArray[nIdx1 + CHANNEL_B] = blue;
		}
	}

	delete [] tempArray;

	return *inputArray;
}


/// <summary> Perform a 3x3 LaPlacian kernel across 2d image
/// <para>inputArray = input image.</para>
/// <para>ImageWidth = width of input image.</para>
/// <para>ImageHeight = height of input image.</para>
/// <para>Returns return *copyToImage </para>
/// </summary>
float LaPlacian3x3EightNeighbors(float *inputArray, int ImageWidth, int ImageHeight)
{
	//create a temp array
	float* tempArray=new float[ImageWidth * ImageHeight * 4];
	
	//copy input to tempArray
	for (int x = 0; x < ImageWidth; x++)
	{
		for (int y = 0; y < ImageHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * ImageWidth;

			float red = inputArray[nIdx1 + CHANNEL_R];
			float green = inputArray[nIdx1 + CHANNEL_G];
			float blue = inputArray[nIdx1 + CHANNEL_B];

			tempArray[nIdx1 + CHANNEL_R] = red;
			tempArray[nIdx1 + CHANNEL_G] = green;
			tempArray[nIdx1 + CHANNEL_B] = blue;
		}
	}


	for (int x = 1; x < ImageWidth - 1; x++)
	{
		for (int y = 1; y < ImageHeight - 1; y++)
		{

			int xplus = x + 1;
			int xminus = x - 1;
			int yplus = y + 1;
			int yminus = y - 1;
			
			//   x-   ◄◄◄◄X►►►►   x+
			//________________________
			//| nIdx1 | nidx2 | nidx3 | y+
			//|_______________________| ▲
			//| nIdx4 | nidx5 | nidx6 | Y
			//|_______________________| ▼
			//| nIdx7 | nidx8 | nidx9 | y-
			//|_______________________| 
			
			//Index for the input image
#pragma region
			int nIdx1 = xminus * 4 + yplus * 4 * ImageWidth;//left above center
			int nIdx2 = x * 4 + yplus * 4 * ImageWidth;//above center
			int nIdx3 = xplus * 4 + yplus * 4 * ImageWidth;//right above center
			int nIdx4 = xminus * 4 + y * 4 * ImageWidth;//left center
			int nIdx5 = x * 4 + y * 4 * ImageWidth; //center
			int nIdx6 = xplus * 4 + y * 4 * ImageWidth;//right center
			int nIdx7 = xminus * 4 + yminus * 4 * ImageWidth;//left below center
			int nIdx8 = x * 4 + yminus * 4 * ImageWidth;//below center
			int nIdx9 = xplus * 4 + yminus * 4 * ImageWidth;//right below center
			//for the larger image

			float red1 = inputArray[nIdx1 + CHANNEL_R];//upper left
			float red2 = inputArray[nIdx2 + CHANNEL_R];//upper center
			float red3 = inputArray[nIdx3 + CHANNEL_R];//upper right
			float red4 = inputArray[nIdx4 + CHANNEL_R];//left center
			float red5 = inputArray[nIdx5 + CHANNEL_R];//center
			float red6 = inputArray[nIdx6 + CHANNEL_R];//right center
			float red7 = inputArray[nIdx7 + CHANNEL_R];//lower left
			float red8 = inputArray[nIdx8 + CHANNEL_R];//lower center
			float red9 = inputArray[nIdx9 + CHANNEL_R];//lower right

			float green1 = inputArray[nIdx1 + CHANNEL_G];//upper left
			float green2 = inputArray[nIdx2 + CHANNEL_G];//upper center
			float green3 = inputArray[nIdx3 + CHANNEL_G];//upper right
			float green4 = inputArray[nIdx4 + CHANNEL_G];//left center
			float green5 = inputArray[nIdx5 + CHANNEL_G];//center
			float green6 = inputArray[nIdx6 + CHANNEL_G];//right center
			float green7 = inputArray[nIdx7 + CHANNEL_G];//lower left
			float green8 = inputArray[nIdx8 + CHANNEL_G];//lower center
			float green9 = inputArray[nIdx9 + CHANNEL_G];//lower right

			float blue1 = inputArray[nIdx1 + CHANNEL_B];//upper left
			float blue2 = inputArray[nIdx2 + CHANNEL_B];//upper center
			float blue3 = inputArray[nIdx3 + CHANNEL_B];//upper right
			float blue4 = inputArray[nIdx4 + CHANNEL_B];//left center
			float blue5 = inputArray[nIdx5 + CHANNEL_B];//center
			float blue6 = inputArray[nIdx6 + CHANNEL_B];//right center
			float blue7 = inputArray[nIdx7 + CHANNEL_B];//lower left
			float blue8 = inputArray[nIdx8 + CHANNEL_B];//lower center
			float blue9 = inputArray[nIdx9 + CHANNEL_B];//lower right
#pragma endregion
			//Index for the input image
			
#pragma region
			//   3X3 LaPlacian Kernel 8 neighbors
			//        -◄◄◄X►►►+
			//______________________
			//| -1/8 | -1/8 | -1/8 | +
			//|____________________| ▲
			//| -1/8 |  1   | -1/8 | Y
			//|____________________| ▼
			//| -1/8 | -1/8 | -1/8 | -
			//|____________________| 

			//   3X3 LaPlacian Kernel
			//        -◄◄◄X►►►+                         -◄◄◄X►►►+
			//___________________________              ___________________
			//| -.1250 | -.1250 | -.1250 | +           | rr1 | rr2 | rr3 | +
			//|__________________________| ▲           |_________________| ▲
			//| -.1250 |  1.000 | -.1250 | Y           | rr4 | rr5 | rr6 | Y
			//|__________________________| ▼           |_________________| ▼
			//| -.1250 | -.1250 | -.1250 | -           | rr7 | rr8 | rr9 | -
			//|__________________________|             |_________________| 
			
			
			float rr1 = -.1250 * red1;
			float rr2 = -.1250 * red2;
			float rr3 = -.1250 * red3;
			float rr4 = -.1250 * red4;
			float rr5 = 1.0000 * red5;
			float rr6 = -.1250 * red6;
			float rr7 = -.1250 * red7;
			float rr8 = -.1250 * red8;
			float rr9 = -.1250 * red9;

			float gg1 = -.1250 * green1;
			float gg2 = -.1250 * green2;
			float gg3 = -.1250 * green3;
			float gg4 = -.1250 * green4;
			float gg5 = 1.0000 * green5;
			float gg6 = -.1250 * green6;
			float gg7 = -.1250 * green7;
			float gg8 = -.1250 * green8;
			float gg9 = -.1250 * green9;

			float bb1 = -.1250 * blue1;
			float bb2 = -.1250 * blue2;
			float bb3 = -.1250 * blue3;
			float bb4 = -.1250 * blue4;
			float bb5 = 1.0000 * blue5;
			float bb6 = -.1250 * blue6;
			float bb7 = -.1250 * blue7;
			float bb8 = -.1250 * blue8;
			float bb9 = -.1250 * blue9;
#pragma endregion
			
			//combine the kernel for gaussian
			float red = rr1 + rr2 + rr3 + rr4 + rr5 + rr6 + rr7 + rr8 + rr9;
			float green = gg1 + gg2 + gg3 + gg4 + gg5 + gg6 + gg7 + gg8 + gg9;
			float blue = bb1 + bb2 + bb3 + bb4 + bb5 + bb6 + bb7 + bb8 + bb9;
			
			tempArray[nIdx5 + CHANNEL_R] = red;
			tempArray[nIdx5 + CHANNEL_G] = green;
			tempArray[nIdx5 + CHANNEL_B] = blue;
			
		}
	}

	//copy tempArray to input
	for (int x = 0; x < ImageWidth; x++)
	{
		for (int y = 0; y < ImageHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * ImageWidth;

			float red = tempArray[nIdx1 + CHANNEL_R];
			float green = tempArray[nIdx1 + CHANNEL_G];
			float blue = tempArray[nIdx1 + CHANNEL_B];

			inputArray[nIdx1 + CHANNEL_R] = red;
			inputArray[nIdx1 + CHANNEL_G] = green;
			inputArray[nIdx1 + CHANNEL_B] = blue;
		}
	}

	delete [] tempArray;

	return *inputArray;
}

float LaPlacian3x3FourNeighbors(float *inputArray, int ImageWidth, int ImageHeight)
{
	//create a temp array
	float* tempArray=new float[ImageWidth * ImageHeight * 4];
	
	//copy input to tempArray
	for (int x = 0; x < ImageWidth; x++)
	{
		for (int y = 0; y < ImageHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * ImageWidth;

			float red = inputArray[nIdx1 + CHANNEL_R];
			float green = inputArray[nIdx1 + CHANNEL_G];
			float blue = inputArray[nIdx1 + CHANNEL_B];

			tempArray[nIdx1 + CHANNEL_R] = red;
			tempArray[nIdx1 + CHANNEL_G] = green;
			tempArray[nIdx1 + CHANNEL_B] = blue;
		}
	}


	for (int x = 1; x < ImageWidth - 1; x++)
	{
		for (int y = 1; y < ImageHeight - 1; y++)
		{

			int xplus = x + 1;
			int xminus = x - 1;
			int yplus = y + 1;
			int yminus = y - 1;
			
			//   x-   ◄◄◄◄X►►►►   x+
			//________________________
			//| nIdx1 | nidx2 | nidx3 | y+
			//|_______________________| ▲
			//| nIdx4 | nidx5 | nidx6 | Y
			//|_______________________| ▼
			//| nIdx7 | nidx8 | nidx9 | y-
			//|_______________________| 
			
			//Index for the input image
#pragma region
			int nIdx1 = xminus * 4 + yplus * 4 * ImageWidth;//left above center
			int nIdx2 = x * 4 + yplus * 4 * ImageWidth;//above center
			int nIdx3 = xplus * 4 + yplus * 4 * ImageWidth;//right above center
			int nIdx4 = xminus * 4 + y * 4 * ImageWidth;//left center
			int nIdx5 = x * 4 + y * 4 * ImageWidth; //center
			int nIdx6 = xplus * 4 + y * 4 * ImageWidth;//right center
			int nIdx7 = xminus * 4 + yminus * 4 * ImageWidth;//left below center
			int nIdx8 = x * 4 + yminus * 4 * ImageWidth;//below center
			int nIdx9 = xplus * 4 + yminus * 4 * ImageWidth;//right below center
			//for the larger image

			float red1 = inputArray[nIdx1 + CHANNEL_R];//upper left
			float red2 = inputArray[nIdx2 + CHANNEL_R];//upper center
			float red3 = inputArray[nIdx3 + CHANNEL_R];//upper right
			float red4 = inputArray[nIdx4 + CHANNEL_R];//left center
			float red5 = inputArray[nIdx5 + CHANNEL_R];//center
			float red6 = inputArray[nIdx6 + CHANNEL_R];//right center
			float red7 = inputArray[nIdx7 + CHANNEL_R];//lower left
			float red8 = inputArray[nIdx8 + CHANNEL_R];//lower center
			float red9 = inputArray[nIdx9 + CHANNEL_R];//lower right

			float green1 = inputArray[nIdx1 + CHANNEL_G];//upper left
			float green2 = inputArray[nIdx2 + CHANNEL_G];//upper center
			float green3 = inputArray[nIdx3 + CHANNEL_G];//upper right
			float green4 = inputArray[nIdx4 + CHANNEL_G];//left center
			float green5 = inputArray[nIdx5 + CHANNEL_G];//center
			float green6 = inputArray[nIdx6 + CHANNEL_G];//right center
			float green7 = inputArray[nIdx7 + CHANNEL_G];//lower left
			float green8 = inputArray[nIdx8 + CHANNEL_G];//lower center
			float green9 = inputArray[nIdx9 + CHANNEL_G];//lower right

			float blue1 = inputArray[nIdx1 + CHANNEL_B];//upper left
			float blue2 = inputArray[nIdx2 + CHANNEL_B];//upper center
			float blue3 = inputArray[nIdx3 + CHANNEL_B];//upper right
			float blue4 = inputArray[nIdx4 + CHANNEL_B];//left center
			float blue5 = inputArray[nIdx5 + CHANNEL_B];//center
			float blue6 = inputArray[nIdx6 + CHANNEL_B];//right center
			float blue7 = inputArray[nIdx7 + CHANNEL_B];//lower left
			float blue8 = inputArray[nIdx8 + CHANNEL_B];//lower center
			float blue9 = inputArray[nIdx9 + CHANNEL_B];//lower right
#pragma endregion
			//Index for the input image
			
#pragma region
			//   3X3 LaPlacian Kernel 8 neighbors
			//        -◄◄◄X►►►+
			//______________________
			//| 0    | -1/4 | 0    | +
			//|____________________| ▲
			//| -1/4 |  1   | -1/4 | Y
			//|____________________| ▼
			//| 0    | -1/4 | 0    | -
			//|____________________| 

			//   3X3 LaPlacian Kernel
			//        -◄◄◄X►►►+                         -◄◄◄X►►►+
			//___________________________              ___________________
			//| 0      | -.250  | 0      | +           | rr1 | rr2 | rr3 | +
			//|__________________________| ▲           |_________________| ▲
			//| -.250  |  1.000 | -.250  | Y           | rr4 | rr5 | rr6 | Y
			//|__________________________| ▼           |_________________| ▼
			//| 0      | -.250  | 0      | -           | rr7 | rr8 | rr9 | -
			//|__________________________|             |_________________| 
			
			
			float rr1 = 0.0 * red1;
			float rr2 = -.250 * red2;
			float rr3 = 0.0 * red3;
			float rr4 = -.250 * red4;
			float rr5 = 1.0000 * red5;
			float rr6 = -.250 * red6;
			float rr7 = 0.0 * red7;
			float rr8 = -.250 * red8;
			float rr9 = 0.0 * red9;

			float gg1 = 0.0 * green1;
			float gg2 = -.250 * green2;
			float gg3 = 0.0 * green3;
			float gg4 = -.250 * green4;
			float gg5 = 1.0000 * green5;
			float gg6 = -.250 * green6;
			float gg7 = 0.0 * green7;
			float gg8 = -.250 * green8;
			float gg9 = 0.0 * green9;

			float bb1 = 0.0 * blue1;
			float bb2 = -.250 * blue2;
			float bb3 = 0.0 * blue3;
			float bb4 = -.250 * blue4;
			float bb5 = 1.0000 * blue5;
			float bb6 = -.250 * blue6;
			float bb7 = 0.0 * blue7;
			float bb8 = -.250 * blue8;
			float bb9 = 0.0 * blue9;
#pragma endregion
			
			//combine the kernel for gaussian
			float red = rr1 + rr2 + rr3 + rr4 + rr5 + rr6 + rr7 + rr8 + rr9;
			float green = gg1 + gg2 + gg3 + gg4 + gg5 + gg6 + gg7 + gg8 + gg9;
			float blue = bb1 + bb2 + bb3 + bb4 + bb5 + bb6 + bb7 + bb8 + bb9;
			
			tempArray[nIdx5 + CHANNEL_R] = abs(red);
			tempArray[nIdx5 + CHANNEL_G] = abs(green);
			tempArray[nIdx5 + CHANNEL_B] = abs(blue);
			
		}
	}

	//copy tempArray to input
	for (int x = 0; x < ImageWidth; x++)
	{
		for (int y = 0; y < ImageHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * ImageWidth;

			float red = tempArray[nIdx1 + CHANNEL_R];
			float green = tempArray[nIdx1 + CHANNEL_G];
			float blue = tempArray[nIdx1 + CHANNEL_B];

			inputArray[nIdx1 + CHANNEL_R] = red;
			inputArray[nIdx1 + CHANNEL_G] = green;
			inputArray[nIdx1 + CHANNEL_B] = blue;
		}
	}

	delete [] tempArray;

	return *inputArray;
}


/// <summary> Perform a 3x3 Gaussian kernel across 2d image
/// <para>inputArray = input image.</para>
/// <para>ImageWidth = width of input image.</para>
/// <para>ImageHeight = height of input image.</para>
/// <para>Returns return *copyToImage </para>
/// </summary>
float Gaussian3x3(float *inputArray, int ImageWidth, int ImageHeight)
{

	//create a temp array
	float* tempArray=new float[ImageWidth * ImageHeight * 4];
	
	//copy input to tempArray
	for (int x = 0; x < ImageWidth; x++)
	{
		for (int y = 0; y < ImageHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * ImageWidth;

			float red = inputArray[nIdx1 + CHANNEL_R];
			float green = inputArray[nIdx1 + CHANNEL_G];
			float blue = inputArray[nIdx1 + CHANNEL_B];

			tempArray[nIdx1 + CHANNEL_R] = red;
			tempArray[nIdx1 + CHANNEL_G] = green;
			tempArray[nIdx1 + CHANNEL_B] = blue;
		}
	}


	for (int x = 1; x < ImageWidth - 1; x++)
	{
		for (int y = 1; y < ImageHeight - 1; y++)
		{

			int xplus = x + 1;
			int xminus = x - 1;
			int yplus = y + 1;
			int yminus = y - 1;
			
			//   x-   ◄◄◄◄X►►►►   x+
			//________________________
			//| nIdx1 | nidx2 | nidx3 | y+
			//|_______________________| ▲
			//| nIdx4 | nidx5 | nidx6 | Y
			//|_______________________| ▼
			//| nIdx7 | nidx8 | nidx9 | y-
			//|_______________________| 
			
			//Index for the input image
#pragma region
			int nIdx1 = xminus * 4 + yplus * 4 * ImageWidth;//left above center
			int nIdx2 = x * 4 + yplus * 4 * ImageWidth;//above center
			int nIdx3 = xplus * 4 + yplus * 4 * ImageWidth;//right above center
			int nIdx4 = xminus * 4 + y * 4 * ImageWidth;//left center
			int nIdx5 = x * 4 + y * 4 * ImageWidth; //center
			int nIdx6 = xplus * 4 + y * 4 * ImageWidth;//right center
			int nIdx7 = xminus * 4 + yminus * 4 * ImageWidth;//left below center
			int nIdx8 = x * 4 + yminus * 4 * ImageWidth;//below center
			int nIdx9 = xplus * 4 + yminus * 4 * ImageWidth;//right below center
			//for the larger image

			float red1 = inputArray[nIdx1 + CHANNEL_R];//upper left
			float red2 = inputArray[nIdx2 + CHANNEL_R];//upper center
			float red3 = inputArray[nIdx3 + CHANNEL_R];//upper right
			float red4 = inputArray[nIdx4 + CHANNEL_R];//left center
			float red5 = inputArray[nIdx5 + CHANNEL_R];//center
			float red6 = inputArray[nIdx6 + CHANNEL_R];//right center
			float red7 = inputArray[nIdx7 + CHANNEL_R];//lower left
			float red8 = inputArray[nIdx8 + CHANNEL_R];//lower center
			float red9 = inputArray[nIdx9 + CHANNEL_R];//lower right

			float green1 = inputArray[nIdx1 + CHANNEL_G];//upper left
			float green2 = inputArray[nIdx2 + CHANNEL_G];//upper center
			float green3 = inputArray[nIdx3 + CHANNEL_G];//upper right
			float green4 = inputArray[nIdx4 + CHANNEL_G];//left center
			float green5 = inputArray[nIdx5 + CHANNEL_G];//center
			float green6 = inputArray[nIdx6 + CHANNEL_G];//right center
			float green7 = inputArray[nIdx7 + CHANNEL_G];//lower left
			float green8 = inputArray[nIdx8 + CHANNEL_G];//lower center
			float green9 = inputArray[nIdx9 + CHANNEL_G];//lower right

			float blue1 = inputArray[nIdx1 + CHANNEL_B];//upper left
			float blue2 = inputArray[nIdx2 + CHANNEL_B];//upper center
			float blue3 = inputArray[nIdx3 + CHANNEL_B];//upper right
			float blue4 = inputArray[nIdx4 + CHANNEL_B];//left center
			float blue5 = inputArray[nIdx5 + CHANNEL_B];//center
			float blue6 = inputArray[nIdx6 + CHANNEL_B];//right center
			float blue7 = inputArray[nIdx7 + CHANNEL_B];//lower left
			float blue8 = inputArray[nIdx8 + CHANNEL_B];//lower center
			float blue9 = inputArray[nIdx9 + CHANNEL_B];//lower right
#pragma endregion
			//Index for the input image
			
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
			
			tempArray[nIdx5 + CHANNEL_R] = red;
			tempArray[nIdx5 + CHANNEL_G] = green;
			tempArray[nIdx5 + CHANNEL_B] = blue;
			
		}
	}

	//copy tempArray to input
	for (int x = 0; x < ImageWidth; x++)
	{
		for (int y = 0; y < ImageHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * ImageWidth;

			float red = tempArray[nIdx1 + CHANNEL_R];
			float green = tempArray[nIdx1 + CHANNEL_G];
			float blue = tempArray[nIdx1 + CHANNEL_B];

			inputArray[nIdx1 + CHANNEL_R] = red;
			inputArray[nIdx1 + CHANNEL_G] = green;
			inputArray[nIdx1 + CHANNEL_B] = blue;
		}
	}

	delete [] tempArray;

	return *inputArray;
}


/// <summary> Perform a 3x3 Gaussian kernel across 2d image
/// <para>inputArray = input image.</para>
/// <para>ImageWidth = width of input image.</para>
/// <para>ImageHeight = height of input image.</para>
/// <para>Returns return *copyToImage </para>
/// </summary>
float SumKernelDifference3x3(float *inputArray, int ImageWidth, int ImageHeight)
{

	//create a temp array
	float* tempArray=new float[ImageWidth * ImageHeight * 4];
	
	//copy input to tempArray
	for (int x = 0; x < ImageWidth; x++)
	{
		for (int y = 0; y < ImageHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * ImageWidth;

			float red = inputArray[nIdx1 + CHANNEL_R];
			float green = inputArray[nIdx1 + CHANNEL_G];
			float blue = inputArray[nIdx1 + CHANNEL_B];

			tempArray[nIdx1 + CHANNEL_R] = red;
			tempArray[nIdx1 + CHANNEL_G] = green;
			tempArray[nIdx1 + CHANNEL_B] = blue;
		}
	}

	float sumRed = 0;
	float sumGreen = 0;
	float sumBlue = 0;

	float differenceRed = 0;
	float differenceGreen = 0;
	float differenceBlue = 0;


	for (int x = 1; x < ImageWidth - 1; x++)
	{
		for (int y = 1; y < ImageHeight - 1; y++)
		{
			int xplus = x + 1;
			int xminus = x - 1;
			int yplus = y + 1;
			int yminus = y - 1;
			
			//   x-   ◄◄◄◄X►►►►   x+
			//________________________
			//| nIdx1 | nidx2 | nidx3 | y+
			//|_______________________| ▲
			//| nIdx4 | nidx5 | nidx6 | Y
			//|_______________________| ▼
			//| nIdx7 | nidx8 | nidx9 | y-
			//|_______________________| 
			
			//Index for the input image
#pragma region
			int nIdx1 = xminus * 4 + yplus * 4 * ImageWidth;//left above center
			int nIdx2 = x * 4 + yplus * 4 * ImageWidth;//above center
			int nIdx3 = xplus * 4 + yplus * 4 * ImageWidth;//right above center
			int nIdx4 = xminus * 4 + y * 4 * ImageWidth;//left center
			int nIdx5 = x * 4 + y * 4 * ImageWidth; //center
			int nIdx6 = xplus * 4 + y * 4 * ImageWidth;//right center
			int nIdx7 = xminus * 4 + yminus * 4 * ImageWidth;//left below center
			int nIdx8 = x * 4 + yminus * 4 * ImageWidth;//below center
			int nIdx9 = xplus * 4 + yminus * 4 * ImageWidth;//right below center
			//for the larger image

			float red1 = inputArray[nIdx1 + CHANNEL_R];//upper left
			float red2 = inputArray[nIdx2 + CHANNEL_R];//upper center
			float red3 = inputArray[nIdx3 + CHANNEL_R];//upper right
			float red4 = inputArray[nIdx4 + CHANNEL_R];//left center
			float red5 = inputArray[nIdx5 + CHANNEL_R];//center
			float red6 = inputArray[nIdx6 + CHANNEL_R];//right center
			float red7 = inputArray[nIdx7 + CHANNEL_R];//lower left
			float red8 = inputArray[nIdx8 + CHANNEL_R];//lower center
			float red9 = inputArray[nIdx9 + CHANNEL_R];//lower right
			sumRed = red1 + red2 + red3 + red4 + red5 + red6 + red7 + red8 + red9;
			float avgRed = sumRed / 9;
			differenceRed = abs(avgRed - red5);

			float green1 = inputArray[nIdx1 + CHANNEL_G];//upper left
			float green2 = inputArray[nIdx2 + CHANNEL_G];//upper center
			float green3 = inputArray[nIdx3 + CHANNEL_G];//upper right
			float green4 = inputArray[nIdx4 + CHANNEL_G];//left center
			float green5 = inputArray[nIdx5 + CHANNEL_G];//center
			float green6 = inputArray[nIdx6 + CHANNEL_G];//right center
			float green7 = inputArray[nIdx7 + CHANNEL_G];//lower left
			float green8 = inputArray[nIdx8 + CHANNEL_G];//lower center
			float green9 = inputArray[nIdx9 + CHANNEL_G];//lower right
			sumGreen = green1 + green2 + green3 + green4 + green5 + green6 + green7 + green8 + green9;
			float avgGreen = sumGreen / 9;
			differenceGreen = abs(avgGreen - green5);

			float blue1 = inputArray[nIdx1 + CHANNEL_B];//upper left
			float blue2 = inputArray[nIdx2 + CHANNEL_B];//upper center
			float blue3 = inputArray[nIdx3 + CHANNEL_B];//upper right
			float blue4 = inputArray[nIdx4 + CHANNEL_B];//left center
			float blue5 = inputArray[nIdx5 + CHANNEL_B];//center
			float blue6 = inputArray[nIdx6 + CHANNEL_B];//right center
			float blue7 = inputArray[nIdx7 + CHANNEL_B];//lower left
			float blue8 = inputArray[nIdx8 + CHANNEL_B];//lower center
			float blue9 = inputArray[nIdx9 + CHANNEL_B];//lower right
			sumBlue = blue1 + blue2 + blue3 + blue4 + blue5 + blue6 + blue7 + blue8 + blue9;
			float avgBlue = sumBlue / 9;
			differenceBlue = abs(avgBlue - blue5);
#pragma endregion
			//Index for the input image
			
			tempArray[nIdx5 + CHANNEL_R] = differenceRed;
			tempArray[nIdx5 + CHANNEL_G] = differenceGreen;
			tempArray[nIdx5 + CHANNEL_B] = differenceBlue;

			
			//char sBuffer6[400];

			/*sprintf(sBuffer6,"red1 = %f\n red2 = %f\n red3 = %f\n red4 = %f\n red5 = %f\n red6 = %f\n red7 = %f\n red8 = %f\n red9 = %f\n\n Center = red5 = %f\n\n sumRed = %f\n\n differenceRed = %f"
				             ,red1,       red2,       red3,       red4,       red5,       red6,       red7,       red8,       red9,                  red5,         sumRed,         differenceRed);
			MessageBox(NULL,sBuffer6,"Image summing", MB_OK);*/
			/*sprintf(sBuffer6,"x = %d\n y = %d\n\n differenceRed = %f\n"
				             ,x,       y,         differenceRed);
			MessageBox(NULL,sBuffer6,"Image summing", MB_OK);*/
		}
	}

	//copy tempArray to input
	for (int x = 0; x < ImageWidth; x++)
	{
		for (int y = 0; y < ImageHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * ImageWidth;

			float red = tempArray[nIdx1 + CHANNEL_R];
			float green = tempArray[nIdx1 + CHANNEL_G];
			float blue = tempArray[nIdx1 + CHANNEL_B];

			inputArray[nIdx1 + CHANNEL_R] = red;
			inputArray[nIdx1 + CHANNEL_G] = green;
			inputArray[nIdx1 + CHANNEL_B] = blue;
		}
	}

	delete [] tempArray;

	return *inputArray;
}
