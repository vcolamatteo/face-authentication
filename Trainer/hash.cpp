#include"hash.h"
#include<vector>
//const int dimension = 150;


Hash::Hash(ifstream &input, int mode)
{

// di defualt ho mode==0 e mi limito a indivuare il numero di occorenze per ogni pattern (poi dopo effettuerò la scrematura con get_pattern)

	if (mode == 0) {
		string pattern;
		while (getline(input, pattern))
		{
			//cout << pattern << endl;
			pattern_map[pattern]++;
		}
	}
	else{

// altrimenti mi genero un file che contiene tutti i pattern nel loro ordine naturale, senza quindi avere (come altrimenti avrei) 
// un file con i pattern senza ripetizioni con la prima colonna del file che mi indica il numero di occoorenze

		std::vector<string>positon;
		ofstream h; h.open("all.txt", ios::out);
		string pattern;
		int count = 0;
		while (getline(input, pattern))
		{
			//cout << pattern << endl;
			//cout << pattern_map[pattern] << endl;
			//system("pause");;
			pattern_map[pattern]++;
			if (pattern_map[pattern] > mode) {
				positon.push_back(pattern);
				//cout << positon[count] << endl;
				count++;
			}
		}
		cout << positon.size() << endl;
		input.close();
		input.open("output.txt", ios::in);

		while (getline(input, pattern))
		{
			for (int i = 0; i < positon.size();i++) {
				//cout << positon[i] << endl;
				if (pattern == positon[i]) {
					//cout << pattern << endl;
					h << pattern << endl;
					break;
				}
			}

		}
		h.close();

	}
}


int Hash::get_pattern(ofstream &output, int theresold)
{
	map<string, int>::iterator loc;
	int count = 0;

	for (loc = pattern_map.begin();loc != pattern_map.end();++loc)
	{
		if (loc->second>theresold) {
			//cout << loc->second << " " << loc->first << endl;
			//cout << loc->second << endl;
			//cout << loc->first << endl;
			//system("pause");
			output << loc->second << " " << loc->first << endl;

			count++;
		}
	}

	return count;
}


int Hash::get_pattern_temp(int theresold)
{
	map<string, int>::iterator loc;
	int count = 0;

	for (loc = pattern_map.begin();loc != pattern_map.end();++loc)
	{
		if (loc->second>theresold)
			count++;

	}

	return count;
}