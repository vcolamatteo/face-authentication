//2440,66.... float version
#include"kmeans.h"
#include"hash.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

Kmeans::Kmeans(int a, int b)
{
	digit = a;
	clunum = b;
}

// Display the contents of a map<string, int> by using an iterator.
void show(const char *msg, map<int, int> mp) {
	map<int, int>::iterator itr;

	cout << msg << endl;
	for (itr = mp.begin(); itr != mp.end(); ++itr)
		cout << "  " << itr->first << ", " << itr->second << endl;
	cout << endl;
}


float Kmeans::run_kmeans(int **data, int * weight, float **clucenter, int PatNum, int nround, vector<int> randNum, vector<int> randPatnum, int modality)
{
	//ifstream input;
	//ofstream output;
	//ofstream random;
	//input.open(input_file, ios::in);
	//ofstream random,output; random.open("random.txt",ios::out);
	//output.open("G.txt", ios::out);


	map<int, int> pattern_map_comparison;
	map<int, int> pattern_map_comparison_2;
	vector<float> result(dimension);

	int tmpint;  int exited = -1;
	//int count;


	/* initialize random seed: */
	//srand(time(NULL));

	// initiate the cluster center
	//float clucenter[dimension][digit];
	//int **clucenter = new int*[dimension];
	/*for (int i = 0; i < dimension; ++i) {
	clucenter[i] = new int[digit];
	}*/

	// RANDOM...

	if (modality == 1) {
		//cout << "Modality: RNPG" << endl;
		for (int j = 0;j != dimension;++j) {
			for (int i = 0;i != digit;++i)
			{
				int random = rand() % 3;
				clucenter[j][i] = random;
				//output << (clucenter[j][i]) << " ";
			}
			//output << endl;
		}
	}



	// carica array da fle...

	if (modality == 2) {
		//cout << "Modality: load external array" << endl;
		//ifstream i; i.open("c.txt",ios::in);	
		ifstream i; i.open("cluCenterFile.txt", ios::in);
		float *Data_array = new float[dimension*digit];
		for (int row = 0; row < dimension; row++)
		{
			for (int col = 0; col < digit; col++)
			{
				//i >> *(Data_array + colNum * row + col);
				i >> clucenter[row][col];
				//clucenter[row][col] = *(Data_array + colNum * row + col);
				//output << (clucenter[row][col]) << " ";
			}
			//output << endl;
		}
		i.close();
	}





	// devo generare un vettore di numeri di 150 casuali tra 0 e PatNum
	// allora mi genero prma una permutazione ta 0 e 150
	// e poi un'altra tra 0 e PatNum
	// infine basta che prendo dalla prima permutazone i valori della seconda in sucessione. 
	if (modality == 0) {
		//cout << "Modality: intra selecting random procedure" << endl;
		std::random_shuffle(randPatnum.begin(), randPatnum.end());

		std::random_shuffle(randNum.begin(), randNum.end());
		for (int j = 0;j < dimension;++j) {
			randNum[j] = randPatnum[randNum[j]];
			for (int i = 0;i != digit;++i)
			{
				clucenter[j][i] = data[randNum[j]][i];
			}
		}
	}


	/*for (std::vector<int>::iterator it = randNum.begin(); it != randNum.end(); ++it)
	//std::cout << ' ' << *it;
	random << *it << " ";

	random.close();*/
	//system("pause");

	//cout << "sdsdfdf" << endl;
	//system("pause");

	/*
	//  Dynamic memory allocation
	int **data = new int*[PatNum];
	for (int i = 0;i != PatNum;++i)
	{
	data[i] = new int[digit];
	}
	int *weight = new int[PatNum]; // num of occurrence for each pattern (midFile)


	//  input the data  (separate ocorrence e pattern)
	for (int i = 0;i != PatNum;++i)
	{
	input >> weight[i];
	//cout << "weght " << weight[i] << endl;

	for (int j = 0;j != digit;++j) {
	input >> data[i][j];  // save row pattern of midFile
	//cout << data[i][j] << " ";
	}
	//cout << endl << i << endl;
	//system("pause");
	}

	*/
	/*	if (modality == 0) {
	for (int j = 0;j != dimension;++j) {
	for (int i = 0;i != digit;++i)
	{
	//cout << randNum[j] << "  " << data[randNum[j]][i] << endl;
	//system("pause");
	clucenter[j][i] = data[randNum[j]][i];
	//output << (clucenter[j][i]) << " ";
	}
	//output << endl;
	}
	}
	*/
	/*	for (int j = 0;j != dimension;++j) {
	for (int i = 0;i != digit;++i)
	{

	output << (clucenter[j][i]) << " ";
	}
	output << endl;
	}*/

	//output.close();
	//input.close();

	//cout << "sdsdfdf" << endl;
	//system("pause");

	//int sumTotal; 
	float distTotal; int zeroDistance = 0;
	//float sum[digit];
	int* sum = new int[digit];
	for (int round = 0;round < nround;++round)
	{
		//sumTotal = 0; 
		float dist = 0; distTotal = 0;
		//cout << "round:" << round << endl;
		//   put the points into clusters
		for (int i = 0;i != PatNum;++i) { // cluster è un vector non continuo di array di interi di 150 elementi..
										  // cioè contiene degli array non in poszione cnsecutve ma sparsi, 
										  // ogni lta che la riga i-seima di midFile è a mnma distanza con la riga tmpnt di clucenter, alora aggiungo un aray in cluster in poszione tmpint
										  // e ci metto dentro il valore della i, cioè della riga di midFile peri tmpint (che è una ga di clucenter) è la rga a minima dsanza dalla riga i di midfile.

										  // misuro la dstanza tra ogni pattern del file di training da quantizzare e il file con c'inizializzazine casuale dei centoidi (clucenter)

										  // tmpint è il numero di pattern (riga dl file inizialzzato a caso,clucenter) che è alla mnima dstanza L2 dal pattern di riga i-esima del file da quantzzare (midFile)

			tmpint = run_distance(data[i], clucenter, dist, zeroDistance);
			distTotal = distTotal + dist;
			/*if (dist - (int)dist != 0) {
			cout << "dist:  "<<dist << endl;
			system("pause");
			}*/
			cluster[tmpint].push_back(i); // ad ogn passaggio aggiungo l aloe tmpnt ad un array 						
										  /*cout << i<<"  "<< "  "<< tmpint<<"  "<<cluster[tmpint].size()<<endl;
										  for (int u = 0; u < cluster[tmpint].size();u++)
										  cout << cluster[tmpint][u] << " ";
										  cout << endl;
										  system("pause");*/


			if (zeroDistance == 1) {
				zeroDistance = 0;
				break;
			}
#ifdef DEBUG
			for (int m = 0;m < digit;m++)
				cout << data[i][m] << " ";
			cout << endl;
			cout << "roune=" << round << "  Pic:" << i << "  clu:" << tmpint << endl;
#endif
		}
		//cout << "distTotal:  " << distTotal << endl;
		//system("pause");
		// quindi all fne d questo ciclo cluster conterrà tutt i PatNum punti distiubuit in un certo numero di cluster, dpende dai punti...
		// ad es. dopo 17 iterazioni si è auto per 15 volte il valore 25 come tmpint e quindi si avrà, cluster[25]=[0 1 2 3 4 5 6 7 8 11 13 14 15 16 17]		
		// in particlare poi, solo due cluster su 17 (il 25 e i 2) saranno aggiunti nell'array cluster (xciò è un vettore sparso...)

		//system("pause");

		// ora siccome è un veore sparso cluster, devo verifcare qauli de 150 possibli cluster contiene degli elemti

		//   recalculate the clustercenters
		//count = 0;
		//sumTotal = 0;
		for (int j = 0;j != dimension;++j)
		{
			float weightSum = 0;
			for (int i = 0;i != digit; ++i)
				sum[i] = 0;
			//#ifdef DEBUG
			if (cluster[j].size() != 0) {
				//cout << " j=" << j << " size=" << cluster[j].size() << endl;
				if (nround == 0) {
					pattern_map_comparison[j] = cluster[j].size();
					pattern_map_comparison_2[j] = cluster[j].size();
					//	show("Contents of m2: ", pattern_map_comparison);
					//  show("Contents of m2: ", pattern_map_comparison_2);
					//	system("pause");	
				}
				else
					pattern_map_comparison_2[j] = cluster[j].size();
			}
			//#endif

			/* ad es. i primi 5 non hanno element, il 6° ne ha 6, che sono:
			787  2
			918  2
			920  2
			934  2
			1192  2
			1323  3

			Il primo numero indica la riga i contenuta nell'array j di cluster, cioè il valore di i del ciclo prcdente, cioè *loc, (mentr 6 è l ho valre tmpint)
			Il secondo numero inda invece il peso, ossia il prmo numero di gni riga dl midFile (cioè weight[(*loc)]), che sono poi stat tutti copiati nel vettore weight
			*/

			for (container<int>::iterator loc = cluster[j].begin();loc != cluster[j].end();++loc)  // da 0 a 5...
			{

				weightSum += weight[(*loc)]; // sommo tutti i pesi dell'array di posizione j di cluster, ossia il numero di occorrenze del singolo pattern del fil midFile nel file output iniziale...
											 //cout << cluster[j].size()<<"  "<<(*loc)<<"  "<<weight[(*loc)] << endl;
											 //system("pause");

											 // ora somma i valor d tutte le righe d posizione (*loc), che lo rcordo ancora, sono tutte le righe del file miDfile che sno a disyanza minima 
											 // rispetto a una stessa rga del file clucenter (la sesta ad es.), ovamnt devo moltiplicare ogni valore della rga per il numero di occorenze weight[(*loc)]

				for (int i = 0;i != digit;++i)
				{
					//cout << "i= "<<i << "  data: " << data[(*loc)][i] << endl;
					//system("pause");
					//cout << "zzz N: "<<i<<"  "<<sum[i] << endl;
					sum[i] += data[(*loc)][i] * weight[(*loc)];
					//cout << "post  zzz:" << sum[i] << endl;
					//sumTotal = sumTotal + sum[i];
					//system("pause");
#ifdef DEBUG
					cout << sum[i] << " ";
#endif
				}
			}

			/*
			for(int i=0;i!=digit;++i)
			sum[i] /= weightSum;
			*/

			if (cluster[j].size() != 0) {  // se nn cambia nessun  j esci...
				for (int i = 0;i != digit;++i)
				{
					clucenter[j][i] = (sum[i] / weightSum);
					//cout << clucenter[j][i] << endl;
					//system("pause");
					//clucenter[j][i] = std::round(sum[i] / weightSum);

					/*					if (clucenter[j][i] > 2) {
					cerr << "j " << j << " i " << i << endl;
					cerr << "cluster[j].size() " << cluster[j].size() << endl;
					for (container<int>::iterator loc = cluster[j].begin();loc != cluster[j].end();++loc)
					{
					sum[i] += data[(*loc)][i];
					cerr << data[(*loc)][i] << "   " << sum[i] << endl;
					}
					cerr << "sum[i] " << sum[i] << " sum[i] / cluster[j].size() " << sum[i] / cluster[j].size() << endl;
					exit(0);
					}*/
#ifdef DEBUG
					cout << clucenter[j][i] << " ";
#endif
				}


				// calculate distance					
				/*for (container<int>::iterator loc = cluster[j].begin();loc != cluster[j].end();++loc)
				{
				result[j] = distanceToMin(data[(*loc)], clucenter[j]);
				//cout << result[j] << endl;
				}*/

				//count++;
				cluster[j].clear();

				/*if (nround == 0 || count != countJ_a)
				countJ_a = count;
				else if (countJ_vec_a == countJ_vec_b) {
				cout << "EXIT" << endl;
				return 0;
				}*/
			}


		} // j  from 1-->150
		  //cout<<"total res:"<< std::accumulate(result.begin(), result.end(), 0)<<endl;


		  /*float square_sum[dimension];
		  float *g = square_sum;
		  for (int i = 0;i != PatNum;++i) {
		  dist = dist + run_distance_2(data[i], clucenter);
		  //cout << "dist:  " << dist << endl;
		  #ifdef DEBUG
		  for (int m = 0;m<digit;m++)
		  cout << data[i][m] << " ";
		  cout << endl;
		  cout << "roune=" << round << "  Pic:" << i << "  clu:" << tmpint << endl;
		  #endif
		  }
		  cout << "dist:  " << dist << endl;

		  dist = 0.0;
		  */

		  //result.clear();
		  //cout << "change:  " << count << endl;
		  //cout << "SumTotal:  " << sumTotal << endl;
		  //system("pause");

		if (pattern_map_comparison == pattern_map_comparison_2) {
			//cout << "Converged at round: " << round << endl;
			exited = 1;
			break;
			return 0;
		}
		else
			pattern_map_comparison = pattern_map_comparison_2;

		pattern_map_comparison_2.clear();



		//cout << "distTotal:  " << distTotal << endl;
	} // nround
	  //cout << "HERE" << endl;
	if (exited == -1) {
		cout << "----------------------------------------------" << endl;
		cout << "Warning: missed convergence in 30 run...!" << endl;
		cout << "----------------------------------------------" << endl;
	}


	//cout << "SumTotal:  " << sumTotal << endl;

	/*
	output.close();
	output.open("cluCenterFile.txt", ios::out | ios::trunc);


	//   output the clustercenters
	for (int j = 0;j != dimension;++j)
	{
	//		if(cluster[j].size() != 0){
	for (int i = 0;i != digit;++i)
	{
	output << std::round(clucenter[j][i]) << " ";
	}
	output << endl;
	//		}
	}
	*/

	//output.close();

	/*
	//   Dynamic memory dispose
	for (int i = 0;i != PatNum;++i)
	{
	delete[] data[i];
	}
	delete[] data;
	delete[] weight;
	*/

	return distTotal;
}




