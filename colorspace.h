#pragma once

#ifndef colorspace_h
#define colorspace_h


class colorspace
{
public:

#include "IPlugin.h"
	
	colorspace(void)
	{	}

	virtual ~colorspace(void)
	{	}

	
};

#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>//to use cout
//hello

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
const double PI = 3.141592653589793238462;

/// <summary> Copies an image from one array to another, the copy to array can be of any size. if copy to image is smaller, image will truncate. 
/// If copy to image is larger will have blank areas.
/// <para>copyFromImage = input image.</para>
/// <para>copyFromImageWidth = width of input image.</para>
/// <para>copyFromImageHeight = height of input image.</para>
/// <para>copyToImage = output image, must be initalized in calling routine.</para>
/// <para>copyToImageWidth = width of output image.</para>
/// <para>copyToImageHeight = height of output image.</para>
/// <para>Returns return *copyToImage </para>
/// </summary>
float copyImage(float *copyFromImage, int copyFromImageWidth, int copyFromImageHeight, float *copyToImage, int copyToImageWidth, int copyToImageHeight)
{
	int createErrorInCPPCheck = 0;// this is so I can check if CPPCheck is doing its job, delete this at some point

	for (int x = 0; x < copyFromImageWidth; x++)
	{
		for (int y = 0; y < copyFromImageHeight; y++)
		{
			int nIdx1 = x * 4 + y * 4 * copyFromImageWidth;
			

			float red = copyFromImage[nIdx1 + CHANNEL_R];
			float green = copyFromImage[nIdx1 + CHANNEL_G];
			float blue = copyFromImage[nIdx1 + CHANNEL_B];

			copyToImage[nIdx1 + CHANNEL_R] = red;
			copyToImage[nIdx1 + CHANNEL_G] = green;
			copyToImage[nIdx1 + CHANNEL_B] = blue;
		}
	}

	return *copyToImage;
}


/// <summary> instead of inializing to all 0's we place .5 in array to make it easier to track with print statements. 
/// <para>*imageArray = image array to be inialtized.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float initalizeArrayNeutralGrey(float *imageArray, int imageWidth, int imageHeight)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			const float neutralGrey = 0.5;

			imageArray[nIdx + CHANNEL_R] = neutralGrey;
			imageArray[nIdx + CHANNEL_G] = neutralGrey;
			imageArray[nIdx + CHANNEL_B] = neutralGrey;
		}//end x
	}//end y

	return *imageArray;
}

///<summary> takes 3 variables and trys to adjust towards 1
/// <para> double array[] = static 3 item array double value
/// </summary>
double adjustTo1Weber3(double array[])
{
	//char sBuffer6[400];

	double value1 = array[0];
	double value2 = array[1];
	double value3 = array[2];

	/*
	sprintf(sBuffer6,"contrast = %f\n saturation = %f\n luminosity = %f"
	                 ,value1,         value2,           value3);
	MessageBox(NULL,sBuffer6,"Values 1", MB_OK);*/

	double totalValue = value1 + value2 + value3;

	

	value1 = value1 / totalValue;
	value2 = value2 / totalValue;
	value3 = value3 / totalValue;

	double totalValue2 = value1 + value2 + value3;

	//special case if slightly over 1.0
	if (totalValue2 > 1.0)
	{
		double difference = abs(totalValue2 - 1.0);

		//find which value is largest
		if ((value1 > value2) && (value1 > value3))
		{
			//value1 is largest
			value1 = value1 - difference;
		}

		if ((value2 > value1) && (value2 > value3))
		{
			//value2 is largest
			value2 = value2 - difference;
		}

		if ((value3 > value1) && (value3 > value2))
		{
			//value3 is largest
			value3 = value3 - difference;
		}
	}

	//special case if slightly under 1.0
	if (totalValue2 < 1.0)
	{
		double difference = abs(totalValue2 - 1.0);

		//find which value is smallest
		if ((value1 < value2) && (value1 < value3))
		{
			//value1 is smallest
			value1 = value1 + difference;
		}

		if ((value2 < value1) && (value2 < value3))
		{
			//value2 is smallest
			value2 = value2 + difference;
		}

		if ((value3 < value1) && (value3 < value2))
		{
			//value3 is smallest
			value3 = value3 + difference;
		}
	}

	//special case if any two variables are alike
	{
		if (value1 == value2)
		{
			value1 = value1 - .0001;
			value2 = value2 + .0001;
		}
		if (value1 == value3)
		{
			value3 = value3 - .0001;
			value1 = value1 + .0001;
		}
		if (value2 == value3)
		{
			value3 = value3 + .0001;
			value2 = value2 - .0001;
		}
	}

	//special case if any variables are 0 or below
	{
		if (value1 <= 0)
		{
			value1 = value1 + .0001;
		}
		if (value2 <= 0)
		{
			value2 = value2 + .0001;
		}
		if (value3 <= 0)
		{
			value3 = value3 + .0001;
		}
		double totalValue3 = value1 + value2 + value3;
		value1 = value1 / totalValue3;
		value2 = value2 / totalValue3;
		value3 = value3 / totalValue3;
	}

	array[0] = value1;
	array[1] = value2;
	array[2] = value3;
	return *array;
}

///<summary> takes 3 variables and trys to adjust towards 1
/// <para> double array[] = static 3 item array double value
/// </summary>
double adjustTo1Weber4(double array[])
{
	//char sBuffer6[400];

	double value1 = array[0];
	double value2 = array[1];
	double value3 = array[2];
	double value4 = array[3];

	
	/*sprintf(sBuffer6,"contrast = %f\n edges = %f\n saturation = %f\n luminosity = %f"
	                 ,value1,         value2,      value3,           value4);
	MessageBox(NULL,sBuffer6,"Values 1", MB_OK);*/

	double totalValue1 = value1 + value2 + value3 + value4;
	totalValue1 = min(1.0, max(totalValue1, .0000001));//clamp

	value1 = value1 / totalValue1;
	value2 = value2 / totalValue1;
	value3 = value3 / totalValue1;
	value4 = value4 / totalValue1;

	double totalValue2 = value1 + value2 + value3 + value4;
	totalValue2 = min(1.0, max(totalValue2, .0000001));//clamp

	//special case if slightly over 1.0
	if (totalValue2 > 1.0)
	{
		double difference = abs(totalValue2 - 1.0);

		//find which value is largest
		if ((value1 > value2) && (value1 > value3) && (value1 > value4))
		{
			//value1 is largest
			value1 = value1 - difference;
		}

		if ((value2 > value1) && (value2 > value3) && (value2 > value4))
		{
			//value2 is largest
			value2 = value2 - difference;
		}

		if ((value3 > value1) && (value3 > value2) && (value3 > value4))
		{
			//value3 is largest
			value3 = value3 - difference;
		}

		if ((value4 > value1) && (value4 > value2) && (value4 > value3))
		{
			//value4 is largest
			value4 = value4 - difference;
		}
	}

	//special case if slightly under 1.0
	if (totalValue2 < 1.0)
	{
		double difference = abs(totalValue2 - 1.0);

		//find which value is smallest
		if ((value1 < value2) && (value1 < value3) && (value1 < value4))
		{
			//value1 is smallest
			value1 = value1 + difference;
		}

		if ((value2 < value1) && (value2 < value3) && (value2 < value4))
		{
			//value2 is smallest
			value2 = value2 + difference;
		}

		if ((value3 < value1) && (value3 < value2) && (value3 < value4))
		{
			//value3 is smallest
			value3 = value3 + difference;
		}

		if ((value4 < value1) && (value4 < value2) && (value4 < value3))
		{
			//value3 is smallest
			value4 = value4 + difference;
		}
	}

	//special case if any two variables are alike
	{
		if (value1 == value2)
		{
			value1 = value1 - .0001;
			value2 = value2 + .0001;
		}
		if (value1 == value3)
		{
			value3 = value3 - .0001;
			value1 = value1 + .0001;
		}
		if (value1 == value4)
		{
			value4 = value4 - .0001;
			value1 = value1 + .0001;
		}
		if (value2 == value3)
		{
			value2 = value2 + .0001;
			value3 = value3 - .0001;
		}
		if (value2 == value4)
		{
			value2 = value2 + .0001;
			value3 = value3 - .0001;
		}
		if (value3 == value4)
		{
			value3 = value3 + .0001;
			value4 = value4 - .0001;
		}
	}

	//special case if any variables are 0 or below
	{
		if (value1 <= 0)
		{
			value1 = value1 + .0001;
		}
		if (value2 <= 0)
		{
			value2 = value2 + .0001;
		}
		if (value3 <= 0)
		{
			value3 = value3 + .0001;
		}
		if (value4 <= 0)
		{
			value4 = value4 + .0001;
		}

		//after all special cases accounted for, reevaulate the formula
		double totalValue3 = value1 + value2 + value3 + value4;
		totalValue3 = min(1.0, max(totalValue3, .0000001));//clamp

		value1 = value1 / totalValue3;
		value2 = value2 / totalValue3;
		value3 = value3 / totalValue3;
		value4 = value4 / totalValue3;
	}

	array[0] = value1;
	array[1] = value2;
	array[2] = value3;
	array[3] = value4;

	/*sprintf(sBuffer6,"contrast = %f\n edges = %f\n saturation = %f\n luminosity = %f"
	                 ,value1,         value2,      value3,           value4);
	MessageBox(NULL,sBuffer6,"Returned Values", MB_OK);*/

	return *array;
}


