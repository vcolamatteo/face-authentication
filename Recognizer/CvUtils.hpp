#ifndef CVUTILS_h
#define CVUTILS_h

using namespace std;

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#include <vector>
#include <cstdlib>

#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */

using std::abs;

class CvUtils {
private:


public:

	static void createMask(IplImage * theMask, CvRect maskRegion, int zeroImage) {
		CvPoint topLeft, bottomRight;
		if(theMask!=NULL) {
			if(zeroImage) {
				cvZero(theMask);
			}
			topLeft.x = cvRound((maskRegion.x ));
			topLeft.y = cvRound((maskRegion.y ));
			bottomRight.x = cvRound((maskRegion.x + maskRegion.width));
			bottomRight.y =  cvRound((maskRegion.y + maskRegion.height));
			cvRectangle(theMask,topLeft,bottomRight,CV_RGB(255,255,255),-1,8,0);
		}
	}




	static IplImage* Sub_Image(IplImage *image, CvRect roi) {
		IplImage *result;

		// sub-image
		result = cvCreateImage( cvSize(roi.width, roi.height), image->depth, image->nChannels );
		cvSetImageROI(image,roi);
		cvCopy(image,result,0);
		cvResetImageROI(image); // release image ROI

		return result;
	}


	static CvRect getEncRect(CvRect *roi, int dst_width, int dst_height) {
			int centerX = 0, centerY=0;
			int encTlRectX = 0;
			int encTlRectY = 0;
			getRectCenter(roi,&centerX,&centerY);
			encTlRectX = cvRound(centerX-(dst_width*0.5));
			encTlRectY = cvRound(centerY-(dst_height*0.5));
			return cvRect(encTlRectX,encTlRectY,dst_width,dst_height);
	}

	static CvRect* getLargestRect(vector <CvRect*>& rects) {
		int largestArea = 0;
		int largestAreaIndex = -1;
		for (int i=0; i<rects.size(); i++) {
			CvRect *thisRect = rects.at(i);
			int thisArea = thisRect->x * thisRect->y;
			if (thisArea > largestArea) {
				largestArea = thisArea;
				largestAreaIndex = i;
			}
		}
		if (largestAreaIndex > -1) {
			return rects.at(largestAreaIndex);
		}
		return 0;
	}


	static void getRectCenter(CvRect *roi, int * centerX, int * centerY) {
		*centerX = cvRound((roi->x + roi->width*0.5));
		*centerY = cvRound((roi->y + roi->height*0.5));
	}

	static CvPoint getRectCenterPoint(CvRect *roi) {
		CvPoint centerPoint = cvPoint(
			cvRound(roi->x + roi->width/2),
			cvRound(roi->y + roi->height/2)
		);
		return centerPoint;
	}


	static void rotateWithQuadrangle(IplImage *src, IplImage *dst, float angle, CvPoint *center) {
		
		// Calcola matrice di rotazione...


		float m[6];
		CvMat M = cvMat(2, 3, CV_32F, m);
		int w = src->width;
		int h = src->height;

		m[0] = (float)(cos(-angle*2*CV_PI/180.));
		m[1] = (float)(sin(-angle*2*CV_PI/180.));
		m[3] = -m[1];
		m[4] = m[0];

		//m[2] = w*0.5f;
		//m[5] = h*0.5f;

		m[2] = center->x;
		m[5] = center->y;
		
		cvGetQuadrangleSubPix( src, dst, &M);

	}


};


#endif
