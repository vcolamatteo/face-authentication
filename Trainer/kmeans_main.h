#pragma once
#include"hash.h"
#include"kmeans.h"
#include <time.h>

extern string Dir_initNorm;

#define dynamicThersold_

int kmeans_(string outputTxt, string MidRes, string cluCenter)
{

	/* initialize random seed: */
	srand(time(NULL)); // se non lo metto la funzone shuffle m genera sempre la stessa sequaenza casuale...lo deo mettre all'inizio altrimenti
					   //il meccansm d gnerazione è più lento dell'esecuzione...credo sia ntrno al secondo (opppur devo mter un system-pause)

	/*if (argc != 4) {
		cerr << "Usage: ./KMeans input midres output\n";
		return -1;
	}*/

	ofstream cc;
	cc.open(Dir_initNorm + "k_means.txt",ios::out);

	int run = 100;
	int attempts = 10;
	int modality = 0;

	// find the patterns appearing more than 10 times
	ifstream input;
	ofstream output;
	input.open(outputTxt, ios::in);
	//input.open("output.txt", ios::in);	
	//output.open("midRes.txt", ios::out);

	int PatNum = 0;
	Hash hash_pattern(input);

#ifdef dynamicThersold
	int done = 0;
	int theresold = 5;bool iter = 1;
		std::vector<int>patNum_vec(5); vector<int>PatNum_signs(5);
	int PatNum_copy = 0; int PatNum_index_copy = 0;
	while (iter)
	{
		//output.open(MidRes, ios::out);
		PatNum = hash_pattern.get_pattern_temp(theresold);		
		
		if (PatNum >= 700)
			PatNum_signs[abs(theresold - 5)] = 1;
		else
			PatNum_signs[abs(theresold - 5)] = -1;

		patNum_vec[abs(theresold - 5)] = abs(700 - PatNum);
		cout << "xx  "<<patNum_vec[abs(theresold - 5)] << endl;
		cc << "xx  " << patNum_vec[abs(theresold - 5)] << endl;
		theresold--;
		cout << PatNum << endl;
		cc << PatNum << endl;
		output.close();
		if (PatNum >= 700 && PatNum <= 599) {
			iter = 0;
			done = 1;

		}
		if (theresold == -1) {			
			std::vector<int>::iterator PatNum_it = std::min_element(std::begin(patNum_vec), std::end(patNum_vec));
			int PatNum_index = std::distance(std::begin(patNum_vec), PatNum_it);
			if (PatNum_signs[PatNum_index] == -1) {
				PatNum = abs(700 - patNum_vec[PatNum_index]);
				//cout << "<=700" << endl;
				//cout << patNum_vec[PatNum_index] << endl;
			}
			else
				PatNum = abs(700 + patNum_vec[PatNum_index]);

			cout << "NN  "<<PatNum_index << "  " << PatNum<<endl;
			cc<< "NN  " << PatNum_index << "  " << PatNum << endl;
			theresold = PatNum_index;

			if (PatNum < 700) {
				PatNum_copy = PatNum;
				PatNum_index_copy = PatNum_index;
				patNum_vec[PatNum_index] = 9999;
				PatNum_it = std::min_element(std::begin(patNum_vec), std::end(patNum_vec));
				PatNum_index = std::distance(std::begin(patNum_vec), PatNum_it);
				if (PatNum_signs[PatNum_index] == -1) {
					PatNum = abs(700 - patNum_vec[PatNum_index]);
					cout << "<=700" << endl;
					cout << patNum_vec[PatNum_index] << endl;

					cc << "<=700" << endl;
					cc << patNum_vec[PatNum_index] << endl;
				}
				else
					PatNum = abs(700 + patNum_vec[PatNum_index]);
				
				cout << "N E W :       NN  " << PatNum_index << "  " << PatNum << endl;
				cc << "N E W :       NN  " << PatNum_index << "  " << PatNum << endl;

				if (PatNum >= 600) {
					if (abs(PatNum - 600) < abs(PatNum_copy - 700)) {
						break;
						theresold = PatNum_index;
					}
					else {
						PatNum = PatNum_copy;
						theresold = PatNum_index_copy;
					}
				}
				else {
					PatNum = PatNum_copy;
					theresold = PatNum_index_copy;
				}
			}
			
			iter = 0;
			cout << "getted zero-Value Thersold!" << endl;
			cc << "getted zero-Value Thersold!" << endl;
		}
	}

	cout << "theresold:  "<<theresold << endl;
	//cc << "theresold:  " << theresold << endl;
	theresold = 1;
	cout << "theresoldCorrected:  " << theresold << endl;
	cc << "theresoldCorrected:  " << theresold << endl;

	output.open(MidRes, ios::out);
	if(done==1)
	PatNum = hash_pattern.get_pattern(output, theresold);
	else
		PatNum = hash_pattern.get_pattern(output, theresold);
	output.close();

#else
	/*int theresold = 5;
	while (PatNum<700)
	{
		output.open(MidRes, ios::out);
		PatNum = hash_pattern.get_pattern(output, theresold);
		theresold--;
		cout << PatNum << endl;
		output.close();

	}
*/

	int theresold = 1;
	output.open(MidRes, ios::out);
	PatNum = hash_pattern.get_pattern(output, theresold);
	output.close();
#endif

	input.close();

	cout << PatNum << "  -- " << theresold<<endl;
	cc << PatNum << "  -- " << theresold << endl;


	// run kmeans		
	//input.open(argv[2],ios::in);
	//output.open("midRes.txt", ios::in);
	//output.open(argv[3],ios::out);
	//output.open("r.txt", ios::out);


	Kmeans pattern_kmeans(48, dimension);


	//string input_file = "midResults.txt";
	//string output_file = "cluCenterFile.txt";
	input.open(MidRes, ios::in);

	float **clucenter = new float*[dimension];
	for (int i = 0; i < dimension; ++i) {
		clucenter[i] = new float[48];
	}


	//  Dynamic memory allocation
	int **data = new int*[PatNum];
	for (int i = 0;i != PatNum;++i)
	{
		data[i] = new int[48];
	}
	int *weight = new int[PatNum]; // num of occurrence for each pattern (midFile)


								   //  input the data  (separate ocorrence e pattern)
	for (int i = 0;i != PatNum;++i)
	{
		input >> weight[i];
		//cout << "weght " << weight[i] << endl;

		for (int j = 0;j != 48;++j) {
			input >> data[i][j];  // save row pattern of midFile
								  //cout << data[i][j] << " ";
		}
		//cout << endl << i << endl;
		//cout << "i  "<<i<<"  weght " << weight[i] << endl;
		//system("pause");
		//cout << endl;
	}
	//int **data2; data2 = data;

	//system("pause");

	std::vector<float**>clucenterBest(attempts);

	std::vector<float>sumTotal(attempts);

	vector<int> randNum(dimension), randPatnum(PatNum);

	if (modality == 0) {
		for (int j = 0;j < PatNum;++j) {
			randPatnum[j] = j;
		}
		for (int j = 1;j < dimension + 1;++j) {
			//randNum[j] = 1 + rand() % PatNum;
			randNum[j - 1] = j;
			//cout << randNum[j-1] << endl;
			//system("pause");
		}

	}
	
//	clock_t begin = clock();

	for (int i = 0; i < attempts; i++) {
	/*	if (i == 0) {
			if(modality==0)
				cout << "Modality: intra selecting random procedure" << endl;
			else if (modality == 2)
				cout << "Modality: load external array" << endl;
			else
				cout << "Modality: RNPG" << endl;
		}*/
		sumTotal[i] = pattern_kmeans.run_kmeans(data, weight, clucenter, PatNum, run, randNum, randPatnum,modality);
		//cout << sumTotal[i] << endl;
		//clucenterBest.push_back(clucenter);
		clucenterBest[i]=clucenter;
	}
	/*clock_t end = clock();		
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "elapsed tim:  " << elapsed_secs << endl;*/
	
	std::vector<float>::iterator result = std::min_element(std::begin(sumTotal), std::end(sumTotal));
	int min = std::distance(std::begin(sumTotal), result);
	cout << "MIN:  " << sumTotal[min] << endl;
	cc << "MIN:  " << sumTotal[min] << endl;

	//system("pause");


	output.open(cluCenter, ios::out | ios::trunc);


	//   output the clustercenters
	for (int j = 0;j != dimension;++j)
	{
		for (int i = 0;i != 48;++i)
		{
			output << std::round(clucenterBest[min][j][i]) << " ";
		}
		output << endl;
	}


	output.close();
	cc.close();

	//   Dynamic memory dispose
	for (int i = 0;i != PatNum;++i)
	{
		delete[] data[i];
	}
	delete[] data;
	delete[] weight;
	


/*
ifstream input; input.open("all.txt",ios::in);
int rowNum = 3344; int colNum = 48;
float *Data_array = new float[rowNum*colNum];
for (int row = 0; row < rowNum; row++)
{
	for (int col = 0; col < colNum; col++)
	{
		input >> *(Data_array + colNum * row + col);
	}
}

cv::Mat g, centers,labels;
cv::Mat Data = cv::Mat(rowNum, colNum, CV_32FC1, Data_array);
clock_t begin = clock();
//for (int i = 0; i < 10;i++) {
	double f = cv::kmeans(Data, 150, labels, cv::TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 30, 0.0001), 10, cv::KMEANS_RANDOM_CENTERS, centers);
	//cout << f << endl;
//}
clock_t end = clock();
double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
cout << "elapsed tim:  " << elapsed_secs << endl;
cout << f << endl;
*/
	return 0;
}
