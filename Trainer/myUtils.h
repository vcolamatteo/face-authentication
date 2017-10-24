#pragma once

#ifdef WIN32
#include <conio.h>
#endif

#include "config.h"
using namespace std;
using namespace cv;

namespace myUtils {


    void getSysLanguage(string& Sys_language);

    void system_pause();

	void MyEntry();
	void MyQuit();
	void myExit_Error();


	void DeleteSeveralFile(string FILE_LQP, string out);

	void CleanDirectory(string directory, string directory_database);

	bool timeData(string& Time, string& Data, int Time_calc = 1, int Data_calc = 1);

	void playSound(string file, int async=0);
	void playSound_beep();
	
	cv::Mat LoadMatrix(string fileToCopyInMat, int rowNum, int colNum, int asVector=-1);

	void CleanActions(string directory);

	void copyFile(string file1 , string file2 );

	Mat Norm_lum(InputArray src, float alpha = 0.1, float tau = 10.0, float gamma = 0.2, int sigma0 = 1, int sigma1 = 2);
	Mat norm_0_255(const Mat& src);


	// MANCA TEMPLATE QUI.....
	std::vector<float> loadVector(std::ifstream& in, int size);
	// MANCA TEMPLATE QUI.....
	void saveVector(string nameFileToSaveAsVector, std::vector<float> myVector);


	bool fexists(string filename);

	void AdjustPath(string &cascade_face, string &cascade_eye_left, string &cascade_eye_right);

	void GetDesktopResolution(int& horizontal, int& vertical);



	void copyDirectory(string DirToCopy, string DirWhereToCopy);

	void copyDirectory(string DirToCopy, string DirWhereToCopy) ;
	bool __CopyDirectory(const char r_szSrcPath[1024], const char r_szDesPath[1024]);

	int numDirectoryList(string path);
	int numDirectoryList_2(string path, int &numDir, std::vector<string> &dirList);

	int numFileListInDirectory(string folderPath);

	void CleanDirectoryList(string path);


	unsigned GetNumberOfDigits(unsigned i);
	void DataAdjust(string current_path, string& Data, string& path_init_Norm);



	void ConsolResize(int X, int Y, int horizontal, int vertical);
	void ShowLastSystemError();
	void SetConsoleWindowSize(int x, int y);

	void DigitalZoom(Mat& img_src, float zoom);
	void DigitalZoom_FC(cv::Mat& img_src, cv::Point face, float zoom);


	void modifyDrawnRect(cv::Mat &frame, cv::Rect r, cv::Scalar Color, int TickSize=5);


	void writeMatrix(Mat Data, string fileWhereTSave, int appendMode=0);
	void writefloat(float v, FILE *f);	
	float readfloat(FILE *f);
	

};
