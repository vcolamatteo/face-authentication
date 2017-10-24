#pragma once
#include <iostream>
#include "myUtils.h"
#include "LQP_main.h"
#include "Antispoofing.h"


using namespace std;

Mat frame, frame_copy_resized;
extern cv::String WINDOW_NAME;

extern int NumMaxFrame;

extern float normWidth, normHeight;
extern int window_width;
extern int window_height;
extern int windowSizeWidth, windowSizeHeight;

extern const int PictureWidth, PictureHeight;

std::vector<float>theta(NumMaxFrame);

int OK = -1;
int test = -10;


extern float meanTotal, theresold;


float theta_min;
int run = 0;

Mat *frame_pointer; 
Rect r;	Rect *r_pointer; 
Rect r2;


double alpha = 0.5; double beta = (1.0 - alpha);

#define time_keeping_

#ifdef time_keeping
clock_t start, stop;
#endif

inline void drawing(cv::Mat &frame, int OK, cv::Rect r, float meanTotal, cv::Point facePosition) {

	/***************************  funzoni di disegno rettangolo/mirino invece del rect iniziale ***************************/
	if (OK == -1) {
		if (r.width >= meanTotal - 5 && r.width <= meanTotal + 5) {
			cv::circle(frame, facePosition, 1, cv::Scalar(0, 255, 0), 5, 5);
			cv::circle(frame, facePosition, r.width / 2, cv::Scalar(255, 0, 0), 5);
			myUtils::modifyDrawnCircle(frame, facePosition, r.width / 2, cv::Scalar(255, 0, 0));
		}
		else {
			cv::rectangle(frame, r, cv::Scalar(255, 0, 0));
			cv::circle(frame, facePosition, 2, cv::Scalar(0, 255, 0), 5, 10);
		}


	}
	else if (OK == 1) {

		if (r.width >= meanTotal - 5 && r.width <= meanTotal + 5) {
			cv::circle(frame, facePosition, r.width / 2, cv::Scalar(255, 255, 0), 2);
			myUtils::modifyDrawnCircle(frame, facePosition, r.width / 2, cv::Scalar(255, 255, 0, 255));
		}
		else {
			cv::rectangle(frame, r, cv::Scalar(255, 255, 0, 255), 1);
			myUtils::modifyDrawnRect(frame, r, cv::Scalar(255, 255, 0, 255));
		}

	}
	else {

		if (r.width >= meanTotal - 5 && r.width <= meanTotal + 5) {
			cv::circle(frame, facePosition, r.width / 2, cv::Scalar(0, 0, 255, 255), 2);
			myUtils::modifyDrawnCircle(frame, facePosition, r.width / 2, cv::Scalar(0, 0, 255, 255));
		}
		else {
			cv::rectangle(frame, r, cv::Scalar(0, 0, 255, 255), 1);
			myUtils::modifyDrawnRect(frame, r, cv::Scalar(0, 0, 255, 255));
		}

	}

	/***************************  funzoni di disegno rettangolo/mirino invece del rect iniziale ***************************/

}



