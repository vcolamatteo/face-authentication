#include "Inizialize.h"


#ifdef _WIN32
string back_slash = "\\";
#else
string back_slash = "/";
#endif


//const cv::String WINDOW_NAME("Camera video");
cv::String WINDOW_NAME;

int NumMaxFrame = 2;
const int PictureWidth = 60;
const int PictureHeight = 80;

string Time, Data;

int numDir; std::vector<string> dirList;

string path_init_Norm;

string init_path;
extern string cascade_face;


string directoryNorm;




int colNum = (PictureWidth*PictureHeight*50)/10/10; int rowNum = 1;

float theresold;
float meanTotal;


//std::vector<cv::Mat> faces;
std::vector<cv::Mat> faces(NumMaxFrame+1);

//extern cv::VideoCapture camera;



float normWidth, normHeight;
int window_width = 480;
int window_height = 350;

int window_width_laserScreen = 250;
int window_height_laserScreen = 320;

int native_width = 1920;
int native_height = 1080;

int windowSizeWidth;
int windowSizeHeight;


void SetPath(string &current_path);

cv::VideoCapture inizialize(int argc, char** argv, string current_path) {



	int numDir; std::vector<string> dirList;



	SetPath(current_path);



	string directoryNorm = "Database_Normalized" + back_slash;

	if (thesis::isDirectory(("Database_Normalized" + back_slash + Data + back_slash).c_str()) == 0) {
#ifdef _WIN32
		ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
		messageBox("", 4);
		myUtils::playSound("click.wav");
		exit(-1);
	}
	//myUtils::system_pause();
	if (!myUtils::timeData(Time, Data)) {
#ifdef _WIN32
		ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
		messageBox("", 4);
		myUtils::playSound("click.wav");
		exit(-1);
	}

	



	path_init_Norm = current_path + back_slash + "Database_Normalized" + back_slash + Data + back_slash;

	int numDirNorm;


	if (myUtils::numDirectoryList(current_path + back_slash + "Database_Normalized", numDir, dirList) <= 1) {
		messageBox("", 4);
		myUtils::playSound("click.wav");
		exit(-1);
	}
	else {
		cout << "numDir  " << numDir << endl;
		string toFind = "-2017"; int countList = 0;
		for (int i = 0; i < numDir; i++) {

			if (dirList[i].length() >= 5 && dirList[i].substr(dirList[i].length() - 5, dirList[i].length()) != toFind) {

				countList++;
			}

		}

		if (countList == numDir - 2) {   // le prime due solo folder di sistema...
			messageBox("", 4);
			myUtils::playSound("click.wav");
			exit(-1);

		}

	}

	if (!thesis::isDirectory(path_init_Norm)) {
		myUtils::DataAdjust(current_path, Data, path_init_Norm);
		cout << "Datacrrected: " << Data << endl;
		numDirNorm = myUtils::numDirectoryList(path_init_Norm, numDir, dirList);
		cout << "numdirnorm:  " << numDirNorm << endl;
		if (numDirNorm == 0) {
			messageBox("", 4);
			myUtils::playSound("click.wav");
			exit(-1);
		}

	}
	else {  // controlla se la cartella cn la dta odierna esiste ma è vuota..
		if (myUtils::numFileListInDirectory(path_init_Norm) <= 1) {
			messageBox("", 4);
			myUtils::playSound("click.wav");
			exit(-1);
		}
	}

	/*else
	numDirNorm = myUtils::numDirectoryList(path_init_Norm, numDir, dirList);
	numDirNorm = numDirNorm - 2;

	if (myUtils::numDirectoryList(path_init_Norm, numDir, dirList) == 0) {
	messageBox("", 4);
	myUtils::playSound("click.wav");
	return -1;
	}
	cout << "numdirnorm:  " << numDirNorm << endl;
	if (numDirNorm == 0) {
	cout << "vxbcbcbc " << path_init_Norm << endl;
	messageBox("", 4);
	myUtils::playSound("click.wav");
	return -1;
	}*/




	std::ifstream inNorm;
	std::vector<float>meanBox;
	inNorm.open((path_init_Norm + "meanBox.data").c_str(), ios::in | ios::binary);

	meanBox = myUtils::loadVectorKnownSize(inNorm, NumMaxFrame/2);
	cout << "<< " << meanBox.size() << endl;
	int Total = 0; //float meanTotal;
	for (int i = 0; i < meanBox.size();i++) {
		cout << "i " << i << ":  " << meanBox[i] << endl;
		if (meanBox[i] != 0) {
			Total = Total + meanBox[i];
		}
	}
	meanTotal = Total/ (NumMaxFrame/2);
	cout << "meanTotal:  " << meanTotal << endl;
	inNorm.close();


	LQP_initParam();

	//float theresold; 
	
	//float theresold_copy;

		if (!myUtils::fexists((current_path + back_slash + "Database_Normalized" + back_slash + Data + back_slash + "Info_temp.data").c_str()) && !myUtils::fexists((current_path + back_slash + "Database_Normalized" + back_slash + Data + back_slash + "Info.data").c_str())) {

	theresold = FindTheresoldValue();
	//theresold_copy = theresold;

	FILE *fp; fp = fopen((current_path + back_slash + "Database_Normalized" + back_slash + Data + back_slash + "Info.data").c_str(), "wb");

	myUtils::writefloat(theresold, fp);

	if (!myUtils::fexists(("Database_Normalized" + back_slash + Data + back_slash + "Info.data"))) {

	cout << "ERRORE" << endl;
	system("pause");
	return -1;
	}
	fclose(fp);
	}
	else if (myUtils::fexists((current_path + back_slash + "Database_Normalized" + back_slash + Data + back_slash + "Info_temp.data").c_str())) {

	FILE *fp; fp = fopen((current_path + back_slash + "Database_Normalized" + back_slash + Data + back_slash + "Info_temp.data").c_str(), "rb");
	float theresold_temp = myUtils::readfloat(fp);
	cout << "theresold_temp:  "<<theresold_temp << endl;
	theresold = FindTheresoldValue(701);
	if (theresold < theresold_temp)
		theresold = theresold_temp;
	//theresold_copy = theresold;
	fclose(fp);
	fp = fopen((current_path + back_slash + "Database_Normalized" + back_slash + Data + back_slash + "Info.data").c_str(), "wb");
	myUtils::writefloat(theresold, fp);
	fclose(fp);
	thesis::delete_file((current_path + back_slash + "Database_Normalized" + back_slash + Data + back_slash + "Info_temp.data").c_str());

	}
	else if (myUtils::fexists((current_path + back_slash + "Database_Normalized" + back_slash + Data + back_slash + "Info.data").c_str())) {
		FILE *fp; fp = fopen((current_path + back_slash + "Database_Normalized" + back_slash + Data + back_slash + "Info.data").c_str(), "rb");
		theresold = myUtils::readfloat(fp);
		fclose(fp);

	}
	cout << "theresold:  "<<theresold << endl;
	

	setGeometries();

	cv::VideoCapture camera(0);

	if (!camera.isOpened()) {

#ifdef _WIN32				
		messageBox("ERRORE nell'apertura della web-cam!", 1);
		myUtils::playSound("click.wav");
		exit(-1);
#else
		int ret = messageBox("ERRORE nell'apertura della web-cam!", 1);
		myUtils::playSound("click.wav");
		return -1;
#endif
	}


	WINDOW_NAME = setFrame_properties("Camera-training");


	/*****************************************************************/
	// Tutta questa parte serve per settare la grandezza della finestra in cui viene aperta la webcam e centrarla sull schermo 
	// in relazione alle dim del display su cui viene eseguita. Su Android essendo visualizzata a tutto schermo potrebbe essere totalmente eliminabile...
	/*
	QRect rec = QApplication::desktop()->screenGeometry();
	cv::Size Screen_Rec_size(640, 480);
	cv::Size Default_ScreenSize(1920, 1080);
	cv::Size Current_ScreenRec_Size;
	cout << rec.width() << "   " << rec.height() << endl;

	if (rec.width() != Default_ScreenSize.width) {
	cout << "num 1" << endl;
	cout << rec.width() << "  " << Default_ScreenSize.width << endl;
	cout << "DIV   " << ((float)rec.width() / (float)Default_ScreenSize.width) << endl;
	float c = (Screen_Rec_size.width*((float)rec.width() / (float)Default_ScreenSize.width));
	cout << "c:  " << c << endl;
	Current_ScreenRec_Size.width = (Screen_Rec_size.width*((float)rec.width() / (float)Default_ScreenSize.width));
	//Current_ScreenRec_Size.width = ((int)(c * 100 + .5) / 100.0);
	cout << Current_ScreenRec_Size.width << endl;
	}
	else {
	Current_ScreenRec_Size.width = Screen_Rec_size.width;
	cout << Current_ScreenRec_Size.width << endl;
	}

	if (rec.height() != Default_ScreenSize.height) {
	Current_ScreenRec_Size.height = Screen_Rec_size.height*((float)rec.height() / (float)Default_ScreenSize.height);
	cout << Current_ScreenRec_Size.height << endl;
	//meanTotal = meanTotal * ((float)rec.height() / (float)Default_ScreenSize.height);
	}
	else {
	Current_ScreenRec_Size.height = Screen_Rec_size.height;
	cout << Current_ScreenRec_Size.height << endl;
	}



	int height = (rec.height() / 2) - (Current_ScreenRec_Size.height / 2);
	int width = (rec.width() / 2) - (Current_ScreenRec_Size.width / 2);
	cout << width << "  " << height << endl;

	camera.set(CV_CAP_PROP_FRAME_WIDTH, Current_ScreenRec_Size.width);
	camera.set(CV_CAP_PROP_FRAME_HEIGHT, Current_ScreenRec_Size.height);

	cv::moveWindow(WINDOW_NAME, (rec.width() / 2) - (Current_ScreenRec_Size.width / 2), height);

	cout << "final dm  " << Current_ScreenRec_Size.width << "  " << Current_ScreenRec_Size.height << endl;
	*/

	/*****************************************************************/

	

	return camera;

}


