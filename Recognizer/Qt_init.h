#pragma once
#include<iostream>
#include <QtWidgets/qapplication.h>

using namespace std;


extern string path_init_Norm, init_path;


void Qt_init(int argc, char** argv) {

	string back_slash="\\";

#ifdef _WIN32
	// gli indico praticamente doe si trova la cartella platforms...
	QCoreApplication::addLibraryPath(QString::fromLocal8Bit((init_path + back_slash + "Windows" + back_slash + "System32").c_str()));
#else
	// gli indico praticamente doe si trova la cartella platforms...
	QCoreApplication::addLibraryPath(QString::fromLocal8Bit((init_path + back_slash + "usr" + back_slash + "lib" + back_slash + "x86_64-linux-gnu").c_str()));
#endif


	QApplication app(argc, argv);

}