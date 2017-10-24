#include "inizialize.h"
#include "VideoFaceDetector.h"
#include "eyesFinder.h"
#include "BackEnd.h"


int dimension = 50;
float *result;
int finalDimension;
float **clucenter;

extern string path_init_Norm, init_path;

string Sys_language="IT";
string current_path, cascade_face;

cv::VideoCapture camera;

using namespace std;

//#ifndef _WIN32
int main(int argc, char *argv[]) {
/*#else
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
*/	

#ifdef _WIN32
	// gli indico praticamente doe si trova la cartella platforms...
	QCoreApplication::addLibraryPath(QString::fromLocal8Bit((init_path + back_slash + "Windows" + back_slash + "System32").c_str()));
#else
	// gli indico praticamente doe si trova la cartella platforms...
	QCoreApplication::addLibraryPath(QString::fromLocal8Bit((init_path + back_slash + "usr" + back_slash + "lib" + back_slash + "x86_64-linux-gnu").c_str()));
#endif

	QApplication app(__argc, __argv);	



	camera = inizialize(__argc, __argv, current_path);
	
	VideoFaceDetector detector(cascade_face, camera);
	 
	
	cout << theresold << endl;


	LBP lbp=antispoofingSetModel();

	while (1) {
	
	
			frameProcessing(detector, lbp);															

	}

	return 0;

}