/// <summary> place our image in the 0-1 range, where 0 is darkest and 1 is lightest. 
/// <para>*imageArray = image array to be reduced.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float colorDepthReduce(float *imageArray, int imageWidth, int imageHeight, float colorDepth)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			//float colorDepth = 255.0f;

			float red = imageArray[nIdx + CHANNEL_R];
			float green = imageArray[nIdx + CHANNEL_G];
			float blue = imageArray[nIdx + CHANNEL_B];

			imageArray[nIdx + CHANNEL_R] = red / colorDepth;
			imageArray[nIdx + CHANNEL_G] = green / colorDepth;
			imageArray[nIdx + CHANNEL_B] = blue / colorDepth;
		}//end x
	}//end y

	return *imageArray;
}


/// <summary> place our image in the 0-255 range, where 0 is darkest and 255 is lightest, normal image display.
/// <para>*imageArray = image array to be expanded.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float colorDepthExpand(float *imageArray, int imageWidth, int imageHeight, float colorDepth)
{
	//place our image in a seperate array in the 0-255 range, where 0 is darkest and 255 is lightest
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
			{
				int nIdx = x * 4 + y * 4 * imageWidth;

				float red = imageArray[nIdx + CHANNEL_R];
				float green = imageArray[nIdx + CHANNEL_G];
				float blue = imageArray[nIdx + CHANNEL_B];

				imageArray[nIdx + CHANNEL_R] = (red * colorDepth);
				imageArray[nIdx + CHANNEL_G] = (green * colorDepth);
				imageArray[nIdx + CHANNEL_B] = (blue * colorDepth);
			}//end x
		}//end y

	return *imageArray;
}

//work in progress
float imageLevels(float *imageArray, int imageWidth, int imageHeight, float gamma)
{
/*
outPixel = (pow(((inPixel * 255.0) - inBlack) / (inWhite - inBlack),
                inGamma) * (outWhite - outBlack) + outBlack) / 255.0;*/

	float minRed = 1.0;
	float minGreen = 1.0;
	float minBlue = 1.0;
	float maxRed = 0.0;
	float maxGreen = 0.0;
	float maxBlue = 0.0;

	float midRed = 0;
	float midGreen = 0;
	float midBlue = 0;

	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			float red = imageArray[nIdx + CHANNEL_R];
			float green = imageArray[nIdx + CHANNEL_G];
			float blue = imageArray[nIdx + CHANNEL_B];

			if (red > maxRed) maxRed = red;
			if (red < minRed) minRed = red;
			if (green > maxGreen) maxGreen = green;
			if (green < minGreen) minGreen = green;
			if (blue > maxBlue) maxBlue = blue;
			if (blue < minBlue) minBlue = blue;

		}
	}

	midRed = (minRed + maxRed) / 2;
	midGreen = (minGreen + maxGreen) / 2;
	midBlue = (minBlue + maxBlue) / 2;


	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
			{
				int nIdx = x * 4 + y * 4 * imageWidth;

				float red = imageArray[nIdx + CHANNEL_R];
				float green = imageArray[nIdx + CHANNEL_G];
				float blue = imageArray[nIdx + CHANNEL_B];

				float red2 = (pow(((red * 1.0) - minRed) / (maxRed - minRed), gamma) * (1.0 - 0) + 0) / 1.0;
				float green2 = (pow(((green * 1.0) - minGreen) / (maxGreen - minGreen), gamma) * (1.0 - 0) + 0) / 1.0;
				float blue2 = (pow(((blue * 1.0) - minBlue) / (maxBlue - minBlue), gamma) * (1.0 - 0) + 0) / 1.0;

				//outPixel = (pow(((inPixel * 255.0) - inBlack) / (inWhite - inBlack), inGamma) * (outWhite - outBlack) + outBlack) / 255.0;


				imageArray[nIdx + CHANNEL_R] = (red2);
				imageArray[nIdx + CHANNEL_G] = (green2);
				imageArray[nIdx + CHANNEL_B] = (blue2);
			}//end x
		}//end y

	return *imageArray;
}

float normalizeImage(float *imageArray, int imageWidth, int imageHeight, float minData, float maxData)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
			{
				int nIdx = x * 4 + y * 4 * imageWidth;

				float red = imageArray[nIdx + CHANNEL_R];
				float green = imageArray[nIdx + CHANNEL_G];
				float blue = imageArray[nIdx + CHANNEL_B];

				red = red - minData / maxData - minData;
				green = green - minData / maxData - minData;
				blue = blue - minData / maxData - minData;


				imageArray[nIdx + CHANNEL_R] = (red);
				imageArray[nIdx + CHANNEL_G] = (green);
				imageArray[nIdx + CHANNEL_B] = (blue);
			}//end x
		}//end y

	return *imageArray;
}



/// <summary>Extract a single or all color channels.
/// <para>*imageArray = image array to be expanded.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// <para>channel = channel you wish to extract, if 0, all channels, if 1 the Red channel, if 2 the Green channel, if 3, the Blue Channel</para>
/// </summary>
float ChannelExtract(float *imageArray, int imageWidth, int imageHeight, int channel)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
			{
				int nIdx = x * 4 + y * 4 * imageWidth;

				float red = imageArray[nIdx + CHANNEL_R];
				float green = imageArray[nIdx + CHANNEL_G];
				float blue = imageArray[nIdx + CHANNEL_B];

				if (channel == 0)
				{
					imageArray[nIdx + CHANNEL_R] = red;
					imageArray[nIdx + CHANNEL_G] = green;
					imageArray[nIdx + CHANNEL_B] = blue;
				}

				if (channel == 1)
				{
					imageArray[nIdx + CHANNEL_R] = red;
					imageArray[nIdx + CHANNEL_G] = red;
					imageArray[nIdx + CHANNEL_B] = red;
				}

				if (channel == 2)
				{
					imageArray[nIdx + CHANNEL_R] = green;
					imageArray[nIdx + CHANNEL_G] = green;
					imageArray[nIdx + CHANNEL_B] = green;
				}

				if (channel == 3)
				{
					imageArray[nIdx + CHANNEL_R] = blue;
					imageArray[nIdx + CHANNEL_G] = blue;
					imageArray[nIdx + CHANNEL_B] = blue;
				}

			}//end x
		}//end y

	return *imageArray;
}


/// <summary> Convert RGB Color image to Rec709Luminance, outputs luminance only on all 3 channels
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float monochromeConversionRec709Luminance(float *imageArray, int imageWidth, int imageHeight)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double wR = 0.212656;
			double wG = 0.715158;
			double wB = 0.072186;
			// [0.212656, 0.715158, 0.072186]

			double red = imageArray[nIdx + CHANNEL_R];
			double green = imageArray[nIdx + CHANNEL_G];
			double blue = imageArray[nIdx + CHANNEL_B];

			double luma = (wR * red) + (wG * green) + (wB * blue);

			imageArray[nIdx + CHANNEL_R] = luma;
			imageArray[nIdx + CHANNEL_G] = luma;
			imageArray[nIdx + CHANNEL_B] = luma;
		}//end x
	}//end y

	return *imageArray;
}

