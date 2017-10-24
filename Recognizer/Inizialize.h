#pragma once
#ifndef _init_h
#define _init_h
#include <istream>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */
#ifdef _WIN32
#include <Windows.h>
#define GetCurrentDir _getcwd
#else
#include<unistd.h>
#endif
#include <random>
#include <vector>
#include <iomanip>      // std::setprecision
#include<ctime>

#include <math.h>

#include "myUtils.h"
#include "Antispoofing.h"

//extern const int dimension;

#include "Qt_messageBox.h"
#include<QtWidgets/qdesktopwidget.h>
#include"LQP_main.h"

using namespace cv;
using namespace std;

//bool inizialize(int argc, char** argv, std::vector<cv::Mat>& faces);
//bool inizialize(int argc, char** argv, std::vector<cv::Mat> &faces);

//double FindTheresoldValue(string file_test, std::vector<cv::Mat>faces, int rowNum, int colNum, int num, string image);
double FindTheresoldValue(int residuals=0);

cv::VideoCapture inizialize(int argc, char** argv, string current_path);
void SetPath(string &current_path, string &cascade_face);

cv::String setFrame_properties(string Title);
void setGeometries();


void LQPvectorLoading();

#endif