void SetPath(string &current_path) {


	cascade_face = "resources" + back_slash + "haarcascade_frontalface_default.xml";	

	char cCurrentPath[FILENAME_MAX];

#ifdef _WIN32
	GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
#else
	getcwd(cCurrentPath, sizeof(cCurrentPath));
#endif

	current_path = cCurrentPath;
#ifdef _WIN32
	init_path = current_path.substr(0, current_path.find_first_of("\\"));
	//current_path = current_path + "\\" + "Windows\\System32\\";
#else
	init_path = current_path.substr(0, current_path.find_first_of("/"));
#endif


#ifdef _WIN32
	//string search_path = init_path + back_slash + "Windows" + back_slash + "System32" + back_slash + "FaceRec_SystemPathDevelopment";
	string search_path = init_path + back_slash + "ProgramData" + back_slash + "FaceAuthenticationSystem" + back_slash + "FaceRec_SystemPathDevelopment";
#else
	string search_path = init_path + back_slash + "usr" + back_slash + "lib" + back_slash + "x86_64-linux-gnu" + back_slash + "FaceRec_SystemPathDevelopment";
	//cout<<"jhgyg  "<<myUtils::fexists(search_path)<<endl;
#endif

	if (!myUtils::fexists(search_path)) {

		if (!myUtils::fexists("resources" + back_slash + "Antispoof" + back_slash + "mappingTable_16pts.txt") || !myUtils::fexists("Database_Normalized" + back_slash + "Theresold" + back_slash + "1a.jpg.bmp") || !myUtils::fexists("resources" + back_slash + "other" + back_slash + "divieto.png") || !myUtils::fexists("resources" + back_slash + "icons" + back_slash + "Recognizer.ico")) {
			//cout << "AAAAAAAAAAAAAAAAAAAAAA" << endl;
			messageBox("Non risulta effettuato alcun setup! Impossibile continuare!", 5);
			//myUtils::playSound("click.wav");
			//return false;
			exit(-1);
		}	

	}
	else {
		ifstream readPath; readPath.open(search_path.c_str(), ios::in);
		while (std::getline(readPath, current_path)) {
			readPath >> current_path;
			//cout << current_path << endl;
			//system("pause");
		}
		readPath.close();

		if (!thesis::isDirectory(current_path)) {
			messageBox("Non risulta effettuato alcun setup! Impossibile continuare!", 5);
			//myUtils::playSound("click.wav");
			//return false;
			exit(-1);
		}
		else {
			//cout << "HERE" << endl;
			//current_path = init_path + back_slash + "FR" + back_slash;
			_chdir(current_path.c_str());
#ifdef _WIN32
			//GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
			//cout << cCurrentPath << endl;
			//system("pause");
			//cout << current_path << endl;
#else
			getcwd(cCurrentPath, sizeof(cCurrentPath));
			current_path = cCurrentPath;
			//cout << "cuurent path 1:  " << current_path << endl;
#endif
		}

	}

	/*********************************************************************/
	

	}