///http://www.babelcolor.com/index_htm_files/A%20review%20of%20RGB%20color%20spaces.pdf
///Illuminant
/// <summary> Different Illuminant types
/// <para>array = reference white point (3 values) to be returned.</para>
/// <para>Array[0] = reference X </para>
/// <para>Array[0] = reference Y  </para>
/// <para>Array[0] = reference Z  </para>
/// <para>type = Illuminant type (use type 4 for standard Illuminant) </para>
/// <para> Type 0 = A 2° Tungsten or Incandescent Bulb 2856K </para>
/// <para> Type 1 = B 2° {obsolete} Direct sunlight at noon x = 99.090 z = 85.324</para>
/// <para> Type 2 = C 2° Average Daylight simulator Shade 6774K </para>
/// <para> Type 3 = D50 2° Horizon Light Illuminant 5003K </para>
/// <para> Type 4 = D55 2° Mid-Morning Daylight Illuminant 5500K </para>
/// <para> Type 5 = D65 2° Noon Daylight  6504K </para>
/// <para> Type 6 = D75 2° Overcast Daylight 7500K </para>
/// <para> Type 7 = E 2° 5400K x = 100 z = 100</para>
/// <para> Type 8 = D93 2° x = 97.135 z = 143.929</para>
/// <para> Type 9 = F2 2° Cool White Fluorescent 4230K </para>
/// <para> Type 10 = F7 2° Broad-Band Fluorescent 6500K </para>
/// <para> Type 11 = F11 2° Fluorescent Narrow Tri-Band 4000K </para>
/// <para> Type 12 TL4 = 2° x = 101.40 z = 65.90 https://support.hunterlab.com/hc/en-us/article_attachments/.../an07_96a.pdf </para>
/// <para> Type 13 UL3000 = 2° x = 107.99 z = 33.91 https://support.hunterlab.com/hc/en-us/article_attachments/.../an07_96a.pdf </para>
/// <para> Type 14 = A 10° Incandescent Bulb  2856K </para>
/// <para> Type 15 = C 10° Average Daylight simulator Shade </para>
/// <para> Type 16 = D50 10° Horizon Light Illuminant 5003K </para>
/// <para> Type 17 = D55 10° Mid-Morning Daylight Illuminant 5500K </para>
/// <para> Type 18 = D65 10° Noon Daylight  6504K </para>
/// <para> Type 19 = D75 10° Overcast Daylight 7500K </para>
/// <para> Type 20 = F2 10° Cool White Fluorescent 4230K </para>
/// <para> Type 21 = F7 10° Broad-Band Fluorescent 6500K </para>
/// <para> Type 22 = F11 10° Fluorescent Narrow Tri-Band 4000K </para>
/// <para> Type 23 TL4 = 10° x = 103.82 z = 66.90 https://support.hunterlab.com/hc/en-us/article_attachments/.../an07_96a.pdf </para>
/// <para> Type 24 UL3000 = 10° x = 111.12 z = 35.21 https://support.hunterlab.com/hc/en-us/article_attachments/.../an07_96a.pdf </para>
/// <para> Type ?? = 9300K 10° not measured</para>
/// </summary>
double Illuminant(double array[], int type)
{
	//reference white
	//if an invalid type is sent, default behavior should be D65 Illuminant/ 2° Observer
	double refX = 95.047;
	double refY = 100.000;
	double refZ = 108.883;

	if (type == 0)// Observer= 2°, Illuminant = A Incandescent Bulb 2856K
	{
		refX = 109.850; 
		refY = 100.000; 
		refZ = 35.585;
	}

	if (type == 1)//B Observer= 2°, Illuminant = B {obsolete} Direct sunlight at noon
	{
		refX = 99.090; 
		refY = 100.000; 
		refZ = 85.324;
	}

	if (type == 2)// Observer= 2°, Illuminant = C Average Daylight simulator Shade 6774K
	{
		refX = 98.074; 
		refY = 100.000; 
		refZ = 118.232;
	}

	if (type == 3)// Observer= 2°, Illuminant = D50 Horizon Light Illuminant 5003K
	{
		refX = 96.422; 
		refY = 100.000; 
		refZ = 82.521;
	}

	if (type == 4)// Observer= 2°, Illuminant = D55 Mid-Morning Daylight Illuminant 5500K
	{
		refX = 95.682; 
		refY = 100.000; 
		refZ = 92.149;
	}

	if (type == 5)// Observer= 2°, Illuminant = D65 Noon Daylight  6504K
	{
		refX = 95.047; 
		refY = 100.000; 
		refZ = 108.883;
	}

	if (type == 6)// Observer= 2°, Illuminant = D75 Overcast Daylight 7500K
	{
		refX = 94.972; 
		refY = 100.000; 
		refZ = 122.638;
	}

	if (type == 7)// Observer= 2°, Illuminant = E Equal Energy 5400K
	{
		refX = 100.000; 
		refY = 100.000; 
		refZ = 100.000;
	}

	if (type == 8)// Observer= 2°, Illuminant = 9300 Overcast Daylight 9300K
	{
		refX = 97.135; 
		refY = 100.000; 
		refZ = 143.929;
	}

	if (type == 9)// Observer= 2°, Illuminant = F2 Cool White Fluorescent 4230K
	{
		refX = 99.187; 
		refY = 100.000; 
		refZ = 67.395;
	}

	if (type == 10)// Observer= 2°, Illuminant = F7 Broad-Band Fluorescent 6500K
	{
		refX = 95.044; 
		refY = 100.000; 
		refZ = 108.755;
	}

	if (type == 11)// Observer= 2°, Illuminant = F11 Fluorescent Narrow Tri-Band 4000K
	{
		refX = 100.966; 
		refY = 100.000; 
		refZ = 64.370;
	}

	if (type == 12)// Observer= 2°, Illuminant = TL4
	{
		refX = 101.40; 
		refY = 100.000; 
		refZ = 65.90;
	}

	if (type == 13)// Observer= 2°, Illuminant = UL3000
	{
		refX = 100.966; 
		refY = 100.000; 
		refZ = 64.370;
	}

	if (type == 14)// Observer= 10°, Illuminant = A Incandescent Bulb  2856K
	{
		refX = 111.144; 
		refY = 100.000; 
		refZ = 35.200;
	}

	if (type == 15)// Observer= 10°, Illuminant = C Average Daylight simulator Shade 
	{
		refX = 97.285; 
		refY = 100.000; 
		refZ = 116.145;
	}

	if (type == 16)// Observer= 10°, Illuminant = D50 Horizon Light Illuminant 5003K
	{
		refX = 96.720; 
		refY = 100.000; 
		refZ = 81.427;
	}

	if (type == 17)// Observer= 10°, Illuminant = D55 Mid-Morning Daylight Illuminant 5500K
	{
		refX = 95.799; 
		refY = 100.000; 
		refZ = 90.926;
	}

	if (type == 18)// Observer= 10°, Illuminant = D65 Noon Daylight  6504K
	{
		refX = 94.811; 
		refY = 100.000; 
		refZ = 107.304;
	}

	if (type == 19)// Observer= 10°, Illuminant = D75 Overcast Daylight 7500K
	{
		refX = 94.416; 
		refY = 100.000; 
		refZ = 120.641;
	}

	if (type == 20)// Observer= 10°, Illuminant = F2 Cool White Fluorescent 4230K
	{
		refX = 103.280; 
		refY = 100.000; 
		refZ = 69.026;
	}

	if (type == 21)// Observer= 10°, Illuminant = F7 Broad-Band Fluorescent 6500K
	{
		refX = 95.792; 
		refY = 100.000; 
		refZ = 107.687;
	}

	if (type == 22)// Observer= 10°, Illuminant = F11 Fluorescent Narrow Tri-Band 4000K
	{
		refX = 103.866; 
		refY = 100.000;
		refZ = 65.627;
	}
	
	if (type == 23)// Observer= 10°, Illuminant = TL4
	{
		refX = 103.82; 
		refY = 100.000;
		refZ = 66.90;
	}

	if (type == 24)// Observer= 10°, Illuminant = UL3000
	{
		refX = 111.12; 
		refY = 100.000;
		refZ = 35.21;
	}




	array[0] = refX;
	array[1] = refY;
	array[2] = refZ;


	return *array;
}




/// <summary> Convert sRGB Color image to CIERGB by removing the gamma associated with sRGB
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float sRGBtoRGB(float *imageArray, int imageWidth, int imageHeight)
{
	//http://www.easyrgb.com/index.php?X=MATH&H=02#text2

	double rgamma;
	double ggamma;
	double bgamma;

	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double red = imageArray[nIdx + CHANNEL_R];
			double green = imageArray[nIdx + CHANNEL_G];
			double blue = imageArray[nIdx + CHANNEL_B];


			if ( red > 0.04045 )			
				rgamma = pow( ( ( red + 0.055 ) / 1.055 ) , 2.4);			
			else
				rgamma = red / 12.92;
			
			if ( green > 0.04045 )			
				ggamma = pow( ( ( green + 0.055 ) / 1.055 ) , 2.4);			
			else
				ggamma = green / 12.92;

			if ( blue > 0.04045 )			
				bgamma = pow( ( ( blue + 0.055 ) / 1.055 ) , 2.4);			
			else
				bgamma = blue / 12.92;

			//double rgamma = pow(red, 2.2);
			//double ggamma = pow(green, 2.2);
			//double bgamma = pow(blue, 2.2);

			imageArray[nIdx + CHANNEL_R] = rgamma;
			imageArray[nIdx + CHANNEL_G] = ggamma;
			imageArray[nIdx + CHANNEL_B] = bgamma;
		}
	}
	return *imageArray;
}

/// <summary> Convert CIERGB Color image to sRGB by adding back the gamma associated with sRGB
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float RGBtosRGB(float *imageArray, int imageWidth, int imageHeight)
{
	double rgamma;
	double ggamma;
	double bgamma;

	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double red = imageArray[nIdx + CHANNEL_R];
			double green = imageArray[nIdx + CHANNEL_G];
			double blue = imageArray[nIdx + CHANNEL_B];

			if ( red > 0.0031308 )			
				rgamma = 1.055 * pow(red, ( 1 / 2.4 ) ) - 0.055;			
			else
				rgamma = 12.92 * red;

			if ( green > 0.0031308 )			
				ggamma = 1.055 * pow(green, ( 1 / 2.4 ) ) - 0.055;			
			else
				ggamma = 12.92 * green;

			if ( blue > 0.0031308 )			
				bgamma = 1.055 * pow(blue, ( 1 / 2.4 ) ) - 0.055;			
			else
				bgamma = 12.92 * blue;

			//double rgamma = pow(red, 1 / 2.2);
			//double ggamma = pow(green, 1 / 2.2);
			//double bgamma = pow(blue, 1 / 2.2);

			imageArray[nIdx + CHANNEL_R] = rgamma;
			imageArray[nIdx + CHANNEL_G] = ggamma;
			imageArray[nIdx + CHANNEL_B] = bgamma;
		}
	}
	return *imageArray;
}


