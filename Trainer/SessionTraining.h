#pragma once

#include <QtCore/qcoreapplication.h>
#include <QtConcurrent/qtconcurrentrun.h>
#include <QtCore/QThread>

#include <math.h>

#include"InitProc.h"

#include "eyesFinder.h"

#include<fstream>
//#include "Gabor.h"
#include "LQP_main.h"
#include "PCA_Whitening.h"

#include "Enhancer.h""


int64 StartTime, endTime;

extern string back_slash;
extern cv::String WINDOW_NAME;

extern string Dir_initNorm;


//int NumMaxFrame = 20;
//int NumMaxFrame = 2;
int NumMaxFrame = 2;
extern string cascade_face;
//const cv::String WINDOW_NAME;
std::vector<float>r_sizes(NumMaxFrame);




int colNum = (PictureWidth*PictureHeight * 50) / 10 / 10; int rowNum = 1;
cv::VideoCapture camera;



double alpha_ = 0.5; double beta_ = (1.0 - alpha_);


extern vector<Mat>Mat_imagesCountDown;
extern Mat red;
extern float normWidth, normHeight;
extern int window_width;
extern int window_height;



int sessionTraining(VideoFaceDetector detector){

	int tent = 0;

	//int colNum = 21600; int rowNum = 1; int indexMin = 0;	

	int countFrame = 0;
	bool trained = FALSE;
	int centre_x = 0;int centre_y = 0;

	cv::Mat frame, frame2;
	Mat *frame_pointer; frame_pointer = &frame;
	Rect r;	Rect *r_pointer; r_pointer = &r;

	int done = 1;


Mat frame_copy_resized;

int f = 0;

Mat dst;
Mat img;



double alpha = 0.5; double beta = (1.0 - alpha);


while (countFrame < NumMaxFrame) {

	// cattura frame		
	detector.SecureVideoCapt(frame);
	detector.getFrameAndDetect(frame);
	r = detector.face();
	r.x = detector.facePosition().x - r.width *0.32; r.y = detector.facePosition().y - r.height *0.3; r.width = 2 * (r.width *0.31); r.height = (r.height * 0.68);

	modifyDrawnRect(frame, r, cv::Scalar(255, 0, 255, 0));
	// face position è il centro del rettangolo
	cv::circle(frame, detector.facePosition(), 2, cv::Scalar(255, 0, 0, 0), 5, 10);

	cv::flip(frame, frame, 1); // effetto specchio

	resize(frame, frame_copy_resized, cvSize(windowSizeWidth, windowSizeHeight));

	if (r.width > 225 || r.width <= 170) {
		addWeighted(frame_copy_resized, alpha, red, beta, 0.0, frame_copy_resized);
	}




	//#ifdef WIN32
	if (cv::waitKey(1) == 27) {
		if (newDataFolder == true)
			thesis::delete_folder_no_Console(Dir_initNorm);

		return 0;
	}
	//#endif

	if (countFrame == 0) {
		myUtils::CleanActions(directory_Norm + Data);
		//if (cv::waitKey(1) == 32)  // premi space bar

		if (tent == 0) {
			for (int i = 0; i < Mat_imagesCountDown.size(); i++) {
				detector.VideoCapt(frame_copy_resized);
				detector.getFrameAndDetect(frame_copy_resized);
				//imshow("", frame_copy_resized); waitKey(0);
				r = detector.face();
				r.x = detector.facePosition().x - r.width *0.32; r.y = detector.facePosition().y - r.height *0.3; r.width = 2 * (r.width *0.31); r.height = (r.height * 0.68);
				//cout << "RRR  " << r << endl;
				while (r.width > 225 || r.width <= 170) {
					resize(frame_copy_resized, frame_copy_resized, cvSize(windowSizeWidth, windowSizeHeight));
					flip(frame_copy_resized, frame_copy_resized, 1);
					myUtils::DigitalZoom_FC(frame_copy_resized, detector.facePosition(), 1.3);
					//putText(frame_copy_resized, "bbsbgfdgbg", Point(240, 175), CV_FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255, 0), 2, CV_AA);
					addWeighted(frame_copy_resized, alpha, red, beta, 0.0, frame_copy_resized);
					//myUtils::playSound("wrong2.wav");						
					Mat divieto = imread("resources"+back_slash+"other" + back_slash + "divieto.png", CV_LOAD_IMAGE_ANYCOLOR);
					resize(divieto, divieto, frame_copy_resized.size());
					addWeighted(frame_copy_resized, alpha, divieto, beta, 0.0, frame_copy_resized);
					cv::imshow(WINDOW_NAME, frame_copy_resized); waitKey(1);

					if (cv::waitKey(10) == 27) {
						if (newDataFolder == true)
							thesis::delete_folder_no_Console(Dir_initNorm);
						return 0; // stop capturing by pressing ESC 
					}

					detector.VideoCapt(frame_copy_resized);
					detector.getFrameAndDetect(frame_copy_resized);
					//imshow("", frame_copy_resized); waitKey(0);
					r = detector.face();
					r.x = detector.facePosition().x - r.width *0.32; r.y = detector.facePosition().y - r.height *0.3; r.width = 2 * (r.width *0.31); r.height = (r.height * 0.68);
					//cout << "RRR  " << r << endl;  
				}
				modifyDrawnRect(frame_copy_resized, r, cv::Scalar(255, 0, 255, 0));
				cv::circle(frame_copy_resized, detector.facePosition(), 2, cv::Scalar(255, 0, 0, 0), 5, 10);
				resize(frame_copy_resized, frame_copy_resized, cvSize(windowSizeWidth, windowSizeHeight));
				flip(frame_copy_resized, frame_copy_resized, 1);
				myUtils::DigitalZoom_FC(frame_copy_resized, detector.facePosition(), 1.3);
				addWeighted(frame_copy_resized, alpha, Mat_imagesCountDown[i], beta, 0.0, frame_copy_resized);
				cv::imshow(WINDOW_NAME, frame_copy_resized); waitKey(1);
				tent = 1;

				if (cv::waitKey(10) == 27) {
					if (newDataFolder == true)
						thesis::delete_folder_no_Console(Dir_initNorm);
					return 0; // stop capturing by pressing ESC 
				}
			}
		}
		if (r.width > 225 || r.width <= 170) {
			addWeighted(frame_copy_resized, alpha, red, beta, 0.0, frame_copy_resized);
		}
		else
			done = 0;


	}
	else {

		done = 0;

	}


	if (done == 0) {

		cv::destroyWindow(WINDOW_NAME);
		if (countFrame == 0) {
			myUtils::playSound("camera_shutter_cutted.wav");
			//cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
			QFuture<void> t1 = QtConcurrent::run(myRunFunction, camera, detector);
		}


		bool eyes = false; int it = 0;

#ifndef WIN32
		cv::destroyWindow(WINDOW_NAME);
		waitKey(1);
		int t = cvStartWindowThread();
		//scout<<"Thread:  "<<t<<endl;
#endif
		Rect r2;
		while (!eyes && it<50) {
			//cout << "It:  " << it << endl;
			try {

				detector.VideoCapt(frame);
				detector.getFrameAndDetect(frame);

				r = detector.face();
				r2 = r;
				r2.x = detector.facePosition().x - r2.width *0.32; r2.y = detector.facePosition().y - r2.height *0.3; r2.width = 2 * (r2.width *0.31); r2.height = (r2.height * 0.68);

				if (r2.width < 225 && r2.width > 170) {


					if (detector.isFaceFound()) {

						cvtColor(frame, frame, CV_RGB2GRAY);
						//auto start = cv::getCPUTickCount();

						frame = findEyes(frame_pointer, r_pointer, detector.facePosition(), eyes, it, countFrame);
						cout << "post:  " << *r_pointer << endl;
						//imshow("", frame); waitKey(0);
						//system("pause");

					}
					it++;
				}


			}
			catch (cv::Exception& e) {
				cerr << "Error Reason: " << e.msg << endl;
				eyes = false;
				it--;
			}

		}



		r_sizes[countFrame] = r2.width;
		//outputList << *r_pointer;
		//imwrite("Original.bmp", frame2);
		cout << *r_pointer << " ---rr-- " << r2 << endl;

		resize(frame, frame, Size(PictureWidth, PictureHeight));

		Scalar meanFrame, stdFrame;
		meanStdDev(frame, meanFrame, stdFrame);
		//outputList << "  --   mean:  " << meanFrame[0] << endl;

		Mat frame2_Norm; frame.copyTo(frame2_Norm);

		countFrame++;
		cout << "countFrame   " << countFrame << endl;

		//if (countFrame <= NumMaxFrame) {
		f = Enhancer(AllMat, rowNum, colNum, frame2_Norm, countFrame, NumMaxFrame);
		//}
		//if (countFrame == NumMaxFrame) {
		//imwrite(Dir_initNorm + "Last_Norm.bmp", frame2_Norm);
		fileList.close();
		done = 1;

		if (f == -1)
			break;
	}

	else {
		myUtils::DigitalZoom_FC(frame_copy_resized, detector.facePosition(), 1.3);
		cv::imshow(WINDOW_NAME, frame_copy_resized);

		if (cv::waitKey(1) == 27) {
			if (newDataFolder == true)
				thesis::delete_folder_no_Console(Dir_initNorm);
			break; // stop capturing by pressing ESC 
		}
	}

}


if (f == -1) {
	/*system("pause");
	cout << "bdggfhbgbdgbhdfgbn" << endl;*/
	return -1;
}

saveVector(("Database_Normalized" + back_slash + Data + back_slash + "meanBox.data"), r_sizes);

/*
string DirToCopyNorm = current_path + "Database_Normalized" + back_slash + Data + back_slash;
//cout << DirToCopyNorm << endl;
string folderToCopyNorm = Data + back_slash;

string DirWhereToCopyNorm = current_path_prefix + back_slash + "Recognizer" + back_slash + "Database_Normalized" + back_slash + Data + back_slash;
//cout << DirWhereToCopyNorm << endl;


//myUtils::CleanDirectoryList(DirWhereToCopyNorm);


//system_pause();
saveVector((DirToCopyNorm + "meanBox.data"), r_sizes);
myUtils::__CopyDirectory(DirToCopyNorm.c_str(), (DirWhereToCopyNorm).c_str());


myUtils::__CopyDirectory(DirToCopyNorm.c_str(), ("C:\\Users\\Valerio\\Documents\\Visual Studio 2015\\Projects\\OpenCV\\Thesis_projects\\FaceRecognitionSystem\\Testing_Procedure\\Testing_Procedure\\Database_Normalized\\" + Data + "\\").c_str());


myUtils::__CopyDirectory(DirToCopyNorm.c_str(), ("C:\\Users\\Valerio\\Documents\\Visual Studio 2015\\Projects\\OpenCV\\Thesis_projects\\FaceRecognitionSystem\\ufi_cropped\\ufi_cropped\\Database_Normalized\\" + Data + "\\").c_str());
//cout<<"copy Done"<<endl;
//system_pause();

if (TRAIN == TRUE) {
//cout << "TARIN" << endl;
// Copy LQP_trained file...


string copyLQP = current_path + "LQP_TRAINED_output.txt";
//cout<<copyLQP<<endl;
string WherecopyLQP = current_path_prefix + back_slash + "Recognizer" + back_slash + "Database_Normalized" + back_slash + "LQP_TRAINED_output.txt";
//cout<<WherecopyLQP<<endl;
//system("pause");

myUtils::copyFile(copyLQP, WherecopyLQP);

myUtils::copyFile(copyLQP, "C:\\Users\\Valerio\\Documents\\Visual Studio 2015\\Projects\\OpenCV\\Thesis_projects\\FaceRecognitionSystem\\Testing_Procedure\\Testing_Procedure\\Database_Normalized\\LQP_TRAINED_output.txt");

myUtils::copyFile(copyLQP, "C:\\Users\\Valerio\\Documents\\Visual Studio 2015\\Projects\\OpenCV\\Thesis_projects\\FaceRecognitionSystem\\ufi_cropped\\ufi_cropped\\Database_Normalized\\LQP_TRAINED_output.txt");
}
*/

while (!fexists("tt.txt")) {};


thesis::delete_file("tt.txt");

#ifdef _WIN32
//system("cls");
////ShowWindow(GetConsoleWindow(), SW_HIDE);		
int ret = messageBox("", 3);
switch (ret) {

case QMessageBox::Ok: {
	//system("aplay resources/sounds/click.wav --quiet");
	myUtils::playSound("click.wav");
	break;
}break;
default:
	// should never be reached
	break;
}
#else
//system("clear");
ret = messageBox("T R A I N I N G  -- T E R M I N A T O !\n", 3);
myUtils::playSound("click.wav");


#endif


}