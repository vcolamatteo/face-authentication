#ifndef SRC_Qt_messageBox_h
#define SRC_Qt_messageBox_h
//#ifndef _WIN32
//#pragma once

#include <iostream>

#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qstylefactory.h>
#include <QtWidgets/qlayoutitem.h>
#include <QtWidgets/qgridlayout.h>

#include "myUtils.h"

#ifdef _WIN32
#include <Windows.h>
#define GetCurrentDir _getcwd
#else
#include<unistd.h>
#endif

using namespace std;

string extern back_slash;
string extern Sys_language;


string extern Time;
string extern Data;

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
	string current_path = logPath;
	//cout<<"cuurent path last:  "<<current_path<<endl;
#else

	getcwd(logPath, sizeof(logPath));
	//string current_path = logPath;
#endif
	if (Sys_language == "IT") {
		sprintf(detaileString, "Impossibile caricare il file di cascade al seguente percorso:\n"
			"%s.\n\nVerificare che lo stesso non sia stato accidentalmente rimosso.\n\n"
			"File di log generato al seguente percorso: %s", classifier, logPath);
	}
	else {
		sprintf(detaileString, "Cascade file cannot being loaded at followng path:\n"
			"%s.\n\nVerify the one not being accidentally removed.\n\n"
			"File-log generated at following path: %s", classifier, logPath);
	}

	msgBox->setDetailedText(detaileString);


	QIcon icon("resources/icons/trainer.ico");
	msgBox->setWindowIcon(icon);


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


