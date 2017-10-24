#pragma once
#include <iostream>
#include "myUtils.h"


#include "Qt_messageBox.h"
#include<QtWidgets/qdesktopwidget.h>

using namespace std;

#ifdef _WIN32
string back_slash = "\\";
#else
string back_slash = "/";
#endif

string init_path = "";
//string cascade_face = "resources" + back_slash + "haarcascade_frontalface_default.xml";
string cascade_face = "resources" + back_slash + "haarcascade_frontalface_alt.xml";
string directory_Norm = "Database_Normalized" + back_slash;
string Dir_initNorm;

bool TRAIN = FALSE;
ofstream fileList;
std::vector<cv::Mat>AllMat;
//ofstream outputList;

string current_path, search_path;
string Time, Data;


extern int NumMaxFrame;
extern int colNum; 
extern int rowNum;
extern cv::VideoCapture camera;

string WINDOW_NAME;
const cv::String WINDOW_REC = "Window_Rec";

extern int exitC;
extern float percentuage;

extern double alpha_; extern double beta_;



float normWidth, normHeight;
int window_width = 480;
int window_height = 350;

int window_width_laserScreen = 250;
int window_height_laserScreen = 320;

int native_width = 1920;
int native_height = 1080;

int windowSizeWidth;
int windowSizeHeight;

vector<Mat>Mat_imagesCountDown, green_laser, Mat_spinners;
Mat red;


cv::String setFrame_properties(string Title = "Camera-training");
void loadImagesForGUI();

bool newDataFolder = false;

void changeDir(string search_path, string& current_path) {

	ifstream readPath; readPath.open(search_path.c_str(), ios::in);
	while (std::getline(readPath, current_path)) {
		readPath >> current_path;
	
	}
	readPath.close();
	

	if (!thesis::isDirectory(current_path)) {
		messageBox("Non risulta effettuato alcun setup! Impossibile continuare!", 5);
		myUtils::playSound("click.wav");
		return;
	}

	
	_chdir(current_path.c_str());
	


}


