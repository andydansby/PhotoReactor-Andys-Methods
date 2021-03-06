/// <summary> Shifts image from the edge to 1/2 kernel input i.e. if using a kernel size of 3, the shift amount is 1.  The edges of the output image will be a reflected copy of the input image.
/// <para>largerPyramidLevelArray = Input image.</para>
/// <para>largerPyramidLevelWidth = Width of input image.</para>
/// <para>largerPyramidLevelHeight = Height of input image.</para>
/// <para>smallerPyramidLevelArray = Output image.</para>
/// <para>smallerPyramidLevelWidth = Width of output image.</para>
/// <para>smallerPyramidLevelHeight = Height of output image.</para>
/// <para>Returns return *smallerPyramidLevelArray </para>
/// </summary>
float gaussianReducepyramid(float *largerPyramidLevelArray, int largerPyramidLevelWidth, int largerPyramidLevelHeight, float *smallerPyramidLevelArray, int smallerPyramidLevelWidth, int smallerPyramidLevelHeight)
{
	char sBuffer6[400];

	//each pyramid level 1/2 the height and width of the prior pyramid


	/*sprintf(sBuffer6,"largerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
	                 ,largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
					   MessageBox(NULL,sBuffer6,"Pyramid Resolutions", MB_OK);*/
		

	int largerPyramidLevelHeightMinus = largerPyramidLevelHeight - 1;
	int largerPyramidLevelWidthMinus = largerPyramidLevelWidth - 1;

	int smallerPyramidWidthMinus = smallerPyramidLevelWidth - 1;
	int smallerPyramidHeightMinus = smallerPyramidLevelHeight - 1;

	//since a gaussian pyramid level is 1/2 the size of the prior level
	//we cannot use the x / y loops directly for the smaller image.
	//We recalcuate the position for the smaller image by checking if the numbers of the
	//x / y loop is even, if so we increment xx and yy by 1

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

			//for testing only
			int CenterIndex = x * 4 + y * 4 * largerPyramidLevelWidth;			
			float redCenter = largerPyramidLevelArray[CenterIndex + CHANNEL_R];//for printing purposes
			//for testing only

			//combine the kernel for gaussian
			float red = rr1 + rr2 + rr3 + rr4 + rr5 + rr6 + rr7 + rr8 + rr9;
			float green = gg1 + gg2 + gg3 + gg4 + gg5 + gg6 + gg7 + gg8 + gg9;
			float blue = bb1 + bb2 + bb3 + bb4 + bb5 + bb6 + bb7 + bb8 + bb9;

			/*
			sprintf(sBuffer6,"redCenter = %f\n\n x = %d\n y = %d\n\n xx = %d\n yy = %d\n\n largerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
			                 ,redCenter,         x,       y,         xx,       yy,         largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
			MessageBox(NULL,sBuffer6,"X and Y", MB_OK);
			*/

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

			
				
			/*if (xx > 120)
			{
			sprintf(sBuffer6,"x = %d\n y = %d\n\n xx = %d\n yy = %d\n\n red = %f\n\nlargerPyramidLevelWidth = %d\n largerPyramidLevelHeight = %d\n\n smallerPyramidLevelWidth = %d\n smallerPyramidLevelHeight = %d"
			,x,       y,         xx,       yy,         red,        largerPyramidLevelWidth,       largerPyramidLevelHeight,         smallerPyramidLevelWidth,       smallerPyramidLevelHeight);
			MessageBox(NULL,sBuffer6,"X and Y", MB_OK);
			}*/

			//for the smaller image
			int nIdx = xx * 4 + yy * 4 * smallerPyramidLevelWidth; //center
			//for the smaller image
			smallerPyramidLevelArray[nIdx + CHANNEL_R] = red;
			smallerPyramidLevelArray[nIdx + CHANNEL_G] = green;
			smallerPyramidLevelArray[nIdx + CHANNEL_B] = blue;

		}//end y
		yy = 0;//reset xx back to 0 to follow the x loop
	}//end x

	///////////////////////////////////////////////////////////////////
	//                       OK to this point                        //
	///////////////////////////////////////////////////////////////////

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
