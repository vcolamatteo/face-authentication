#include "myUtils.h"
#include<iostream>

#ifdef _WIN32
#include <direct.h>
#include <conio.h>
#define GetCurrentDir _getcwd
#else
#include<dirent.h>
#include <unistd.h>
#define GetCurrentDir getcwd
#include "patch_namespace.h"
#endif
#include "Mat_to_binary.h"
#include "dirent.h"


extern string Sys_language;

namespace myUtils {

	// su windows non server xkè il comando system pausecambia da solo in base alla lingua...
void getSysLanguage(string& Sys_language) {


	char lang[10]; char* p; p = lang;
	//cout<<setlocale(LC_CTYPE, "")<<endl;
	for (int i = 0; i<5;i++) {
		p[i] = setlocale(LC_CTYPE, "")[i];
		//cout<<p[i];
	}//cout<<endl;
	string L = lang; //L=L.substr(0,L.length()-1);
	std::transform(L.begin(), L.end(), L.begin(), ::toupper);
	L = L.substr(0, 2);
	//cout<<L<<endl;
	if (L == "IT")
		Sys_language = "IT";
	else
		Sys_language = "EN";

	//cout<<"sys: "<<Sys_language<<endl;
}

void system_pause(){

#ifndef WIN32_  // Considero solo italiano e inglese
	//cout<<"lang:   "<<Sys_language<<endl;
	if(Sys_language=="IT"){
//std::cin.ignore(1024, '\n');
cout << "Premere invio per continuare...";
std::cin.get();
	}else{

		cout << "Press enter to continue...";
		std::cin.get();
	}

#else
system("pause");
#endif
}


#ifdef WIN32
	void MyEntry() {   // customized starting point

		printf("Premere un tasto per iniziare:\n");
		_getch();

	}

	void MyQuit()     // customized ending point
	{
		printf("Premere un tasto per terminare:\n");
		_getch();
		_getch();

	}


	void myExit_Error() {
		printf("Esecuziona terminata con errore. Permi un tasto per uscire immediatamente.\n");
		_getch();

	}

#endif


	void  DeleteSeveralFile(string FILE_LQP, string out) {

		//thesis::delete_file(cluCetenter.c_str());	
		thesis::delete_file(FILE_LQP.c_str());
		thesis::delete_file(out.c_str());


	}

	void CleanDirectory(string directory, string directory_database) {


		bool c = thesis::isDirectory(directory);
		if (c == 0)
			thesis::make_dir(directory.c_str());
		else {
			// delete_file mi cancella solo i file in una cartella se i file sono contenuti in una cartella non li cancella, allora la cancello tutta e la ricreo vuota
			thesis::delete_folder(directory.c_str());
			thesis::make_dir(directory.c_str());
		}

		//vector<cv::Mat> featureMaps;
		//vector<float> featureVector;


		// controlla se esiste o meno la directory in cui salvare le immagini, se non esiste la crea...

		c = thesis::isDirectory(directory_database);
		if (c == 0)
			thesis::make_dir(directory_database.c_str());
		else // cancella tutti i file nella directory...
			thesis::delete_file(directory_database.c_str());


	}
#ifdef WIN32
	bool timeData(string& Time, string& Data, int Time_calc, int Data_calc) {

		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 80, "%d-%m-%Y_%I_%M_%S", timeinfo);
		std::string time(buffer);

		if (Time_calc == 1 && Data_calc == 1) {  // crea le folder solo se devo calcolare la data
			Data = time.substr(0, time.find('_'));
			//cout << data << endl;
			if (thesis::isDirectory("Database_Normalized") == 0) { //if (thesis::isDirectory("Database\\") == 0)
				thesis::make_dir("Database_Normalized");
				Time = time.substr(time.find('_') + 1, time.length());
				return false;
			}
			if (thesis::isDirectory(("Database_Normalized\\" + Data + "\\").c_str()) == 0) { // if (thesis::isDirectory(("Database\\" + Data + "\\").c_str()) == 0)
			    //thesis::make_dir(("Database\\" + Data + "\\").c_str());
				Time = time.substr(time.find('_') + 1, time.length());
				//return false;
			}
			//mkdir(("frames/"+data).c_str());
			//system(("mkdir -p /frames/" + data).c_str());
			Time = time.substr(time.find('_') + 1, time.length());

		}

		else if (Time_calc == 1 && Data_calc == 0)
			Time = time.substr(time.find('_') + 1, time.length());

