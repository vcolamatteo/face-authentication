#pragma once
#ifdef _WIN32
#include <Windows.h>
#endif
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv\cv.h>
#include <opencv\cxcore.h>
#include <opencv\highgui.h>

#include <iostream>
#include <queue>
#include <stdio.h>
#include <math.h>

#include "constants.h"
#include "findEyeCenter.h"

using namespace std;
using namespace cv;


double expandPercentage = 10;
CvPoint* centerRotatePoint_pointer = NULL;
Mat *FaceCropped = NULL;


cv::Mat faceROI;
Rect operationRect;
//cv::Point centre_face;
//double fps = 0, time_per_frame;



//std::string face_window_name = "Capture - Face";
string face_rotated_window_name = "rotated";


void rotateWithQuadrangle(IplImage *src, IplImage *dst, float angle, CvPoint *center);
IplImage* Sub_Image(IplImage *image, CvRect roi);


cv::Mat findEyes(cv::Mat* frame, cv::Rect* face, cv::Point centre_face, bool &eyes, int it, int countFrame) {


	std::vector<cv::Rect> faces;
	//cv::Mat frame_gray;

	

	// devo per forza fare una opia locale della ROI altrimenti mi stampa i retangoli facciali anche sulla immagine ruotata...
	(*frame)(*face).copyTo(faceROI);
	//Mat* g = &(*frame)(*face);
	// così non fa la copia ma ho  etangoli e cerch stampati. 
	//faceROI= frame(face);

	//cv::Mat debugFace = faceROI;

	if (kSmoothFaceImage) {
		double sigma = kSmoothFaceFactor * face->width;
		GaussianBlur(faceROI, faceROI, cv::Size(0, 0), sigma);
	}
	//-- Find eye regions and draw them
	//-- Find eye regions and draw them
	int eye_region_width = face->width * (kEyePercentWidth / 100.0);
	int eye_region_height = face->width * (kEyePercentHeight / 100.0);
	int eye_region_top = face->height * (kEyePercentTop / 100.0);
	cv::Rect leftEyeRegion(face->width*(kEyePercentSide / 100.0),
		eye_region_top, eye_region_width, eye_region_height);
	cv::Rect rightEyeRegion(face->width - eye_region_width - face->width*(18 / 100.0),
		eye_region_top, eye_region_width, eye_region_height);


	float angle = 0.0;
	cv::Point rightPupil, leftPupil;

	//-- Find Eye Centers
			leftPupil = findEyeCenter(faceROI, leftEyeRegion, "Left Eye");
			rightPupil = findEyeCenter(faceROI, rightEyeRegion, "Right Eye");

			// change eye centers to face coordinates
			rightPupil.x += rightEyeRegion.x;
			rightPupil.y += rightEyeRegion.y;
			leftPupil.x += leftEyeRegion.x;
			leftPupil.y += leftEyeRegion.y;
			//std::cout << leftPupil << "  " << rightPupil << std::endl;

			// draw eye centers
			//std::min(std::max(val, min), max);
			//circle(faceROI, rightPupil, std::min(std::max(5 - (int)(500 / face->width), 0), 10), 1234);
			/*circle((*frame)(*face), rightPupil, 3, 1234);
			circle((*frame)(*face), leftPupil, 3, 1234);
			imwrite("faceROI_eyes.bmp", (*frame)(*face));*/
			
			
			//circle(faceROI, rightPupil, 3, 1234);
			//circle(faceROI, leftPupil, 3, 1234);
			//imwrite("faceROI_eyes.bmp", faceROI);






			float distanceX = (float)(leftPupil.y) - (float)rightPupil.y;
			float distanceY = (float)(leftPupil.x) - (float)rightPupil.x;
			angle = atan2(distanceX, distanceY) * 180 / CV_PI;

			angle = angle + ((180 - angle) / 2);
			//cout << angle << endl;


			if (angle < 1.2 || angle >(178.8)) {
				/*circle(faceROI, rightPupil, 3, 1234);
				circle(faceROI, leftPupil, 3, 1234);
				imwrite(Dir_initNorm+"faceROI_eyes_#" + to_string(it) + ".bmp", faceROI);*/
				cout << "BREAK AT #: " << it << endl;
				cout << angle << endl;
				eyes = true;
			}
			else {
				/*circle(faceROI, rightPupil, 3, 1234);
				circle(faceROI, leftPupil, 3, 1234);
				imwrite(Dir_initNorm+"faceROI_eyes_#" + to_string(it) + ".bmp", faceROI);*/
				cout << "RUN # " << it << endl;
				cout << angle << endl;
			}			
		
		/*if (done == 1) {
			circle(faceROI, rightPupil, 3, 1234);
			circle(faceROI, leftPupil, 3, 1234);
			imwrite("faceROI_eyes.bmp", faceROI);
			break;
		}*/
	
	if (eyes){
		

		
		/*circle(faceROI, rightPupil, 3, 1234);
		circle(faceROI, leftPupil, 3, 1234);
		imwrite(Dir_initNorm + "faceROI_PREeyes_#_" + to_string(countFrame) + ".bmp", faceROI);
		*/

		int distEyes = (rightPupil.x - leftPupil.x);
		int dist_030 = 2 * round(distEyes*0.15);
		face->x = round(leftPupil.x - distEyes*0.15); face->width = distEyes + dist_030;
		face->y = leftPupil.y - dist_030;
		//face->height = distEyes + distEyes*0.3 + (distEyes*0.25);
		//cout << "size:   "<<faceROI.size() << endl;
		//cout << "face->x  " << face->x << "  " << distEyes*0.15 << "  width:   "<< face->width<<endl;
		//cout <<"distEyes:  "<< distEyes <<"  face-y:  "<< dist_030 <<"  "<< (distEyes + dist_030) + ((distEyes + dist_030)*0.25) << endl;
		face->height = (distEyes + dist_030) + ((distEyes + dist_030)*0.25);
		
		/*cout << "face  " << *face << endl;

		rectangle(faceROI, (*face), Scalar(255, 255, 255));
		imwrite(Dir_initNorm + "faceROI_POST_eyes_#_" + to_string(countFrame) + ".bmp", faceROI);
		
		imwrite(Dir_initNorm + "faceROI_eyes_#_" + to_string(countFrame) + ".bmp", faceROI(*face));
		*/
		//imshow("", faceROI(*face)); waitKey(0);

		//cout << "face  " << *face << endl;


		//cv::Mat faceROI = frame_gray(face);
		//imgOperation = cvCreateImage(cvSize(small_img->width, small_img->height), small_img->depth,
		//small_img->nChannels);
		//CvPoint centerRotatePoint = cvPoint( (frame(*face).rows / 2), (frame(*face).cols / 2));


		//face->x = centre_face.x - face->width *0.3; face->y = centre_face.y - face->height *0.3; face->width = 2 * (face->width *0.32); face->height = (face->height * 0.65);
		//face->x = centre_face.x - face->width *0.32; face->y = centre_face.y - face->height *0.25; face->width = 2 * (face->width *0.32); face->height = (face->height * 0.6);
		
		
		//face->x = centre_face.x - face->width *0.27; face->y = centre_face.y - face->height *0.28; face->width = (face->width *0.52); face->height = (face->height * 0.62);


		// devo aggiungere un pò di padding per fare la rotazione....
		//double expandPercentage = 10;
		double expandX = (face->width * (100 + expandPercentage) / 100) - face->width;
		double expandY = (face->height * (100 + expandPercentage) / 100) - face->height;
		

		//int s1 = face->width, s2 = face->height;

		face->x = face->x - expandX / 2;
		face->y = face->y - expandY / 2;
		face->width = face->width + expandX;
		face->height = face->height + expandY;

		cout << "NEW face  " << *face << endl;

		CvPoint centerRotatePoint = cvPoint((face->width / 2), (face->height / 2));

		//circle(frame, Point(rightPupil.x + face.x, rightPupil.y + face.y), 3, 1234);
		//circle(frame, Point(leftPupil.x + face.x, leftPupil.y + face.y), 3, 1234);
		//imshow("fdgfdsggd", frame_gray);

		IplImage* frameNew = cvCloneImage(&(IplImage)faceROI(*face));
		//system("pause");
		IplImage* frameNew_2 = cvCreateImage(cvSize(face->width, face->height), 8, 1);

		rotateWithQuadrangle(frameNew, frameNew_2, angle, &centerRotatePoint);


		Mat f = Mat(frameNew_2);


		face->x = face->x + expandX / 2;
		face->y = face->y + expandY / 2;
		face->width = face->width - expandX;
		face->height = face->height - expandY;


		

		operationRect.x = frameNew_2->width / 2 - face->width / 2;	// x = start from leftmost 			
		operationRect.y = frameNew_2->height / 2 - face->height / 2; // y = a few pixels from the top 			
		operationRect.width = f.cols - operationRect.x - expandX / 2;	// width = same width with the face
		operationRect.height = f.rows - operationRect.y - expandY / 2; // height = 1/3 of face height

		//rectangle(f, operationRect, Scalar(255, 255, 255));
		//imwrite(Dir_initNorm+"faceROI_eyes_"+to_string(countFrame)+".bmp", f);
		f = f(operationRect);
		
		
		return f;

	}
	else if(it==49){
		cout << "NO eyes-----------------------------------------"<<endl;
		cout << angle << endl;		
		//r.x = face.x - r.width *0.32; r.y = face.y - r.height *0.3; r.width = 2 * (r.width *0.31); r.height = (r.height * 0.68);

		//rectangle((*frame), (*face), Scalar(255, 255, 255));
		//imwrite(Dir_initNorm+"faceROI_before_eyes_#" + to_string(it) + ".bmp", (*frame));
		//cout << "PRE face:  " << *face << endl;

		int face_030 = round(face->width *0.30);
		int face_030_020= round(face_030*0.20);
		//cout << "----  "<<face_030 << "  " << face_030_020 << endl;
		//face->x = centre_face.x - face_030; face->y = centre_face.y - face->height *0.25; face->width = 2*face_030; face->height = (face->height * 0.6);
		face->x = face->x + (face_030 - face_030_020);
		face->width = 1.7 * face_030; 
		//face->height =  (face->width - face->x)*0.2; 
		face->height = (face->width + 2 * face_030_020 - face_030_020*0.5);
		face->y = face->y+1.5*(face->width*0.25);
		/*cout << "face:  "<<*face << endl;
		cout << "face:  " << faceROI.size() << endl;
		rectangle((*frame), (*face), Scalar(255, 255, 255));
		imwrite(Dir_initNorm + "faceROI_before_eyes_#" + to_string(it) + ".bmp", (*frame));
		
		rectangle(faceROI, (*face), Scalar(255, 255, 255));
		imwrite(Dir_initNorm+"faceROI_eyes_#"+to_string(it)+".bmp", (*frame));
		cout << *face << endl;*/
		return (*frame)(*face);

	}
	else
		return (*frame)(*face);
	//imshow("", faceROI);waitKey(0);

	
}

void rotateWithQuadrangle(IplImage *src, IplImage *dst, float angle, CvPoint *center) {

	// Calcola matrice di rotazione...


	float m[6];
	CvMat M = cvMat(2, 3, CV_32F, m);
	//int w = src->width;
	//int h = src->height;

	m[0] = (float)(cos(-angle * 2 * CV_PI / 180.));
	m[1] = (float)(sin(-angle * 2 * CV_PI / 180.));
	m[3] = -m[1];
	m[4] = m[0];

	//m[2] = w*0.5f;
	//m[5] = h*0.5f;

	m[2] = center->x;
	m[5] = center->y;

	cvGetQuadrangleSubPix(src, dst, &M);

}


IplImage* Sub_Image(IplImage *image, CvRect roi) {
	IplImage *result;

	// sub-image
	result = cvCreateImage(cvSize(roi.width, roi.height), image->depth, image->nChannels);
	cvSetImageROI(image, roi);
	cvCopy(image, result, 0);
	cvResetImageROI(image); // release image ROI

	return result;
}