void PrelminarySetts(string& current_path, string& search_path) {


	myUtils::getSysLanguage(Sys_language);	

	char cCurrentPath[FILENAME_MAX];

#ifdef _WIN32

	GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
	current_path = cCurrentPath;	

	init_path = current_path.substr(0, current_path.find_first_of("\\"));

	// gli indico praticamente doe si trova la cartella platforms...
	QCoreApplication::addLibraryPath(QString::fromLocal8Bit((init_path + back_slash + "Windows" + back_slash + "System32").c_str()));
	

	//search_path = init_path + back_slash + "Windows" + back_slash + "System32" + back_slash + "FaceRec_SystemPathDevelopment";
	search_path = init_path + back_slash + "ProgramData" + back_slash + "FaceAuthenticationSystem" + back_slash + "FaceRec_SystemPathDevelopment";
#else
	getcwd(*cCurrentPath, sizeof(cCurrentPath));
	current_path = *cCurrentPath;

	// gli indico praticamente doe si trova la cartella platforms...
	QCoreApplication::addLibraryPath(QString::fromLocal8Bit((init_path + back_slash + "usr" + back_slash + "lib" + back_slash + "x86_64-linux-gnu").c_str()));

	string init_path = "";
	string search_path = init_path + back_slash + "usr" + back_slash + "lib" + back_slash + "x86_64-linux-gnu" + back_slash + "FaceRec_SystemPathDevelopment";
	//cout<<"search_path:  "<<search_path<<endl;
#endif

	/*GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
	cout << cCurrentPath << endl;
	cout<<myUtils::fexists("resources" + back_slash +"Antispoof" + back_slash + "mappingTable_16pts.txt") << endl;
	cout << "resources" + back_slash + "Antispoof" + back_slash + "mappingTable_16pts.txt" << endl;
	cout << myUtils::fexists("Database_Normalized" + back_slash + "Theresold" + back_slash + "1a.jpg.bmp") << endl;
	cout << myUtils::fexists("resources" + back_slash + "icons" + back_slash + "Recognizer.ico") << endl;
	system("pause");*/
	

	if (!myUtils::fexists(search_path)) {

		if (!myUtils::fexists("resources" + back_slash + "Antispoof" + back_slash + "mappingTable_16pts.txt") || !myUtils::fexists("Database_Normalized" + back_slash + "Theresold" + back_slash + "1a.jpg.bmp") || !myUtils::fexists("resources" + back_slash + "other" + back_slash + "divieto.png") || !myUtils::fexists("resources" + back_slash + "icons" + back_slash + "Recognizer.ico")) {
			//cout << "AAAAAAAAAAAAAAAAAAAAAA" << endl;
			messageBox("Non risulta effettuato alcun setup! Impossibile continuare!", 5);
			//myUtils::playSound("click.wav");
			//return false;
			exit(-1);
		}

		else {
			if (!thesis::isDirectory(init_path + back_slash + "ProgramData" + back_slash + "FaceAuthenticationSystem"))
				thesis::make_dir((init_path + back_slash + "ProgramData" + back_slash + "FaceAuthenticationSystem").c_str());
			//cout << "GGGGGGGGGGGGGGG" << endl;
			GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
			string path = cCurrentPath;
			ofstream file; file.open((search_path).c_str());
			file << path << endl;
			file.close();

		}

	}
	else {
		ifstream readPath; readPath.open(search_path.c_str(), ios::in);
		while (std::getline(readPath, current_path)) {
			readPath >> current_path;
			//cout << current_path << endl;
			//system("pause");
		}
		readPath.close();

		if (!thesis::isDirectory(current_path)) {
			messageBox("Non risulta effettuato alcun setup! Impossibile continuare!", 5);
			//myUtils::playSound("click.wav");
			//return false;
			exit(-1);
		}
		else {
			//cout << "HERE" << endl;
			//current_path = init_path + back_slash + "FR" + back_slash;
			_chdir(current_path.c_str());
#ifdef _WIN32
			//GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
			//cout << cCurrentPath << endl;
			//system("pause");
			//cout << current_path << endl;
#else
			getcwd(cCurrentPath, sizeof(cCurrentPath));
			current_path = cCurrentPath;
			//cout << "cuurent path 1:  " << current_path << endl;
#endif
		}

	}







	/*
	if (!myUtils::fexists(search_path) && !myUtils::fexists("Database_Normalized"+back_slash+"Theresold" + back_slash + "1a.jpg.bmp") && !myUtils::fexists("resources" + back_slash + "other" + back_slash + "divieto.png")) {
		messageBox("Non risulta effettuato alcun setup! Impossibile continuare!", 5);

		exit(-1);
	}
	else

	changeDir(search_path, current_path);*/


}





int checkForTrainedFile(string current_path) {


	int Trained_AlreadyDone = 0;
	int numDir; std::vector<string> dirList;
	if (myUtils::numDirectoryList_2(current_path + back_slash + "Database_Normalized", numDir, dirList) <= 3) {

		Trained_AlreadyDone = -1;
	}
	else {
		string toFind = "-2017"; int countList = 0;
		for (int i = 0; i < numDir; i++) {
			if (dirList[i].length() >= 5 && dirList[i].substr(dirList[i].length() - 5, dirList[i].length()) != toFind) {

				countList++;
			}
			else if (dirList[i].length() >= 5 && dirList[i].substr(dirList[i].length() - 5, dirList[i].length()) == toFind) {

				if (myUtils::numFileListInDirectory(current_path + back_slash + "Database_Normalized" + back_slash + dirList[i])==0) {

					countList++;
				}
			}

		}

		if (countList == numDir - 2) {   // le prime due solo folder di sistema...
			Trained_AlreadyDone = -1;

		}

	}

	return Trained_AlreadyDone;
}