		else if (Time_calc == 0 && Data_calc == 1) {
			Data = time.substr(0, time.find('_'));
			if (thesis::isDirectory(("frames" + Data + "\\").c_str()) == 0) //if (thesis::isDirectory(("frames\\" + Data + "\\").c_str()) == 0)
				thesis::make_dir(("frames\\" + Data + "\\").c_str()); // thesis::make_dir(("frames\\" + Data + "\\").c_str());
		}
	}

#else
	bool timeData(string& Time, string& Data, int Time_calc, int Data_calc) {

		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 80, "%d-%m-%Y_%I_%M_%S", timeinfo);
		std::string time(buffer);

		if (Time_calc == 1 && Data_calc == 1) {  // crea le folder solo se devo calcolare la data
			Data = time.substr(0, time.find('_'));
			//cout << data << endl;
			if (thesis::isDirectory("Database_Normalized") == 0){ //if (thesis::isDirectory("Database\\") == 0)
				thesis::make_dir("Database_Normalized");
				Time = time.substr(time.find('_') + 1, time.length());
				return false;
			}
			if (thesis::isDirectory(("Database_Normalized/" + Data + "/").c_str()) == 0){ // if (thesis::isDirectory(("Database\\" + Data + "\\").c_str()) == 0)
				//thesis::make_dir(("Database_Normalized/" + Data + "/").c_str());  //thesis::make_dir(("Database\\" + Data + "\\").c_str());
				Time = time.substr(time.find('_') + 1, time.length());
			//return false;
			}
			//mkdir(("frames/"+data).c_str());
			//system(("mkdir -p /frames/" + data).c_str());
			Time = time.substr(time.find('_') + 1, time.length());

		}

		else if (Time_calc == 1 && Data_calc == 0)
			Time = time.substr(time.find('_') + 1, time.length());

		else if (Time_calc == 0 && Data_calc == 1) {
			Data = time.substr(0, time.find('_'));
			if (thesis::isDirectory(("frames" + Data + "/").c_str()) == 0) //if (thesis::isDirectory(("frames\\" + Data + "\\").c_str()) == 0)
				thesis::make_dir(("frames/" + Data + "/").c_str()); // thesis::make_dir(("frames\\" + Data + "\\").c_str());
		}

		return true;
	}
#endif


#ifdef WIN32
#pragma comment(lib, "Winmm.lib")  // for the sound...

	void playSound(string file) {
		char file_to_play[200];
		sprintf(file_to_play, "resources\\sounds\\%s", file.c_str());
		PlaySound(file_to_play, NULL, SND_FILENAME); //SND_FILENAME or SND_LOOP



	}
#else
	void playSound(string file) {

		char file_to_play[200];
		sprintf(file_to_play, "aplay  resources/sounds/%s  --quiet",file.c_str());
		//cout<<file_to_play<<endl;
		system(file_to_play);
	    //system("aplay resources/sounds/camera_shutter_cutted.wav --quiet");
	}


