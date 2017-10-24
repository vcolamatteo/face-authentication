#pragma once
#include<fstream>
#include<vector>
#include<list>
#include<iostream>

#include <time.h>  
#include <numeric>
#include <algorithm>

using namespace std;
#define container vector
const int dimension = 50;


class Kmeans
{
public:
	int digit;

	Kmeans(int a,int b);

	float Kmeans::run_kmeans(int **data, int * weight, float **clucenter, int PatNum, int nround, vector<int> randNum, vector<int> randPatnum, int modality);

	int Kmeans::run_distance(int* a, float** b, float& dist, int& zeroDistance);
	float Kmeans::distanceToMin(float* a, float* b);
	float Kmeans::run_distance_2(float* a, float** b);
private:

	

	int clunum;

	container <int> cluster[dimension];
};
