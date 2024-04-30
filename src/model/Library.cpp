#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <stdexcept>
#include <vector>

#include <thread>
#include <unistd.h>
#include <mutex>
#include <atomic>

#include <chrono>
#include <ctime>

#include <string>
#include <cstring>

#include <regex>

#include <wiringPi.h>
#include <mysql/mysql.h>
#include <curl/curl.h>


//MODEL
#ifndef TEST_LED_H
#ifndef TEST_LED
#define TEST_LED_H
#include "Led.cpp"
#endif
#endif

#ifndef TEST_LED_INTERNET_H
#ifndef TEST_LED_INTERNET
#ifndef TEST_LED // non devo ereditare i figli nelle classi padri!
#define TEST_LED_INTERNET_H
#include "LedInternet.cpp"
#endif
#endif
#endif

#ifndef TEST_LED_SIGNAL_H
#ifndef TEST_LED_SIGNAL
#ifndef TEST_LED_WRITE
#ifndef TEST_LED // non devo ereditare i figli nelle classi padri!
#ifndef TEST_SYSTEM // devo metterlo per tutte le classi che usano SystemState se no i test per la classe SystemState si rompono!
#define TEST_LED_SIGNAL_H
#include "LedSignal.cpp"
#endif
#endif
#endif
#endif
#endif

#ifndef TEST_LED_WRITE_H
#ifndef TEST_LED_WRITE
#ifndef TEST_LED // non devo ereditare i figli nelle classi padri!
#ifndef TEST_LED_SIGNAL // devo metterlo per tutte le classi che usano LedSignal se no i test per la classe LedSignal si rompono!
#ifndef TEST_SYSTEM// devo metterlo per tutte le classi che usano SystemState se no i test per la classe SystemState si rompono!
#define TEST_LED_WRITE_H
#include "LedWrite.cpp"
#endif
#endif
#endif
#endif
#endif

#ifndef TEST_BUZZER_H
#ifndef TEST_BUZZER
#define TEST_BUZZER_H
#include "Buzzer.cpp"
#endif
#endif

#ifndef TEST_QUERY_H
#ifndef TEST_QUERY
#define TEST_QUERY_H
#include "../model/Query.cpp"
#endif
#endif

/*IL PROBLEMA SI PRESENTA PERCHE HO DIPENDENZA CIRCOLARE, QUINDI DEVO NECESSARIAMENTE RICORRERE A .H!*/
/*
#ifndef TEST_SYSTEM_H
#ifndef TEST_SYSTEM
#define TEST_SYSTEM_H
//#include "SystemState.cpp" -> ho dovuto creare .h per evitare problemi di dipendenza circolare vari!
#endif
#endif
*/

#ifndef TEST_BUTTON_H
#ifndef TEST_BUTTON
#define TEST_BUTTON_H
#include "Button.cpp"
#endif
#endif

#ifndef TEST_BUTTON_WRITE_H
#ifndef TEST_BUTTON_WRITE
#ifndef TEST_SYSTEM // devo metterlo per tutte le classi che usano SystemState se no i test per la classe SystemState si rompono!
#ifndef TEST_BUTTON //non devo ereditare i figli nelle classi padri!
#define TEST_BUTTON_WRITE_H
#include "ButtonWrite.cpp"
#endif
#endif
#endif
#endif

// CONTROLLER
#ifndef TEST_DB_H
#ifndef TEST_DB
#define TEST_DB_H
#include "../controller/DatabaseConnection.cpp"
#endif
#endif

#ifndef TEST_DB_SECURE_H
#ifndef TEST_DB_SECURE
#ifndef TEST_DB // non devo ereditare i figli nelle classi padri!
#define TEST_DB_SECURE_H
//#include "../controller/DatabaseSecureConnection.cpp"
#endif
#endif
#endif

#ifndef TEST_DB_TIMBRATURE_H
#ifndef TEST_DB_TIMBRATURE
#ifndef TEST_DB // non devo ereditare i figli nelle classi padri!
#define TEST_DB_TIMBRATURE_H
#include "../controller/DatabaseTimbrature.cpp"
#endif
#endif
#endif

#ifndef TEST_GIT_H
#ifndef TEST_GIT
#define TEST_GIT_H
#include "../controller/Github.cpp"
#endif
#endif

#ifndef TEST_INTERNET_H
#ifndef TEST_INTERNET
#define TEST_INTERNET_H
#include "../controller/InternetConnection.cpp"
#endif
#endif

#ifndef TEST_MAIL_H
#ifndef TEST_MAIL
#define TEST_INTERNET_H
#include "../controller/MailHandler.cpp"
#endif
#endif

#ifndef TEST_MAIN_CONTROLLER_H
#ifndef TEST_MAIN_CONTROLLER
#ifndef TEST_SYSTEM // devo metterlo per tutte le classi che usano SystemState se no i test per la classe SystemState si rompono!
#ifndef TEST_LED_WRITE // devo metterlo per tutte le classi che usano LedWrite se no i test per la classe LedWrite si rompono!
#ifndef TEST_LED_SIGNAL // devo metterlo per tutte le classi che usano LedSignal se no i test per la classe LedSignal si rompono!
#define TEST_MAIN_CONTROLLER_H
// #include "../controller/MainController.cpp"
#endif
#endif
#endif
#endif
#endif

#ifndef TEST_RFID_H
#ifndef TEST_RFID
#define TEST_RFID_H
#include "../controller/RFIDAdapter.cpp"
#endif
#endif

class Library
{
    
};