#endif

	cv::Mat LoadMatrix(string B, int colNum, int rowNum) {

		ifstream input;
		input.open(B.c_str());
		float *Data_array = new float[rowNum*colNum];
		//float sum1 = 0.0;
		for (int row = 0; row < rowNum; row++)
		{
			for (int col = 0; col < colNum; col++)
			{

				input >> *(Data_array + colNum * row + col);
				//sum1 = sum1 + *(Data_array + colNum * row + col);
				//cout << *(Data_array + colNum * row + col) <<" ";
			}
		}
		//cout << "SUM1 --- :  " << sum1 << endl;
		//system("pause");

		input.close();
		cv::Mat Matrix = cv::Mat(1, rowNum*colNum, CV_32FC1, Data_array);
		delete[] Data_array;
		return Matrix;


	}

	void CleanActions(string directory) {

		bool c = thesis::isDirectory(directory);
		if (c == 1) {
			// delete_file mi cancella solo i file in una cartella se i file sono contenuti in una cartella non li cancella, allora la cancello tutta e la ricreo vuota
			thesis::delete_folder(directory.c_str());
			thesis::make_dir(directory.c_str());
		}

		myUtils::DeleteSeveralFile("LQP_features.txt", "LQP_feautures_Backup.txt");

	}

	void copyFile(string file_toCopy, string file_whereCopyFile1) {

		fstream stream1("LQP_features.txt");
		ofstream stream2("LQP_feautures_Backup.txt", ios::app);
		stream2 << stream1.rdbuf();
		//out << stream1.rdbuf();
		stream1.close(), stream2.close();


	}


	std::vector<float> loadVectorKnownSize(std::ifstream& in, int size) {

		Mat MeanV=Mat();

		bool c = readMatBinary(in, MeanV);
		in.close();
	    //MeanV=MeanV.reshape(1, 20);
		cout << "MeanV size:   "<< MeanV.size() << endl;

		std::vector<float> newVector(size);
		float* k; k= &MeanV.at<float>(0);
		for (int i=0; i<size; i++)
		newVector[i] = k[i];
		//cout << "VEC size:   " << newVector.size() << endl;

		//for (int i = 0; i < newVector.size(); i++)
		  //cout << newVector[i]<<" ";

		return newVector;
	}



	std::vector<float> loadVector(string nameFileToSaveAsVector) {

		std::ifstream in; in.open(nameFileToSaveAsVector.c_str(), std::ios_base::binary);

		Mat MeanV = Mat();

		bool c = readMatBinary(in, MeanV);
		in.close();
		//MeanV=MeanV.reshape(1, 20);
		//cout << "MeanV size:   "<< MeanV.size() << endl;

		std::vector<float> newVector;
		float* k; k = &MeanV.at<float>(0);
		//for (int i=0; i<4; i++)
		int i = 0;
		while (1) {
			newVector.push_back(k[i]);
			i++;
			if (k[i] == NULL)
				break;
		}
		//cout << "VEC size:   " << newVector.size() << endl;

		//for (int i = 0; i < newVector.size(); i++)
		//cout << newVector[i]<<" ";

		return newVector;
	}


	void saveVector(string nameFileToSaveAsVector, std::vector<float> myVector) {  // ANDREBBE FATTO UN TEMPLATE.....

		Mat V = Mat(myVector, 1);
		std::ofstream infile; infile.open(nameFileToSaveAsVector.c_str(), std::ios_base::binary);

		bool c = SaveMatBinary_2(infile, V);
		infile.close();

	}


	bool fexists(string filename)
	{
		ifstream ifile(filename);
		return (bool)ifile;
	}



	void AdjustPath(string &cascade_face, string &cascade_eye_left, string &cascade_eye_right) {

#ifdef WIN32
		char cCurrentPath[FILENAME_MAX];
		GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
#else
		cout << "ATTENZIONE: Su sistema LINUX spostare la cartella resources nel path corrente" << endl;
		std::cin.get();
		char cCurrentPath[FILENAME_MAX];
		 getcwd(cCurrentPath, sizeof(cCurrentPath));
		 //string current_path = cCurrentPath;

		//exit(-1);
#endif

		string g = cCurrentPath;
		int pos = g.find('x') - 1;
		string p = g.substr(0, pos);
		int pos2 = p.find_last_of('\\');
		if (pos > 0) {
			//cout << endl << pos << endl;
			//cout << "pos2:  " << pos2 << endl;
			string pp = g.substr(pos2, pos - pos2 + 1);
			string path = p + pp;
			//cout << "pp:  " << pp << endl;
			//cout << "path:  " << path << endl;


			cascade_face = path + cascade_face;
			cascade_eye_left = path + cascade_eye_left;
			cascade_eye_right = path + cascade_eye_right;

		}

	}

#ifdef WIN32
	// Get the horizontal and vertical screen sizes in pixel
	void GetDesktopResolution(int& horizontal, int& vertical)
	{
		RECT desktop;
		// Get a handle to the desktop window
		const HWND hDesktop = GetDesktopWindow();
		// Get the size of screen to the variable desktop
		GetWindowRect(hDesktop, &desktop);
		// The top left corner will have coordinates (0,0)
		// and the bottom right corner will have coordinates
		// (horizontal, vertical)
		horizontal = desktop.right;
		vertical = desktop.bottom;
	}

#endif