cv::VideoCapture camera_actions(int Trained_AlreadyDone, bool TRAIN, ofstream &fileList) {


	// Open webcam
	cv::VideoCapture camera(0);
	if (!camera.isOpened()) {

#ifdef _WIN32
		messageBox("", 1);
		myUtils::playSound("click.wav");
		exit(-1);
#else
		int ret = messageBox("ERRORE nell'apertura della web-cam!", 1);
		myUtils::playSound("click.wav");
		return -1;
#endif
	}

	
#ifdef _WIN32
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
	int ret, ret2; int discard = 1;

	while (discard) {

		if (Trained_AlreadyDone == 0)
			//ret = messageBox("SI VUOLE EFFETTUARE UN NUOVO TRAINING ?\n", 2);
			//ret = messageBox("SI STA PER AVVIARE UNA NUOVO ENROLLING.\n", 2);
			ret = messageBox("No training", 2);
		else
			ret = messageBox("", 2);

		switch (ret) {



		case QMessageBox::Ok: {
			//system("aplay resources/sounds/click.wav --quiet");
			myUtils::playSound("click.wav");
			TRAIN = TRUE;
			if (myUtils::fexists(directory_Norm + "FileList_2.txt") == TRUE)
				thesis::delete_file((directory_Norm + "FileList_2.txt").c_str());

			fileList.open((directory_Norm + "FileList_2.txt").c_str(), ios::app);

#ifdef _WIN32
			//ShowWindow(GetConsoleWindow(), SW_RESTORE);
#endif


			ret2 = messageBox("", 7);
			if (ret2 == QMessageBox::Ok) {
				myUtils::playSound("click.wav");
				discard = 0;
			}
			else if (ret2 == QMessageBox::Discard) {
				myUtils::playSound("click.wav");
				discard = 1;
			}
			else {
				myUtils::playSound("click.wav");
				camera.release();
				exit(-1);
			}							
			

		}break;
		case QMessageBox::Cancel: {
			//system("aplay resources/sounds/click.wav --quiet");
			myUtils::playSound("click.wav");
			discard = 0;
			camera.release();
			//QApplication::quit();
			//exit(EXIT_FAILURE);
			exit(-1);
		}break;
		default:
			// should never be reached
			break;
		}
		//#endif
	}


	return camera;

}




void setGeometries() {

	QRect rec = QApplication::desktop()->screenGeometry();
	normWidth = std::round((rec.width() / native_width));
	
	normHeight = std::round((rec.height() / native_height));


	windowSizeWidth = normWidth*window_width;
	windowSizeHeight = normHeight*window_height;
}


cv::VideoCapture Inits() {

	int Trained_AlreadyDone = checkForTrainedFile(current_path);	
	

	std::vector<cv::Mat> faces(NumMaxFrame + 1);


	for (int i = 0;i < NumMaxFrame + 1;i++) {
		faces[i] = Mat(rowNum, colNum, CV_32FC1);	
	}
	
	setGeometries();	
	
	loadImagesForGUI();


	camera = camera_actions(Trained_AlreadyDone, TRAIN, fileList);
	
	WINDOW_NAME = setFrame_properties();
	
	if (myUtils::timeData(Time, Data))
		newDataFolder = true;
	Dir_initNorm = "Database_Normalized" + back_slash + Data + back_slash;
	
	//outputList.open((directory_Norm + Data + back_slash + "OutputList_2.txt").c_str(), ios::out);

	return camera;

}


cv::String setFrame_properties(string Title) {

	const cv::String WINDOW_NAME(Title);

	cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);

	int width = (normWidth*native_width) / 2 - (window_width / 2);

	cv::moveWindow(WINDOW_NAME, width, 0);


	return WINDOW_NAME;
}




