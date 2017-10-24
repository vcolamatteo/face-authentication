#include"myUtils.h"

using namespace std;
using namespace cv;
using namespace myUtils;


string extern back_slash;

int my_PCA(Mat Data, Mat &DataWhitened,string Dir);
extern int colNum, rowNum;

int DataWhitening(Mat Data, Mat &DataWhitened)
{

	// CARICA DATI IN LETTURA....	
	//colNum = 21600; rowNum = 1;
	//colNum = 21600; rowNum = 5;
	colNum = Data.cols; rowNum = Data.rows;

	/*
	ifstream inputFile;

	//inputFile.open("LQP_feautures.txt");  //colNum = 21600; rowNum = 1;
	inputFile.open("Prova_LQP.txt");       //colNum = 21600; rowNum = 5;


										   //CutFile("LQP_SINGOLA.txt", 1,40);
										   //system("pause");

	float *Data_array = new float[rowNum*colNum];
	for (int row = 0; row < rowNum; row++)
	{
		for (int col = 0; col < colNum; col++)
		{
			inputFile >> *(Data_array + colNum * row + col);
		}
	}
	inputFile.close();

	Mat Data = Mat(rowNum, colNum, CV_32FC1, Data_array);
	*/
	/*
	for (int i = 0; i < 1; i++) 
		for (int j = 0; j < 30; j++)
			cout << Data.at<float>(i, j) << "  ";
	*/
	
	int Whitening = my_PCA(Data,DataWhitened,"");

	//system("pause");


	return Whitening;
}



int DataWhitening_V2(int NumMaxFrame, string fileToRead)
{

	// CARICA DATI IN LETTURA....	
	colNum = 21600; rowNum = NumMaxFrame*1;
	
	ifstream inputFile;
	inputFile.open((fileToRead+"LQP.txt").c_str());
	//cout << fileToRead + ".txt" << endl;
	float *Data_array = new float[rowNum*colNum];
	for (int row = 0; row < rowNum; row++)
	{
	for (int col = 0; col < colNum; col++)
	{
	inputFile >> *(Data_array + colNum * row + col);
	}
	}
	inputFile.close();

	Mat Data = Mat(rowNum, colNum, CV_32FC1, Data_array);
	Mat DataWhitened;	
	/*
	for (int i = 0; i < 1; i++)
	for (int j = 0; j < 30; j++)
	cout << Data.at<float>(i, j) << "  ";
	*/

	//cout << "HERE" << endl;
	//system("pause");
	int Whitening = my_PCA(Data, DataWhitened, fileToRead);
	//cout << "HERE" << endl;
	//system("pause");

	std::vector<float>Data_To_Vector;

	if (DataWhitened.isContinuous()) {
		Data_To_Vector.assign((float*)DataWhitened.datastart, (float*)DataWhitened.dataend);
	}
	//else {
		//for (int i = 0; i < Data.rows; ++i) {
			//array.insert(array.end(), (float*)mat.ptr<uchar>(i), (float*)mat.ptr<uchar>(i) + mat.cols);
		//}
	//}
	
	cout << "DataToVector size:  "<<Data_To_Vector.size() << endl;
	saveVector((fileToRead+"LQP.data"), Data_To_Vector);

	return Whitening;
}


int DataWhitening_V3(int NumMaxFrame, Mat Data,string fileToRead)
{
	//cout << "Daa size  " << Data.size() << endl;
	/*
	colNum = 21600; rowNum = NumMaxFrame * 1;
	ifstream inputFile;
	inputFile.open(fileToRead + ".txt");       //colNum = 21600; rowNum = 5;
											   //cout << fileToRead + ".txt" << endl;
	float *Data_array = new float[rowNum*colNum];
	for (int row = 0; row < rowNum; row++)
	{
		for (int col = 0; col < colNum; col++)
		{
			inputFile >> *(Data_array + colNum * row + col);
		}
	}
	inputFile.close();
	Mat Data2 = Mat(rowNum, colNum, CV_32FC1, Data_array);
	*/
	Mat DataWhitened;
	/*
	for (int i = 0; i < 1; i++)
	for (int j = 0; j < 100; j++)
	cout << Data.at<float>(19, j) << "  ";
	*/

	//cout << "HERE" << endl;
	//system("pause");
	int Whitening = my_PCA(Data, DataWhitened, fileToRead);
	//cout << "HERE" << endl;
	//system("pause");


	std::vector<float>Data_To_Vector;

	if (DataWhitened.isContinuous()) {
		Data_To_Vector.assign((float*)DataWhitened.datastart, (float*)DataWhitened.dataend);
	}
	//else {
	//for (int i = 0; i < Data.rows; ++i) {
	//array.insert(array.end(), (float*)mat.ptr<uchar>(i), (float*)mat.ptr<uchar>(i) + mat.cols);
	//}
	//}

	//cout << "DataToVector size:  "<<Data_To_Vector.size() << endl;
	saveVector((fileToRead + "LQP.data"), Data_To_Vector);

	return Whitening;
}



