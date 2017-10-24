#pragma once
#include"LQP.h"
#include"kmeans_main.h"
#include<time.h>
//const int dimension = 150;

// 3 è il raggio, 48 è la somma dei pixel attorno al pixel centrale (considerando, dato un raggio==3, 7 come lunghezza (e larghezza) del disco)

//clock_t startTime, endTime;
#define OptionG
IplImage* resize1(IplImage *ima);

int finalDimension;


using namespace std;
//int LQP_gen(string imageList, string outputFile, string cluCenterFile, char* option)
int LQP_gen(vector<Mat> imageList, string outputFile, string cluCenterFile, std::vector<Mat>&Im, char* option)
{
	//cout << argc << endl;
	/*if (argc != 5) {
		cerr << "Usage:./extractLQP jpglist outputFile ClucenterFile option(-g=generate codebook,-e=extract LQP for PCA)\n" <<
			"./extractLQP jpglist directory ClucenterFile option(-e2=extract LQP for test)\n"
			"./extractLQP jpglist directory ClucenterFile option(-p extract LQP for pyramid PCA)\n"
			"./extractLQP jpglist directory ClucenterFile option(-p2=extract LQP pyramid for test)" << endl;
		return -1;
	}*/

	/////////////////////////////////////////
	//ifstream ofs; ofs.open("fileList_img.txt", ios::in);
	////////////////////////////////////////
	
	float *result = NULL;
	float **clucenter = NULL;
	float** LQP_vec = NULL;	

	bool optionG = strcmp("-g", option);
	bool optionE = strcmp("-e", option);


	// initialize the file stream
	//ifstream input;
	ifstream clucenterinput;
	ofstream output;
	//input.open(imageList, ios::in);
	output.open(outputFile, ios::out);
	//cout << argv[3] << endl;
	if (!optionE) {
		clucenterinput.open(cluCenterFile, ios::in);
		//if (clucenterinput.is_open())
			//cout << "YES" << endl;
		//system("pause");


		//  Dynamic memory allocation
		clucenter = new float*[dimension];
		for (int i = 0;i != dimension;++i)
		{
			clucenter[i] = new float[48];
		}
		for (int i = 0;i != dimension;++i) {
			for (int j = 0;j != 48;++j) {
				clucenterinput >> clucenter[i][j];
				//system("pause");
				//cout << clucenter[i][j] << "  " ;
			}
		}
		finalDimension = dimension*PictureWidth*PictureHeight / WidthStep / HeightStep;
		result = new float[finalDimension] {0};

		/*LQP_vec = new float*[imageList.size()];
		for (int i = 0;i != imageList.size();++i)
		{
			LQP_vec[i] = new float[finalDimension];
		}*/		

	}
	//cout << endl;
	
	//cout << finalDimension << endl;
	
	//double *result;
	// la dimensione la posso consderare come fissa xkè la dim delle immagini è sempre la stessa in teoria...
	//double copy_result[18000];
	//for (int i = 0;i<finalDimension;i++)
	//copy_result[i] = 0;
	// inizialize array...
	//std::fill_n(copy_result, finalDimension, 0);
	//double * p;  double s[2] = {1,2}; p = &s[0];
	//result = &copy_result[0];


	//system("cls");

	// input the pictures
	IplImage* img = NULL;
	//IplImage* input_img = NULL;
	//char jpgname[100];
	string jpgName;
	//strng fileListName;

	//startTime = clock();

		//while (ofs >> fileListName) {
	//input.open(argv[1], ios::in);
	//cout << "--------------------------------------------------" << endl;
	//cout << fileListName << endl;
	//cout << "--------------------------------------------------" << endl;
	//input.clear();
	//input.seekg(0, ios::beg);
	//for (int i = 0;i<40;i++) {
		//jpgName = jpgName.erase();
	for (int i = 0; i < imageList.size();i++){
	//while (input >> jpgName){

		//cout << "jpgName:  "<<jpgName << endl;
		//jpgName = "myImages\\" + jpgName;			
		//jpgName = "Gabor\\"+fileListName +"\\"+ jpgName;
		
		//jpgName = "images\\" + jpgName;

		//char *jpgname = new char[jpgName.length() + 1];
		//strcpy(jpgname, jpgName.c_str());
		
		// do stuff
		//img = cvLoadImage(jpgName.c_str());
		//img = cvLoadImage(imageList[i].c_str());
		//cvShowImage("", img); cvWaitKey(0);
		img= cvCloneImage(&(IplImage)imageList[i]);
		if (!img) {
		cerr << "error in reading image:  " << jpgName << endl;
		return -1;
		}
		
		//img = resize1(img);
		//img=input_img;
		LQP a(img);

		//for (int u = 0;u < 20;u++)
			//cout << (int)CV_IMAGE_ELEM(img, uchar, 59, 59) << endl;
			//cout << pixval8(img, 57, 49) << endl;
			
		//system("pause");

		if (optionG == false)
		{
			//cout << "Option-g" << endl;

			float* LQP_train = new float[48];
			for (int i = 0;i != 48;i++)
				*(LQP_train + i) = 0;
			//cout << "G " << endl;
			a.cal_LQP(3, output);                //used for generating codebook			
			//cout << *LQP_train << endl;
			//cv::Mat bestLabels;
			//cv::kmeans(*LQP_train, 150, bestLabels, cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 1.0), 10, CV_KMEANS_USE_INITIAL_LABELS);

			//cout << bestLabels.size();
//			output << bestLabels;
		}
		else if (optionE == false)
			//if (optionE == false)
		{
			//cout << "Option-e" << endl;
			//cout << "finalDimension  " << finalDimension << endl;
			// calculate LQP histogram
			//copy_result[0] = 0;
			//result = copy_result;
			//cout << "copy_res   "<<copy_result[0] << "  " << copy_result[finalDimension-1] << endl;
			//cout <<"res  "<< result[0] << "  " << result[1] << "  " << result[10] << "  " << result[100] << "  " << result[finalDimension] << endl;
			
			//for (int i = 0;i < finalDimension;i++)
				//result[i] = 0;
			//memset(result, 0, sizeof(int)*finalDimension);
			std::fill(result, result + finalDimension, 0);

			a.cal_LQP_histogram(3, 48, clucenter, dimension, result);
			for (int j = 0;j < finalDimension;j++) {
												   //if (*(result + i) != 0)
				output << *(result + j) << " ";			

			//LQP_vec[i][j] = *(result + j);


			}
			
			output << endl;
			//cout << "here  " << endl;
			Mat T=Mat(1, finalDimension, CV_32FC1, result);
			T.copyTo(Im[i]);
			//Im[i] = Mat(&result, 1);
			//cout << "IM []   " << Im[i].size() << endl;
						

			Scalar mean, std;
			//for (int i = 0; i < imageList.size(); i++) {
			meanStdDev(Im[i], mean, std);
			Im[i].convertTo(Im[i], -1, 1 / std[0], -mean[0] / std[0]);
			//}

			
		}
		else
		{
			cerr << "wrong option (-g=generate codebook,-e=extract LQP feature)" << endl;
			return -1;
		}
		//cout << jpgname << endl;
		//delete[] result;



	}
	
		
	

	//}

	/*endTime = clock();
	cout << "\n\n\nGenerating Table took " << double(endTime - startTime) / double(CLOCKS_PER_SEC) << "s  ---  " << (double(endTime - startTime) / double(CLOCKS_PER_SEC)) / 60 << "min." << endl;
	system("pause");*/

	if (optionE == false) {

/*		Mat LQP_array = Mat(imageList.size(), finalDimension, CV_32FC1,LQP_vec);
		ofstream c; c.open("data.txt", ios::out);
		for (int i = 0; i < imageList.size(); i++) {
			for (int j = 0; j < finalDimension; j++)
				c << LQP_array.at<float>(i, j) << "  ";
			c << endl;
		}
*/		

		// Dynamic memory dispose
		delete[] result;
		for (int i = 0;i != dimension;++i)
		{
			delete[] clucenter[i];
		}
		delete[] clucenter;

		clucenterinput.close();

	}

	//input.close();
	output.close();
	/*if (optionE == false) {
		cout << "DHJFFDHGHLHDFGQLDHHDGHJDHGFDHFHGWGHFDG" << endl;
		//for (int j = 0; j < 6;j++) {
			for (int i = 0;i < 50;i++)
				cout << Im[5].at<float>(0, i) << "  ";
			//cout << "J  " << j << endl << endl;
		//}
	}*/
	return 0;
}






