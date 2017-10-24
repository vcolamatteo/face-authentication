#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<opencv/cv.h>
#include "myUtils.h"
#include "config.h"
#include "Mat_to_binary.h"
#include "LQP_main.h"

using namespace std;
using namespace cv;


extern string back_slash;
extern int finalDimension;
//extern vector< Mat> Im;


int exitC = 0;
float percentuage = 0.1;

extern int STOP;
extern string back_slash;

extern bool newDataFolder;

double FindTheresoldValue(std::vector<Mat>&Im);
double FindTheresoldValueShortTimeVersion(std::vector<Mat>&Im);

double NoiseEstimator(Mat image) {


	Mat abs_dst, dst;
	int kernel_size = 3;
	int scale = 1;
	int deltaL = 0;
	int ddepth = CV_16S;


	Mat my_kernel = (Mat_<double>(kernel_size, kernel_size) << 1, -2, 1, -2, 4, -2, 1, -2, 1);
	//imageOR = imread("results\\_normalized_41.bmp",CV_LOAD_IMAGE_ANYCOLOR);
	filter2D(image, dst, ddepth, my_kernel, Point(-1, -1), 0, BORDER_DEFAULT);

	//Laplacian(imageOR, dst, ddepth, kernel_size, scale, deltaL, BORDER_DEFAULT);	
	//convertScaleAbs(dst, abs_dst);
	double Sigma = cv::sum(abs(dst))[0];
	//cout << "Sigma:  " << Sigma << endl;
	//cout << Sigma*(sqrt(0.5*CV_PI)) << endl;
	//cout << (6 * (image.rows - 2)*(image.cols - 2)) << endl;
	Sigma = Sigma*(sqrt(0.5*CV_PI)) / (6 * (image.rows - 2)*(image.cols - 2));
	//cout << "Sigma:  " << Sigma << endl;

	return Sigma;
}


void GaussianNoise(Mat& image, int &init, float &digit, float min, float max) {
	Scalar mean, std;
	cv::meanStdDev(image, mean, std);
	Mat result;

	double delta = 0.01; int count = 1;
	digit = delta*count;
	while (mean[0] < 25 || mean[0] >35) {

		image.copyTo(result);
		digit = delta*count;
		result.convertTo(result, -1, digit, 0);
		cv::meanStdDev(result, mean, std);
		//cout << mean[0] << endl;
		//system("pause");

		count++;

	}


	result.copyTo(image);
	//cv::imshow("OUTPUT", image); waitKey(0);
	// imGray is the grayscale of the input image
	cv::Mat noise = Mat(image.size(), CV_8UC1);
	//normalize(image, result, 1,0, CV_MINMAX, CV_8UC1);
	//cv::imshow("OUTPUT_NOrm", result); waitKey(0);

	init = 0; delta = 0.05; count = 1;
	std::vector<int>countSave;
	//cv::randn(noise, 0, 7);
	//result = result + noise;
	double Sigma = NoiseEstimator(image);
	//cout << "Sigma INIT:  " << Sigma << endl;
	int done = 0;
	while (!done) {
		cv::randn(noise, 0, init + (count*delta));
		image = image + noise;

		image = myUtils::Norm_lum(image);
		// Draw it on screen:
		//imshow("Original Image", imageOR);
		image = myUtils::norm_0_255(image);
		//imshow("TanTriggs Preprocessed Image", imageOR);
		//imwrite(dataPath + filename + "TAn" + type, imageOR);
		//cv::equalizeHist(image, image);
		//cv::equalizeHist(image, image);
		//cv::imshow("NOISgjhE", image); waitKey(0);
		double Sigma = NoiseEstimator(image);
		//cout << "Sigma 1:  " << Sigma << " val " << init + (count*delta) << endl;
		if (Sigma < max && Sigma > min) {
			done = 1;
			//cout << "Sigma:  " << Sigma << " val " << init + (count*delta) << endl;
			//cout << "HERE" << endl;
		}
		else {
			if (Sigma - max < 0.1 || Sigma - min > -0.1) {
				countSave.push_back(init + (count*delta));
				//cout << "HERE GOOD" << endl;
			}
			result.copyTo(image);
			//system("pause");
			count++;
			//cout << count << endl;
			if (Sigma > max) {
				//cout << "HERE" << endl;
				int min = *std::min_element(std::begin(countSave), std::end(countSave));
				//cout << "MIN:    " << min << endl;
				//system("pause");
				cv::randn(noise, 0, min);
				image = image + noise;
				image = myUtils::Norm_lum(image);;
				image = myUtils::norm_0_255(image);
				//cv::equalizeHist(image, image);
				//cv::equalizeHist(image, image);
				//cv::imshow("FINAL", image); waitKey(0);
				done = 1;
				//cout << "Sigma final:  " << Sigma << " val " << init + (count*delta) << endl;
				//system("pause");
			}
		}
	}

	//normalize(result, result, 0.12, 0, CV_MINMAX, CV_8UC1);
	//cv::imshow("NOISE", image); waitKey(0);
	image.copyTo(result);
}