/// <summary> Convert CIERGB Color image to HSL
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float RGBtoHSL(float *imageArray, int imageWidth, int imageHeight)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double red = imageArray[nIdx + CHANNEL_R];
			double green = imageArray[nIdx + CHANNEL_G];
			double blue = imageArray[nIdx + CHANNEL_B];

			//var_Min = min( var_R, var_G, var_B ) 
			double var_Min1 = min(red, green);//Min. value of RGB
			double var_Min = min(var_Min1,blue);

			//var_Max = max( var_R, var_G, var_B )    //Max. value of RGB
			double var_Max1 = max(red, green);//Min. value of RGB
			double var_Max = max(var_Max1,blue);

			//del_Max = var_Max - var_Min             //Delta RGB value
			double del_Max = var_Max - var_Min;

			double hslH = 0.0;
			double hslS = 0.0;
			//L = ( var_Max + var_Min ) / 2
			double hslL = ( var_Max + var_Min ) / 2.0;

			if ( del_Max == 0)                     //This is a gray, no chroma...
			{
				hslH = 0.0;                               //HSL results from 0 to 1
				hslS = 0.0;
			}
			else                                    //Chromatic data...
			{
				if ( hslL < 0.5 ) 
				{
					// S = del_Max / ( var_Max + var_Min )
					hslS = del_Max / ( var_Max + var_Min );
				}
				else           
				{
					// S = del_Max / ( 2 - var_Max - var_Min )
					hslS = del_Max / ( 2.0 - var_Max - var_Min );
				}

				//       del_R = ( ( ( var_Max - var_R ) / 6 ) + ( del_Max / 2   ) ) / del_Max
				double del_red = ( ( ( var_Max - red ) / 6.0 ) + ( del_Max / 2.0 ) ) / del_Max;
				//         del_G = ( ( ( var_Max - var_G ) / 6   ) + ( del_Max / 2   ) ) / del_Max
				double del_green = ( ( ( var_Max - green ) / 6.0 ) + ( del_Max / 2.0 ) ) / del_Max;
				//        del_B = ( ( ( var_Max - var_B ) / 6  ) + ( del_Max / 2   ) ) / del_Max
				double del_blue = ( ( ( var_Max - blue ) / 6.0 ) + ( del_Max / 2.0 ) ) / del_Max;

				if ( red == var_Max ) 
				{
					hslH = del_blue - del_green;
				}

				else if ( green == var_Max ) 
				{
					hslH = ( 1.0 / 3.0 ) + del_red - del_blue;
				}
				else if ( blue == var_Max ) 
				{
					hslH = ( 2.0 / 3.0 ) + del_green - del_red;
				}

				if ( hslH < 0 )
				{
					hslH += 1;
				}
				if ( hslH > 1 ) 
				{
					hslH -= 1;
				}
			}

			imageArray[nIdx + CHANNEL_R] = hslH;
			imageArray[nIdx + CHANNEL_G] = hslS;
			imageArray[nIdx + CHANNEL_B] = hslL;
		}//end x
	}//end y
	return *imageArray;
}


/// <summary> Subroutine for HSL to convert Hue to RGB
/// <para>value1 = .</para>
/// <para>value2 =</para>
/// <para>vHue = </para>
/// </summary>
double Hue_2_RGB(double value1, double value2, double vHue)
{
	if ( vHue < 0.0 ) 
	{
		vHue += 1;
	}

   if ( vHue > 1.0 ) 
   {
	   vHue -= 1;
   }

   if ( ( 6.0 * vHue ) < 1.0 ) 
   {
	   return ( value1 + ( value2 - value1 ) * 6.0 * vHue );
   }
   
   if ( ( 2.0 * vHue ) < 1.0 ) 
   {
	   return ( value2 );
   }

   if ( ( 3.0 * vHue ) < 2.0 ) 
   {
	   return ( value1 + ( value2 - value1 ) * ( ( 2.0 / 3.0 ) - vHue ) * 6.0 );
   }

   return ( value1 );
}


/// <summary> Convert HSL Color image to CIERGB
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float HSLtoRGB(float *imageArray, int imageWidth, int imageHeight)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double hslH = imageArray[nIdx + CHANNEL_R];
			double hslS = imageArray[nIdx + CHANNEL_G];
			double hslL = imageArray[nIdx + CHANNEL_B];

			double red = 0.0;
			double green = 0.0;
			double blue = 0.0;

			double var_1 = 0.0;
			double var_2 = 0.0;

			if ( hslS == 0)                       //HSL from 0 to 1
			{
				red = hslL;                      //RGB results from 0 to 255
				green = hslL;
				blue = hslL;
			}
			else
			{
				if ( hslL < 0.5 )
				{
					var_2 = hslL * ( 1.0 + hslS );
				}
				else
				{
					var_2 = ( hslL + hslS ) - ( hslS * hslL );
				}

				var_1 = 2.0 * hslL - var_2;

				red = Hue_2_RGB( var_1, var_2, hslH + ( 1.0 / 3.0 ) );
				green = Hue_2_RGB( var_1, var_2, hslH );
				blue = Hue_2_RGB( var_1, var_2, hslH - ( 1.0 / 3.0 ) );
			}

			imageArray[nIdx + CHANNEL_R] = red;
			imageArray[nIdx + CHANNEL_G] = green;
			imageArray[nIdx + CHANNEL_B] = blue;
		}//end x
	}//end y
	return *imageArray;
}




float RGBtoHSV(float *imageArray, int imageWidth, int imageHeight)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double red = imageArray[nIdx + CHANNEL_R];
			double green = imageArray[nIdx + CHANNEL_G];
			double blue = imageArray[nIdx + CHANNEL_B];

			//double var_Min = min( var_R, var_G, var_B )    //Min. value of RGB
			double var_Min1 = min(red, green);//Min. value of RGB
			double var_Min = min(var_Min1,blue);

			//var_Max = max( var_R, var_G, var_B )    //Max. value of RGB
			double var_Max1 = max(red, green);//Min. value of RGB
			double var_Max = max(var_Max1,blue);

			double del_Max = var_Max - var_Min;             //Delta RGB value 

			double hsvH = 0;
			double hsvS = 0;
			double hsvV = var_Max;
			

			if ( del_Max == 0 )                     //This is a gray, no chroma...
			{
				hsvH = 0;                                //HSV results from 0 to 1
				hsvS = 0;
			}
			else                                    //Chromatic data...
			{
				hsvS = del_Max / var_Max;
			}

			double del_R = ( ( ( var_Max - red ) / 6.0 ) + ( del_Max / 2.0 ) ) / del_Max;
			double del_G = ( ( ( var_Max - green ) / 6.0 ) + ( del_Max / 2.0 ) ) / del_Max;
			double del_B = ( ( ( var_Max - blue ) / 6.0 ) + ( del_Max / 2.0 ) ) / del_Max;

			if ( red == var_Max )
			{
				hsvH = del_B - del_G;
			}

			else if ( green == var_Max ) 
			{
				hsvH = ( 1.0 / 3.0 ) + del_R - del_B;
			}

			else if ( blue == var_Max ) 
			{
				hsvH = ( 2.0 / 3.0 ) + del_G - del_R;
			}

			if (hsvH < 0.0) 
			{
				hsvH += 1;
			}

			if ( hsvH > 1.0 ) 
			{
				hsvH -= 1;
			}
		

			imageArray[nIdx + CHANNEL_R] = hsvH;
			imageArray[nIdx + CHANNEL_G] = hsvS;
			imageArray[nIdx + CHANNEL_B] = hsvV;
		}//end x
	}//end y
	return *imageArray;
}


float HSVtoRGB(float *imageArray, int imageWidth, int imageHeight)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double hsvH = imageArray[nIdx + CHANNEL_R];
			double hsvS = imageArray[nIdx + CHANNEL_G];
			double hsvV = imageArray[nIdx + CHANNEL_B];

			double red = 0;
			double green = 0;
			double blue = 0;

			double var_h = 0;
			double var_i = 0;
			double var_1 = 0;
			double var_2 = 0;
			double var_3 = 0;

			if ( hsvS == 0 )                       //HSV from 0 to 1
			{
				red = hsvV;
				green = hsvV;
				blue = hsvV;
			}
			else
			{
				var_h = hsvH * 6.0;

				if ( var_h == 6.0 ) 
				{
					var_h = 0.0;      //H must be < 1
				}

				var_i = floor( var_h );             //Or ... var_i = floor( var_h )

				var_1 = hsvV * ( 1.0 - hsvS );
				var_2 = hsvV * ( 1.0 - hsvS * ( var_h - var_i ) );
				var_3 = hsvV * ( 1.0 - hsvS * ( 1.0 - ( var_h - var_i ) ) );

				if( var_i == 0) 
				{ 
					red = hsvV; 
					green = var_3;
					blue = var_1;
				}

				else if ( var_i == 1) 
				{ 
					red = var_2; 
					green = hsvV; 
					blue = var_1;
				}

				else if ( var_i == 2) 
				{ 
					red = var_1; 
					green = hsvV; 
					blue = var_3;
				}

				else if ( var_i == 3) 
				{
					red = var_1;
					green = var_2;
					blue = hsvV;
				}

				else if ( var_i == 4) 
				{
					red = var_3; 
					green = var_1 ; 
					blue = hsvV;     
				}

				else
				{
					red = hsvV; 
					green = var_1; 
					blue = var_2;
				}
			}

			imageArray[nIdx + CHANNEL_R] = red;
			imageArray[nIdx + CHANNEL_G] = green;
			imageArray[nIdx + CHANNEL_B] = blue;
		}//end x
	}//end y
	return *imageArray;
}




/// <summary> Convert CIERGB Color image to CIEXYZ
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float RGBtoCIEXYZ(float *imageArray, int imageWidth, int imageHeight)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double red = imageArray[nIdx + CHANNEL_R];
			double green = imageArray[nIdx + CHANNEL_G];
			double blue = imageArray[nIdx + CHANNEL_B];

			double var_R = red * 100;
			double var_G = green * 100;
			double var_B = blue * 100;

			//Observer. = 2°, Illuminant = D65
			double xyzX = var_R * 0.4124 + var_G * 0.3576 + var_B * 0.1805;
			double xyzY = var_R * 0.2126 + var_G * 0.7152 + var_B * 0.0722;
			double xyzZ = var_R * 0.0193 + var_G * 0.1192 + var_B * 0.9505;

			imageArray[nIdx + CHANNEL_R] = xyzX;
			imageArray[nIdx + CHANNEL_G] = xyzY;
			imageArray[nIdx + CHANNEL_B] = xyzZ;
		}//end x
	}//end y
	return *imageArray;
}

