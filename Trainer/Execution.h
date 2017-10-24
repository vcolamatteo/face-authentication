#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace cv;


//////////////////////////////////
//std::vector<float>meanAlls;
int alpha_target = 1; int beta_target = +150;
float alpha = 0.5; int beta = 0;
float delta_alpha = 0.5; int delta_beta = -25;
int max_alpha = ((alpha_target - alpha) / delta_alpha) + 1; // + 1 per lo zero...
int max_beta = ((beta_target / abs(delta_beta)) * 2) + 1; // + 1 per lo zero e (*2) per la presenza dei beta negativi ...
//////////////////////////////////

string Time, Data;

void Execution(Mat frame2, int countFrame, int NumMaxFrame, int NumImageToSelect, std::vector<float>meanAlls, std::vector<Mat>faces, std::vector<Mat>facesWhitened) {


	frame2 = myUtils::Norm_lum(frame2);
	frame2 = myUtils::norm_0_255(frame2);
	cv::equalizeHist(frame2, frame2);

	Scalar mean, std;  Scalar meanWhitened, stdWhitened;
	//imshow(name, frame2); waitKey(0);


	ShowWindow(GetConsoleWindow(), SW_RESTORE);

	myUtils::timeData(Time, Data, 1, 0);


	//cout << directory + namePath + to_string(countFrame) + "alpha_" + to_string(alpha + (delta_alpha*jj)) + "__beta_" + to_string(beta + (delta_beta*j)) + "_.bmp" << endl;
	countFrame++;
	//string Dir = "Database\\" + Data + "\\" + "LQP_featuresEnhancedVersion_#" + to_string(countFrame) + "_.txt";
	//string Dir = "Database\\" + Data + "\\" + "#" + to_string(countFrame) ;			
	string Dir_init = "Database_Norm\\" + Data + "\\";
	imwrite(Dir_init + "Last_Norm.bmp", frame2);


	cout << "CountFrame:  " << countFrame << endl;

	if (countFrame < NumMaxFrame + 1) {

		//float meanAll = 0.0, stdAll = 0.0;

		Enhancer(frame2, alpha, delta_alpha, beta, delta_beta, countFrame, Dir_init, (int)NumMaxFrame, meanAlls, alpha_target, beta_target);
		//FramesMean.push_back(meanAll);
	}
	else {
		//cout << "HERE" << endl;
		imwrite(Dir_init + "Last.bmp", frame2);
		//frame_Norm = myUtils::Norm_lum(frame2);
		//frame_Norm = myUtils::norm_0_255(frame_Norm);
		//imwrite(Dir + "Last_Norm.bmp", frame_Norm);
		Scalar meanLast = 0.0, stdLast = 0.0;
		Mat LAST = Mat(rowNum, colNum, CV_64FC1);
		//int c = LQP_EXTRACT("LQP_features.txt", frame2,LAST);
		int c = LQP_EXTRACT("LQP_features.tx t", frame2, LAST);
		//frame2_Norm.copyTo(frame2);


		LAST.convertTo(LAST, CV_32FC1);
		LAST.copyTo(faces[NumMaxFrame]);

		cout << "SIZE:    " << meanAlls.size() << endl;
		std::vector<float>meanVec(meanAlls.size() / NumMaxFrame);

		for (int i = 0; i < meanAlls.size();i++)
			cout << "mean maeanAlls:  " << meanAlls[i] << endl;

		int countIndex = 0;
		for (int i = 0; i < meanVec.size(); i++) {
			float SumTmp = 0.0;
			for (int j = (i*NumMaxFrame); j < ((i*NumMaxFrame) + NumMaxFrame); j++) {
				SumTmp = SumTmp + meanAlls[j];
			}

			meanVec[i] = SumTmp / NumMaxFrame;
			//countIndex = countIndex + 2;
		}

		for (int i = 0; i < meanVec.size(); i++)
			cout << "meanVec[i]:  " << meanVec[i] << endl;
		system("pause");

		myUtils::saveVector("Means_Vector.data", meanVec);
		string otherPath = "C:\\Users\\Valerio\\Documents\\Visual Studio 2015\\Projects\\OpenCV\\Thesis_projects\\LFW\\Single_frame_AGGIORNATO\\Single_frame_AGGIORNATO\\";
		myUtils::saveVector(otherPath + "Means_Vector.data", meanVec);

		// Se voglio utilizzare come Testng il frame Normalizzato
		//meanStdDev(frame2_Norm, meanLast, stdLast);
		// Se voglio utilizzare come Testng il frame NON Normalizzato
		meanStdDev(frame2, meanLast, stdLast);

		cout << "meanLast:  " << meanLast[0] << endl;
		cout << "meanAlls.size:  " << meanAlls.size() << endl;

		//indexMin = DB_Response(meanVec,(float)meanLast[0]);
		std::vector<int> SelectedIndex(NumImageToSelect);
		SelectedIndex = DB_Response(meanVec, (float)meanLast[0], (int)NumImageToSelect);



		for (int indexMin = 0; indexMin < SelectedIndex.size(); indexMin++) {

			cout << "MIN_INdex[" << indexMin << "]:  " << SelectedIndex[indexMin] << endl;
			string Dir = Dir_init + to_string(SelectedIndex[indexMin] + 1) + "\\" + "LQP_featuresEnhancedVersion_#" + to_string(SelectedIndex[indexMin] + 1) + "_.txt";
			cout << Dir << endl;

			ifstream File; File.open(Dir, ios::in);
			Mat Data = Read_TXT_MAt(File, rowNum, colNum, (int)NumMaxFrame, faces);

			Mat DataWhited = Mat(NumMaxFrame*Data.rows, Data.cols, CV_32FC1);
			cout << "Data size:   " << Data.size() << endl;
			int Whitened = DataWhitening(Data, DataWhited);
			for (int i = 0; i < NumMaxFrame;i++)
				facesWhitened[i] = DataWhited.row(i);


			Mat Data_single = Mat(Data.rows, Data.cols, CV_32FC1);

			Whitened = DataWhitening(LAST, Data_single);

			//LAST.copyTo(facesWhitened[NumMaxFrame]);
			Data_single.copyTo(facesWhitened[NumMaxFrame]);

			/*
			for (int i = 0; i < 30; i++)
			cout << faces[countFrame - 1].at<float>(i) << " ";
			cout << endl << endl;
			for (int i = 0; i < 30; i++)
			cout << facesWhitened[countFrame - 1].at<float>(i) << " ";
			*/
			if (Whitened == 0) {
				cout << "CRITICAL ERROR IN DATA-WHITENING PHASE" << endl;
				system("pause");
				return;

			}


			for (int j = 0; j < NumMaxFrame; j++) {
				theta[indexMin][j] = (faces[NumMaxFrame].dot(faces[j])) / (norm(faces[NumMaxFrame])*(norm(faces[j])));
				thetaWhitened[indexMin][j] = (facesWhitened[NumMaxFrame].dot(facesWhitened[j])) / (norm(facesWhitened[NumMaxFrame]) * norm(facesWhitened[j]));
				//cout << "DOT P.:  " << (facesWhitened[NumMaxFrame].dot(facesWhitened[j])) << endl;
				//cout << "NORM:  "<<  norm(facesWhitened[j]) << endl;
				//thetaFile << theta[j] << " ";
				//thetaWhitenedFile << thetaWhitened[j] << " ";
			}
			AllResult[indexMin] = *std::max_element(std::begin(theta[indexMin]), std::end(theta[indexMin]));
			cout << "best res N " << indexMin << ":  " << AllResult[indexMin] << endl;
			AllResult_withened[indexMin] = *std::max_element(std::begin(thetaWhitened[indexMin]), std::end(thetaWhitened[indexMin]));
			cout << "best res Whitened N " << indexMin << ":  " << AllResult_withened[indexMin] << endl;

		}

		int bestIndex, best_withenedIndex;
		bestIndex = std::distance(begin(AllResult), std::max_element(std::begin(AllResult), std::end(AllResult)));
		best_withenedIndex = std::distance(begin(AllResult_withened), std::max_element(std::begin(AllResult_withened), std::end(AllResult_withened)));
		cout << "Best index " << bestIndex << endl;
		cout << "Best index Wthened " << best_withenedIndex << endl;
		system("pause");


		// Ora mi posso salvare il risultato migliore...
		ofstream thetaFile; thetaFile.open("Theta.txt", ios::out);
		ofstream thetaWhitenedFile; thetaWhitenedFile.open("ThetaWhitened.txt", ios::out);
		for (int j = 0; j < NumMaxFrame; j++) {
			thetaFile << theta[bestIndex][j] << " ";
			thetaWhitenedFile << thetaWhitened[best_withenedIndex][j] << " ";
		}
		thetaFile.close(); thetaWhitenedFile.close();

		//for (int j = 0; j < NumMaxFrame; j++)
		//cout << "thetaW.[" << j << "]: " << thetaWhitened[j] << endl;

		//system("cls");
		cout << "\n\n\n\n\n\n\n\n\n\n";
		cout << "-----------------------------------------------------------------------------\n";
		cout << "Max Theta:  " << *std::max_element(std::begin(theta[bestIndex]), std::end(theta[bestIndex])) << endl;
		cout << "Max ThetaWhitened:  " << *std::max_element(std::begin(thetaWhitened[best_withenedIndex]), std::end(thetaWhitened[best_withenedIndex])) << endl;
		meanStdDev(theta[bestIndex], mean, std); meanStdDev(thetaWhitened[best_withenedIndex], meanWhitened, stdWhitened);
		cout << "Theta Theresold (0.75):  " << mean + 0.75*std << "  ----  " << "ThetaWhitened (0.75):  " << meanWhitened + 0.75*stdWhitened << endl;
		//cout << "Theta Theresold (0.75):  " << mean + 0.75*std << endl;
		cout << "Theta Theresold (0.5):  " << mean + 0.5*std << "  ----  " << "ThetaWhitened (0.5):  " << meanWhitened + 0.5*stdWhitened << endl;
		cout << "-----------------------------------------------------------------------------\n";
		system("pause");


	}





}