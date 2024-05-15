// ПРИМЕР ЧТЕНИЯ ДАННЫХ С ПРОВЕРКОЙ ИЗ МОДУЛЯ HTL:                                 //
// Чтение данных без проверки доступно в примере "getDataShort"                    //
                                                                                   //
#include <SoftwareSerial.h>                                                        //   Подключаем библиотеку для работы с программной шиной UART.
#include <iarduino_Modbus.h>                                                       //   Подключаем библиотеку для работы по протоколу Modbus.
#include <iarduino_MB_HTL.h>                                                       //   Подключаем библиотеку для работы с модулем HTL.
                                                                                   //
SoftwareSerial  rs485(8,9);                                                        //   Создаём объект для работы с программной шиной UART-RS485 указывая выводы RX, TX.
ModbusClient    modbus(rs485, 2);                                                  //   Создаём объект для работы по протоколу Modbus указывая объект программной шины UART-RS485 и вывод DE конвертера UART-RS485.
iarduino_MB_HTL sensor(modbus);                                                    //   Создаём объект для работы с модулем HTL указывая объект протокола Modbus.
                                                                                   //
void setup(){                                                                      //
     Serial.begin(9600);   while(!Serial);                                         //   Инициируем передачу данных в монитор последовательного порта, указав его скорость.
     rs485.begin(9600); // while(!rs485 );                                         //   Инициируем работу с программной шиной UART-RS485 указав её скорость.
     modbus.begin();                                                               //   Инициируем работу по протоколу Modbus.
//   modbus.setTimeout(10);                                                        //   Указываем максимальное время ожидания ответа по протоколу Modbus.
//   modbus.setDelay(4);                                                           //   Указываем минимальный интервал между отправляемыми сообщениями по протоколу Modbus.
//   modbus.setTypeMB( MODBUS_RTU );                                               //   Указываем тип протокола Modbus: MODBUS_RTU (по умолчанию), или MODBUS_ASCII.
     sensor.begin(3);                                                              //   Инициируем работу с модулем HTL, указав его адрес. Если адрес не указан sensor.begin(), то он будет найден, но это займёт некоторое время.
//   sensor.setPeriod( SENSOR_SHT, 0.5f );                                         //   Указываем модулю обновлять данные датчика влажности и температуры каждые 0.5 секунд.
//   sensor.setPeriod( SENSOR_LTR, 1.0f );                                         //   Указываем модулю обновлять данные датчика освещённости каждую секунду.
}                                                                                  //
                                                                                   //
void loop(){                                                                       //
//   Задержка (не обязательно):                                                    //
     delay(1000);                                                                  //
                                                                                   //
//   Проверяем работу датчиков (не обязательно):                                   //
     int8_t err = sensor.checkSensor(SENSOR_ALL);                                  //   Проверяем все датчики модуля. Можно проверить конкретный датчик: SENSOR_SHT (влажность и температура) или SENSOR_LTR (освещённость).
     if( err<0 ){ Serial.println("Модуль не отвечает"); delay(1000); return;    }  //   Ошибка чтения данных из модуля. Модуль не отвечает.
                                                                                   //
     if( err                  )    { Serial.println("Обнаружены ошибки:");      }  //   Ошибка модуля, невозможно проверить датчики.
     if( err & ERROR_SHT_INIT )    { Serial.println("- неисправен датчик SHT"); }  //   Модуль не смог инициировать датчик влажности и температуры.
     if( err & ERROR_SHT_DATA )    { Serial.println("- ошибка чтения SHT");     }  //   Модуль выявил ошибку при чтении данных из датчика влажности и температуры.
     if( err & ERROR_LTR_INIT )    { Serial.println("- неисправен датчик LTR"); }  //   Модуль не смог инициировать датчик освещённости.
     if( err & ERROR_LTR_DATA )    { Serial.println("- ошибка чтения LTR");     }  //   Модуль выявил ошибку при чтении данных из датчика освещённости.
     if( err                  )    { sensor.reset(); delay(1000); return;       }  //   Если есть любая ошибка, то перезагружаем модуль. Датчики модуля будут переинициированы.
                                                                                   //
     float data;                                                                   //   Объявляем переменную для получения данных.
                                                                                   //
//   Читаем температуру:                                                           //
     data = sensor.getTEM();         Serial.print("TEM=" );                        //   Читаем данные.
     if( data < -40 )              { Serial.print("ERROR"); }                      //   Сообщаем об ошибке чтения.
     else                          { Serial.print(data, 1); }                      //   Выводим данные с одном знаком после запятой.
                                     Serial.print("°C, " );                        //   Выводим единицы измерения.
//   Читаем относительную влажность:                                               //
     data = sensor.getHUM();         Serial.print("HUM=" );                        //   Читаем данные.
     if( data < 0 )                { Serial.print("ERROR"); }                      //   Сообщаем об ошибке чтения.
     else                          { Serial.print(data, 1); }                      //   Выводим данные с одном знаком после запятой.
                                     Serial.print("%, "  );                        //   Выводим единицы измерения.
//   Читаем абсолютную влажность:                                                  //
     data = sensor.getHUMA();        Serial.print("HUM=" );                        //   Читаем данные.
     if( data < 0 )                { Serial.print("ERROR"); }                      //   Сообщаем об ошибке чтения.
     else                          { Serial.print(data, 2); }                      //   Выводим данные с двумя знаками после запятой.
                                     Serial.print("г/м3, ");                       //   Выводим единицы измерения.
//   Читаем освещённость:                                                          //
     data = sensor.getLUX();         Serial.print("LUX=" );                        //   Читаем данные.
     if( data < 0 )                { Serial.print("ERROR"); }                      //   Сообщаем об ошибке чтения.
     else                          { Serial.print(data, 0); }                      //   Выводим данные целочисленно.
                                     Serial.print("лк.\r\n" );                     //   Выводим единицы измерения.
}                                                                                  //