#ifdef WIN32
	void copyDirectory(string DirToCopy, string DirWhereToCopy) {

		SHFILEOPSTRUCT sf;
		memset(&sf, 0, sizeof(sf));
		sf.hwnd = 0;
		sf.wFunc = FO_COPY;
		string ss = DirToCopy;
		string st = DirWhereToCopy;
		//cout << ss << endl;
		//cout << st << endl;
		sf.pFrom = ss.c_str();
		sf.pTo = st.c_str();
		sf.fFlags = FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR | FOF_NOERRORUI;
		int n = SHFileOperation(&sf);
		if (n == 0)
		{
			//cout << "Success\n";
			ShowWindow(GetConsoleWindow(), SW_HIDE);
			system("cls");
			MessageBox(NULL, "\tPROCESSO TERMINATO!\n\tDIRECTORY COPIATA CON SUCCESSO!\n", "Operazione di background!", MB_ICONINFORMATION | MB_OK);
			ShowWindow(GetConsoleWindow(), SW_RESTORE);
		}
		else
		{
			//cout << "Failed\n";
			system("cls");
			ShowWindow(GetConsoleWindow(), SW_HIDE);
			MessageBox(NULL, "\tPROCESSO TERMINATO!\n\tDIRECTORY COPIATA NON RIUSCITA!\n", "Operazione di background!", MB_ICONERROR | MB_OK);
			ShowWindow(GetConsoleWindow(), SW_RESTORE);
		}
	}

#endif

int numDirectoryList(string path, int &numDir, std::vector<string> &dirList) {

	    DIR *dir;  string folder = "";		
		struct dirent *ent;
		numDir = 0; // le prime due solo folder di sistema...
						 /* open directory stream */
		dir = opendir(path.c_str());
		if (dir != NULL) {

			/* print all the files and directories within directory */
			while ((ent = readdir(dir)) != NULL) {
				if (ent->d_type == DT_DIR) {
					folder = ent->d_name;
					//cout << ent->d_name << endl;
					//cout << folder << endl;
					numDir++;
					dirList.push_back(folder);

				}
			}

			closedir(dir);
		}
		else {
			/* could not open directory */
			perror("");
			return EXIT_FAILURE;
		}

		return numDir;

	}



int numFileListInDirectory(string folderPath) {

	vector<string>fileVec;

	glob(folderPath, fileVec);
	//cout << "size:   "<<fileVec.size() << endl;


	return fileVec.size();

}

unsigned GetNumberOfDigits(unsigned i)  // Calcola numero d cifre di un intero
{
	return i > 0 ? (int)log10((double)i) + 1 : 1;
}

#ifdef WIN32

void DataAdjust(string current_path, string& Data, string& path_init_Norm) { // Solo giorno e mese...

	string year = "-2017";
	int mouth_digit;
	string Data_2 = Data;

	int posMouth = Data_2.find_first_of('-') + 1;
	string mouth = Data.substr(posMouth, posMouth - 1);
	//cout << mouth << endl;
	if (stoi(Data.substr(posMouth, posMouth - 1).c_str()) == 0) {

		//cout << "substr 1 :  " << Data.substr(posMouth, posMouth - 1) << endl;
		mouth_digit = stoi(Data.substr(posMouth, posMouth - 1).c_str());

	}
	else {

		//cout << "substr:  " << Data.substr(posMouth, posMouth - 1) << endl;
		mouth_digit = stoi(Data.substr(posMouth, posMouth - 1).c_str());
	}


	//cout << "mouth_digit   "<<mouth_digit << endl;
	int numMouth = mouth_digit;
	int mouth_digit_init = mouth_digit;



	int pos = Data_2.find_first_of('-');
	Data_2 = Data_2.substr(0, pos);
	//string Data_3; Data_3 = Data.substr(pos+1, Data.find_last_of('-'));
	mouth = Data.substr(posMouth - 1, posMouth);
	//cout << "mouth:  "<<mouth << endl;
	//system("pause");
	int digit = stoi(Data_2.c_str());
	int digit_init = digit;
	//digit--;
	Data = to_string(digit) + mouth + year;
	//cout << Data << endl;
	//system("pause");
	path_init_Norm = current_path + "\\Database_Normalized\\" + Data + "\\";
	mouth_digit++;
	while (!thesis::isDirectory(path_init_Norm)) {
		digit = 31;	
		mouth_digit--; //cout << mouth_digit << endl;
			if (GetNumberOfDigits(mouth_digit) == 1)
				mouth = "-0" + to_string(mouth_digit);
			else
				mouth = "-" + to_string(mouth_digit);
			Data = to_string(digit) + mouth + year;
			path_init_Norm = current_path + "\\Database_Normalized\\" + Data + "\\";
			//cout << "path:   "<<Data << endl;
			if (!thesis::isDirectory(path_init_Norm)) {
				//mouth_digit = mouth_digit_init;
				for (int i = 0; i < 31;i++) {
					if (GetNumberOfDigits(digit) == 2)
						Data = to_string(digit) + mouth + year;
					else						
					  Data = "0" + to_string(digit) + mouth + year;
					//cout << "DATA-------   " << Data << endl;
					path_init_Norm = current_path + "\\Database_Normalized\\" + Data + "\\";
					if (thesis::isDirectory(path_init_Norm))
						break;
					else
						digit--;
					//system("pause");
				}
			}
			else
				break;		

	}

}