void myRunFunction(cv::VideoCapture camera, VideoFaceDetector detector)
{


	cv::destroyWindow(WINDOW_NAME);

	cv::namedWindow(WINDOW_REC);

	int width = std::round(normWidth*native_width)/ 2 - (normWidth*window_width_laserScreen / 2);

	int height = 0;

	cv::moveWindow(WINDOW_REC, width, height);

	int done = 1;
	cv::Mat frame, image;
	Mat green_perc;

	while (1) {

		if (exitC == 1)
		{
			ofstream tt;
			frame.copyTo(image);			
			Mat K = imread("resources" + back_slash + "other" + back_slash + "tick.png", CV_LOAD_IMAGE_ANYCOLOR);
			resize(K, K, image.size());
			addWeighted(frame, alpha_, K, beta_, 0.0, frame);
			cv::imshow(WINDOW_REC, frame);
			waitKey(500);

			destroyAllWindows();
			tt.open("tt.txt", ios::out);
			tt.close();

			break;

		}
		else if (exitC == 100) {
			ofstream tt;
			tt.open("tt.txt", ios::out);
			tt.close();

			for (int i = 0; i < Mat_spinners.size(); i++) {

				cv::imshow(WINDOW_REC, Mat_spinners[i]);
				waitKey(1);

			}
		}
		else {

			int ii = 0; int jj = 0;

			for (int i = 0; i < green_laser.size(); i++) {

				try {
					detector.VideoCapt(frame);
					detector.getFrameAndDetect(frame);
				}
				catch (cv::Exception& e) {
	            cerr << "Error Reason_2: " << e.msg << endl;
				if (i > 0)
					i--;
				else
					i = 0;

				cout << "iiii:    " << i<<endl;

				Mat ALLred = Mat(cvSize(frame.cols, frame.rows), CV_8UC3, Scalar(0, 0, 255));
				addWeighted(frame, alpha_, ALLred, beta_, 0.0, frame);
				//myUtils::modifyDrawnRect(frame, r, cv::Scalar(255, 0, 255, 0));
				//cv::circle(frame, detector.facePosition(), 2, cv::Scalar(255, 0, 0, 0), 5, 10);

				Mat divieto = imread("resources"+ back_slash +"other"+back_slash+"divieto.png", CV_LOAD_IMAGE_ANYCOLOR);
				resize(divieto, divieto, frame.size());				
				addWeighted(frame, alpha_, divieto, beta_, 0.0, frame);
				resize(frame, frame, cvSize(normWidth*window_width_laserScreen, normHeight*window_height_laserScreen));
				flip(frame, frame, 1);
				cv::imshow(WINDOW_REC, frame);
				waitKey(1);
				ofstream stop; stop.open("stop", ios::out);
				stop.close();


				}
				Point face = detector.facePosition();
				Rect r = detector.face();
				r.x = face.x - r.width *0.32; r.y = face.y - r.height *0.3; r.width = 2 * (r.width *0.31); r.height = (r.height * 0.68);
				frame.copyTo(image);
				//cout << "r:   " << r << endl;
				if (r.width > 225 || r.width <= 170) {

					i--;

					Mat ALLred = Mat(cvSize(frame.cols, frame.rows), CV_8UC3, Scalar(0, 0, 255));
					addWeighted(frame, alpha_, ALLred, beta_, 0.0, frame);
					//myUtils::playSound("wrong2.wav");
					myUtils::modifyDrawnRect(frame, r, cv::Scalar(255, 0, 255, 0));
					cv::circle(frame, detector.facePosition(), 2, cv::Scalar(255, 0, 0, 0), 5, 10);

					Mat divieto = imread("resources" + back_slash + "other" + back_slash + "divieto.png", CV_LOAD_IMAGE_ANYCOLOR);
					resize(divieto, divieto, frame.size());
					addWeighted(frame, alpha_, divieto, beta_, 0.0, frame);
					resize(frame, frame, cvSize(normWidth*window_width_laserScreen, normHeight*window_height_laserScreen));
					flip(frame, frame, 1);
					cv::imshow(WINDOW_REC, frame);
					waitKey(1);
					ofstream stop; stop.open("stop", ios::out);
					stop.close();

					if (cv::waitKey(10) == 27) {
						destroyAllWindows();
						exitC = -1; return;

					}
				}
				else {
					if (myUtils::fexists("stop"))
						thesis::delete_file("stop");

					detector.VideoCapt(frame);
					detector.getFrameAndDetect(frame);
					Point face = detector.facePosition();
					resize(frame, frame, cvSize(normWidth*window_width_laserScreen, normHeight*window_height_laserScreen));
					myUtils::DigitalZoom_FC(frame, face, 1.5);

					if (i < 25) {
						frame.copyTo(image);

						if (i == 0) {

							green_perc = Mat(image.rows, image.cols * 0.03, CV_8UC3, Scalar(0, 155, 0));
							green_perc.copyTo(image(Rect(0, 0, green_perc.cols, green_perc.rows)));
						}
						else if (i < 13) {
							green_perc = Mat(image.rows, image.cols*((jj + 1) * 7) / 100, CV_8UC3, Scalar(0, 155, 0));
							green_perc.copyTo(image(Rect(0, 0, green_perc.cols, green_perc.rows)));
						}
						else {
							green_perc = Mat(image.rows, abs(image.cols - image.cols* ((jj + 1) * 8) / 100), CV_8UC3, Scalar(0, 155, 0));
							green_perc.copyTo(image(Rect(image.cols - green_perc.cols, 0, green_perc.cols, green_perc.rows)));
						}

						jj++;
					}
					else {
						frame.copyTo(image);

						if (i == 25 || i == 26) {
							green_perc = Mat(image.rows * 0.02, image.cols, CV_8UC3, Scalar(0, 155, 0));
							
							green_perc.copyTo(image(Rect(image.cols - green_perc.cols, 0, green_perc.cols, green_perc.rows)));
						}
						else if (i>26 && i< (26 + 13)) {
							green_perc = Mat(image.rows*((ii + 1) * 7) / 100, image.cols, CV_8UC3, Scalar(0, 155, 0));							
							green_perc.copyTo(image(Rect(image.cols - green_perc.cols, 0, green_perc.cols, green_perc.rows)));
						}
						else {
							green_perc = Mat(abs(image.rows - image.rows* ((ii + 1) * 7) / 100), image.cols, CV_8UC3, Scalar(0, 155, 0));
							green_perc.copyTo(image(Rect(0, image.rows - green_perc.rows, green_perc.cols, green_perc.rows)));							
						}

						ii++;
					}
					addWeighted(image, alpha_, green_laser[i], beta_, 0.0, image);

					addWeighted(image, alpha_, frame, beta_, 0.0, frame);


					if (exitC == 1 || exitC == 100) {
						i = green_laser.size();
					}					

					flip(frame, frame, 1);
					
					//myUtils::DigitalZoom_FC(frame, face, 1.3);
					cv::imshow(WINDOW_REC, frame);
					waitKey(1);

					if (cv::waitKey(10) == 27) {
						destroyAllWindows();
						ofstream stop; stop.open("stop", ios::out);
						stop.close();
						exitC = -1; break;
					}
				}

			}

/*			for (int i = 0; i < Mat_spinners.size(); i++) {

				cv::imshow(WINDOW_REC, Mat_spinners[i]);
				waitKey(1);
			}
*/
		}
	}
	return;
}


