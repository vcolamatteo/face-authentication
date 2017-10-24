#include"LQP.h"



LQP::LQP()
{
	cerr << "bad initialization" << endl;
}





LQP::LQP(IplImage* input)
{
	img = input;
}




LQP::~LQP()
{
	cvReleaseImage(&img);
}





int LQP::cal_LQP(int R, ofstream &output)
{

	//img = resize1(input_img);
	for (int i = 0;i != img->height;i += HeightStep)
	{
		for (int j = 0;j != img->width;j += WidthStep)
		{
			cal_block(output, R, i, j);
		}
	}
	return 0;
}




int LQP::cal_block(ofstream &output, int R, int i, int j)
{
	int itempx;
	int itempy;
	double tempx = 0.0;
	double tempy = 0.0;
	double dx = 0.0;
	double dy = 0.0;
	int Img1;
	int Img2;
	int Img3;
	int Img4;
	int value;
	int newvalue;
	int Midvalue;


	for (int m = i;m<i + HeightStep;m++)  // from 0 to 64+8 in altezza
	{
		for (int n = j;n<j + WidthStep;n++) // from 0 to 64+8 in larghezza
		{
			for (int radius = R;radius != 0;--radius) // from 3 to 0
			{
				Midvalue = pixval8(img, m, n); // y,x determina valore coordinate pixel
				for (int k = 0;k<8 * radius;k++) // sono 3 giri attorno al pixel centrale, contenetei 8, 16 e 24 pixel risp.
				{
					tempx = n + radius* cos(2.0*CV_PI*k / 8 / radius);
					tempy = m - radius* sin(2.0*CV_PI*k / 8 / radius);
					itempx = static_cast<int>(floor(tempx));
					itempy = static_cast<int>(floor(tempy));

					itempx = ((itempx) >= PictureWidth) ? PictureWidth - 1 : ((itempx) < 0) ? 0 : (itempx);
					itempy = ((itempy) >= PictureWidth) ? PictureWidth - 1 : ((itempy) < 0) ? 0 : (itempy);

					//cout << itempx << "   " << itempy << "  "<<tempx<<"   "<<tempy<<endl;

					dx = (tempx - itempx);
					dy = (tempy - itempy);
					Img1 = pixval8(img, itempy, itempx); //(x,y)

					int itempy_2 = itempy + 1;
					itempy_2 = ((itempy_2) >= PictureWidth) ? PictureWidth - 1 : (itempy_2);

					Img2 = pixval8(img, itempy_2, itempx); //(x,y+1)

					int itempx_2 = itempx + 1;
					itempx_2 = ((itempx_2) >= PictureWidth) ? PictureWidth - 1 : (itempx_2);

					Img3 = pixval8(img, itempy, itempx_2); //(x+1,y)
					Img4 = pixval8(img, itempy_2, itempx_2);//(x+1,y+1)
					value = static_cast<int>(Img1*(1 - dx)*(1 - dy) + Img2*(1 - dx)*dy + Img3*dx*(1 - dy) + Img4*dx*dy);


					//output<<( Midvalue>=(value+5)  ? 2 : (Midvalue<=(value-5) ? 0 : 1) )<<" ";
					output << (value >= (Midvalue + 5) ? 2 : (value <= (Midvalue - 5) ? 0 : 1)) << " ";
					//*(LQP_fea + count) = value > (Midvalue + 7) ? 2 :(value < (Midvalue - 7) ? 0 : 1);
				}
			}
			output << endl;
		}
	}
	return 0;
}





IplImage* LQP::resize1(IplImage *ima)
{
	if (!ima) { cerr << "could not open image" << endl; }


	// resize the image
	IplImage *dst = 0;
	CvSize dst_cvsize;
	dst_cvsize.width = img->width;
	dst_cvsize.height = img->height;
	dst = cvCreateImage(dst_cvsize, ima->depth, ima->nChannels);
	cvResize(ima, dst, CV_INTER_LINEAR);


	//color to gray
	if (dst) {
		int height = dst->height;
		int width = dst->width;
		IplImage *imaMid = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
		if (dst->nChannels == 3)
			cvCvtColor(dst, imaMid, CV_RGB2GRAY);
		else
			cvCopy(dst, imaMid);
		cvReleaseImage(&dst);
		//		cvSaveImage("res.jpg",imaMid);		
		return imaMid;
	}
	else
		cerr << "resize error" << endl;

}