#else

void DataAdjust(string current_path, string& Data, string& path_init_Norm){ // Solo giorno e mese...

	// controlla se la cartella non è vuota (prima di usare il classifcatore va effettuato l'addestramento...)
	//int numDirNorm = myUtils::numDirectoryList(path_init_Norm);
	//cout<<"NUM:  "<<numDirNorm<<endl;
	//myUtils::system_pause();

	string year = "-2017";
	int mouth_digit;
	string Data_2 = Data;

	int posMouth= Data_2.find_first_of('-')+1;
	string mouth = Data.substr(posMouth, posMouth-1);
	//cout << mouth << endl;

// stoi dovrebbe funzionare anche se da errore eclipse...
	if (stoi(Data.substr(posMouth, posMouth - 1).c_str()) == 0) {

		//cout << "substr 1 :  " << Data.substr(posMouth, posMouth - 1) << endl;
		mouth_digit = stoi(Data.substr(posMouth, posMouth - 1).c_str()) ;

	}
	else {

		//cout << "substr:  " << Data.substr(posMouth, posMouth - 1) << endl;
		mouth_digit = stoi(Data.substr(posMouth, posMouth - 1).c_str()) ;
	}


	//cout << "mouth_digit   "<<mouth_digit << endl;
	int numMouth=mouth_digit;
	int mouth_digit_init=mouth_digit;



	int pos = Data_2.find_first_of('-');
	Data_2 = Data_2.substr(0, pos);
	//string Data_3; Data_3 = Data.substr(pos+1, Data.find_last_of('-'));
	mouth = Data.substr(posMouth-1, posMouth);
	//cout << "mouth:  "<<mouth << endl;
	//system("pause");
	int digit = stoi(Data_2.c_str());
	int digit_init = digit;
	//digit--;
	Data = patch::to_string(digit) + mouth + year;
	//cout << Data << endl;
	//system("pause");
	path_init_Norm = current_path + "/Database_Normalized/" + Data + "/";
	
	mouth_digit++;
	while (!thesis::isDirectory(path_init_Norm)) {
		digit = 31;
		mouth_digit--; //cout << mouth_digit << endl;
		if (GetNumberOfDigits(mouth_digit) == 1)
			mouth = "-0" + to_string(mouth_digit);
		else
			mouth = "-" + to_string(mouth_digit);
		Data = to_string(digit) + mouth + year;
		path_init_Norm = current_path + "/Database_Normalized/" + Data + "/";
		//cout << "path:   " << Data << endl;
		if (!thesis::isDirectory(path_init_Norm)) {
			//mouth_digit = mouth_digit_init;
			for (int i = 0; i < 31;i++) {
				if (GetNumberOfDigits(digit) == 2)
					Data = to_string(digit) + mouth + year;
				else
					Data = "0" + to_string(digit) + mouth + year;
				//cout << "DATA-------   " << Data << endl;
				path_init_Norm = current_path + "/Database_Normalized/" + Data + "/";
				if (thesis::isDirectory(path_init_Norm))
					break;
				else
					digit--;
				//system("pause");
			}
		}
		else
			break;	

	}
	

}

#endif




#ifdef WIN32

#include <stdexcept>