void loadImagesForGUI() {
	
	red = Mat(cvSize(normWidth*window_width, normHeight*window_height), CV_8UC3, Scalar(0, 0, 255));


	ifstream o;
#ifdef _WIN32
	o.open("resources"+back_slash+"frameList_WIN32.txt", ios::in);
#else
	o.open("resources" + back_slash + "frameList_Linux.txt", ios::in);
#endif
	string image;

	while (o >> image) {		
		Mat img = imread(image, CV_LOAD_IMAGE_ANYCOLOR);
		resize(img, img, Size(normWidth*window_width, normHeight*window_height));
		//imwrite(image,img);
		Mat_imagesCountDown.push_back(img);
	}
	o.close();



	vector<string>images;
	glob("resources" + back_slash + "other" + back_slash + "green_laser", images);
	green_laser.resize(images.size());

	

	for (int i = 0; i < images.size(); i++) {
		green_laser[i] = imread(images[i], CV_LOAD_IMAGE_ANYCOLOR);
		resize(green_laser[i], green_laser[i], Size(normWidth*window_width_laserScreen, normHeight*window_height_laserScreen));
		//imwrite(images[i],green_laser[i]);
	}
	
	glob("resources" + back_slash + "other" + back_slash + "frames_", images);
	Mat_spinners.resize(images.size());

	for (int i = 0; i < images.size(); i++) {
		Mat_spinners[i] = imread(images[i], CV_LOAD_IMAGE_ANYCOLOR);
		resize(Mat_spinners[i], Mat_spinners[i], Size(normWidth*window_width_laserScreen, normHeight*window_height_laserScreen));
		//imwrite(images[i],Mat_spinners[i]);

	}


	
}