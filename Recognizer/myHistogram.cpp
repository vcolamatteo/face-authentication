
#include "myHistogram.h"


void drawHist(vector<double> hist, int histSize, int hist_w, int hist_h, string title) {


	int bin_w = cvRound((double)hist_w / histSize);

	cv::Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0)); // 400 rows
															 //cout << "aaaa:  " << hist[57] << endl; // valore prima della normalizzazione (tutti i valori compresi tra zero e 400)
															 /// Normalize the result to [ 0, histImage.rows ]

	normalize(hist, hist, 0, histImage.rows*0.9, NORM_MINMAX, -1, Mat());
	//cout << "histImage.rows:  "<<histImage.rows << endl;


	/// Draw for each channel
	for (int i = 1; i < histSize + 1; i++)
	{
		//if (i == 58)
		//cout << "after: "<<cvRound(hist[i - 1]) << endl;   // valore dopo la normalizzazione

		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist[i - 1])),
			Point(bin_w*(i), hist_h - cvRound(hist[i])),
			Scalar(255, 0, 0), 2, 8, 0);

	}

	/// Display
	namedWindow(title, CV_WINDOW_AUTOSIZE);
	imshow(title, histImage);

	waitKey(0);
}


Mat drawHist_rect(vector<double> _histMat, int _histSize, int w, int h)
{



	//int w = 400; int h = 400;
	//int w = 300; int h = 240;
	Mat histImage(h, w, CV_8UC1, Scalar(0, 0, 0));
	//Mat i2;
	cv::normalize(_histMat, _histMat, 0, histImage.rows, CV_MINMAX);

	//cout << "Hist SIZE:  " << _histSize << endl;
	for (int i = 0; i < _histSize + 1; i++)
	{
		int bin_w = cvRound((double)w / _histSize);
		rectangle(histImage, Point(i*bin_w, h), Point((i + 1)*bin_w, h - cvRound(_histMat[i] * h / 255.0)), Scalar(120, 120, 120), -1);

	}

	return histImage;
}

Mat drawHist_2(vector<double> _histMat, int _histSize, int w, int h)
{



	//int w = 400; int h = 400;
	//int w = 300; int h = 240;
	Mat histImage(h, w, CV_8UC1, Scalar(0, 0, 0));
	//Mat i2;
	cv::normalize(_histMat, _histMat, 0, histImage.rows, CV_MINMAX);

	cout << "Hist SIZE:  " << _histSize << endl;
	for (int i = 0; i < _histSize + 1; i++)
	{
		int bin_w = cvRound((double)w / _histSize);
		rectangle(histImage, Point(i*bin_w, h), Point((i + 1)*bin_w, h - cvRound(_histMat[i] * h / 255.0)), Scalar(120, 120, 120), -1);
		/*line( histImage, Point( bin_w*(i-1), hist_h - cvRound(1*i2.at<float>(i-1)) ) ,
		Point( bin_w*(i), hist_h - cvRound(1*i2.at<float>(i)) ),
		Scalar( 255, 0, 0), 2, 8, 0  );
		/*line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
		Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
		Scalar( 0, 255, 0), 2, 8, 0  );
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
		Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
		Scalar( 0, 0, 255), 2, 8, 0  );*/
	}

	return histImage;
}


void spatial_Histogram(LBP lbp, Mat lbpImg, int width, int height, vector<double> &histC, int block) {
	Mat cell; vector<double> hist;

	int cnt = 0;

	for (int i = 0;i < block;i++)
	{
		for (int j = 0;j < block;j++)
		{
			cell = lbpImg(Rect(j*width, i*height, width, height)); //cout << cell.size() << endl;
			lbp.setLBPImage(cell);
			hist = lbp.calcHist().getHist(false);


			/*
			Mat P=drawHist_2(hist, 59,320,240);
			imshow("P", P);waitKey(0);*/
			/*
			for (int i = 0;i < 10 ;i++)
			cout<<hist[i]<<" ";
			cout << endl << endl;
			*/


			double * ptr = &hist[0];  
									  
			for (int k = 0; k<hist.size(); k++)  // 531 bn
			{
				//if (ptr[k] == 0)
					//ptr[k] = 1.0 / 59;
				histC[(cnt * hist.size()) + k] = ptr[k];
				//  cerr << ptr[k] << endl;
			}
			cnt++; //cout << "count  " << cnt << endl;


		}
	}


}