void SetConsoleWindowSize(int x, int y)
{

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (h == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Unable to get stdout handle.");

	// If either dimension is greater than the largest console window we can have,
	// there is no point in attempting the change.
	{
		COORD largestSize = GetLargestConsoleWindowSize(h);
		if (x > largestSize.X)
			throw std::invalid_argument("The x dimension is too large.");
		if (y > largestSize.Y)
			throw std::invalid_argument("The y dimension is too large.");
	}


	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	if (!GetConsoleScreenBufferInfo(h, &bufferInfo))
		throw std::runtime_error("Unable to retrieve screen buffer info.");

	SMALL_RECT& winInfo = bufferInfo.srWindow;
	COORD windowSize = { winInfo.Right - winInfo.Left + 1, winInfo.Bottom - winInfo.Top + 1 };

	if (windowSize.X > x || windowSize.Y > y)
	{
		// window size needs to be adjusted before the buffer size can be reduced.
		SMALL_RECT info =
		{
			0,
			0,
			x < windowSize.X ? x - 1 : windowSize.X - 1,
			y < windowSize.Y ? y - 1 : windowSize.Y - 1
		};

		if (!SetConsoleWindowInfo(h, TRUE, &info))
			throw std::runtime_error("Unable to resize window before resizing buffer.");
	}

	COORD size = { x, y };
	if (!SetConsoleScreenBufferSize(h, size))
		throw std::runtime_error("Unable to resize screen buffer.");


	SMALL_RECT info = { 0, 0, x - 1, y - 1 };
	if (!SetConsoleWindowInfo(h, TRUE, &info))
		throw std::runtime_error("Unable to resize window after resizing buffer.");
}



void ShowLastSystemError()
{
	LPSTR messageBuffer;
	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		0,          // source
		GetLastError(),
		0,          // lang
		(LPSTR)&messageBuffer,
		0,
		NULL);

	std::cerr << messageBuffer << '\n';
	LocalFree(messageBuffer);
}
/*
COORD QueryUserForConsoleSize()
{
	COORD size = { 0, 0 };

	//std::cout << "New console size: ";
	//std::cin >> size.X >> size.Y;
	
	return size;
}
*/
void ConsolResize(int X,int Y, int horizontal, int vertical)
{
	HWND hwnd = GetConsoleWindow();
	
	MoveWindow(hwnd, (int)(vertical - (int)(horizontal*0.5) / 2), (int)(vertical/ 2)-Y*10, -1, -1, FALSE);

	COORD consoleSize; consoleSize.X = X; consoleSize.Y = Y;

	//std::cout << "An x or y size of 0 will terminate the program\n";
//	while (consoleSize = QueryUserForConsoleSize(),consoleSize.X && consoleSize.Y)
//	{
		try {
			SetConsoleWindowSize(consoleSize.X, consoleSize.Y);
		}

		catch (std::logic_error& ex)
		{
			std::cerr << ex.what() << '\n';
		}

		catch (std::exception& ex)
		{
			std::cerr << ex.what() << "\nSystem error: ";
			ShowLastSystemError();
		}	//}
}

#endif


void modifyDrawnRect(cv::Mat &frame, cv::Rect r, cv::Scalar Color, int TickSize) {

	cv::line(frame, cv::Point(r.x, r.y), cv::Point(r.x + r.width*0.35, r.y ), Color, TickSize);
	cv::line(frame, cv::Point(r.x, r.y), cv::Point(r.x, r.y + r.height*0.35), Color, TickSize);
			
	cv::line(frame, cv::Point(r.x, r.y+r.height), cv::Point(r.x + r.width*0.35, r.y+r.height), Color, TickSize);
	cv::line(frame, cv::Point(r.x, r.y + r.height), cv::Point(r.x, r.y + r.height - r.height*0.35), Color, TickSize);

	cv::line(frame, cv::Point(r.x+r.width, r.y), cv::Point(r.x + r.width - r.width*0.35, r.y), Color, TickSize);
	cv::line(frame, cv::Point(r.x + r.width, r.y), cv::Point(r.x+r.width, r.y + r.height*0.35), Color, TickSize);

	cv::line(frame, cv::Point(r.x + r.width, r.y+r.height), cv::Point(r.x + r.width - r.width*0.35, r.y + r.height), Color, TickSize);
	cv::line(frame, cv::Point(r.x + r.width, r.y + r.height), cv::Point(r.x + r.width, r.y + r.height -r.height*0.35), Color, TickSize);


	cv::line(frame,cv::Point(r.x + r.width/2, r.y-r.height*0.025), cv::Point(r.x + r.width / 2, r.y + r.height*0.025),Color,2); // lato sup
	cv::line(frame, cv::Point(r.x -r.width*0.025, r.y +r.height/2), cv::Point(r.x + r.width*0.025, r.y + r.height / 2), Color, 2); // lato sx
	cv::line(frame, cv::Point(r.x + r.width / 2, r.y +r.height - r.height*0.025), cv::Point(r.x + r.width / 2, r.y + r.height + r.height*0.025), Color, 2); // lato inf
	cv::line(frame, cv::Point(r.x + r.width - r.width*0.025, r.y + r.height / 2), cv::Point(r.x + r.width + r.width*0.025, r.y + r.height / 2), Color, 2); // lato dx


	// mirino centrale
	//cv::line(frame, cv::Point(r.x + r.width/2 - r.width*0.025, r.y + r.height / 2), cv::Point(r.x + r.width/2 + r.width*0.025, r.y + r.height / 2), Color, 2); // lato dx
	//cv::line(frame, cv::Point(r.x + r.width / 2, r.y + r.height / 2 - r.height*0.025), cv::Point(r.x + r.width / 2, r.y + r.height / 2 + r.height*0.025), Color, 2); // lato dx

}