/// <summary> Convert CIEXYZ Color image to CIERGB
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float CIEXYZtoRGB(float *imageArray, int imageWidth, int imageHeight)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double xyzX = imageArray[nIdx + CHANNEL_R];
			double xyzY = imageArray[nIdx + CHANNEL_G];
			double xyzZ = imageArray[nIdx + CHANNEL_B];

			double var_X = xyzX / 100;
			double var_Y = xyzY / 100;
			double var_Z = xyzZ / 100;

			//Observer. = 2°, Illuminant = D65
			double red = var_X *  3.2406 + var_Y * -1.5372 + var_Z * -0.4986;
			double green = var_X * -0.9689 + var_Y *  1.8758 + var_Z *  0.0415;
			double blue = var_X *  0.0557 + var_Y * -0.2040 + var_Z *  1.0570;

			imageArray[nIdx + CHANNEL_R] = red;
			imageArray[nIdx + CHANNEL_G] = green;
			imageArray[nIdx + CHANNEL_B] = blue;
		}//end x
	}//end y
	return *imageArray;
}

/// <summary> Convert CIEXYZ Color image to CIEYXY
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float CIEXYZtoCIEYXY(float *imageArray, int imageWidth, int imageHeight)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double xyzX = imageArray[nIdx + CHANNEL_R];
			double xyzY = imageArray[nIdx + CHANNEL_G];
			double xyzZ = imageArray[nIdx + CHANNEL_B];

			double yxyY = xyzY;
			double yxyX = xyzX / (xyzX + xyzY + xyzZ);
			double yxyYY = xyzY / (xyzX + xyzY + xyzZ);

			imageArray[nIdx + CHANNEL_R] = yxyY;
			imageArray[nIdx + CHANNEL_G] = yxyX;
			imageArray[nIdx + CHANNEL_B] = yxyYY;
		}//end x
	}//end y
	return *imageArray;
}

/// <summary> Convert CIEYXY Color image to CIEXYZ
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float CIEYXYtoCIEXYZ(float *imageArray, int imageWidth, int imageHeight)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double yxyY = imageArray[nIdx + CHANNEL_R];
			double yxyX = imageArray[nIdx + CHANNEL_G];
			double yxyYY = imageArray[nIdx + CHANNEL_B];

			double xyzX = yxyX * (yxyY / yxyYY);
			double xyzY = yxyY;
			double xyzZ = ( 1 - yxyX - yxyYY ) * ( yxyY / yxyYY );

			imageArray[nIdx + CHANNEL_R] = xyzX;
			imageArray[nIdx + CHANNEL_G] = xyzY;
			imageArray[nIdx + CHANNEL_B] = xyzZ;
		}//end x
	}//end y
	return *imageArray;
}




/// <summary> Convert CIEXYZ Color image to CIELAB
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// <para>illuminantType = Illuminant type (use type 4 for standard Illuminant) </para>
/// <para> Type 0 = A 2° Incandescent Bulb 2856K </para>
/// <para> Type 1 = C 2° Average Daylight simulator Shade 6774K </para>
/// <para> Type 2 = D50 2° Horizon Light Illuminant 5003K </para>
/// <para> Type 3 = D55 2° Mid-Morning Daylight Illuminant 5500K </para>
/// <para> Type 4 = D65 2° Noon Daylight  6504K </para>
/// <para> Type 5 = D75 2° Overcast Daylight 7500K </para>
/// <para> Type 6 = F2 2° Cool White Fluorescent 4230K </para>
/// <para> Type 7 = F7 2° Broad-Band Fluorescent 6500K </para>
/// <para> Type 8 = F11 2° Fluorescent Narrow Tri-Band 4000K </para>
/// <para> Type 9 = A 10° Incandescent Bulb  2856K </para>
/// <para> Type 10 = C 10° Average Daylight simulator Shade </para>
/// <para> Type 11 = D50 10° Horizon Light Illuminant 5003K </para>
/// <para> Type 12 = D55 10° Mid-Morning Daylight Illuminant 5500K </para>
/// <para> Type 13 = D65 10° Noon Daylight  6504K </para>
/// <para> Type 14 = D75 10° Overcast Daylight 7500K </para>
/// <para> Type 15 = F2 10° Cool White Fluorescent 4230K </para>
/// <para> Type 16 = F7 10° Broad-Band Fluorescent 6500K </para>
/// <para> Type 17 = F11 10° Fluorescent Narrow Tri-Band 4000K </para>
/// </summary>
float CIEXYZtoCIELAB(float *imageArray, int imageWidth, int imageHeight, int illuminantType)
{
	//char sBuffer6[400];
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double var_X = 0;
			double var_Y = 0;
			double var_Z = 0;

			double array[3];//used to return 3 values for reference white

			double xyzX = imageArray[nIdx + CHANNEL_R];
			double xyzY = imageArray[nIdx + CHANNEL_G];
			double xyzZ = imageArray[nIdx + CHANNEL_B];


			Illuminant(array, illuminantType);

			double refX = array[0];
			double refY = array[1]; 
			double refZ = array[2];


			/*sprintf(sBuffer6,"refX = %f\n\n refY = %f\n\n refZ = %f\n"
	                         ,refX,         refY,         refZ);
			MessageBox(NULL,sBuffer6,"Illuminant", MB_OK);*/

			//reference white
			//double refX = 95.047; // Observer= 2°, Illuminant= D65
			//double refY = 100.000; 
			//double refZ = 108.883;

			//adjust LAB to reference white
			double var_X1 = xyzX / refX;
			double var_Y1 = xyzY / refY;
			double var_Z1 = xyzZ / refZ;

			//LAB Conversion
			if (var_X1 > 0.008856f) 
			{
				var_X = powf(var_X1 , 1.0f/3.0f); 
			}
			else 
			{
				var_X = (7.787f * var_X1) + (16.0f/116.0f);
			}

			if (var_Y1 > 0.008856f) 
			{ 
				var_Y = powf(var_Y1 , 1.0f/3.0f); 
			}
			else 
			{ 
				var_Y = (7.787f * var_Y1) + (16.0f/116.0f);
			}

			if (var_Z1 > 0.008856f) 
			{
				var_Z = powf(var_Z1 , 1.0f/3.0f); 
			}
			else 
			{ 
				var_Z = (7.787f * var_Z1) + (16.0f/116.0f);
			}

			//adjust LAB scale
			double cieL1 = (116.0f * var_Y) - 16.0f;
			double cieA1 = 500.0f * (var_X - var_Y);
			double cieB1 = 200.0f * (var_Y - var_Z);

			//place LAB image in array
			imageArray[nIdx + CHANNEL_R] = cieL1;
			imageArray[nIdx + CHANNEL_G] = cieA1;
			imageArray[nIdx + CHANNEL_B] = cieB1;
		}//end x
	}//end y
	return *imageArray;
}

/// <summary> Convert CIELAB Color image to CIEXYZ
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// <para>illuminantType = Illuminant type (use type 4 for standard Illuminant) </para>
/// <para> Type 0 = A 2° Incandescent Bulb 2856K </para>
/// <para> Type 1 = C 2° Average Daylight simulator Shade 6774K </para>
/// <para> Type 2 = D50 2° Horizon Light Illuminant 5003K </para>
/// <para> Type 3 = D55 2° Mid-Morning Daylight Illuminant 5500K </para>
/// <para> Type 4 = D65 2° Noon Daylight  6504K </para>
/// <para> Type 5 = D75 2° Overcast Daylight 7500K </para>
/// <para> Type 6 = F2 2° Cool White Fluorescent 4230K </para>
/// <para> Type 7 = F7 2° Broad-Band Fluorescent 6500K </para>
/// <para> Type 8 = F11 2° Fluorescent Narrow Tri-Band 4000K </para>
/// <para> Type 9 = A 10° Incandescent Bulb  2856K </para>
/// <para> Type 10 = C 10° Average Daylight simulator Shade </para>
/// <para> Type 11 = D50 10° Horizon Light Illuminant 5003K </para>
/// <para> Type 12 = D55 10° Mid-Morning Daylight Illuminant 5500K </para>
/// <para> Type 13 = D65 10° Noon Daylight  6504K </para>
/// <para> Type 14 = D75 10° Overcast Daylight 7500K </para>
/// <para> Type 15 = F2 10° Cool White Fluorescent 4230K </para>
/// <para> Type 16 = F7 10° Broad-Band Fluorescent 6500K </para>
/// <para> Type 17 = F11 10° Fluorescent Narrow Tri-Band 4000K </para>
/// </summary>
float CIELABToXYZ(float *imageArray, int imageWidth, int imageHeight, int illuminantType)//CIE LAB
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double array[3];

			double cieL = imageArray [nIdx + CHANNEL_R];
			double cieA = imageArray [nIdx + CHANNEL_G];
			double cieB = imageArray [nIdx + CHANNEL_B];

			double var_Y = (cieL + 16.0) / 116.0;
			double var_X = cieA / 500.0 + var_Y;
			double var_Z = var_Y - cieB / 200.0;

			if (pow(var_Y, 3.0) > 0.008856)
			{ 
				var_Y = pow(var_Y, 3.0); 
			}
			else 
			{ 
				var_Y = (var_Y - 16.0 / 116.0) / 7.787; 
			}
			if (pow(var_X , 3.0) > 0.008856) 
			{ 
				var_X = pow(var_X, 3.0); 
			}
			else 
			{ 
				var_X = (var_X - 16.0 / 116.0) / 7.787; 
			}
			if (pow(var_Z, 3.0) > 0.008856 ) 
			{
				var_Z = pow(var_Z, 3.0); 
			}
			else 
			{
				var_Z = (var_Z - 16.0 / 116.0 ) / 7.787; 
			}

			Illuminant(array, illuminantType);

			double refX = array[0];
			double refY = array[1]; 
			double refZ = array[2];

			//reference white
			//double refX = 95.047; // Observer= 2°, Illuminant= D65
			//double refY = 100.000; 
			//double refZ = 108.883;

			double cieX = refX * var_X;
			double cieY = refY * var_Y;
			double cieZ = refZ * var_Z;

			imageArray[nIdx + CHANNEL_R] = cieX;
			imageArray[nIdx + CHANNEL_G] = cieY;
			imageArray[nIdx + CHANNEL_B] = cieZ;	
		}
	}
	return *imageArray;
}

