#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include "LBP_maker.h"
#include "OpenFile.h"

using namespace std;
using namespace cv;


extern string back_slash;


// file in cui salva il feature vector estratto fotogramma per fotogramma
static string inputFile = "resources"+back_slash+ "Antispoof" + back_slash + "outputFile"+back_slash+"mine_raw.test";  //.test
												 /*************************   MODELS   *******************************/

												 //char* modelFile = "output_TRAIN_normALL.train.model";


												 //char* modelFile = "Ultimate_riu2.train.model";


												 //char* modelFile = "Ultimate_2.train.model";  // best
												 //char* modelFile = "no_setPrecision.train.model";
												 //char* modelFile = "output_TRAIN_normALL_g200.train.model";

static string modelFile = "resources" + back_slash + "Antispoof" + back_slash + "no_setPrecisiong200.train.model";

//char* modelFile = "prova.model";
//char* modelFile = "no_setPrecision300.train.model";
//char* modelFile = "no_setPrecision500.train.model";
//char* modelFile = "no_setPrecision400.train.model";
//char* modelFile = "no_setPrecision450.train.model";

//char* modelFile = "setPrecision4_OnlyClass0.train.model";
//char* modelFile = "setPrecision3_OnlyClass0.train.model";

//char* modelFile = "Ultimate_precision3.train.model";
//char* modelFile = "Ultimate_precision4.train.model";


/*************************   MODELS   *******************************/


////////////////////////////  LBP Tables  ///////////////////////////////
static string mappingTable_16 = "resources" + back_slash + "Antispoof"+ back_slash + "mappingTable_16pts.txt";
static string mappingTable_8 = "resources" + back_slash + "Antispoof" + back_slash + "mappingTable_8pts.txt";

static string mappingTable_RIU2_16 = "resources" + back_slash + "Antispoof" + back_slash + "mappingTable_RIU2_16pts.txt";
static string mappingTable_RIU2_8 = "resources" + back_slash + "Antispoof" + back_slash + "mappingTable_RIU2_8pts.txt";
////////////////////////////  LBP Tables  ///////////////////////////////

//string path_dir = "C:\\Users\\Valerio\\Desktop\\Thesis\\Databse\\NormalizedFace\\ClientNormalized\\";


/************* DEFAULT CLASS ********************/
static String Class_ = "1";   // Impostor
//String Class_ = "0";   // Client
/***********************************************/


static int rad_int = 1; static int *rad = &rad_int;
static int pts_int = 8;  static int *pts = &pts_int;
static string mapping = "riu2";

static LBP  antispoofingSetModel() {


	
	bool outputHist = true, normalizeHist = false;
	
	//cout << back_slash << endl;
	//cout << modelFile << endl;
	
	OpenFile(modelFile);

	// Create an LBP instance of type "mapping" using "pts" support points
	LBP lbp(*pts);
	if (mapping == "u2") {
		lbp.loadMapping(mappingTable_16, 2);
		lbp.loadMapping(mappingTable_8, 1);
	}
	else {  // attenzione all'ordine...
		lbp.loadMapping(mappingTable_RIU2_16, 2);
		lbp.loadMapping(mappingTable_RIU2_8, 1);
	}

	return lbp;

}


static bool antispoofing(Mat frame2, cv::Rect &r, LBP lbp) {

	cvtColor(frame2, frame2, CV_RGB2GRAY);


	frame2 = frame2(r);
	
	//cv::imshow("tyrtyr", frame2);
	//cout << frame2.size() << endl;

	//if (r.width > 2 && r.height > 2) {

	//if (r.width < 140 || r.height < 140 || mean(frame2)[0] >= 120) {
	if ( mean(frame2)[0] >= 150) {
		//cout << "AUTOMATIC FAKE" << endl;
		cout << "FAKE User" << endl;
		//cv::rectangle(frame, r, cv::Scalar(0, 0, 255), 3);
		return false;
	}
	else {


		cv::resize(frame2, frame2, Size(64, 64), CV_INTER_LINEAR);
		//Mat frame3; frame2.copyTo(frame3);
		///////////////////////////////
		double percentageFromTop = 30;
		double percentageFromBottom = 60;


		Rect t = Rect(0, (frame2.cols * percentageFromTop / 100), frame2.rows, frame2.cols - (frame2.cols * percentageFromBottom / 100));

		//if (t.width > 2 && t.height > 2) {
		// crea una roi allinterno della roi del viso (image) da considerazioni euristiche
		Mat ROI = frame2(Rect(0, (frame2.cols * percentageFromTop / 100), frame2.rows, frame2.cols - (frame2.cols * percentageFromBottom / 100)));
		//frame2(t).copyTo(ROI);

		//imshow("eye-block", ROI); //waitKey(0);
		//imwrite("eye-block.bmp",ROI);

		//Mat eyeBlockCorr = Mat(ROI.rows/2,ROI.cols, ROI.type(), Scalar(0));					
		for (int i = 0; i < ROI.rows / 3;i++) {
			uchar* p = ROI.ptr(i);

			for (int j = 0; j < ROI.cols;j++) {
				p[j] = 0;

			}
		}

		//imshow("eye-blockCorr", ROI); waitKey(0);
		//cout << r.width << endl;				
		//cout << "mean:           " << mean(ROI)[0] << endl;				

		//imshow("UUUU", frame2(Rect(0, (frame2.cols * percentageFromTop / 100), frame2.rows, frame2.cols - (frame2.cols * percentageFromBottom / 100)))); waitKey(0);

		//if (r.width < 500 && mean(ROI)[0] < 120)
		//ROI.copyTo(frame2(Rect(0, (frame2.cols * percentageFromTop / 100), frame2.rows, frame2.cols - (frame2.cols * percentageFromBottom / 100))));
		
		//imshow("UUUU", frame2); //waitKey(0);



								//cv::resize(frame2, frame2, Size(64, 64), CV_INTER_LINEAR);

								//if (frame2.size() != Size(0, 0))
								//cv::imshow("64x64", frame2);

								//frame2.convertTo(frame2, CV_64F);
		makeFeaturesVector(frame2, *pts, *rad, inputFile, Class_, mapping, lbp);

		
		bool correct = Classifier(inputFile, model);
		//cout << "correct:   " << correct<<endl;
		if (correct > 0) {
			cout << "REAL User" << endl;
			return true;
		}
		else {
			cout << "FAKE User" << endl;
			return false;
		}
	}


	//endTime_ = clock();
	//cout << "Generating Table took " << double(endTime_ - startTime_) / double(CLOCKS_PER_SEC) << "s" << endl;	

	// premere ESC per uscire
	//if (cv::waitKey(3) == 27)
	//return 0;

	//}



}