int LQP::cal_LQP_histogram(int R, int digit, float**clucenter, int dimension, float* histo)
{


	//        img = resize1(input_img);
	//cout<<"H:"<<HeightStep<<" W:"<<WidthStep<<endl;

	int offset = 0;
	for (int y = 0;y != img->height;y += HeightStep)
	{
		for (int x = 0;x != img->width;x += WidthStep)
		{
			cal_LQP_histogram_Core(R, digit, clucenter, dimension, histo + offset, x, y);
			offset += dimension;
			//cout<<endl<<"offset:"<<offset<<"x y:"<<x<<" "<<y<<endl;
		}
	}
	return offset;
}


int LQP::cal_LQP_histogram_Core(int R, int digit, float**clucenter, int dimension, float* histo, int x, int y)
{
	float* LQP_fea = new float[digit];
	for (int i = 0;i != digit;i++)
		*(LQP_fea + i) = 0;
	float* distance = new float[dimension];
	//float* distance_2 = new float[dimension];




	int itempx;
	int itempy;
	/*double tempx = 0.0;
	double tempy = 0.0;
	double dx = 0.0;
	double dy = 0.0;*/
	float tempx = 0.0;
	float tempy = 0.0;
	float dx = 0.0;
	float dy = 0.0;
	int Img1;
	int Img2;
	int Img3;
	int Img4;
	int value;
	int newvalue;
	int Midvalue;

	int count;
	float min;
	int minflag = -1;

	for (int m = x;m<x + WidthStep;m++)
	{
		for (int n = y;n<y + HeightStep;n++)
		{
			//			cout<<"m:"<<m<<" n:"<<n<<endl;
			count = 0;
			for (int radius = R;radius != 0;--radius)
			{
				Midvalue = pixval8(img, m, n); // y,x
											   //cout << Midvalue << endl<<endl<<endl<<endl;
				for (int k = 0;k<8 * radius;k++)
				{
					/*if (tempx - int(tempx) != 0 || tempy - int(tempy) != 0) {
					cout << tempx << endl;
					cout << tempy << endl;
					cout << x <<"  "<< y << endl;
					cout << m << "  " << n << "  " << radius << "  " << k<<endl;
					system("pause");
					}*/
					tempx = n + radius* cos(2.0*CV_PI*k / 8 / radius);
					tempy = m - radius* sin(2.0*CV_PI*k / 8 / radius);
					//cout << tempx << endl;
					//cout << tempy << endl;
					//cout << m << "  " << n << "  " << radius << "  " << k << endl;

					itempx = static_cast<int>(floor(tempx));
					itempy = static_cast<int>(floor(tempy));

					// faccio una saturazione....
					itempx = ((itempx) >= PictureWidth) ? PictureWidth - 1 : ((itempx) < 0) ? 0 : (itempx);
					itempy = ((itempy) >= PictureWidth) ? PictureWidth - 1 : ((itempy) < 0) ? 0 : (itempy);
					//cout << "i:  "<<itempx << endl;
					//cout << "i:  "<<itempy << endl;
					//system("pause");
					/*
					if (itempx >= 60)
					itempx = 59;
					if (itempy >= 60)
					itempy = 59;
					if (itempx < 0)
					itempx = 0;
					if (itempy <0 )
					itempy = 0;
					*/
					dx = (tempx - itempx);
					dy = (tempy - itempy);

					Img1 = pixval8(img, itempy, itempx); //(x,y)										
														 //tt << itempy<<"  "<<itempx<<"  "<<Img1 <<endl;
														 //tt<< Img1 <<" ";
					int itempy_2 = itempy + 1;
					itempy_2 = ((itempy_2) >= PictureWidth) ? PictureWidth - 1 : (itempy_2);
					//if (itempy_2 >= 60)
					//itempy_2 = 59;
					Img2 = pixval8(img, itempy_2, itempx); //(x,y+1)
														   //tt << itempy_2 << "  " << itempx << "  " << Img2 << endl;
														   //tt << Img2 <<" ";                                       
					int itempx_2 = itempx + 1;
					itempx_2 = ((itempx_2) >= PictureWidth) ? PictureWidth - 1 : (itempx_2);
					//if (itempx_2 >= 60)
					//  itempx_2 = 59;

					Img3 = pixval8(img, itempy, itempx_2); //(x+1,y)

					Img4 = pixval8(img, itempy_2, itempx_2);//(x+1,y+1)
															// cout << count << endl;
					value = static_cast<int>(Img1*(1 - dx)*(1 - dy) + Img2*(1 - dx)*dy + Img3*dx*(1 - dy) + Img4*dx*dy);
					//cout << "value_md:  " << value << "  " << Midvalue <<endl;
					//system("pause");
					//*(LQP_fea + count) = value > (Midvalue +7) ? 2 :(value < (Midvalue -7) ? 0 : 1);
					*(LQP_fea + count) = value >= (Midvalue + 7) ? 2 : (value <= (Midvalue - 7) ? 0 : 1);

					/* *(LQP_fea + count) = value >(pixval8(img, m, n) + 7) ? 2 :
					(value < (pixval8(img, m, n) - 7) ? 0 : 1);
					*/

					//cout << value << endl;
					//cout << value<<"   mid+7:  "<<(Midvalue )<<"  mid-7:   "<< (Midvalue )<<"  LQP_fea  "<<*(LQP_fea + count) << "   "<<endl;
					//output << (Midvalue >= (value + 5) ? 2 : (Midvalue <= (value - 5) ? 0 : 1)) << " ";
					//	system("pause");
					count++;
				}
			}

			// Qua finisce il calclo degli LQP...
			min = VeryMin;
			for (int i = 0;i < dimension;i++) {
				distance[i] = 0;
				//distance_2[i] = 0;
			}
			for (int i = 0;i<dimension;i++)
			{
				for (int j = 0;j<digit;j++)
				{
					distance[i] += (*(LQP_fea + j) - clucenter[i][j]) *(*(LQP_fea + j) - clucenter[i][j]);
					//distance[i] += pow((*(LQP_fea + j) - clucenter[i][j]), 2);// *(*(LQP_fea + j) - clucenter[i][j]);
					//distance[i] += abs((*(LQP_fea + j) - clucenter[i][j]));// *(*(LQP_fea + j) - clucenter[i][j]);					
					//cout << "distance:  " << distance_2[i];
					//system("pause");
					//cout<< "distance:  "<<distance[i] <<"   mn: "<<min<<endl;
				}
				//cout << distance[i] - distance_2[i] << endl;
				//cout<<i<<"  ";
				//system("pause");
				//if(distance_2[i]<min){
				if (distance[i]<min) {
					//cout << "distance:   "<<distance[i] << endl;
					//system("pause");
					//cout << i << "  ";
					min = distance[i];
					//min = distance[i]; 
					//cout << "newMin:  " << min << "  ndex -i:  " << i;
					//system("pause");
					minflag = i;
				}
			}
			if (minflag != -1) {
				histo[minflag]++;
				//cout << "hsto[minFlag]:   " << histo[minflag] << "  ndex -i (minFlag):  " << minflag << endl;
			}
			//system("pause");
		}
	}
	/*double histTotal = 0;
	for (int i = 0;i<dimension;i++)
	histTotal= histTotal +histo[i];
	cout << "histTotal:  "<<histTotal << endl; */
	for (int i = 0;i<dimension;i++)
	{
		//cout<<histo[i]<<" ";
		histo[i] = sqrt(histo[i] / 100);  // sum(histo)==100;
										  //system("pause");
	}

	delete[] distance;
	delete[] LQP_fea;
	return 0;
}
