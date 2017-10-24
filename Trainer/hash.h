#pragma once
#include<map>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;

class Hash
{
public:
	Hash(ifstream &input, int mode=0);
	//Hash::Hash(ifstream &input);

	int Hash::get_pattern(ofstream &output, int theresold);
	int Hash::get_pattern_temp(int theresold);

private:

	map<string,int> pattern_map;	
};
