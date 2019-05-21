//  Данный пример демонстрирует автоматическую перезагрузку модуля при его "зависании":
//  ==========================================================================================
#include <iarduino_GSM.h>                                    // Подключаем библиотеку для работы с GSM/GPRS Shield.
#include <SoftwareSerial.h>                                  // Подключаем библиотеку для работы с программной шиной UART.
                                                             //
iarduino_GSM   gsm;                                          // Объявляем  объект gsm для работы с функциями и методами библиотеки iarduino_GSM.
SoftwareSerial ccu(7,8);                                     // Объявляем  объект ccu для работы с программной шиной UART указывая выводы RX и TX платы Arduino.
uint8_t        cnt=0;                                        // Определяем переменную для хранения количества зафиксированных подряд ошибок.
                                                             //
void setup(){                                                //
    gsm.begin(ccu);                                          // Инициируем работу GSM/GPRS Shield, указывая объект шины UART.
//  Ждём завершения регистрации модема в сети оператора:     //
    for(int i=0; i<120; i++){ delay(1000);                   // Выполняем цикл 120 раз примерно за 120 секунд ...
        if (gsm.status()==GSM_OK){i=120;}                    // Если модуль готов к работе, то досрочно выходим из цикла for().
    }                                                        //
}                                                            //
                                                             //
void loop(){                                                 //
//  Место для оосновного кода программы:                     //
//  ...                                                      //
//  Код проверки работоспособности модуля:                   //
    if (millis()%60000 < 1000){ delay(1000);                 // Разрешаем выполнять код в теле оператора if один раз в минуту ...
//      Считаем количество ошибок состояния модуля:          //
        if (gsm.runAT("AT\r\n").indexOf("OK")<0){cnt++;}else // Если модуль не ответил OK на команду AT, то увеличиваем счётчик ошибок cnt.
        if (gsm.status() != GSM_OK             ){cnt++;}else // Если статус модуля отличен от GSM_OK   , то увеличиваем счётчик ошибок cnt.
                                                {cnt=0;}     // Иначе (если модуль работает корректно) , то сбрасываем  счётчик ошибок cnt.
//      Перезагружаем модуль если было 3 ошибки подряд:      //
        if (cnt>3){                                          // Если зафиксировано более 3 ошибок подряд, то ...
            cnt=0;                                           // Сбрасываем счётчик количества обнаруженных подряд ошибок.
            gsm.reset();                                     // Перезагружаем модуль (выполняется более чем за 2 секунды).
//          Ждём завершения регистрации модема в сети:       //
            for(int i=0; i<120; i++){ delay(1000);           // Выполняем цикл 120 раз примерно за 120 секунд ...
                if (gsm.status()==GSM_OK){i=120;}            // Если модуль готов к работе, то досрочно выходим из цикла for().
            }                                                //
        }                                                    //
    }                                                        //
//  Место для оосновного кода программы:                     //
//  ...                                                      //
}                                                            //