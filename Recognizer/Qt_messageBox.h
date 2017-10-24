#ifndef SRC_Qt_messageBox_h
#define SRC_Qt_messageBox_h
//#ifndef _WIN32
//#pragma once


#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qstylefactory.h>
#include <QtWidgets/qlayoutitem.h>
#include <QtWidgets/qgridlayout.h>
//#include "myUtils.h"

#ifdef _WIN32
#include <Windows.h>
#define GetCurrentDir _getcwd
#else
#include<unistd.h>
#endif

extern string back_slash;
extern string Sys_language;


extern string Time;
extern string Data;

#include "Logging.h"

inline int messageBox(const char * classifier, int type, int argc = 0, char** argv = NULL);
/*
inline QMessageBox * QtMessageBoxCreatorError(){
z
QMessageBox *msgBox = new QMessageBox(0);
msgBox->setText("Test\n Allora funziona?");
msgBox->setWindowModality(Qt::NonModal);
msgBox->setInformativeText("Do you want to save your changes?");
msgBox->setStandardButtons(QMessageBox::Save | QMessageBox::Discard |
QMessageBox::Cancel);
msgBox->setDefaultButton(QMessageBox::Save);
msgBox->setWindowTitle("WARNING!");
msgBox->setIcon(QMessageBox::Critical);
msgBox->setStyle(QStyleFactory::create("Fusion"));
QPalette darkPalette;
darkPalette.setColor(QPalette::Window, QColor(53,53,53));
darkPalette.setColor(QPalette::WindowText, Qt::white);
darkPalette.setColor(QPalette::Base, QColor(25,25,25));
darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
darkPalette.setColor(QPalette::ToolTipText, Qt::white);
darkPalette.setColor(QPalette::Text, Qt::white);
darkPalette.setColor(QPalette::Button, QColor(53,53,53));
darkPalette.setColor(QPalette::ButtonText, Qt::white);
darkPalette.setColor(QPalette::BrightText, Qt::red);
darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
darkPalette.setColor(QPalette::HighlightedText, Qt::black);

qApp->setPalette(darkPalette);

qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");

return msgBox;
}
*/

