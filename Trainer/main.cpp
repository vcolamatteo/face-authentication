#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */
#ifdef _WIN32
#include <Windows.h>
#define GetCurrentDir _getcwd
#else
#include<unistd.h>
#endif


#include "VideoFaceDetector.h"
#include"InitProc.h"

#include "LQP_main.h"

#include "SessionTraining.h"

string Sys_language;



const int PictureWidth = 60;
const int PictureHeight = 80;





//#ifndef _WIN32
int main(int argc, char *argv[]) {
/*	#else
	int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	#endif*/



#ifndef _WIN32
	QApplication app(argc, argv);
#else
	QApplication app(__argc, __argv);
#endif

	PrelminarySetts(current_path, search_path);


	camera = Inits();
	

	VideoFaceDetector detector(cascade_face, camera);


	sessionTraining(detector);



	return 0;
}