int Enhancer(std::vector<cv::Mat>& AllMat, int rowNum, int colNum, Mat frame_2,int countFrame, int NumMaxFrame) {


	Scalar mean, std;
	meanStdDev(frame_2, mean, std);	

	int count = 1;

	for (int jj = 0; jj < 1; jj++) { 


		Mat frame;
		frame_2.copyTo(frame);

		if (jj == 0 ) {}


		frame = myUtils::Norm_lum(frame);
		frame = myUtils::norm_0_255(frame);




		if (jj == 0) {
			imwrite(Dir_initNorm + "#" + to_string(countFrame) + "__beta_.bmp", frame);
		}
		
		AllMat.push_back(frame);

		count++;
	}





	while (fexists("stop")) {
		if (exitC == -1) { thesis::delete_file("stop"); 
		if (newDataFolder == true) {
			thesis::delete_folder_no_Console(Dir_initNorm);
		}
		exit(-1); }
	}


	//system("pause");

	if (countFrame == NumMaxFrame) {
		


		/*exitC = 100;
		while (!fexists("tt.txt")) {}
		thesis::delete_file("tt.txt");*/
		

		std::vector<Mat>Im(NumMaxFrame);
		LQP_gen(AllMat, Dir_initNorm + "output.txt", "cluCenterFile.txt", Im, "-g");
		//LQP_gen("images_new.txt", "output.txt", "cluCenterFile.txt", "-g");		
		kmeans_(Dir_initNorm + "output.txt", Dir_initNorm + "midResults.txt", Dir_initNorm + "cluCenterFile.txt");
		//system("pause");
		LQP_gen(AllMat, Dir_initNorm + "LQP.txt", Dir_initNorm + "cluCenterFile.txt", Im, "-e");
		//LQP_gen(AllMat, Dir_initNorm+"LQP.txt", Dir_initNorm+"cluCenterFile.txt",Im, "-e");
		//LQP_gen("images_new.txt", "LQP.txt", "cluCenterFile.txt", "-e");		



		while (fexists("stop")) {
			if (exitC == -1) {  thesis::delete_file("stop"); 
			if (newDataFolder == true) {
				thesis::delete_folder_no_Console(Dir_initNorm);
			}
			exit(-1); }
		}

		Mat Dat = Mat(AllMat.size(), Im[0].cols, CV_32FC1);
		for (int i = 0; i < AllMat.size();i++)
			Im[i].copyTo(Dat.row(i));

		myUtils::writeMatrix(Dat, Dir_initNorm + "data.txt");
		SaveMatBinary(Dir_initNorm + "Dat.data", Dat);


		while (fexists("stop")) {
			if (exitC == -1) {  thesis::delete_file("stop");
			if (newDataFolder == true) {
				thesis::delete_folder_no_Console(Dir_initNorm);
			}
			exit(-1); }
		}

		float theresold = FindTheresoldValue(Im);		
		

		FILE *fp; 
		fp = fopen((current_path + back_slash + "Database_Normalized" + back_slash + Data + back_slash + "Info_temp.data").c_str(), "wb");

		myUtils::writefloat(theresold, fp);


		//exitC = 100;
		while (!fexists("tt.txt")) {}
		thesis::delete_file("tt.txt");

		//if (countFrame == 2) {
		exitC = 1;
		//while (!fexists("tt.txt")) {}
		//thesis::delete_file("tt.txt"); 
	}


	return 0;

}