int Kmeans::run_distance(int* a, float** b, float& dist, int& zeroDistance)
{
	//int square_sum[dimension];
	vector<float>square_sum(dimension);
	//int min = 10000;
	//int flag;

	/*	for (int u = 0; u < 48;u++)
	cout << a[u] << " ";
	cout << "------------------"<<endl;	*/

	// calculate the distance	
	for (int j = 0;j != dimension;++j)
	{
		square_sum[j] = 0;

		for (int i = 0;i != digit;++i)
		{
			//square_sum[j] += (a[i]-*(b+j*digit+i))*(a[i]-*(b+j*digit+i));

			square_sum[j] = square_sum[j] + (a[i] - (b[j][i]))*(a[i] - (b[j][i]));
			/*if (square_sum[j] - (int)square_sum[j] != 0) {
			cout << i << "  " << j << "square_sum[j]  " << square_sum[j] << endl;
			system("pause");
			}*/
			//cout << "a:  " << *a << "  b:  " << *b << "  " <<i<<"  "<<j<< "  bb  "<<(j*digit + i) <<"  "<<*(b + j*digit + i)<<"  "<<square_sum[j] << endl;
			//system("pause");
			/*cout << (a[i] - *(b + j*digit + i)) << "  " << (a[i] - *(b + j*digit + i)) << endl;
			cout << "a:  "<<*a<<"  b:  "<<*b<<"  "<<square_sum[j] << endl;
			system("pause");*/
			//cout << i<<"  "<<j<<"  "<<b[j][i] << endl;
			//system("pause");
		}
		if (square_sum[j] == 0.0) {
			/*zeroDistance = 1;
			for (int i = 0;i != digit;++i)
			cout << a[i] << " ";
			cout << endl;
			for (int i = 0;i != digit;++i)
			cout << b[j][i] <<" ";
			cout<<endl;
			system("pause");*/
			dist = square_sum[j];
			return j;
		}
		//cout << j << "  square_sum[j]  " << square_sum[j] << endl;
	}


	//int min_2 = *std::min_element(square_sum.begin(), square_sum.end());
	//cout << "MY  " << min_2 <<endl;
	std::vector<float>::iterator result = std::min_element(std::begin(square_sum), std::end(square_sum));
	int min = std::distance(std::begin(square_sum), result);
	dist = square_sum[min];
	//cout << "MY  " << square_sum[min_2] <<"  at:  "<<min_2<<endl;
	//std::cout << "min element at: " << std::distance(std::begin(square_sum), result);

	/*
	// return the min distance and flag
	for (int j = 0;j != dimension;++j)
	{
	if ((int)square_sum[j]<(int)min) {
	min = square_sum[j];
	flag = j;
	#ifdef DEBUG
	cout << square_sum[j] << " ";
	cout << flag << " ";
	#endif
	}
	}
	*/

	//cout << "min:  " << min << "flag:  " << flag << endl;
	//system("pause");


#ifdef DEBUG
	//cout << endl << flag << endl;
	cout << "min:  " << min << "flag:  " << flag << endl;
	for (int u = 0; u < 48;u++)
		cout << b[flag][u] << " ";
	cout << endl;


	cout << "FINAL" << endl;
	cout << "suqare " << square_sum[flag] << endl;
	system("pause");

	square_sum[flag] = 0;
	for (int u = 0; u < 48;u++) {
		cout << "ccc  " << u << "  " << (a[u] - (b[flag][u])) << "  for 2 :" << (a[u] - (b[flag][u]))*(a[u] - (b[flag][u])) << endl;
		square_sum[flag] = square_sum[flag] + (a[u] - (b[flag][u]))*(a[u] - (b[flag][u]));
		cout << "u: " << u << " " << square_sum[flag] << endl;
	}

	system("pause");
#endif
	return min;
}