IplImage* resize1(IplImage *ima)
{
	if (!ima) { cerr << "could not open image" << endl; }


	// resize the image
	IplImage *dst = 0;
	CvSize dst_cvsize;
	dst_cvsize.width = PictureWidth;
	dst_cvsize.height = PictureHeight;
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
		//cvShowImage("res.jpg", imaMid);cvWaitKey(0);
		//              cvSaveImage("res.jpg",imaMid);
		return imaMid;
	}
	else
		cerr << "resize error" << endl;

}

inline void LQP_EXTRACT_noSave(Mat image, Mat &faces, string cluCenterFile)
{

	float *result = NULL;
	float **clucenter = NULL;
	float** LQP_vec = NULL;
	

	// initialize the file stream

	ifstream clucenterinput;

		clucenterinput.open(cluCenterFile, ios::in);

		//  Dynamic memory allocation
		clucenter = new float*[dimension];
		for (int i = 0;i != dimension;++i)
		{
			clucenter[i] = new float[48];
		}
		for (int i = 0;i != dimension;++i) {
			for (int j = 0;j != 48;++j) {
				clucenterinput >> clucenter[i][j];
				//system("pause");
				//cout << clucenter[i][j] << "  " ;
			}
		}
		finalDimension = dimension*PictureWidth*PictureHeight / WidthStep / HeightStep;
		result = new float[finalDimension] {0};


	
	//img = resize1(img);
	IplImage* img = cvCloneImage(&(IplImage)image);
	LQP a(img);

	/*
	cout << finalDimension << "  dim: " << dimension << endl;


	for (int i = 0;i != dimension;++i) {
	//for (int j = 0;j != 48;++j) {
	cout<<clucenter[i][0]<<" ";
	//system("pause");
	//cout << clucenter[i][j] << "  " ;
	}
	//}
	cout << endl;
	*/

	//for (int i = 0;i < finalDimension;i++)
	//result[i] = 0;
	std::fill(result, result + finalDimension, 0);
	a.cal_LQP_histogram(3, 48, clucenter, dimension, result);
	//double * k = &res.at<double>(0);
	//for (int i = 0;i < finalDimension;i++) {
	//output << *(result + i) << " ";
	faces = Mat(1, finalDimension, CV_32FC1, result);
	//Mat Data = Mat(1, finalDimension, CV_32FC1, result);
	//cout << Data.size() << endl;
	//k[i] = *(result + i);

	//}
	Scalar mean, std;
	//for (int i = 0; i < faces.cols; i++) {
	meanStdDev(faces, mean, std);
	faces.convertTo(faces, -1, 1 / std[0], -mean[0] / std[0]);
	//}


	//Data = cv::Mat(Data_array);
	//Data = Data.reshape(1, 1);

	// Dynamic memory dispose
	/*
	delete[] result;

	for (int i = 0;i != dimension;++i)
	{
	delete[] clucenter[i];
	}
	delete[] clucenter;
	*/

	//clucenterinput.close();
	//output.close();

	//return Data;
}