std::vector<int> DB_Response(std::vector<float> meanVec, float meanLAst, int NumImageToSelect) {
	// Seleziono i "NumImageToSelect" migliori...

	std::vector<int>SelectedIndex(NumImageToSelect);

	std::vector<float> diff(meanVec.size());
	for (int i = 0; i < meanVec.size(); i++) {
		diff[i] = abs(meanVec[i] - meanLAst);

	}



	for (int i = 0; i < NumImageToSelect; i++) {
		int IndexMin = std::distance(std::begin(diff), std::min_element(std::begin(diff), std::end(diff)));
		SelectedIndex[i] = IndexMin;
		diff[IndexMin] = 100;  // maggioro volonttariamente l'indice trovato...
	}



	return SelectedIndex;
}


double FindTheresoldValue(std::vector<Mat>&Im) {

	// Read file created before....
#ifdef _WIN32
	ifstream file; file.open("Database_Normalized" + back_slash + "list_images_WIN32.txt", ios::in);
#else
	ifstream file; file.open("Database_Normalized" + back_slash + "list_images_LINUX.txt", ios::in);
#endif
	std::string line;
	std::vector<std::string> myLines;
	while (std::getline(file, line))
	{
		myLines.push_back(line);
	}

	cout << myLines.size() << endl;
	file.close();


	cv::Mat LAST;// = cv::Mat(rowNum, colNum, CV_64FC1);
	std::vector<float>data(myLines.size());
 //	for (int i = 0; i < myLines.size(); i++) {
	for (int i = 0; i < 701; i++) {
		cv::Mat img = cv::imread(myLines[i], CV_LOAD_IMAGE_ANYCOLOR);
		/*if (!img.data) {
		cerr << "error in reading image:  " << myLines[i] << endl;
		myUtils::system_pause();
		exit(-1);
		}*/
		if (i==150)
			exitC = 100;
		//resize(img,img,Size(PictureWidth, PictureHeight));

		LQP_EXTRACT_noSave(img, LAST, Dir_initNorm + "cluCenterFile.txt");


		std::vector<double>theta_(NumMaxFrame);
		for (int j = 0; j < NumMaxFrame; j++)
			theta_[j] = (LAST.dot(Im[j])) / (norm(LAST)*(norm(Im[j])));

	
		data[i] = *std::max_element(std::begin(theta_), std::end(theta_));
	


	}


	double Theresold;
	double theta_2 = *std::max_element(std::begin(data), std::end(data));
	cout << "Theta_2:  " << theta_2 << endl;
	Theresold = theta_2;
	
	cout << "Theresold:  " << Theresold << endl;



	return Theresold;
}


double FindTheresoldValueShortTimeVersion(std::vector<Mat>&Im) {

	
	cv::Mat DataALL=LoadMatrix("Database_Normalized" + back_slash + "databaseLQP.txt", 1437, colNum, 0);

	for (int i = 0; i < 1; i++)
		for (int j = 0; j < 30; j++)
			cout << DataALL.at<float>(i, j) << "  ";

	system("pause");
	std::vector<double>theta_(NumMaxFrame);
	std::vector<double>data(1437);
	for (int i = 0; i < 1437; i++) {
		

		
		for (int j = 0; j < NumMaxFrame; j++)
			theta_[j] = (DataALL.row(i).dot(Im[j])) / (norm(DataALL.row(i))*(norm(Im[j])));

		//double theta_1 = *std::max_element(theta_.begin(), theta_.end());
		data[i] = *std::max_element(std::begin(theta_), std::end(theta_));
		cout<<data[i] << endl;

	}


	double Theresold = *std::max_element(std::begin(data), std::end(data));	

	cout << "Theresold:  " << Theresold << endl;

	return Theresold;
}


