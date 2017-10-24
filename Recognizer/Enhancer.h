#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "patch_namespace.h"

//#include<iostream>
//#include <vector>
//#include <algorithm>
#include<iterator>

using namespace std;
using namespace cv;

void Enhancer(Mat frame,Mat frame_Norm, float alpha, float delta_alpha, int beta, int delta_beta, int countFrame, string Dir, int NumMaxFrame,std::vector<float>& meanAlls,int max_alpha, int max_beta) {

	//std::vector<cv::Mat>Frames; 
	Mat frame2;
	Scalar mean, std; //float meanAll=0.0, stdAll=0.0;
	//cout << "SIZENIT:  "<<meanAlls.size() << endl;


	/*
	int alpha_target = 1; int beta_target = +25;
	float alpha = 0.6; int beta = 0;
	float delta_alpha = 0.2; int delta_beta = -25;
	int max_alpha = ((alpha_target-alpha)/delta_alpha)+1; // + 1 per lo zero...
	int max_beta = ((beta_target / abs(delta_beta))*2) + 1; // + 1 per lo zero e (*2) per la presenza dei beta negativi ...
	*/

	
	int count = 0; int j, jj;
	for ( j = -2; j <= 2; j++) {  // beta
		for ( jj = 0; jj <= 1; jj++) { // alpha
			frame.convertTo(frame2, -1, alpha + (delta_alpha*jj), beta + (delta_beta*j));			
			//Dir = tmp + patch::to_string(count);
			if (countFrame == 1) 			
					thesis::make_dir((Dir + patch::to_string(count + 1)).c_str());
			//if (countFrame == 1 || countFrame == 2) {
				frame_Norm.convertTo(frame_Norm, -1, alpha + (delta_alpha*jj), beta + (delta_beta*j));
				if (countFrame == 1 || countFrame == 2) 
				imwrite(Dir + patch::to_string(count) + "\\" + "#" + patch::to_string(countFrame) + "NORMALIZED.bmp", frame_Norm);
				// Se voglio inserire nel calcolo della media i frmae normalizzati
				//meanStdDev(frame_Norm, mean, std);
				
				// Se voglio inserire nel calcolo della media i frmae NON normalizzati
				meanStdDev(frame2, mean, std);
					//meanAlls.insert(meanAlls.begin() + (countFrame - 1)*NumMaxFrame, (float)mean[0]);
					meanAlls[(countFrame - 1)+ count*(NumMaxFrame)] = (float)mean[0];
					cout<<"Insered in "<< (countFrame - 1) + count*(NumMaxFrame) <<"  value: "<<meanAlls[(countFrame - 1) + count*(NumMaxFrame)] << endl;
			
			
					count++;

				imwrite(Dir + patch::to_string(count) + "\\" + "#" + patch::to_string(countFrame) + "_alpha_" + patch::to_string(alpha + (delta_alpha*jj)) + "__beta_" + patch::to_string(beta + (delta_beta*j)) + ".bmp", frame2);
				//cout << "DIR  " << Dir + patch::to_string(count) + "\\alpha_" + patch::to_string(alpha + (delta_alpha*jj)) + "__beta_" + patch::to_string(beta + (delta_beta*j)) + ".bmp" << endl;
				LQP_EXTRACT_V2(Dir + patch::to_string(count) + "\\" + "LQP_featuresEnhancedVersion_#" + patch::to_string(count) + "_.txt", frame2);
			
		}
		

	}
	

}


int DB_Response(std::vector<float> meanVec,float meanLAst) {
	
	std::vector<float> diff(meanVec.size());
	for (int i = 0; i < meanVec.size(); i++) {
		diff[i] = abs(meanVec[i]-meanLAst);

	}
	//int min = *std::min_element(diff.begin(), diff.end());
	int IndexMin = std::distance(diff.begin(), std::min_element(diff.begin(), diff.begin()));
	//int IndexMin = std::distance(std::begin(diff), std::min_element(std::begin(diff), std::end(diff)));
	//cout << "margine:  "<<diff[IndexMin] << endl;

	//cout <<"MININdex:  "<< IndexMin << endl;
	

	return IndexMin;
}


int DB_Response_vector(std::vector<float> meanVec, std::vector<float>  meanLAst) {
	cout << meanVec.size() << "  " << meanLAst.size() << endl;
	if (meanVec.size() != meanLAst.size()) {
		cout << "ERRORE, dimensione errata dei due vettori" << endl;
		system("pause");
		exit(-1);
	}


	std::vector<float> diff(meanVec.size());
	for (int i = 0; i < meanVec.size(); i++) {
		diff[i] = abs(meanVec[i] - meanLAst[i]);

	}
	//int IndexMin = std::distance(std::begin(diff), std::min_element(std::begin(diff), std::end(diff)));
	int IndexMin = std::distance(diff.begin(), std::min_element(diff.begin(), diff.begin()));
	cout << "margine:  "<<diff[IndexMin] << endl;

	cout <<"MININdex:  "<< IndexMin << endl;


	return IndexMin;
}


#pragma once
Mat Read_TXT_MAt(ifstream& inputFile,int rowNum, int colNum, int NumMaxFrame, std::vector<cv::Mat> &faces ) {


	

		float *Data_array = new float[NumMaxFrame*rowNum*colNum];
		for (int row = 0; row < NumMaxFrame*rowNum; row++)
		{
			for (int col = 0; col < colNum; col++)
			{
				inputFile >> *(Data_array + colNum * row + col);
			}
		}
		
		Mat Data = Mat(NumMaxFrame*rowNum, colNum, CV_32FC1, Data_array);
		//faces.push_back(Data);
		
		for (int i = 0; i < NumMaxFrame;i++)
			faces[i] = Data.row(i);
	
	inputFile.close();

	
/*
		for (int i = 0; i < 1; i++)
		for (int j = 0; j < 30; j++)
		cout << faces[0].at<float>(i, j) << "  ";
*/		

	return Data;
}