void modifyDrawnCircle(cv::Mat &frame, cv::Point centre, int radius,cv::Scalar Color, int TickSize) {

	

	cv::line(frame, cv::Point(centre.x, centre.y - radius -radius*0.15), cv::Point(centre.x, centre.y - radius +radius*0.35), Color, 5); // lato sup
	cv::line(frame, cv::Point(centre.x - radius- radius*0.15, centre.y ), cv::Point(centre.x -radius + radius*0.35, centre.y), Color, 5); // lato sx
	cv::line(frame, cv::Point(centre.x, centre.y + radius - radius*0.35), cv::Point(centre.x, centre.y + radius + radius*0.15), Color, 5); // lato inf
	cv::line(frame, cv::Point(centre.x + radius - radius*0.35, centre.y ), cv::Point(centre.x + radius + radius*0.15, centre.y), Color, 5); // lato dx


																																						   // mirino centrale
																																						   //cv::line(frame, cv::Point(r.x + r.width/2 - r.width*0.025, r.y + r.height / 2), cv::Point(r.x + r.width/2 + r.width*0.025, r.y + r.height / 2), Color, 2); // lato dx
																																						   //cv::line(frame, cv::Point(r.x + r.width / 2, r.y + r.height / 2 - r.height*0.025), cv::Point(r.x + r.width / 2, r.y + r.height / 2 + r.height*0.025), Color, 2); // lato dx

}

void writeMatrix(Mat Data, string fileWhereTSave) {

	std::ofstream fout(fileWhereTSave.c_str());

	float *ptr;

	for (int i = 0; i < Data.rows; i++)
	{
		ptr = &Data.at<float>(i);
		for (int j = 0; j < Data.cols; j++) {
			fout << ptr[j] << " ";
		}
		fout << endl;
	}

	fout.close();

}


void writefloat(float v, FILE *f) {
	fwrite((void*)(&v), sizeof(v), 1, f);
}

float readfloat(FILE *f) {
	float v;
	fread((void*)(&v), sizeof(v), 1, f);
	return v;
}



	/*****************************************************************************************************
	*   Script di calcolo del "TanTriggs Preprocessing process" per la normalizzazione della luminosit�. *
	*   Fonte:																							 *
	*																								     *
	*         Tan, X., and Triggs, B. "Enhanced local texture feature sets for face                      *
	*         recognition under difficult lighting conditions.". IEEE Transactions                       *
	*         on Image Processing 19 (2010), 1635�650.                                                   *
	*																									 *
	******************************************************************************************************/
	Mat Norm_lum(InputArray src, float alpha, float tau, float gamma, int sigma0, int sigma1) {

		// Conversione in floating point:
		Mat X = src.getMat();
		X.convertTo(X, CV_32FC1);

		Mat I;
		pow(X, gamma, I);
		// Calcola la DOG Image:
		{
			Mat gaussian0, gaussian1;
			// Kernel Size:
			int kernel_sz0 = (3 * sigma0);
			int kernel_sz1 = (3 * sigma1);
			// algoritmo
			kernel_sz0 += ((kernel_sz0 % 2) == 0) ? 1 : 0;
			kernel_sz1 += ((kernel_sz1 % 2) == 0) ? 1 : 0;
			GaussianBlur(I, gaussian0, Size(kernel_sz0, kernel_sz0), sigma0, sigma0, BORDER_REPLICATE);
			GaussianBlur(I, gaussian1, Size(kernel_sz1, kernel_sz1), sigma1, sigma1, BORDER_REPLICATE);
			subtract(gaussian0, gaussian1, I);
		}

		{
			double meanI = 0.0;
			{
				Mat tmp;
				pow(abs(I), alpha, tmp);
				meanI = mean(tmp).val[0];

			}
			I = I / pow(meanI, 1.0 / alpha);
		}

		{
			double meanI = 0.0;
			{
				Mat tmp;  //float c=abs(I); c=min(c,tau); cout<<pow(c,alpha,tmp)<<endl;
				Mat c=abs(I);
				pow(min(c, tau), alpha, tmp);
				meanI = mean(tmp).val[0];
			}
			I = I / pow(meanI, 1.0 / alpha);
		}


		{
			Mat exp_x, exp_negx;
			exp(I / tau, exp_x);
			exp(-I / tau, exp_negx);
			divide(exp_x - exp_negx, exp_x + exp_negx, I);
			I = tau * I;
		}
		return I;
	}

	// Normalizes a given image into a value range between 0 and 255.
	Mat norm_0_255(const Mat& src) {
		// Create and return normalized image:
		Mat dst;
		switch (src.channels()) {
		case 1:
			cv::normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
			break;
		case 3:
			cv::normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
			break;
		default:
			src.copyTo(dst);
			break;
		}
		return dst;
	}