float Kmeans::distanceToMin(float* a, float* b)
{
	float distance = 0.0;

	// calculate the distance	
	for (int i = 0;i != digit;++i)
	{
		//square_sum[j] += (a[i]-*(b+j*digit+i))*(a[i]-*(b+j*digit+i));
		distance += (a[i] - (b[i])*(a[i] - (b[i])));
		//cout<< i << "  " << j << "square_sum[j]  "<<square_sum[j] << endl;
		//system("pause");
		//cout << "a:  " << *a << "  b:  " << *b << "  " <<i<<"  "<<j<< "  bb  "<<(j*digit + i) <<"  "<<*(b + j*digit + i)<<"  "<<square_sum[j] << endl;
		//system("pause");
		/*cout << (a[i] - *(b + j*digit + i)) << "  " << (a[i] - *(b + j*digit + i)) << endl;
		cout << "a:  "<<*a<<"  b:  "<<*b<<"  "<<square_sum[j] << endl;
		system("pause");*/
	}
	//cout << j << "  square_sum[j]  " << square_sum[j] << endl;



	return distance;
}

float Kmeans::run_distance_2(float* a, float** b)
{


	float square_sum[dimension], min = 10000;
	int flag;

	// calculate the distance	
	for (int j = 0;j != dimension;++j)
	{
		square_sum[j] = 0;

		for (int i = 0;i != digit;++i)
		{
			//square_sum[j] += (a[i]-*(b+j*digit+i))*(a[i]-*(b+j*digit+i));
			square_sum[j] += (a[i] - (b[j][i])*(a[i] - (b[j][i])));
			//cout<< i << "  " << j << "square_sum[j]  "<<square_sum[j] << endl;
			//system("pause");
			//cout << "a:  " << *a << "  b:  " << *b << "  " <<i<<"  "<<j<< "  bb  "<<(j*digit + i) <<"  "<<*(b + j*digit + i)<<"  "<<square_sum[j] << endl;
			//system("pause");
			/*cout << (a[i] - *(b + j*digit + i)) << "  " << (a[i] - *(b + j*digit + i)) << endl;
			cout << "a:  "<<*a<<"  b:  "<<*b<<"  "<<square_sum[j] << endl;
			system("pause");*/
		}
		//cout << j << "  square_sum[j]  " << square_sum[j] << endl;
	}


	// return the min distance and flag
	for (int j = 0;j != dimension;++j)
	{
		if (square_sum[j]<min) {
			min = square_sum[j];

#ifdef DEBUG
			cout << square_sum[j] << " ";
			cout << flag << " ";
#endif
		}
	}
#ifdef DEBUG
	cout << endl << flag << endl;
#endif
	return min;
}