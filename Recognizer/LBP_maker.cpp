#include "LBP_maker.h"

//clock_t startTime, endTime;


Mat img; double *ptr;
vector<double> hist;


vector<double>histC(118);

void makeFeaturesVector(Mat imgOrg, int pts, int rad, string outFilename, string Class_, string mapping, LBP lbp) {

	//	lbp_l.loadMapping("mappingTable_16pts.txt",2);
	//	lbp_l.loadMapping("mappingTable_8pts.txt", 1);

	//system("pause");



	int sizeH;
	int sizeBlock = 3;



	if (mapping == "u2") {
		histC.resize(833);
		sizeH = 59;
	}
	else
		sizeH = 10;
	//else
	//vector<double>histC(118);


	// Read an (RGB) image and convert to monochrome
	//Mat imgOrg = imread(fileName, CV_LOAD_IMAGE_GRAYSCALE);

	//imgOrg = Norm_lum(imgOrg);
	//imgOrg = norm_0_255(imgOrg);
	// Draw it on screen:
	//imshow("TanTriggs Preprocessed Image", imgOrg);
	//waitKey(0);


	// convert to double precision
	//imgOrg.convertTo(imgOrg, CV_64F);



	Mat lbpImg = Mat(imgOrg.size(), CV_8UC1, Scalar(0));

	// Create an LBP instance of type "mapping" using "pts" support points


	//LBP lbp(pts, 1);

	//startTime = clock();

	//lbpImg = lbp.LbpInit(lbp, imgOrg, rad);


	img = imgOrg;

	lbp.calcLBP(img, 1, rad);

	lbpImg = lbp.getLBPImage();



	//imshow("", lbpImg); waitKey(0);
	//imwrite("LBPU_image (8,1).png", lbpImg);

	int width = lbpImg.cols / sizeBlock;  // blocco dim=3
	int height = lbpImg.rows / sizeBlock; // blocco dim=3
										  // costrusce istogramma blocco per blocco
	spatial_Histogram(lbp, lbpImg, width, height, histC);

	//***************************************//
	// LBPU (8,2)
	//cout << endl << endl << endl << endl << "-------------------------------------" << endl << endl << endl;

	pts = 8; rad = 2;

	img = imgOrg;

	lbp.calcLBP(img, 1, rad);
	lbpImg = lbp.getLBPImage();

	//imshow("LBPU_image (8,2)", lbpImg); waitKey(0);
	//imwrite("LBPU (8,2).png", lbpImg);


	hist = lbp.calcHist().getHist(false);

	// inserisco dati in histC

	ptr = &hist[0];
	for (int k = 0; k<hist.size(); k++)  // 531 bn
	{
		//if (ptr[k] == 0) {
		//ptr[k] = 1.0 / 59; cout << "ptk_0:  " << ptr[k] << endl;
		//}
		histC[(sizeH*sizeBlock*sizeBlock) + k] = ptr[k];
		//  cerr << ptr[k] << endl;
	}






	//***************************************//
	// LBPU (16,2)
	//cout << endl << endl << endl << endl << "-------------------------------------" << endl << endl << endl;
	//lbp.loadMapping(mappingTable_RIU2_16, 2);
	pts = 16; rad = 2;
	lbp.associateTableMapping(pts, mapping);

	//LBP lbp2(pts, 2);
	//lbp.set_num(243);
	//lbp.set_samples(pts);


	img = imgOrg;
	lbp.calcLBP(img, 2, rad);

	lbpImg = lbp.getLBPImage();

	//imshow("LBPU_image (16,2)", lbpImg); waitKey(0);
	//imwrite("LBPU (16,2).png", lbpImg);

	hist = lbp.calcHist().getHist(false);

	// draw histogram
	//drawHist(hist, 243, 320, 200,"Hist (16,2)");


	// inserisco dati in histC

	ptr = &hist[0];  //cout << "size:  " << hist.size() << endl;
					 //for (int k = 0; k<tmp_feature.cols - 1; k++)  // 522 bin
	for (int k = 0; k<hist.size(); k++)  // 531 bn
	{
		//if (ptr[k] == 0)
		//ptr[k] = 1.0 / 243;
		histC[(sizeH*sizeBlock*sizeBlock) + sizeH + k] = ptr[k];
		//  cerr << ptr[k] << endl;
	}

	// sum of HistC
	double sum = 0;
	//	std::for_each(histC.begin(), histC.end(), [&](int n) {
	//		sum += n;
	//	});


	for (std::vector<double>::iterator it = histC.begin(); it != histC.end(); ++it) {
		//cout << *it << endl;
		sum += *it; //count++;
	}


	//for (int i = 0;i < histC.size(); i++)
		//histC[i]=histC[i] / sum;

	//cout << "SUM:  " << sum << endl;  cout << "count:  "<<count << endl;
	// write histogram

	ofstream ofs;
	ofs.open((outFilename).c_str(), ios::out);
	ofs << Class_;
	for (int i = 0; i < histC.size(); i++) {
		//if (i == 0) ofs << Class_;
		//if (i > 0) ofs << " ";
		ofs << " "<< i + 1 << ":" << histC[i] / sum;
	}
	ofs << endl;
	ofs.close();
	



	//endTime = clock();
	//cout << "Generating Table took " << double(endTime - startTime) / double(CLOCKS_PER_SEC) << "s" << endl;

	//	Mat P = drawHist_2(histC, 833, 600, 400);
	//	imshow("All", P);waitKey(0);
	//  imwrite("All_histogram.png", P);


	//system("pause");
	//return 0;
}