inline QMessageBox* QtMessageBoxCreatorErrorCascadeOrWebcam(const char * classifier, int type) {

	//char buffer [50];
	//int n, a=5, b=3;
	//n=sprintf (buffer, "%d plus %d is %d", a, b, a+b);

	QMessageBox *msgBox = new QMessageBox(0); //const char cascade[]="resources\eye_left_18x12.xml";

	if (type == 0) {
		char all[100];
		if (Sys_language == "IT")
			sprintf(all, "CASCADE NON TROVATO: %s\n", classifier);
		else
			sprintf(all, "CASCADE NOT FOUND: %s\n", classifier);
		msgBox->setText(all);
	}
	else {
		if (Sys_language == "IT")
			msgBox->setText(classifier);
		else
			msgBox->setText("WEB-CAM NOT AVAIBLE FOR OPENING!");
	}


	msgBox->setWindowModality(Qt::NonModal);
	if (Sys_language == "IT")
		msgBox->setInformativeText("Programma terminato con errore");
	else
		msgBox->setInformativeText("Program exited with errors");

	//msgBox->setStandardButtons(QMessageBox::Escape);
	//QSpacerItem* horizontalSpacer = new QSpacerItem(1000, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
	//QGridLayout* layout = (QGridLayout*)msgBox->layout();
	//layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
	//msgBox->setBaseSize(QSize(600, 520));
	//msgBox->setFixedSize ( 500,500);
	QAbstractButton* exit = msgBox->addButton("Esci", QMessageBox::NoRole);

	//QAbstractButton* moreInfo =msgBox->addButton("Altre info", QMessageBox::NoRole);
	char logPath[500];
	char detaileString[1000];
#ifdef _WIN32

	GetCurrentDir(logPath, sizeof(logPath));
	string current_path = logPath + back_slash + "resources" + back_slash + "File_log";
	//cout<<"cuurent path last:  "<<current_path<<endl;
#else

	getcwd(logPath, sizeof(logPath));
	string current_path = logPath + back_slash + "resources" + back_slash + "File_log";
#endif
	if (type == 0) {

		if (Sys_language == "IT") {
			sprintf(detaileString, "Impossibile caricare il file di cascade al seguente percorso:\n"
				"%s.\n\nVerificare che lo stesso non sia stato accidentalmente rimosso.\n\n"
				"File di log generato al seguente percorso: %s", classifier, current_path.c_str());
		}
		else {
			sprintf(detaileString, "Cascade file cannot being loaded at followng path:\n"
				"%s.\n\nVerify the one not being accidentally removed.\n\n"
				"File-log generated at following path: %s", classifier, current_path.c_str());
		}
	}
	else {

		if (Sys_language == "IT") {
			sprintf(detaileString, "Nessun dispositivo di cattura audio/video rilevato:\n\n"
				"File di log generato al seguente percorso: %s", current_path.c_str());
		}
		else {
			sprintf(detaileString, "Cascade file cannot being loaded at followng path:\n"
				"%s.\n\nVerify the one not being accidentally removed.\n\n"
				"File-log generated at following path: %s", classifier, current_path.c_str());
		}

	}
	msgBox->setDetailedText(detaileString);

	msgBox->setWindowFlags(msgBox->windowFlags() & Qt::WindowCloseButtonHint);
	// se metto così levva la x
	//msgBox->setWindowFlags(msgBox->windowFlags() & ~Qt::WindowCloseButtonHint);

	//QAbstractButton* open=msgBox->addButton("Apri", QMessageBox::NoRole);

	msgBox->setDefaultButton(0);
	if (Sys_language == "IT")
		msgBox->setWindowTitle("ERRORE CRITCO");
	else
		msgBox->setWindowTitle("CRITICAL ERROR");
	msgBox->setIcon(QMessageBox::Critical);
	msgBox->setStyle(QStyleFactory::create("Fusion"));
	msgBox->setFixedSize(542, 503);
	//msgBox->move((window_w-message.width())/2,(window_h-message.height())/2);

	QPalette darkPalette;
	darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));  darkPalette.shadow();
	darkPalette.setColor(QPalette::WindowText, Qt::white);
	darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
	darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
	darkPalette.setColor(QPalette::ToolTipText, Qt::white);
	darkPalette.setColor(QPalette::Text, Qt::white);
	darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
#ifdef _WIN32
	darkPalette.setColor(QPalette::ButtonText, QColor(25, 25, 25));
#else
	darkPalette.setColor(QPalette::ButtonText, Qt::white);
#endif    
	darkPalette.setColor(QPalette::BrightText, Qt::red);
	darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

	darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::HighlightedText, Qt::black);

	qApp->setPalette(darkPalette);

	qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");

	return msgBox;
}


inline QMessageBox * QtMessageBoxCreatorErrorTrainRequest(const char * classifier) {

	QMessageBox *msgBox = new QMessageBox(0);
	//char all[100];
	//sprintf(all,"CASCADE NON TROVATO: %s\n",classifier);

	msgBox->setText(classifier);

	msgBox->setWindowModality(Qt::NonModal);
	if (Sys_language == "IT")
		msgBox->setInformativeText("I dati precedenti non verranno eliminati");
	else
		msgBox->setInformativeText("All previous data won't be removed");


	msgBox->setWindowModality(Qt::NonModal);
	msgBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	msgBox->setDefaultButton(QMessageBox::No);
	if (Sys_language == "IT")
		msgBox->setWindowTitle("SISTEMA DI TRAINING");
	else
		msgBox->setWindowTitle("TRAINING SYSTEM");
	msgBox->setIcon(QMessageBox::Question);
	msgBox->setStyle(QStyleFactory::create("Fusion"));



	msgBox->setIcon(QMessageBox::Question);
	msgBox->setStyle(QStyleFactory::create("Fusion"));
	msgBox->setFixedSize(542, 503);
	//msgBox->move((window_w-message.width())/2,(window_h-message.height())/2);

	QPalette darkPalette;
	darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));  darkPalette.shadow();
	darkPalette.setColor(QPalette::WindowText, Qt::white);
	darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
	darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
	darkPalette.setColor(QPalette::ToolTipText, Qt::white);
	darkPalette.setColor(QPalette::Text, Qt::white);
	darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