/// <summary> Convert CIEXYZ Color image to Hunter LAB
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float CIEXYZtoHunterLAB(float *imageArray, int imageWidth, int imageHeight)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double xyzX = imageArray[nIdx + CHANNEL_R];
			double xyzY = imageArray[nIdx + CHANNEL_G];
			double xyzZ = imageArray[nIdx + CHANNEL_B];

			//(H)L = 10 * sqrt( Y )
			//(H)a = 17.5 * ( ( ( 1.02 * X ) - Y ) / sqrt( Y ) )
			//(H)b = 7 * ( ( Y - ( 0.847 * Z ) ) / sqrt( Y ) )

			//adjust LAB scale
			double hunterL = 10 * sqrt(xyzY);
			double hunterA = 17.5 * ( ( ( 1.02 * xyzX ) - xyzY ) / sqrt( xyzY ) );
			double hunterB = 7 * ( ( xyzY - ( 0.847 * xyzZ ) ) / sqrt( xyzY ) );

			//place LAB image in array
			imageArray[nIdx + CHANNEL_R] = hunterL;
			imageArray[nIdx + CHANNEL_G] = hunterA;
			imageArray[nIdx + CHANNEL_B] = hunterB;
		}//end x
	}//end y
	return *imageArray;
}


/// <summary> Convert Hunter LAB Color image to CIEXYZ
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float HunterLABtoCIEXYZ(float *imageArray, int imageWidth, int imageHeight)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double hunterL = imageArray[nIdx + CHANNEL_R];
			double hunterA = imageArray[nIdx + CHANNEL_G];
			double hunterB = imageArray[nIdx + CHANNEL_B];

			double varY = hunterL / 10;
			double varX = hunterA / 17.5 * hunterL / 10;
			double varZ = hunterB / 7 * hunterL / 10;
			//var_Y = (H)L / 10
			//var_X = (H)a / 17.5 * (H)L / 10
			//var_Z = (H)b / 7 * (H)L / 10

			//Y = var_Y ^ 2
			//X = ( var_X + Y ) / 1.02
			//Z = -( var_Z - Y ) / 0.847

			//adjust LAB scale
			double cieY = pow(varY , 2);
			double cieX = ( varX + cieY ) / 1.02;
			double cieZ = -( varZ - cieY ) / 0.847;

			//place LAB image in array
			imageArray[nIdx + CHANNEL_R] = cieX;
			imageArray[nIdx + CHANNEL_G] = cieY;
			imageArray[nIdx + CHANNEL_B] = cieZ;
		}//end x
	}//end y
	return *imageArray;
}



/// <summary> Convert CIELAB Color image to CIELCH
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float CIELABToCIELCH(float *imageArray, int imageWidth, int imageHeight)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double cieL = imageArray [nIdx + CHANNEL_R];
			double cieA = imageArray [nIdx + CHANNEL_G];
			double cieB = imageArray [nIdx + CHANNEL_B];

			double cieH = atan2(cieB,cieA);

			if ( cieH > 0 ) 
				cieH = ( cieH / PI ) * 180;
			else
				cieH = 360 - ( abs( cieH ) / PI ) * 180;

			double cieC = sqrt(pow(cieA,2) + pow(cieB , 2) );

			/*
			var_H = arc_tangent( CIE-b*, CIE-a* );  //Quadrant by signs

			if ( var_H > 0 ) 
				var_H = ( var_H / PI ) * 180;
			else
				var_H = 360 - ( abs( var_H ) / PI ) * 180;

			CIE-L* = CIE-L*;
			CIE-C* = sqrt( CIE-a* ^ 2 + CIE-b* ^ 2 );
			CIE-H° = var_H;
			*/

			imageArray[nIdx + CHANNEL_R] = cieL;
			imageArray[nIdx + CHANNEL_G] = cieC;
			imageArray[nIdx + CHANNEL_B] = cieH;	
		}
	}
	return *imageArray;
}



/// <summary> Convert CIELCH Color image to CIELAB
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float CIELCHToCIELAB(float *imageArray, int imageWidth, int imageHeight)
{
	#define degree2radian(a) (a * 0.017453292519)

	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double cieL = imageArray [nIdx + CHANNEL_R];
			double cieC = imageArray [nIdx + CHANNEL_G];
			double cieH = imageArray [nIdx + CHANNEL_B];

			/*
			//CIE-H° from 0 to 360°

			CIE-L* = CIE-L*;
			CIE-a* = cos( degree_2_radian( CIE-H° ) ) * CIE-C*;
			CIE-b* = sin( degree_2_radian( CIE-H° ) ) * CIE-C*;
			*/
			double cieA = cos( degree2radian( cieH ) ) * cieC;
			double cieB = sin( degree2radian( cieH ) ) * cieC;

			imageArray[nIdx + CHANNEL_R] = cieL;
			imageArray[nIdx + CHANNEL_G] = cieA;
			imageArray[nIdx + CHANNEL_B] = cieB;	
		}
	}
#undef degree2radian

	return *imageArray;
}


/// <summary> Convert CIEXYZ Color image to CIELUV
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// <para>illuminantType = Illuminant type (use type 4 for standard Illuminant) </para>
/// <para> Type 0 = A 2° Incandescent Bulb 2856K </para>
/// <para> Type 1 = C 2° Average Daylight simulator Shade 6774K </para>
/// <para> Type 2 = D50 2° Horizon Light Illuminant 5003K </para>
/// <para> Type 3 = D55 2° Mid-Morning Daylight Illuminant 5500K </para>
/// <para> Type 4 = D65 2° Noon Daylight  6504K </para>
/// <para> Type 5 = D75 2° Overcast Daylight 7500K </para>
/// <para> Type 6 = F2 2° Cool White Fluorescent 4230K </para>
/// <para> Type 7 = F7 2° Broad-Band Fluorescent 6500K </para>
/// <para> Type 8 = F11 2° Fluorescent Narrow Tri-Band 4000K </para>
/// <para> Type 9 = A 10° Incandescent Bulb  2856K </para>
/// <para> Type 10 = C 10° Average Daylight simulator Shade </para>
/// <para> Type 11 = D50 10° Horizon Light Illuminant 5003K </para>
/// <para> Type 12 = D55 10° Mid-Morning Daylight Illuminant 5500K </para>
/// <para> Type 13 = D65 10° Noon Daylight  6504K </para>
/// <para> Type 14 = D75 10° Overcast Daylight 7500K </para>
/// <para> Type 15 = F2 10° Cool White Fluorescent 4230K </para>
/// <para> Type 16 = F7 10° Broad-Band Fluorescent 6500K </para>
/// <para> Type 17 = F11 10° Fluorescent Narrow Tri-Band 4000K </para>
/// </summary>
float CIEXYZtoCIELUV(float *imageArray, int imageWidth, int imageHeight, int illuminantType)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double xyzX = imageArray[nIdx + CHANNEL_R];
			double xyzY = imageArray[nIdx + CHANNEL_G];
			double xyzZ = imageArray[nIdx + CHANNEL_B];

			double var_U = ( 4.0 * xyzX ) / ( xyzX + ( 15.0 * xyzY ) + ( 3.0 * xyzZ ) );
			double var_V = ( 9.0 * xyzY ) / ( xyzX + ( 15.0 * xyzY ) + ( 3.0 * xyzZ ) );

			double var_Y = xyzY / 100.0;

			if (var_Y > 0.008856) 
				var_Y = pow(var_Y,( 1.0/3.0 ));
			else
				var_Y = ( 7.787 * var_Y ) + ( 16.0 / 116.0 );

			double array[3];//used to return 3 values for reference white
			Illuminant(array, illuminantType);
			double refX = array[0];
			double refY = array[1]; 
			double refZ = array[2];

			double ref_U = ( 4.0 * refX ) / ( refX + ( 15.0 * refY ) + ( 3.0 * refZ ) );
			double ref_V = ( 9.0 * refY ) / ( refX + ( 15.0 * refY ) + ( 3.0 * refZ ) );


			
			//CIE-u* = 13 * CIE-L* * ( var_U - ref_U );
			//CIE-v* = 13 * CIE-L* * ( var_V - ref_V );


			//adjust LAB scale
			double cieL1 = (116.0f * var_Y) - 16.0f;
			double cieU1 = 13.0 * cieL1 * (var_U - ref_U);
			double cieV1 = 13.0 * cieL1 * (var_V - ref_V);

			//place LAB image in array
			imageArray[nIdx + CHANNEL_R] = cieL1;
			imageArray[nIdx + CHANNEL_G] = cieU1;
			imageArray[nIdx + CHANNEL_B] = cieV1;
		}//end x
	}//end y
	return *imageArray;
}