inline QMessageBox * QtMessageBoxCreatorErrorTrainRequest(string classifier) {

	QMessageBox *msgBox = new QMessageBox(0);
	//char all[100];
	//sprintf(all,"CASCADE NON TROVATO: %s\n",classifier);

	QString labelText = "<P><b><center><FONT COLOR='#E0E0E0'><br><br>";
	labelText.append("FACE AUTHNTICATION SYSTEM ");
	labelText.append("</center></P></b><b><br><br><br><br><br><br><FONT COLOR='#5ddffe'>");
	//labelText.append("</center></P></b><b><br><br><br><br><br><br><FONT COLOR='#bdfffe'>");

	//labelText.append("<center><u><b><p align='justify'>Si sta per avviare una nuova procedura di enrollment.</p></b></u><br><br><br>");
	//labelText.append(classifier);
	labelText.append("<center><FONT COLOR='#b4b4b6' FONT SIZE=4><br><br><br><br>ATTENZIONE:</center><br>");
	labelText.append("<center><u><FONT COLOR='#36d6f6'>SI STA PER AVVIARE UNA NUOVA SESSIONE DI ENROLLMENT</u></center><br><br>");
	labelText.append("<p align='justify'><FONT COLOR='#E0E0E0' FONT SIZE=4><br><br>Verrà effettato uno scanning facciale necessario per poter essere successivamente autenticati dal sistema.<br>Proseguendo, i dati relativi a sessioni di training precedenti saranno sovrascritti ed andranno perduti.<br>");
	labelText.append("Interrompendo prematuramente la procedura non sarà più possibile autenticarsi sino al nuovo enrollment.<br></p>");
	labelText.append("<FONT COLOR='#b4b4b6' FONT SIZE=4>Proseguire solo se si è effettivamente certi della scelta.</p>");
	labelText.append("</b></P>");
	//QLabel label->setText(labelText);

	msgBox->setText(labelText);

	msgBox->setWindowModality(Qt::NonModal);

	//labelText = "<FONT COLOR='#E0E0E0' FONT SIZE=3><br><br><br><br><br><br><br><p><center><b>N.B.: <FONT COLOR='#408fdd' FONT SIZE=2><u>";
	labelText = "<FONT COLOR='#E0E0E0' FONT SIZE=4><br><br><br><br><br><br><br><br><br><br><br><p><center><b><b><br><br><br>N.B.: <FONT COLOR='#b4b4b6' FONT SIZE=3><u>";

	if (Sys_language == "IT") {
		//msgBox->setInformativeText(labelText);
		//labelText.append("Al termine, i dati precedenti verranno sovrascritti.");
		if (classifier!="")
			labelText.append("Su questa macchina risulta già effettuata una sessione di training.");		  
		else
			labelText.append("Non risultano al momento effettuate altre sessioni di enrollment.");
	}
	else
		//msgBox->setInformativeText("All previous data won't be removed");
		labelText.append("Take attention: previous data will be removed");

	labelText.append("</u></center></p></b>");
	msgBox->setInformativeText(labelText);


	QIcon icon("resources/icons/trainer.ico");
	msgBox->setWindowIcon(icon);

	msgBox->setWindowModality(Qt::NonModal);
	msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	msgBox->setDefaultButton(QMessageBox::Ok);
	if (Sys_language == "IT")
		msgBox->setWindowTitle("SISTEMA DI TRAINING FACCIALE");
	else
		msgBox->setWindowTitle("FACE TRAINING SYSTEM");
	//msgBox->setIcon(QMessageBox::Question);
	//msgBox->setIconPixmap(QPixmap("resources/icons/QA.png"));
	msgBox->setIconPixmap(QPixmap("resources/icons/Face-scanning.jpg"));
	//msgBox->setStyle(QStyleFactory::create("Fusion"));



	//msgBox->setIcon(QMessageBox::Question);
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


inline QMessageBox * QtMessageBoxCreatorInstructions() {

	QMessageBox *msgBox = new QMessageBox(0);
	//char all[100];
	//sprintf(all,"CASCADE NON TROVATO: %s\n",classifier);

	QString labelText = "<P><b><center><FONT COLOR='#E0E0E0' FONT SIZE=4><br><br>";
	labelText.append("FACE AUTHNTICATION SYSTEM ");
	labelText.append("<br><br><FONT SIZE=3 FONT COLOR= '#5ddffe'><u>");
	labelText.append("Note per il corretto utilizzo:</u></center>");
	labelText.append("<br><br><br>");
	labelText.append("<b><FONT COLOR='#b8fffc'  FONT SIZE=4>");
	//labelText.append("<b><FONT COLOR='#5ddffe'  FONT SIZE=4>");
	labelText.append("<ul>");
	labelText.append("<li><p align='justify'>Nel corso del count-down posizonarsi al meglio all'interno della finestra.</li>");
	labelText.append("<li><p align='justify'>Nel caso ci si posizioni ad una distanza non corretta il count-down verrà sospeso e la procedura non potrà avere inizio sino al corretto riposizionamento del volto.</li>");
	labelText.append("<li><p align='justify'>Al temine del count-down, verrà avviata la fase di scanning del volto. L'intera pocedura durerà solo pochi secondi. Si consiglia di mantenere la posizione assunta durante il count-down per l'intera durata del processo.</li>");
	labelText.append("<li><p align='justify'>Si consiglia di rimanere sempre al centro dell'immagine video.</li>");
	labelText.append("<li><p align='justify'><u><FONT COLOR= '#5ddffe'><strong>Lo sguardo deve unicamente essere rivolto verso l'obiettivo della camera e non sull'immagine visibile a schermo.</strong></u></li>");
	labelText.append("<li><p align='justify'><FONT COLOR='#b8fffc'>Nella fase di scanning, nel caso si assuma inavvertitamente una posizione non corretta la procerdura verrà momentaneamente sospesa sino al corretto riposizionamento.</li>");
	labelText.append("<li><p align='justify'>E' possibile interrompere in qualsiasi momento la procedura tenendo premuto il tasto ESC sulla tastiera.</li>");
	labelText.append("</ul></p>");
	//labelText.append("</center></P></b><b><br><br><br><br><br><br><FONT COLOR='#E0E0E0'>");	
	labelText.append("</center></P></b><b><br>");
	labelText.append("</b></P>");
	//QLabel label->setText(labelText);

	msgBox->setText(labelText);

	msgBox->setWindowModality(Qt::NonModal);

	//labelText = "<FONT COLOR='#408fdd' FONT SIZE=3><br><br><br><br><br><br><br><p><center><b>N.B.: <FONT COLOR='#408fdd' FONT SIZE=3><u>";
	labelText = "<FONT COLOR='#E0E0E0' FONT SIZE=3><br><br><br><br><p><center><b>N.B.: <FONT COLOR='#5ddffe' FONT SIZE=3><u>";

	if (Sys_language == "IT") {
		//msgBox->setInformativeText(labelText);
		labelText.append("La pocedura può essere ripetuta in qualsiasi momento");
	}
	else
		//msgBox->setInformativeText("All previous data won't be removed");
		labelText.append("Take attention: previous data will be removed");

	labelText.append("</u></center></p></b><br><br>");
	msgBox->setInformativeText(labelText);


	QIcon icon("resources/icons/trainer.ico");
	msgBox->setWindowIcon(icon);

	msgBox->setWindowModality(Qt::NonModal);
	msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel | QMessageBox::Discard);
	msgBox->setDefaultButton(QMessageBox::Ok);
	if (Sys_language == "IT")
		msgBox->setWindowTitle("SISTEMA DI TRAINING FACCIALE");
	else
		msgBox->setWindowTitle("FACE TRAINING SYSTEM");
	//msgBox->setIcon(QMessageBox::Question);
	//msgBox->setIconPixmap(QPixmap("resources/icons/QA.png"));
	msgBox->setIconPixmap(QPixmap("resources/icons/a.png"));
	//msgBox->setStyle(QStyleFactory::create("Fusion"));



	//msgBox->setIcon(QMessageBox::Question);
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




inline QMessageBox * QtMessageBoxCreatorErrorTrainRequestAlreadyDone(const char * classifier) {

	QMessageBox *msgBox = new QMessageBox(0);
	//char all[100];
	//sprintf(all,"CASCADE NON TROVATO: %s\n",classifier);

	QString labelText = "<P><b><center><FONT COLOR='#E0E0E0'<br><br>";
	labelText.append("FACE AUTHNTICATION SYSTEM ");
	labelText.append("</center></P></b><b><br><br><br><br><br><br><FONT COLOR='#E0E0E0'>");

	labelText.append("Prima di iniziare è necessario effettuare una sessione di training.");
	labelText.append("</b></P>");
	//QLabel label->setText(labelText);

	msgBox->setText(labelText);

	msgBox->setWindowModality(Qt::NonModal);

	labelText = "<FONT COLOR='#E0E0E0' FONT SIZE=3><br><br><br><br><br><br><br><p><center>N.B.: <u><b>";

	if (Sys_language == "IT") {
		//msgBox->setInformativeText(labelText);
		labelText.append("Non risultano al momento effettuate altre sessioni di enrollment");
	}
	else
		//msgBox->setInformativeText("All previous data won't be removed");
		labelText.append("Take attention: previous data will be removed");

	labelText.append("</u></center></p></b>");
	msgBox->setInformativeText(labelText);


	QIcon icon("resources/icons/trainer.ico");
	msgBox->setWindowIcon(icon);

	msgBox->setWindowModality(Qt::NonModal);
	msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	msgBox->setDefaultButton(QMessageBox::Ok);
	if (Sys_language == "IT")
		msgBox->setWindowTitle("SISTEMA DI TRAINING FACCIALE");
	else
		msgBox->setWindowTitle("FACE TRAINING SYSTEM");
	//msgBox->setIcon(QMessageBox::Question);
	msgBox->setIconPixmap(QPixmap("resources/icons/QA.png"));
	//msgBox->setStyle(QStyleFactory::create("Fusion"));



	//msgBox->setIcon(QMessageBox::Question);
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



inline QMessageBox * QtMessageBoxCreatorTrainCompleted() {

	QMessageBox *msgBox = new QMessageBox(0);

	//QString labelText = "<FONT COLOR = '#009245'><h2><br><p><center>";
	QString labelText = "";
	

	if (Sys_language == "IT") {
		//labelText.append("   Premere ok per terminare... ");
		labelText.append("<FONT SIZE=5 FONT COLOR= '#E0E0E0'><u><b><center>Training completato con successo.</center></b></u>");
		labelText.append("<br><br><FONT SIZE=4 FONT COLOR= '#E0E0E0'><br><br><br><p align='justify'><b>Da ora è possible autentcarsi nel sistema con l'applicativo apposito.<br><br>");
		labelText.append("<br><FONT SIZE=4 FONT COLOR= '#9bbfd9'><b>In caso non si siano seguite le indicazioni d'uso elencate nella grafica iniziale di disclaimer o si ritenga vi siano intercorsi degli errori nel corso della procedura di enrollment o, semplicemente, non si sia sodidsfatti dell'operato del recognizer, è possibile ripetere la sessione di training appena conclusasi in qualsiasi momento.</b></p>");
		labelText.append("<br>");
	}
	else {
		//labelText.append("   Press ok for exiting... ");
		labelText.append("   Training data successfully ended... ");
	}

	labelText.append("");
	msgBox->setInformativeText(labelText);

	/*
	if (Sys_language=="IT"){
	msgBox->setText(classifier);
	msgBox->setInformativeText("\n\n   Premere ok per terminare...\n");
	}else{
	msgBox->setText("T R A I N I N G   C O M P L E T E D !");
	msgBox->setInformativeText("\n\nPress ok button for exiting...");
	}
	*/
	msgBox->setWindowModality(Qt::NonModal);
	msgBox->setStandardButtons(QMessageBox::Ok);
	msgBox->setDefaultButton(QMessageBox::No);
	//c("SISTEMA DI TRAINING");  
	QIcon icon("resources/icons/trainer.ico");
	msgBox->setWindowIcon(icon);
	//msgBox->setIconPixmap(QPixmap("resources/icons/QA.png"));
	msgBox->setIconPixmap(QPixmap("resources/icons/nec-facialrecognition.jpg"));
	msgBox->setStyle(QStyleFactory::create("Fusion"));


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

	QIcon icon(("files" + back_slash + "trainer.ico").c_str());
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

	//QApplication app(argc, argv);
	QMessageBox * msgBox = NULL;

	//QIcon icon("resources/icons/success.png");	

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

	else if (type == 6) {
		msgBox = QtMessageBoxCreatorErrorTrainRequestAlreadyDone("");
		myUtils::playSound("bell.wav");
	}
	else if (type == 7) {
		msgBox = QtMessageBoxCreatorInstructions();
		myUtils::playSound("bell.wav");
	}

	else if (type == 3) {
		msgBox = QtMessageBoxCreatorTrainCompleted();
		if (Sys_language == "IT")
			FileLoggingITA(Data, Time, type, classifier);
		else if (Sys_language == "EN")
			FileLoggingENG(Data, Time, type, classifier);
	}

	if (type == 0 || type == 1)
		//system("aplay resources/sounds/dialog-error.wav --quiet");
		myUtils::playSound("bell.wav");

	else if (type == 2)
		//system("aplay resources/sounds/dialog-question.wav --quiet");
		myUtils::playSound("bell.wav");

	else if (type == 3)
		//system("aplay resources/sounds/bell.wav --quiet");
		//myUtils::playSound("bell.wav");
	      myUtils::playSound("end.wav",1);


	else if (type == 5) {
		msgBox = QtMessageBox_SetupNotDone(classifier);
		myUtils::playSound("bell.wav");
	}

	int ret = msgBox->exec();



	return ret;
}


#endif