#ifdef _WIN32
	darkPalette.setColor(QPalette::ButtonText, QColor(25, 25, 25));
#else
	darkPalette.setColor(QPalette::ButtonText, Qt::white);
#endif    
	darkPalette.setColor(QPalette::BrightText, Qt::red);
	darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

	darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::HighlightedText, Qt::black);

	qApp->setPalette(darkPalette);

	qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");

	return msgBox;
}



inline QMessageBox * QtMessageBoxCreatorTrainCompleted(const char * classifier) {

	QMessageBox *msgBox = new QMessageBox(0);
	//char all[100];
	//sprintf(all,"CASCADE NON TROVATO: %s\n",classifier);


	if (Sys_language == "IT") {
		msgBox->setText(classifier);
		msgBox->setInformativeText("\n\nPremere ok per terminare...");
	}
	else {
		msgBox->setText("T R A I N I N G   C O M P L E T E D !");
		msgBox->setInformativeText("\n\nPress ok button for exiting...");
	}

	msgBox->setWindowModality(Qt::NonModal);
	msgBox->setStandardButtons(QMessageBox::Ok);
	msgBox->setDefaultButton(QMessageBox::No);
	msgBox->setWindowTitle("SISTEMA DI TRAINING");
	msgBox->setIconPixmap(QPixmap("resources/icons/success.png"));
	msgBox->setStyle(QStyleFactory::create("Fusion"));



	msgBox->setStyle(QStyleFactory::create("Fusion"));
	msgBox->setFixedSize(542, 503);
	//msgBox->move((window_w-message.width())/2,(window_h-message.height())/2);

	QPalette darkPalette;
	darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));  darkPalette.shadow();
	darkPalette.setColor(QPalette::WindowText, Qt::white);
	darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
	darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
	darkPalette.setColor(QPalette::ToolTipText, Qt::white);
	darkPalette.setColor(QPalette::Text, Qt::white);
	darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
#ifdef _WIN32
	darkPalette.setColor(QPalette::ButtonText, QColor(25, 25, 25));
#else
	darkPalette.setColor(QPalette::ButtonText, Qt::white);
#endif    
	darkPalette.setColor(QPalette::BrightText, Qt::white);
	darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

	darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::HighlightedText, Qt::black);

	qApp->setPalette(darkPalette);

	qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");

	return msgBox;
}