/// <summary> Convert CIEXYZ Color image to CIELUV
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// <para>illuminantType = Illuminant type (use type 4 for standard Illuminant) </para>
/// <para> Type 0 = A 2° Incandescent Bulb 2856K </para>
/// <para> Type 1 = C 2° Average Daylight simulator Shade 6774K </para>
/// <para> Type 2 = D50 2° Horizon Light Illuminant 5003K </para>
/// <para> Type 3 = D55 2° Mid-Morning Daylight Illuminant 5500K </para>
/// <para> Type 4 = D65 2° Noon Daylight  6504K </para>
/// <para> Type 5 = D75 2° Overcast Daylight 7500K </para>
/// <para> Type 6 = F2 2° Cool White Fluorescent 4230K </para>
/// <para> Type 7 = F7 2° Broad-Band Fluorescent 6500K </para>
/// <para> Type 8 = F11 2° Fluorescent Narrow Tri-Band 4000K </para>
/// <para> Type 9 = A 10° Incandescent Bulb  2856K </para>
/// <para> Type 10 = C 10° Average Daylight simulator Shade 6774K</para>
/// <para> Type 11 = D50 10° Horizon Light Illuminant 5003K </para>
/// <para> Type 12 = D55 10° Mid-Morning Daylight Illuminant 5500K </para>
/// <para> Type 13 = D65 10° Noon Daylight  6504K </para>
/// <para> Type 14 = D75 10° Overcast Daylight 7500K </para>
/// <para> Type 15 = F2 10° Cool White Fluorescent 4230K </para>
/// <para> Type 16 = F7 10° Broad-Band Fluorescent 6500K </para>
/// <para> Type 17 = F11 10° Fluorescent Narrow Tri-Band 4000K </para>
/// </summary>
float CIELUVtoCIEXYZ(float *imageArray, int imageWidth, int imageHeight, int illuminantType)
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double cieL = imageArray[nIdx + CHANNEL_R];
			double cieU = imageArray[nIdx + CHANNEL_G];
			double cieV = imageArray[nIdx + CHANNEL_B];

			double var_Y = ( cieL + 16.0 ) / 116.0;

			if ( pow(var_Y,3.0) > 0.008856 ) 
				var_Y = pow(var_Y,3.0);
			else
				var_Y = ( var_Y - 16.0 / 116.0 ) / 7.787;

			double array[3];//used to return 3 values for reference white
			Illuminant(array, illuminantType);
			double refX = array[0];
			double refY = array[1]; 
			double refZ = array[2];


			double ref_U = ( 4.0 * refX ) / ( refX + ( 15.0 * refY ) + ( 3.0 * refZ ) );
			double ref_V = ( 9.0 * refY ) / ( refX + ( 15.0 * refY ) + ( 3.0 * refZ ) );

			double var_U = cieU / ( 13.0 * cieL ) + ref_U;
			double var_V = cieV / ( 13.0 * cieL ) + ref_V;

			double cieY = var_Y * 100;
			double cieX =  - ( 9 * cieY * var_U ) / ( ( var_U - 4 ) * var_V  - var_U * var_V );
			double cieZ = ( 9 * cieY - ( 15 * var_V * cieY ) - ( var_V * cieX ) ) / ( 3 * var_V );

			//place LAB image in array
			imageArray[nIdx + CHANNEL_R] = cieX;
			imageArray[nIdx + CHANNEL_G] = cieY;
			imageArray[nIdx + CHANNEL_B] = cieZ;
		}//end x
	}//end y
	return *imageArray;
}




/// <summary> Convert RGB Color image to the YCbCr Color space, Red Channel = Y, Green = Cb, Blue = Cr
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float RGBToYCBCR(float *imageArray, int imageWidth, int imageHeight)//ycbcr
{
	for (int x = 0; x< imageWidth; x++)
	{
		for (int y = 0; y< imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double red = imageArray[nIdx + CHANNEL_R];
			double green = imageArray[nIdx + CHANNEL_G];
			double blue = imageArray[nIdx + CHANNEL_B];

			//first we will convert the RGB image to XYZ
			double ycbcrY = (0.299f * red) + (0.587f * green) + (0.114f * blue);
			double ycbcrB = (-0.16874f * red) + (-0.33126f * green) + (0.50000f * blue);
			double ycbcrR = (0.50000f * red) + (-0.41869f * green) + (-0.08131f * blue);

			imageArray[nIdx + CHANNEL_R] = ycbcrY;
			imageArray[nIdx + CHANNEL_G] = ycbcrB;
			imageArray[nIdx + CHANNEL_B] = ycbcrR;
		}
	}
	return *imageArray;
}


/// <summary> Convert YCbCr Color image to the RGB Color space, Red Channel = Y, Green = Cb, Blue = Cr
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float YCBCRToRGB(float *imageArray, int imageWidth, int imageHeight)
#pragma region   //use ycbcr
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double red = imageArray [nIdx + CHANNEL_R];
			double green = imageArray [nIdx + CHANNEL_G];
			double blue = imageArray [nIdx + CHANNEL_B];

			double rgbR = (1.00000f * red) + (-0.00001f * green) + (1.40200f * blue);
			double rgbG = (1.00000f * red) + (-0.34413f * green) + (-0.71414f * blue);
			double rgbB = (1.00000f * red) + (1.77200f * green) + (0.00002f * blue);

			imageArray[nIdx + CHANNEL_R] = rgbR;
			imageArray[nIdx + CHANNEL_G] = rgbG;
			imageArray[nIdx + CHANNEL_B] = rgbB;	
		}
	}

	return *imageArray;
}

















/// <summary> Convert RGB Color image to an Alternate Lab Color space, Red Channel = Luminance, Green = A, Blue = B
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float convertRGBToAltLAB(float *imageArray, int imageWidth, int imageHeight)// use alternate LAB
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double red = imageArray[nIdx + CHANNEL_R];
			double green = imageArray[nIdx+CHANNEL_G];
			double blue = imageArray[nIdx+CHANNEL_B];

			//first we will convert the RGB image to LMS with a matrix
			double lmsL = (0.3811 * red) + (0.5783 * green) + (0.0402 * blue);
			double lmsM = (0.1967 * red) + (0.7244 * green) + (0.0782 * blue);
			double lmsS = (0.0241 * red) + (0.1288 * green) + (0.8444 * blue);

			//convert LMS to LAB part 1
			double labL = 1.0 / sqrt(3.0) * lmsL;
			double labA = 1.0 / sqrt(6.0) * lmsM;
			double LabB = 1.0 / sqrt(2.0) * lmsS;

			//convert LMS to LAB part 2
			double labL1 = (labL * 1.0) + (labA * 1.0) + (LabB * 1.0);
			double labA1 = (labL * 1.0) + (labA * 1.0) + (LabB * -2.0);
			double labB1 = (labL * 1.0) + (labA * -1.0) + (LabB * 0.0);

			//we are now in the LAB colorspace

			//place LAB image in temp array
			imageArray [nIdx + CHANNEL_R] = labL1;
			imageArray [nIdx + CHANNEL_G] = labA1;
			imageArray [nIdx + CHANNEL_B] = labB1;
		}
	}
	return *imageArray;
}

/// <summary> Convert RGB Color image to the CIE Lab Color space, Red Channel = Luminance, Green = A, Blue = B
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float convertRGBToCIELAB(float *imageArray, int imageWidth, int imageHeight)// using CIE LAB
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double var_X;
			double var_Y;
			double var_Z;

			double red = double(imageArray[nIdx + CHANNEL_R]);
			double green = double(imageArray[nIdx + CHANNEL_G]);
			double blue  = double(imageArray[nIdx + CHANNEL_B]);

			if (red > 0.04045f)
			{ 
				red = powf((red + 0.055f) / 1.055f, 2.4f); 
			}
			else 
			{ 
				red = red / 12.92f; 
			}
			if (green > 0.04045f)
			{ 
				green = powf((green + 0.055f) / 1.055f, 2.4f); 
			}
			else 
			{ 
				green = green / 12.92f; 
			}
			if (blue > 0.04045f)
			{ 
				blue = powf((blue + 0.055f) / 1.055f, 2.4f); 
			}
			else 
			{	
				blue = blue / 12.92f; 
			}

			red   = red * 100.0f;
			green = green * 100.0f;
			blue  = blue * 100.0f;

			//first we will convert the RGB image to XYZ
			double xyzX = (0.412453f * red) + (0.357580f * green) + (0.180423f * blue);
			double xyzY = (0.212671f * red) + (0.715160f * green) + (0.072169f * blue);
			double xyzZ = (0.019334f * red) + (0.119193f * green) + (0.950227f * blue);

			//reference white
			double refX = 95.047f; // Observer= 2°, Illuminant= D65
			double refY = 100.000f; 
			double refZ = 108.883f;

			//adjust LAB to reference white
			double var_X1 = xyzX / refX;
			double var_Y1 = xyzY / refY;
			double var_Z1 = xyzZ / refZ;

			//LAB Conversion
			if (var_X1 > 0.008856f) 
			{
				var_X = powf(var_X1 , 1.0f/3.0f); 
			}
			else 
			{
				var_X = (7.787f * var_X1) + (16.0f/116.0f);
			}

			if (var_Y1 > 0.008856f) 
			{ 
				var_Y = powf(var_Y1 , 1.0f/3.0f); 
			}
			else 
			{ 
				var_Y = (7.787f * var_Y1) + (16.0f/116.0f);
			}

			if (var_Z1 > 0.008856f) 
			{
				var_Z = powf(var_Z1 , 1.0f/3.0f); 
			}
			else 
			{ 
				var_Z = (7.787f * var_Z1) + (16.0f/116.0f);
			}

			//adjust LAB scale
			double cieL1 = (116.0f * var_Y) - 16.0f;
			double cieA1 = 500.0f * (var_X - var_Y);
			double cieB1 = 200.0f * (var_Y - var_Z);

			//place LAB image in array
			imageArray[nIdx + CHANNEL_R] = cieL1;
			imageArray[nIdx + CHANNEL_G] = cieA1;
			imageArray[nIdx + CHANNEL_B] = cieB1;
		}
	}
	return *imageArray;
}