inline void classifier(std::vector<cv::Mat>&faces, std::vector<float>&theta, float &theresold, float &theta_min, int &OK, int &test, int &run, clock_t start = -1) {


	/*******  I primi due Mat del vector Theta sono le immagini raccolte in fase di Training,
	le confronto con la terza (frame corrente) attraverso il cosine-similarity         *******/

	if (start == -1) {
		for (int j = 0; j < NumMaxFrame; j++) {
			//theta_min = (faces[NumMaxFrame].dot(faces[j])) / (cv::norm(faces[NumMaxFrame])*(cv::norm(faces[j])));
			theta[j] = (faces[NumMaxFrame].dot(faces[j])) / (cv::norm(faces[NumMaxFrame])*(cv::norm(faces[j])));
			/*if (theta_min > theresold) {
			cout << theta_min << endl;
			break;
			}*/
			cout << theta[j] << "  ";
		}
		cout << endl;

		std::vector<float>::iterator result = std::max_element(std::begin(theta), std::end(theta));
		int max = std::distance(std::begin(theta), result);
		theta_min = theta[max];
		cout << "Max Theta:  " << theta_min << " at:  " << max + 1 << endl;
	}
	else {

		for (int j = 0; j < NumMaxFrame; j++) {
			theta_min = (faces[NumMaxFrame].dot(faces[j])) / (cv::norm(faces[NumMaxFrame])*(cv::norm(faces[j])));
			if (theta_min > theresold) {
				//cout << theta_min << endl;
				break;
			}
		}
		clock_t stop = clock();
		cout << double(stop - start) / CLOCKS_PER_SEC << endl;
	}



	if (theta_min > theresold) {
		run = 6;
		OK = 1;
		test = -2;
		if (start == -1)
		  cout << endl << endl << endl;

	}
	else if (theta_min <= theresold) {
		if (run == 5) {

			OK = 0;
			test = -2;
			run++;
			if (start == -1)
			  cout << endl << endl << endl;

		}
		else
			run++;
	}
	/*else {

	}*/




}


void prelimininate(VideoFaceDetector& detector) {


	// cattura frame
	detector.SecureVideoCapt(frame);
	// face detection
	detector.getFrameAndDetect(frame);
	//frame.copyTo(frame2);
	// rect-face detection
	r = detector.face();

	r2 = r;
	r2.x = detector.facePosition().x - r2.width *0.32; r2.y = detector.facePosition().y - r2.height *0.3; r2.width = 2 * (r2.width *0.31); r2.height = (r2.height * 0.68);

	//r.x = r.x *1.1; r.y = r.y + (r.height * 1 / 5); r.width = r.width * 0.8; r.height = r.height * 0.8;
	//r.x = detector.facePosition().x - r.width *0.32; r.y = detector.facePosition().y - r.height *0.3; r.width = 2 * (r.width *0.31); r.height = (r.height * 0.68);

	
	//system("pause");
	frame.copyTo(frame_copy_resized);
	drawing(frame_copy_resized, OK, r2, meanTotal, detector.facePosition());


	//if (cv::waitKey(10) == 27) return 0; // stop capturing by pressing ESC 
	if (cv::waitKey(10) == 27) exit(-1); // stop capturing by pressing ESC 


	cv::flip(frame_copy_resized, frame_copy_resized, 1); // evita l'effetto specchio, da provare su Android se serve...
	resize(frame_copy_resized, frame_copy_resized, cvSize(windowSizeWidth, windowSizeHeight));

	myUtils::DigitalZoom_FC(frame_copy_resized, detector.facePosition(), 1.3);
	cv::imshow(WINDOW_NAME, frame_copy_resized);



	/* condizioni da verfcarsi per iniziare il riconoscimento del frame acquisito...

	- 1)  pressione barra spaziatrice;
	- 2)  rilevamento della "ottima" distanza dall'obietttivo.

	*/
	//if (cv::waitKey(1) == 32)  // == premere space-bar
		//test = 0;
	//else if (r.width < meanTotal - 5 || r.width > meanTotal + 5) // distanza ottima
	if (r2.width < meanTotal - 5 || r2.width > meanTotal + 5) // distanza ottima
		test = -1;
	else if (r2.width >= meanTotal - 5 && r2.width <= meanTotal + 5 && test == -2) {} // se ha appena effettuato un riconoscimento NON ne effettua subito un altro

	else if (r2.width >= meanTotal - 5 && r2.width <= meanTotal + 5 && test == -1)
		test = 0;

	// Se si è verificata una delle condizioni di cui sopra, si avvia il riconoscimento


}