inline QMessageBox* QtMessageBoxCreatorNoDataTrained() {


	//char buffer [50];
	//int n, a=5, b=3;
	//n=sprintf (buffer, "%d plus %d is %d", a, b, a+b);

	QMessageBox *msgBox = new QMessageBox(0); //const char cascade[]="resources\eye_left_18x12.xml";


											  /*QString labelText = "<P><b><FONT COLOR='#cc0000' FONT SIZE = 5>";
											  labelText.append("E&nbsp;&nbsp;R&nbsp;&nbsp;R&nbsp;&nbsp;O&nbsp;&nbsp;R&nbsp;&nbsp;E&nbsp;&nbsp;"
											  "&nbsp;&nbsp;&nbsp;&nbsp;C&nbsp;&nbsp;R&nbsp;&nbsp;I&nbsp;&nbsp;T&nbsp;&nbsp;I&nbsp;&nbsp;C&nbsp;&nbsp;O&nbsp;&nbsp;!");
											  labelText.append("</b></P></br>");
											  labelText.append("<P><b><i><FONT COLOR='#E0E0E0' FONT SIZE = 4>");
											  //QLabel label->setText(labelText);
											  labelText.append("P r o c e d u r a  &nbsp;d i&nbsp;  t r a i n i n g &nbsp;n o n &nbsp;e f f e t t u a t a !");
											  labelText.append("</i></b></P></br>");	*/

	QString labelText = ("<P><b><center><FONT COLOR='#cc0000' FONT SIZE = 5><u>ATTENZIONE:</u><br></b></P></center>");
	labelText.append("<P><b><FONT COLOR='#ffffff' FONT SIZE = 3>");
	labelText.append("P r o c e d u r a  &nbsp;d i&nbsp;  t r a i n i n g &nbsp;n o n &nbsp;e f f e t t u a t a !");
	labelText.append("</i></b></P></br>");

	msgBox->setText(labelText);

	msgBox->setWindowModality(Qt::NonModal);

	//labelText.append("</u></center></p></h3>");
	//msgBox->setInformativeText("\n\n<u>Programma terminato con errore</u>");
	labelText = "<br><br><FONT COLOR='#ffff00'  FONT SIZE = 2>\n\n<b><u>Programma terminato con errore.</u></b>";
	msgBox->setInformativeText(labelText);


	QIcon icon(("resources" + back_slash + "icons" + back_slash + "face.ico").c_str());
	msgBox->setWindowIcon(icon);

	//msgBox->setStandardButtons(QMessageBox::Escape);
	//QSpacerItem* horizontalSpacer = new QSpacerItem(1000, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
	//QGridLayout* layout = (QGridLayout*)msgBox->layout();
	//layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
	//msgBox->setBaseSize(QSize(600, 520));
	//msgBox->setFixedSize ( 500,500);
	QAbstractButton* exit = msgBox->addButton("Esci", QMessageBox::NoRole);

	//QAbstractButton* moreInfo =msgBox->addButton("Altre info", QMessageBox::NoRole);
	/*
	char logPath[500];
	char detaileString[1000];
	#ifdef _WIN32

	GetCurrentDir(logPath, sizeof(logPath));
	string current_path = logPath;
	//cout<<"cuurent path last:  "<<current_path<<endl;
	#else

	getcwd(logPath, sizeof(logPath));
	//string current_path = logPath;
	#endif

	sprintf(detaileString, "Impossibile caricare il file di cascade al seguente percorso:\n"
	"%s.\n\nVerificare che lo stesso non sia stato accidentalmente rimosso.\n\n"
	"File di log generato al seguente percorso: %s", classifier, logPath);
	msgBox->setDetailedText(detaileString);
	*/
	msgBox->setWindowFlags(msgBox->windowFlags() & Qt::WindowCloseButtonHint);
	// se metto così levva la x
	//msgBox->setWindowFlags(msgBox->windowFlags() & ~Qt::WindowCloseButtonHint);

	//QAbstractButton* open=msgBox->addButton("Apri", QMessageBox::NoRole);

	//msgBox->setDefaultButton(0);

	msgBox->setWindowTitle("CRITICAL ERROR");
	msgBox->setIcon(QMessageBox::Critical);
	msgBox->setStyle(QStyleFactory::create("Fusion"));
	//msgBox->setFixedSize(542, 503);
	//msgBox->move((window_w-message.width())/2,(window_h-message.height())/2);

	QPalette darkPalette;
	darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));  darkPalette.shadow();

	darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));

	darkPalette.setColor(QPalette::ButtonText, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::WindowText, Qt::white);




	//qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
	qApp->setPalette(darkPalette);
	msgBox->setStyleSheet("QToolTip { }");
	//msgBox->setPalette(darkPalette);



	//qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");

	return msgBox;
}