double FindTheresoldValue(int residuals) {

// Read file created before....
#ifdef _WIN32
ifstream file; file.open("Database_Normalized" + back_slash + "list_images_WIN32.txt", ios::in);
#else
ifstream file; file.open("Database_Normalized" + back_slash + "list_images_LINUX.txt", ios::in);
#endif
std::string line;
std::vector<std::string> myLines;
while (std::getline(file, line))
{
myLines.push_back(line);
}

cout << myLines.size() << endl;
file.close();


cv::Mat LAST;// = cv::Mat(rowNum, colNum, CV_64FC1);
std::vector<float>data(myLines.size());
for (int i = residuals; i < myLines.size(); i++) {
cv::Mat img = cv::imread(myLines[i], CV_LOAD_IMAGE_ANYCOLOR);
/*if (!img.data) {
cerr << "error in reading image:  " << myLines[i] << endl;
myUtils::system_pause();
exit(-1);
 }*/

//resize(img,img,Size(PictureWidth, PictureHeight));

LQP_EXTRACT_noSave(img, LAST);
//LAST.convertTo(LAST, CV_32FC1);

//cv::Mat Data_1 = Data.row(0);
//cv::Mat Data_2 = Data.row(1);

std::vector<double>theta_(NumMaxFrame);
for (int j = 0; j < NumMaxFrame; j++)
theta_[j] = (LAST.dot(faces[j])) / (norm(LAST)*(norm(faces[j])));

//double theta_1 = *std::max_element(theta_.begin(), theta_.end());
data[i] = *std::max_element(std::begin(theta_), std::end(theta_));
//theta_1 = (double)(int(theta_1 * 100000)) / 100000;
//data[i] = theta_1;
//cout << "["<<i<<"]:  "<<data[i] << endl;
//string p = to_string(theta_1);



}


double Theresold;
double theta_2 = *std::max_element(std::begin(data), std::end(data));
//cout << "Theta_2:  " << theta_2 << endl;
Theresold = theta_2;
//cout << "thweta_1 - theta_2: " << theta_2 - theta_1 << endl;

/*if (theta_1 - theta_2 > 0)
Theresold = theta_1;
else if ((theta_2 - theta_1) > 0.035) {
//cout << "HERE" << endl;
//theta_1 = ((int)(theta_1 * 100 + .5) / 100.0);
Theresold = theta_1 + 0.03;
}
else
Theresold = theta_2 + 0.00001;*/


/*if (ufi_theta_2 > Theresold)
Theresold = ufi_theta_2 + 0.00001;*/
//else
//Theresold = theta_1+ 0.01;  // se ho arrotondato per ecesso non sommo nnt...
cout << "Theresold:  " << Theresold << endl;

/*
if (theta_1 >= 0.48)
Theresold = theta_1 - 0.02;
else
Theresold = theta_1 - 0.01;

cout << "Theresold:  " << Theresold << endl;
*/
/*
if (theta_me - theta_1 >= 0.29)
Theresold = theta_1 + 0.02;
else
Theresold = theta_1 + 0.03;
cout << "Fixed:  " << Theresold << endl;
*/

return Theresold;
}


cv::String setFrame_properties(string Title) {

	const cv::String WINDOW_NAME(Title);
	//WINDOW_NAME=Title;

	//cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);

	int width = (normWidth*native_width) / 2 - (window_width / 2);

	cv::moveWindow(WINDOW_NAME, width, 0);


	return WINDOW_NAME;
}


void setGeometries() {

	QRect rec = QApplication::desktop()->screenGeometry();
	normWidth = std::round((rec.width() / native_width));

	normHeight = std::round((rec.height() / native_height));


	windowSizeWidth = normWidth*window_width;
	windowSizeHeight = normHeight*window_height;
}