inline void frameProcessing(VideoFaceDetector& detector, LBP &lbp) {


	prelimininate(detector);
	

	//cout << "gdfgdsgdgdf    " << OK << endl;
	if (!test){

	frame_pointer = &frame;
	r_pointer = &r;

	int run = 0;
	while (run < 6) {
		bool eyes = false; int it = 0;

		
		while (!eyes && it < 5) {


			try {
				if (run != 0) {
					detector.VideoCapt(frame);
#ifdef time_keeping
					start = clock();
#endif
					detector.getFrameAndDetect(frame);

					r = detector.face();
					r2 = r;
					r2.x = detector.facePosition().x - r2.width *0.32; r2.y = detector.facePosition().y - r2.height *0.3; r2.width = 2 * (r2.width *0.31); r2.height = (r2.height * 0.68);
				}

				//imshow("", frame(r));waitKey(0);
				//if (r2.width < 225 && r2.width > 170) {
				if (r2.width > 170) {


					if (detector.isFaceFound()) {

						//cvtColor(frame, frame, CV_RGB2GRAY);
						if (run==0)
						    if(!antispoofing(frame,r, lbp)){
								OK = 0;
								test = -2;
								run = 6;	
								//if (start == -1)
									cout << endl << endl << endl;
									break;
							}
						


						cvtColor(frame, frame, CV_RGB2GRAY);


						//auto start = cv::getCPUTickCount();
						frame = findEyes(frame_pointer, r_pointer, detector.facePosition(), eyes, it);
						//						cout << "post:  " << *r_pointer << endl;
						//imshow("", frame); waitKey(0);
						//system("pause");

					}
					/*else
					{
					Mat divieto = imread("divieto.png", CV_LOAD_IMAGE_ANYCOLOR);
					resize(divieto, divieto, frame_copy_resized.size());
					addWeighted(frame_copy_resized, alpha, divieto, beta, 0.0, frame_copy_resized);
					cv::imshow(WINDOW_NAME, frame_copy_resized); waitKey(1);
					if (cv::waitKey(10) == 27) return 0; // stop capturing by pressing ESC
					}*/

					it++;
				}
				else
				{
					Mat divieto = imread("divieto.png", CV_LOAD_IMAGE_ANYCOLOR);
					resize(frame, frame_copy_resized, cvSize(windowSizeWidth, windowSizeHeight));
					resize(divieto, divieto, frame_copy_resized.size());
					addWeighted(frame_copy_resized, alpha, divieto, beta, 0.0, frame_copy_resized);
					flip(frame_copy_resized, frame_copy_resized, 1);
					cv::imshow(WINDOW_NAME, frame_copy_resized); waitKey(1);
					if (cv::waitKey(10) == 27) exit(-1); // stop capturing by pressing ESC 
					break;
				}


			}
			catch (cv::Exception& e) {
				cerr << "Error Reason: " << e.msg << endl;
				eyes = false;
				it--;
			}


			resize(frame, frame, Size(PictureWidth, PictureHeight));
			frame = myUtils::Norm_lum(frame);
			frame = myUtils::norm_0_255(frame);
			//cv::equalizeHist(frame, frame);
			//cv::equalizeHist(frame, frame);

			//imwrite(path_init_Norm+"frame.bmp", frame);

			LQP_EXTRACT_noSave(frame, faces[NumMaxFrame]);
			//LQP_gen(faces[NumMaxFrame], "Database_Normalized" + back_slash + Data + back_slash + "LQP_Frame.txt", "Database_Normalized"+ back_slash+Data + back_slash+"cluCenterFile.txt", "-e");
			//myUtils::writeMatrix(faces[NumMaxFrame],  + "DDDDDDDD.txt");

#ifndef time_keeping
			cout << "run  " << run << endl;
			classifier(faces, theta, theresold, theta_min, OK, test, run);
			//cout << "run  " << run << endl;
			//system("pause");
#else

			classifier(faces, theta, theresold, theta_min, OK, test, run, start);

#endif
			// setto comunque una condizione di uscita nel caso in cui 
			// si entri in un loop di exceptions, allora dopo 10 run cmq esce 
			if (run == 10)
				break;
		}
	  }

	}
}