int my_PCA(Mat Data, Mat &DataWhitened, string Dir) {

	// La PCA non serve credo in realt�...
	//PCA pca(Data, cv::Mat(), CV_PCA_DATA_AS_COL, 0.95);
	//Mat point = pca.project(Data); // == Mat point;  pca.project(Data, point);
	
	//cout << "size  " << point.size() << endl;
	//system("pause");
	
	/*
	ofstream outputFile;
	
		// Stampa su file il risultato della proiezione...
		if (rowNum == 1)
			outputFile.open("Data_Single.txt");
		else
			outputFile.open("Data.txt");


		//cout << endl << endl << "Insieme dei punti nel nuovo spazio...  " << endl;
		for (int i = 0; i < Data.rows;i++) {
			for (int j = 0; j < Data.cols;j++)
				outputFile << Data.at<float>(i, j) << " ";
			outputFile << endl;
		}
		//cout << endl << endl << endl;
		outputFile.close();
	*/

	// FASE DI WHITENING DEI DATI....
	Mat point=Mat(Data.rows,Data.cols,CV_32FC1);
	// sottraggo la media
	for (int i = 0; i < point.rows; i++)
		point.row(i) = Data.row(i) - mean(Data.row(i))[0];
/*

		if (rowNum == 1)
			outputFile.open("Data_centered_SINGLE.txt");
		else
			outputFile.open("Data_centered.txt");



		for (int i = 0; i < point.rows;i++) {
			for (int j = 0; j < point.cols;j++)
				outputFile << point.at<float>(i, j) << " ";
			outputFile << endl;
		}

		//cout << endl << endl << endl;
		outputFile.close();
*/

	// calcolo matrice covarianza...
	Mat cov = (point*point.t()) / (point.cols - 1);

	//cout << "covSize "<<cov.size() << endl;
	// calcolo autovalori e autovettori della matrice di cov...
	Mat eigen, eigenVect;
	bool c = cv::eigen(cov, eigen, eigenVect);
	//cout << "Eigen size  " << eigen.size() << endl;
	//cout << "Vect size  "<<eigenVect.size() << endl;
	eigenVect = eigenVect.t();
	
	/*
	outputFile.open("Vect.txt");

	for (int i = 0; i < eigenVect.rows;i++) {
	for (int j = 0; j < eigenVect.cols;j++)
	outputFile << eigenVect.at<float>(i, j) << " ";
	outputFile << endl;
	}

	outputFile.close();

	*/

	//for (int j = 0; j < eigen.rows;j++) 
	//cout << 1.0 / sqrt(eigen.at<float>(j)) << endl;

	Mat D2 = Mat::zeros(eigen.rows, eigen.rows, CV_32FC1); // creo diretamente una matrice diagonale...

		for (int j = 0; j < eigen.rows;j++) 
				D2.at<float>(j, j) = 1.0 / sqrt(eigen.at<float>(j));

	/*
	//ofstream outputFile;
	outputFile.open("D2.txt");

	for (int i = 0; i < D2_Mat.rows;i++) {
	for (int j = 0; j < D2_Mat.cols;j++)
	outputFile << D2_Mat.at<float>(i, j) << " ";
	outputFile << endl;
	}

	outputFile.close();
	*/
	//cout << D2_Mat.size() << endl;
	//Mat Y2;
	//if (rowNum == 1)
		Mat Y2 = D2*eigenVect.t()*Data;
	//else
		//Y2 = D2_Mat*eigenVect.t()*point;

		ofstream outputFile;
			if (rowNum == 1)
				outputFile.open("Y2_SINGLE.txt");
			else
				outputFile.open((Dir+ back_slash + "Y2.txt").c_str());



			for (int i = 0; i < Y2.rows;i++) {
				for (int j = 0; j < Y2.cols;j++)
					outputFile << Y2.at<float>(i, j) << " ";
				outputFile << endl;
			}

			outputFile.close();		


	Y2.copyTo(DataWhitened);
	
	// sottraggo la media
	for (int i = 0; i < Y2.rows; i++)
		Y2.row(i) = Y2.row(i) - mean(Y2.row(i))[0];


		Mat covY2 = (Y2*Y2.t()) / (point.cols - 1);

	/*
	outputFile.open("COV_Y2.txt");
	//cout << "rows:  " << (float)covY2.rows << endl;

	for (int i = 0; i < covY2.rows;i++) {
	for (int j = 0; j < covY2.cols;j++)
	outputFile << covY2.at<float>(i, j) << " ";
	outputFile << endl;
	}
	outputFile.close();
	*/
	int Whitening = 0;
	//cout << "COARIANCE.at(0,0):  " << covY2.at<float>(0, 0) << endl;
	if (rowNum != 1) {
		if (round((float)sum(covY2)[0]) == (float)covY2.rows) {
			/*
			cout << endl << "------------------------------------------" << endl;
			cout << "\tWHTENING --->>> OK!" << endl;
			cout << endl << "------------------------------------------" << endl;
			*/
			Whitening = 1;

		}
		/*else {
			cout << endl << "------------------------------------------" << endl;
			cout << "\tWHTENING --->>> WRONG!" << endl;
			cout << endl << "------------------------------------------" << endl;

		}*/
	}
	else {
		if (round(covY2.at<float>(0, 0)) == (float)covY2.rows) {
			/*
			cout << endl << "------------------------------------------" << endl;
			cout << "\tWHTENING --->>> OK!" << endl;
			cout << endl << "------------------------------------------" << endl;
			*/
			Whitening = 1;

		}
		/*
		else {
			
			cout << endl << "------------------------------------------" << endl;
			cout << "\tWHTENING --->>> WRONG!" << endl;
			cout << endl << "------------------------------------------" << endl;			
		}
		*/
	}

	//cout<<"Sum Cov "<< sum(covY2)[0]<<endl;
	return Whitening;

}
