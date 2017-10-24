#ifndef _logging_h
#define _logging_h

#include "config.h"
#include <iostream>
#include <fstream>

string extern back_slash;

using namespace std;

//#include "myUtils.h"
inline  bool fexists__(string filename)
{
	ifstream ifile(filename);
	return (bool)ifile;
}

inline void FileLoggingITA(string Data, string Time, int type, string side){


	string filelog="Log_file_at_"+Data+".dat";

	ofstream FILE_log;

	bool c = thesis::isDirectory("resources" + back_slash + "File_log");
	//cout << "c  " << c << endl;
	if (c == 0)
	thesis::make_dir(("resources"+back_slash+"File_log"+back_slash).c_str());

	if (fexists__(("resources"+back_slash+"File_log" +back_slash+ filelog).c_str())) {
	FILE_log.open(("resources"+back_slash+"File_log" +back_slash+ filelog).c_str(), ios::app);
	FILE_log <<"*** -- - -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- ***\n";
	}
	else{
	FILE_log.open(("resources"+back_slash+"File_log" +back_slash+ filelog).c_str(), ios::out);
	FILE_log <<"***************************************************************************************************\n";
}

	//__17-10-2016 AT: 12_02_44__

	FILE_log <<"*                                                                                                 *\n";
	FILE_log <<"*                                 __" << Data << " AT: " << Time <<"__                                     *"<< endl;
	FILE_log <<"*                                                                                                 *\n";
	FILE_log <<"***************************************************************************************************\n";

      if (type==0){

   FILE_log << "  *  (Run-Time error -- Training System Face Recognition:) Errore nel caricamento del file di   *\n";
   if (side == "rx")
   FILE_log << "  *  cascade seguente: resources\\eye_right_18x12.xml.                                            *\n";
		else
   FILE_log << "  *  cascade seguente: resources\\eye_left_18x12.xml.                                             *\n"
               "  *  E' probabile che sia stato accidentalmente rimosso o sposato.                              *\n";
               "  *  Ricollocare il file nella posizione indicata e provare a rieseguire il programma.          *\n";
      }


      if (type==1){

       FILE_log <<"  * (Run-Time error -- Training System Face Recognition:) Errore intercorso nell'apertura della *\n"
    		      "  * camera del proprio PC                                                                       *\n"
                  "  * Per risolvere verificare quanto segue:                                                      *\n"
    		      "  *                                                                                             *\n"
                  "  *                                                                                             *\n"
                  "  *  -  Il PC deve essere dotato internamente o previo collegamento esterno di una webcam con   *\n"
                  "  *     risoluzione minima VGA (640x320 pixel);                                                 *\n"
    		      "  *                                                                                             *\n"
                  "  *  -  Nel caso in cui siano collegate più camere allo stesso PC il programma cerca di aprire  *\n"
                  "  *     la camera impostata come principale dal sistema: verificre se il relativo dispositivo   *\n"
                  "  *     (unità di ordine 0) sia effettivamente funzionante;                                     *\n"
                  "  *     E' possibile che la camera principale (camera di ordine zero) sia \"controllata\" da      *\n"
                  "  *     un applicativo terzo che ne impedisce l'apertura. Tipicamente ciò accade se sia hanno   *\n"
                  "  *     applicazioni di utilizzo specifico della webcam correntemente installate sul proprio    *\n"
                  "  *     PC. In tal caso provare ad avviare tale applicazione prima di eseguire il programma o,  *\n"
                  "  *     alternativamente, dalle impostazioni del sistema operativo, variare l'ordine di         *\n"
                  "  *     importanza dei dispositivi di cattura audio/video installati indicando come di root     *\n"
                  "  *     (dispositivo di output di ordine 0) la camera stessa e non l'applicativo terzo di       *\n"
                  "  *     cui prima. In ultima analisi, provare a disinstallare tutte le applicazioni presenti    *\n"
                  "  *     di comando delle webcam.                                                                *\n";
      }

      if (type==3){

       FILE_log <<"  /*********************   PROCEDURA DI TRAINING COMPLETATA CON SUCCESSO   *********************/\n ";
      }

	FILE_log <<"  *     ----           ----           ----           ----           ----           ----         *\n\n";


}

inline void FileLoggingENG(string Data, string Time, int type, string side){


	string filelog="Log_file_at_"+Data+".dat";

	ofstream FILE_log;

	bool c = thesis::isDirectory("resources" + back_slash + "File_log");
	//cout << "c= " << c << endl;
	if (c == 0)
	thesis::make_dir(("resources"+back_slash+"File_log"+back_slash).c_str());

	if (fexists__(("resources" + back_slash + "File_log" +back_slash+ filelog).c_str())) {
	FILE_log.open(("resources" + back_slash + "File_log" +back_slash+ filelog).c_str(), ios::app);
	FILE_log <<"*** -- - -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- ***\n";
	}
	else{
	FILE_log.open(("resources" + back_slash + "File_log" +back_slash+ filelog).c_str(), ios::out);
	FILE_log <<"***************************************************************************************************\n";
}

	//__17-10-2016 AT: 12_02_44__

	FILE_log <<"*                                                                                                 *\n";
	FILE_log <<"*                                 __" << Data << " AT: " << Time <<"__                                     *"<< endl;
	FILE_log <<"*                                                                                                 *\n";
	FILE_log <<"***************************************************************************************************\n";

      if (type==0){

   FILE_log << "  *  (Run-Time error -- Training System Face Recognition:) Error caused by the missing of the   *\n";
   if (side == "rx")
	   FILE_log << "  *  following file-cascade: resources\\eye_right_18x12.xml.                                      *\n";
   else
	   FILE_log << "  *  following file-cascade: resources\\eye_left_18x12.xml.                                       *\n";
       FILE_log << "  *  This file could be accidentally moved or deleteted.                                        *\n"
                   "  *  Replace the file in its original path and try to run the program again.                    *\n";
      }


      if (type==1){

       FILE_log <<"  * (Run-Time error -- Training System Face Recognition:) Error caused by not-opening device    *\n"
    		      "  * camera of your PC.                                                                          *\n"
                  "  * Bypass this point should be done thanks one of the following:                               *\n"
    		      "  *                                                                                             *\n"
                  "  *                                                                                             *\n"
                  "  *  -  Your PC should be have a webcam with VGA as minimum resolution (640x320 pixel);         *\n"
    		      "  *                                                                                             *\n"
                  "  *  -  If you have more camera-device connected at your PC, you should know this program try   *\n"
                  "  *     opening the one setted as the principal (tpically named as number 0) from your O.S.: so *\n"
                  "  *     first of all identify it and verify it can work;                                        *\n"
                  "  *     It's also possible that the principal camera is \"controlled\" by a third application     *\n"
                  "  *     that you usually use for the current use of the camera. Then, this app could deny its   *\n"
                  "  *     access by other programs. If so you should try to start your favorite camera-app before *\n"
                  "  *     launching this program. On the other hand you could go in settings of your O.S. and set *\n"
                  "  *     your cam (and not your favorite app) as principal camera device (tipically root-device  *\n"
                  "  *     or device number 0).                                                                    *\n"
                  "  *     Your last chance could be obviously uninstall all camera app installed on your PC that  *\n"
                  "  *     could cause this iussue.                                                                *\n";
      }

      if (type==3){

      FILE_log <<"  ***************************   TRAINING SUCCESSFULLY COMPLETED!   ******************************  \n";
      }

	  FILE_log << "  *     ----           ----           ----           ----           ----           ----         *\n\n";


}

#endif /* SRC_LOGGING_H_ */