inline QMessageBox* QtMessageBox_SetupNotDone(const char * classifier) {


	//char buffer [50];
	//int n, a=5, b=3;
	//n=sprintf (buffer, "%d plus %d is %d", a, b, a+b);

	QMessageBox *msgBox = new QMessageBox(0); //const char cascade[]="resources\eye_left_18x12.xml";

	QString labelText;
	labelText.append("<P><b><center><FONT COLOR='#cc0000' FONT SIZE = 5><u>ATTENZIONE:</u><br><br></b></P></center>");
	labelText.append("<P><b><FONT COLOR='#ffffff' FONT SIZE = 4>");
	labelText.append(classifier);
	labelText.append("</P></b>");

	msgBox->setText(labelText);
	//msgBox->setInformativeText("\n\nScegliere No per cambiare directory...");


	msgBox->setWindowModality(Qt::NonModal);
	labelText = "<br><br>N:B.:&emsp;&emsp; <FONT COLOR='#ffff00'><u>Eseguire l'apposita applicazione di setup e rieseguire il programma</u>";
	msgBox->setInformativeText(labelText);

	//msgBox->setStandardButtons(QMessageBox::Escape);
	//QSpacerItem* horizontalSpacer = new QSpacerItem(1000, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
	//QGridLayout* layout = (QGridLayout*)msgBox->layout();
	//layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
	//msgBox->setBaseSize(QSize(600, 520));
	//msgBox->setFixedSize ( 500,500);
	msgBox->setStandardButtons(QMessageBox::Ok);
	//msgBox->setDefaultButton(QMessageBox::Ok);

	QIcon icon(("files" + back_slash + "gear.ico").c_str());
	msgBox->setWindowIcon(icon);

	msgBox->setWindowTitle("ERRORE IRREVERSIBILE");
	msgBox->setIcon(QMessageBox::Critical);
	msgBox->setStyle(QStyleFactory::create("Fusion"));
	msgBox->setFixedSize(542, 503);
	//msgBox->move((window_w-message.width())/2,(window_h-message.height())/2);

	QPalette darkPalette;
	darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));  darkPalette.shadow();

	darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));

	darkPalette.setColor(QPalette::ButtonText, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::WindowText, Qt::white);




	//qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
	qApp->setPalette(darkPalette);
	msgBox->setStyleSheet("QToolTip { }");
	//msgBox->setPalette(darkPalette);



	//qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");

	return msgBox;
}



inline int messageBox(const char * classifier, int type, int argc, char** argv) {
	//QCoreApplication::addLibraryPath("C:\\Users\\Valerio\\Downloads\\Qt\\5.7\\msvc2015_64\\plugins\\platforms");
	//QApplication app(argc, argv);
	QMessageBox * msgBox = NULL;
	if (type == 0 || type == 1) {

		if (Sys_language == "IT") {
			msgBox = QtMessageBoxCreatorErrorCascadeOrWebcam(classifier, type);
			FileLoggingITA(Data, Time, type, classifier);
		}
		else if (Sys_language == "EN")
			FileLoggingENG(Data, Time, type, classifier);
	}

	else if (type == 2)
		msgBox = QtMessageBoxCreatorErrorTrainRequest(classifier);

	else if (type == 3) {
		msgBox = QtMessageBoxCreatorTrainCompleted(classifier);
		if (Sys_language == "IT")
			FileLoggingITA(Data, Time, type, classifier);
		else if (Sys_language == "EN")
			FileLoggingENG(Data, Time, type, classifier);
	}

	else if (type == 4) {
		msgBox = QtMessageBoxCreatorNoDataTrained();
		if (Sys_language == "IT")
			FileLoggingITA(Data, Time, type, classifier);
		else if (Sys_language == "EN")
			FileLoggingENG(Data, Time, type, classifier);
	}

	else if (type == 5) {
		msgBox = QtMessageBox_SetupNotDone(classifier);
		//myUtils::playSound("dialog-error.wav");
		myUtils::playSound("bell.wav");
	}



	if (type == 0 || type == 1 || type == 4) {
		//system("aplay resources/sounds/dialog-error.wav --quiet");
		//myUtils::playSound("dialog-error.wav");
		myUtils::playSound("bell.wav");
	}

	else if (type == 2)
		//system("aplay resources/sounds/dialog-question.wav --quiet");
		myUtils::playSound("bell.wav");
	//myUtils::playSound("dialog-question.wav");

	else if (type == 3)
		//system("aplay resources/sounds/bell.wav --quiet");
		myUtils::playSound("bell.wav");


	int ret = msgBox->exec();

	return ret;
}

#endif