/// <summary> Convert RGB Color image to the CIE XYZ Color space, Red Channel = X, Green = Y, Blue = Z
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float convertRGBToCIEXYZ(float *imageArray, int imageWidth, int imageHeight)//use XYZ
{
	for (int x = 0; x< imageWidth; x++)			
	{
		for (int y = 0; y< imageHeight; y++)			
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double red = imageArray[nIdx + CHANNEL_R];
			double green = imageArray[nIdx + CHANNEL_G];
			double blue = imageArray[nIdx + CHANNEL_B];
					
			//first we will convert the RGB image to XYZ
			double xyzX = (0.436052025f * red) + (0.385081593f * green) + (0.143087414f * blue);
			double xyzY = (0.222491598f * red) + (0.716886060f * green) + (0.060621486f * blue);
			double xyzZ = (0.013929122f * red) + (0.097097002f * green) + (0.714185470f * blue);

			//place LAB image in temp array
			imageArray[nIdx + CHANNEL_R] = xyzX;
			imageArray[nIdx + CHANNEL_G] = xyzY;
			imageArray[nIdx + CHANNEL_B] = xyzZ;
		}
	}
	return *imageArray;
}

/// <summary> Convert RGB Color image to the YCbCr Color space, Red Channel = Y, Green = Cb, Blue = Cr
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float convertRGBToYCBCR(float *imageArray, int imageWidth, int imageHeight)//ycbcr
{
	for (int x = 0; x< imageWidth; x++)
	{
		for (int y = 0; y< imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double red = imageArray[nIdx + CHANNEL_R];
			double green = imageArray[nIdx + CHANNEL_G];
			double blue = imageArray[nIdx + CHANNEL_B];

			//first we will convert the RGB image to XYZ
			double ycbcrY = (0.299f * red) + (0.587f * green) + (0.114f * blue);
			double ycbcrB = (-0.16874f * red) + (-0.33126f * green) + (0.50000f * blue);
			double ycbcrR = (0.50000f * red) + (-0.41869f * green) + (-0.08131f * blue);

			imageArray[nIdx + CHANNEL_R] = ycbcrY;
			imageArray[nIdx + CHANNEL_G] = ycbcrB;
			imageArray[nIdx + CHANNEL_B] = ycbcrR;
		}
	}
	return *imageArray;
}

/// <summary> Convert Alt LAB Color image to the RGB Color space, Red Channel = L, Green = A, Blue = B
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float convertAltLABToRGB(float *imageArray, int imageWidth, int imageHeight)//use alternative lab
{
	for (int x = 0; x< imageWidth; x++)
	{
		for (int y = 0; y< imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double labL1 = imageArray [nIdx + CHANNEL_R];
			double LabA1 = imageArray [nIdx + CHANNEL_G];
			double LabB1 = imageArray [nIdx + CHANNEL_B];

			double labL11 = (0.333 * labL1) + (0.167 * LabA1) + (0.500 * LabB1);
			double labA11 = (0.333 * labL1) + (0.167 * LabA1) + (-0.500 * LabB1);
			double labB11 = (0.333 * labL1) + (-0.333 * LabA1) + (0.000 * LabB1);

			double lmsL1 = labL11 * 1.73205080;
			double lmsM1 = labA11 * 2.44948974;
			double lmsS1 = labB11 * 1.41421356;


			double rgbR = (lmsL1 * 4.4679) + (lmsM1 * -3.5873) + (lmsS1 * 0.1193);
			double rgbG = (lmsL1 * -1.2186) + (lmsM1 * 2.3809) + (lmsS1 * -0.1624);
			double rgbB = (lmsL1 * 0.0497) + (lmsM1 * -0.2439) + (lmsS1 * 1.2045);

			imageArray[nIdx + CHANNEL_R] = rgbR;
			imageArray[nIdx + CHANNEL_G] = rgbG;
			imageArray[nIdx + CHANNEL_B] = rgbB;	
		}
	}
	return *imageArray;
}

/// <summary> Convert CIE LAB Color image to the RGB Color space, Red Channel = L, Green = A, Blue = B
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float convertCIELABToRGB(float *imageArray, int imageWidth, int imageHeight)//CIE LAB
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			//reference white
			double refX = 95.047f; // Observer= 2°, Illuminant= D65
			double refY = 100.000f; 
			double refZ = 108.883f;

			double cieL = imageArray [nIdx + CHANNEL_R];
			double cieA = imageArray [nIdx + CHANNEL_G];
			double cieB = imageArray [nIdx + CHANNEL_B];

			double var_Y = (cieL + 16.0f) / 116.0f;
			double var_X = cieA / 500.0f + var_Y;
			double var_Z = var_Y - cieB / 200.0f;

			if (powf(var_Y, 3.0f) > 0.008856)
			{ 
				var_Y = powf(var_Y, 3.0f); 
			}
			else 
			{ 
				var_Y = (var_Y - 16.0f / 116.0f) / 7.787f; 
			}
			if (powf(var_X , 3.0f) > 0.008856f) 
			{ 
				var_X = powf(var_X, 3.0f); 
			}
			else 
			{ 
				var_X = (var_X - 16.0f / 116.0f) / 7.787f; 
			}
			if (powf(var_Z, 3.0f) > 0.008856 ) 
			{
				var_Z = powf(var_Z, 3.0f); 
			}
			else 
			{
				var_Z = (var_Z - 16.0f / 116.0f ) / 7.787f; 
			}

			double cieX = refX * var_X;
			double cieY = refY * var_Y;
			double cieZ = refZ * var_Z;

			var_X = cieX / 100.0f;        
			var_Y = cieY / 100.0f;        
			var_Z = cieZ / 100.0f;

			double red = (var_X * 3.240479f) + (var_Y * -1.537150f) + (var_Z * -0.498535f);
			double green = (var_X * -0.969256f) + (var_Y * 1.87599f) + (var_Z * 0.041556f);
			double blue = (var_X * 0.055648f) + (var_Y * -0.204043f) + (var_Z * 1.057311f);

			if (red > 0.0031308f) 
			{ 
				red = 1.055f * powf(red , (1.0f / 2.4f)) - 0.055f; 
			}
			else 
			{ 
				red = 12.92f * red; 
			}
			if (green > 0.0031308f) 
			{ 
				green = 1.055f * powf(green , (1.0f / 2.4f)) - 0.055f; 
			}
			else 
			{ 
				green = 12.92f * green; 
			}
			if (blue > 0.0031308f) 
			{ 
				blue = 1.055f * powf(blue , (1.0f / 2.4f)) - 0.055f; 
			}
			else 
			{
				blue = 12.92f * blue; 
			}

			imageArray[nIdx + CHANNEL_R] = red;
			imageArray[nIdx + CHANNEL_G] = green;
			imageArray[nIdx + CHANNEL_B] = blue;	
		}
	}
	return *imageArray;
}

/// <summary> Convert CIE XYZ Color image to the RGB Color space, Red Channel = X, Green = Y, Blue = Z
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float convertCIEXYZtoRGB(float *imageArray, int imageWidth, int imageHeight)//use XYZ
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double red = imageArray [nIdx + CHANNEL_R];
			double green = imageArray [nIdx + CHANNEL_G];
			double blue = imageArray [nIdx + CHANNEL_B];

			double rgbR = (3.134051341f * red) + (-1.617027711f * green) + (-0.490652210f * blue);
			double rgbG = (-0.978762730f * red) + (1.916142228f * green) + (0.033449629f * blue);
			double rgbB = (0.071942577f * red) + (-0.228971180f * green) + (1.405218305f * blue);

			imageArray[nIdx + CHANNEL_R] = rgbR;
			imageArray[nIdx + CHANNEL_G] = rgbG;
			imageArray[nIdx + CHANNEL_B] = rgbB;	
		}
	}
	return *imageArray;
}

/// <summary> Convert YCbCr Color image to the RGB Color space, Red Channel = Y, Green = Cb, Blue = Cr
/// <para>*imageArray = image array to be converted.</para>
/// <para>imageWidth = width of input image</para>
/// <para>imageHeight = height of input image</para>
/// </summary>
float convertYCBCRToRGB(float *imageArray, int imageWidth, int imageHeight)
#pragma region   //use ycbcr
{
	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			int nIdx = x * 4 + y * 4 * imageWidth;

			double red = imageArray [nIdx + CHANNEL_R];
			double green = imageArray [nIdx + CHANNEL_G];
			double blue = imageArray [nIdx + CHANNEL_B];

			double rgbR = (1.00000f * red) + (-0.00001f * green) + (1.40200f * blue);
			double rgbG = (1.00000f * red) + (-0.34413f * green) + (-0.71414f * blue);
			double rgbB = (1.00000f * red) + (1.77200f * green) + (0.00002f * blue);

			imageArray[nIdx + CHANNEL_R] = rgbR;
			imageArray[nIdx + CHANNEL_G] = rgbG;
			imageArray[nIdx + CHANNEL_B] = rgbB;	
		}
	}

	return *imageArray;
}












#endif // colorspace_h