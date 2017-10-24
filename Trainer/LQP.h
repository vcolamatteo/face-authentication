#pragma once
#include<opencv2/opencv.hpp>
#include<opencv/cv.h>
#include<fstream>
#include<vector>
#include<omp.h>
#include<iostream>
#include <stdlib.h>
#include<string>
using namespace std;

/*
#define PictureWidth 100
#define PictureHeight 100
#define WidthStep 10
#define HeightStep 10
*/
//const int PictureWidth = 60;
//const int PictureHeight = 80;
extern const int PictureWidth, PictureHeight;
const int WidthStep = 10;
const int HeightStep = 10;
#define VeryMin 100000000000



class LQP
{
public:
	LQP();

	LQP(IplImage* input);

	int cal_LQP(int R, ofstream &output);

	int cal_LQP_histogram_Core(int R, int digit, float**clucenter, int dimension, float* histo, int x, int y);

	int cal_LQP_histogram(int R, int digit, float**clucenter, int dimension, float* histo);

	~LQP();
private:

	IplImage* resize1(IplImage *img);

	int cal_block(ofstream &output, int R, int i, int j);

	IplImage* img;
};

static inline int pixval8(IplImage*img, int r, int c)
{

	//r :row
	//c :col
	return (int)CV_IMAGE_ELEM(img, uchar, r, c);
	//return (int)(((uchar*)(img->imageData+img->widthStep*r))[c]);

}