void DigitalZoom(cv::Mat& img_src, float zoom) {

		//float zoom = 1; float deltaZoom = 0.1;

		int interpolation_type = CV_INTER_LINEAR;
		// zoom region to zoom in on within the image

		//Mat img_src = imread("Last.bmp"); 
		Mat img_zoomed;
		//imshow("ORIGINAL", img_src); waitKey(0);

//		while (zoom != -1) {

			// calculate a zoom sub-region (in the centre of the image)
			int x = cvFloor((((img_src.cols / zoom) * (zoom / 2.0)) - ((img_src.cols / zoom) / 2.0)));
			int y = cvFloor((((img_src.rows / zoom) * (zoom / 2.0)) - ((img_src.rows / zoom) / 2.0)));
			//system("pause");
			int width = cvFloor((img_src.cols / zoom));
			int height = cvFloor((img_src.rows / zoom));

			// use ROI settings to zoom into it 
			Rect roi(x, y, width, height);
			//cout << roi << endl;
			Mat image_roi = img_src(roi);
			resize(image_roi, img_zoomed, img_src.size());

			//imshow("ZOOMED", img_zoomed); waitKey(0);

			/*
			if (cv::waitKey(1) == 27) // tasto esc
				zoom = -1;

			else if ((char)cv::waitKey(1) == '+') {
				zoom = zoom + deltaZoom;
				cout << "zoomed-in at: " << zoom << endl;
			}

			else if ((char)cv::waitKey(1) == '-') {
				zoom = zoom - deltaZoom;
				cout << "zoomed-out at: " << zoom << endl;
			}
			*/
		//}
			img_zoomed.copyTo(img_src);

	}



void DigitalZoom_FC(cv::Mat& img_src, cv::Point face, float zoom) { // Face Centered

	//float zoom = 1; float deltaZoom = 0.1;

	int interpolation_type = CV_INTER_LINEAR;
	// zoom region to zoom in on within the image

	//Mat img_src = imread("Last.bmp"); 
	Mat img_zoomed;
	//imshow("ORIGINAL", img_src); waitKey(0);

	//		while (zoom != -1) {

	// calculate a zoom sub-region (in the centre of the image)
	int x = cvFloor((((face.x / zoom) * (zoom / 2.0)) - ((face.x / zoom) / 2.0)));
	int y = cvFloor((((face.y / zoom) * (zoom / 2.0)) - ((face.y / zoom) / 2.0)));
	//system("pause"); 
	int width = cvFloor((img_src.cols / zoom));
	int height = cvFloor((img_src.rows / zoom));

	// use ROI settings to zoom into it 
	Rect roi(x, y, width, height);
	//cout << roi << endl;
	Mat image_roi = img_src(roi);
	resize(image_roi, img_zoomed, img_src.size());

	//imshow("ZOOMED", img_zoomed); waitKey(0);

	/*
	if (cv::waitKey(1) == 27) // tasto esc
	zoom = -1;

	else if ((char)cv::waitKey(1) == '+') {
	zoom = zoom + deltaZoom;
	cout << "zoomed-in at: " << zoom << endl;
	}

	else if ((char)cv::waitKey(1) == '-') {
	zoom = zoom - deltaZoom;
	cout << "zoomed-out at: " << zoom << endl;
	}
	*/
	//}
	img_zoomed.copyTo(img_src);

}




};
