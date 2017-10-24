#pragma once

#include<iostream>
#include "myUtils.h"

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include<fstream>

using namespace std;
using namespace cv;



#define NumMaxFrame 6


extern string path_init_Norm;

void LQPvectorLoading_(Mat &AllFacesNorm,std::vector<cv::Mat>& faces) {


	int colNum = 12150;
	int rowNum = 1;

	//faces.resize(NumMaxFrame + 1);
	//	std::vector<cv::Mat> faces(NumMaxFrame+1);

	std::ifstream inNorm;

	std::vector<float>LQP_VecNorm(colNum*NumMaxFrame*rowNum);
	//std::vector<Mat>AllFacesNorm(numDirNorm);
	//std::vector<Mat>AllFacesNorm(NumMaxFrame);


	string fileName_init = "Dat";
	string tmpNorm = "";

	tmpNorm = path_init_Norm + fileName_init + ".data";
	cout << tmpNorm << endl;
	if (myUtils::fexists(tmpNorm)) {
		//for (int i = 0; i < numDirNorm; i++) {
		//tmpNorm = path_init_Norm + to_string(i + 1) + back_slash + fileName_init + ".data";
		//cout << tmpNorm << endl;
		inNorm.open(tmpNorm.c_str(), std::ios_base::binary);
		LQP_VecNorm = myUtils::loadVectorKnownSize(inNorm, colNum*rowNum*NumMaxFrame);
		//myUtils::system_pause();
		//}


		//	for (int i = 0; i < numDirNorm; i++) {
		AllFacesNorm = Mat(LQP_VecNorm);
		cout << "fdgdgfdgdfgh n  " << AllFacesNorm.at<float>(5, 12143) << endl;
		//cout<<AllFacesNorm.size() << endl;
		//AllFacesNorm = AllFacesNorm.reshape(1, rowNum*NumMaxFrame);
		/*cout << "vggggg  "<<AllFacesNorm.size() << endl;
		cout << "vggggg  " << AllFacesNorm.rows << endl;
		for (int i = 0; i < 30; i++)
		cout << AllFacesNorm.row(5).at<float>(i) << " ";cout<< endl;*/
		//	}
		cout << "bbbbbbbbbbbbbbbbbbbbbb   " << AllFacesNorm.size() << endl;
	}

	//for (int i = 0;i < NumMaxFrame + 1;i++)
	//faces[i] = Mat(rowNum, colNum, CV_32FC1);

	cout << "bbbbbbbbbbbbbbbbbbbbbb   " << AllFacesNorm.size() << endl;
	AllFacesNorm = AllFacesNorm.reshape(1, rowNum*NumMaxFrame);

	for (int i = 0; i<NumMaxFrame; i++)
		faces[i] = Mat(AllFacesNorm.row(i));


	cout << "size AllFacesNorm   " << AllFacesNorm.row(5).size() << endl;
	cout << "size sss   " << faces[0].size() << endl;

	cout << "bbbbbbbbbbbbbbbbbbbbbb   " << AllFacesNorm.size() << endl;
	cout << "DDDDDDDDDDDDDDDDDDD " << AllFacesNorm.at<float>(5, 12149) << endl;

	cout << "fgdsgffd" << endl;
	for (int i = 0; i < 30; i++)
		cout << faces[5].at<float>(i) << "  ";


	//myUtils::writeMatrix(faces[5], "AALL.txt");

	system("pause");

	return;

}
