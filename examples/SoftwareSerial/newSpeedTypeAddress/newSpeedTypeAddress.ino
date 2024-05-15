// ПРИМЕР СМЕНЫ АДРЕСА, СКОРОСТИ И ТИПА ПРОТОКОЛА MODBUS:                                          //
// На шине должен быть только один модуль HTL.                                                     //
// Текщий адрес модуля, скорость шины и тип протокола Modbus будут определены автоматически.       //
                                                                                                   //
#include <SoftwareSerial.h>                                                                        //   Подключаем библиотеку для работы с программной шиной UART.
#include <iarduino_Modbus.h>                                                                       //   Подключаем библиотеку для работы по протоколу Modbus.
#include <iarduino_MB_HTL.h>                                                                       //   Подключаем библиотеку для работы с модулем HTL.
                                                                                                   //
SoftwareSerial  rs485(8,9);                                                                        //   Создаём объект для работы с программной шиной UART-RS485 указывая выводы RX, TX.
ModbusClient    modbus(rs485, 2);                                                                  //   Создаём объект для работы по протоколу Modbus указывая объект программной шины UART-RS485 и вывод DE конвертера UART-RS485.
iarduino_MB_HTL sensor(modbus);                                                                    //   Создаём объект для работы с модулем HTL указывая объект протокола Modbus.
                                                                                                   //
uint32_t        newSpeed   = 9600;                                                                 //   Новая скорость ( 2400 / 4800 / 9600 / 19200 / 38400 / 57600 / 115200 ).
uint8_t         newAddress = 3;                                                                    //   Новый адрес ( 1 - 247 ).
uint8_t         newType    = MODBUS_RTU;                                                           //   Новый тип протокола Modbus ( MODBUS_RTU / MODBUS_ASCII ).
                                                                                                   //
#ifdef RENESAS_CORTEX_M4                                                                           //   Для плат Arduino UNO R4 ...
void wait_rs485(void){delay(10);}                                                                  //   Библиотека SoftwareSerial не поддерживает operator!(bool). По состоянию на март 2024г.
#else                                                                                              //   Для остальных плат ...
void wait_rs485(void){while(!rs485); delay(10);}                                                   //   Библиотека SoftwareSerial работает корректно.
#endif                                                                                             //   Возможно в будущем в библиотеку SoftwareSerial добавят operator!(bool).
                                                                                                   //
void setup(){                                                                                      //
     Serial.begin(9600 ); while(!Serial);                                                          //   Инициируем передачу данных в монитор последовательного порта, указав его скорость.
     modbus.begin();                                                                               //   Инициируем работу по протоколу Modbus.
     modbus.setTimeout(10);                                                                        //   Указываем максимальное время ожидания ответа по протоколу Modbus.
     modbus.setDelay(4);                                                                           //   Указываем минимальный интервал между отправляемыми сообщениями по протоколу Modbus.
//   Находим текущий адрес модуля HTL, скорость и тип протокола Modbus:                            //
//   - если тип протокола Modbus известен, то его изменение можно удалить.                         //
//   - если скорость известна, то строки с другими скоростями можно удалить.                       //
             bool f=false;                                                                         //   Определяем флаг для получения результатов из функций.
             Serial.print("Поиск модуля HTL...");                                                  //
     if(!f){ modbus.setTypeMB( MODBUS_RTU ); }                                                     //   Указываем тип протокола Modbus RTU.
     if(!f){ rs485.begin(  2400); wait_rs485(); Serial.print('.'); f=sensor.begin(); }             //   Инициируем работу с модулем на скорости   2400, без указания адреса (адрес будет найден автоматически).
     if(!f){ rs485.begin(  4800); wait_rs485(); Serial.print('.'); f=sensor.begin(); }             //   Инициируем работу с модулем на скорости   4800, без указания адреса (адрес будет найден автоматически).
     if(!f){ rs485.begin(  9600); wait_rs485(); Serial.print('.'); f=sensor.begin(); }             //   Инициируем работу с модулем на скорости   9600, без указания адреса (адрес будет найден автоматически).
     if(!f){ rs485.begin( 19200); wait_rs485(); Serial.print('.'); f=sensor.begin(); }             //   Инициируем работу с модулем на скорости  19200, без указания адреса (адрес будет найден автоматически).
     if(!f){ rs485.begin( 38400); wait_rs485(); Serial.print('.'); f=sensor.begin(); }             //   Инициируем работу с модулем на скорости  38400, без указания адреса (адрес будет найден автоматически).
     if(!f){ rs485.begin( 57600); wait_rs485(); Serial.print('.'); f=sensor.begin(); }             //   Инициируем работу с модулем на скорости  57600, без указания адреса (адрес будет найден автоматически).
     if(!f){ rs485.begin(115200); wait_rs485(); Serial.print('.'); f=sensor.begin(); }             //   Инициируем работу с модулем на скорости 115200, без указания адреса (адрес будет найден автоматически).
     if(!f){ modbus.setTypeMB( MODBUS_ASCII ); }                                                   //   Указываем тип протокола Modbus ASCII.
     if(!f){ rs485.begin(  2400); wait_rs485(); Serial.print('.'); f=sensor.begin(); }             //   Инициируем работу с модулем на скорости   2400, без указания адреса (адрес будет найден автоматически).
     if(!f){ rs485.begin(  4800); wait_rs485(); Serial.print('.'); f=sensor.begin(); }             //   Инициируем работу с модулем на скорости   4800, без указания адреса (адрес будет найден автоматически).
     if(!f){ rs485.begin(  9600); wait_rs485(); Serial.print('.'); f=sensor.begin(); }             //   Инициируем работу с модулем на скорости   9600, без указания адреса (адрес будет найден автоматически).
     if(!f){ rs485.begin( 19200); wait_rs485(); Serial.print('.'); f=sensor.begin(); }             //   Инициируем работу с модулем на скорости  19200, без указания адреса (адрес будет найден автоматически).
     if(!f){ rs485.begin( 38400); wait_rs485(); Serial.print('.'); f=sensor.begin(); }             //   Инициируем работу с модулем на скорости  38400, без указания адреса (адрес будет найден автоматически).
     if(!f){ rs485.begin( 57600); wait_rs485(); Serial.print('.'); f=sensor.begin(); }             //   Инициируем работу с модулем на скорости  57600, без указания адреса (адрес будет найден автоматически).
     if(!f){ rs485.begin(115200); wait_rs485(); Serial.print('.'); f=sensor.begin(); }             //   Инициируем работу с модулем на скорости 115200, без указания адреса (адрес будет найден автоматически).
//   Выводим результат обнаружения модуля HTL:                                                     //
     if(!f){ Serial.println("\r\nМодуль HTL не найден"); return; }                                 //
     else  { Serial.println("\r\nМодуль HTL найден"   );         }                                 //
//   Меняем адрес модуля HTL:                                                                      //
     f =     sensor.changeID(newAddress);                                                          //
     if(!f){ Serial.println("Адрес не изменён"); return; }                                         //
//   Устанавливаем новую скорость передачи данных модуля HTL:                                      //
     f =     sensor.setSpeedMB(newSpeed);                                                          //   После установки новой скорости, её нужно подтвердить в течении 2 секунд.
     if(!f){ Serial.println("Скорость не изменена"); return; }                                     //
//   Меняем скорость шины:                                                                         //
             rs485.begin(newSpeed); wait_rs485();                                                  //
//   Подтверждаем изменение скорости передачи данных модуля HTL:                                   //
     f =     sensor.ackSpeedMB();                                                                  //   Если скорость не подтверждена за 2 секунды, модуль вернёт предыдущую скорость.
     if(!f){ Serial.println("Скорость не подтверждена"); return; }                                 //
//   Устанавливаем новый тип протокола модуля HTL:                                                 //
     f =     sensor.setTypeMB(newType);                                                            //   После установки нового типа протокола, его нужно подтвердить в течении 2 секунд.
     if(!f){ Serial.println("Тип протокола не изменён"); return; }                                 //
//   Меняем тип протокола на шине:                                                                 //
             modbus.setTypeMB(newType); delay(10);                                                 //
//   Подтверждаем изменение типа протокола модуля HTL:                                             //
     f =     sensor.ackTypeMB();                                                                   //   Если тип протокола не подтверждён за 2 секунды, модуль вернёт предыдущий протокол.
     if(!f){ Serial.println("Тип протокола не подтверждён"); return; }                             //
//   Выводим сообшение об успешном изменении адреса, скорости и типа протокола:                    //
             Serial.println(         "Адрес, скорость и тип протокола успешно изменены"  );        //
             Serial.println((String) "Скорость = "+newSpeed                              );        //   Выводим скорость передачи данных.
             Serial.println((String) "Modbus   = "+(newType==MODBUS_ASCII?"ASCII":"RTU") );        //   Выводим тип протокола Modbus.
             Serial.println((String) "Адрес    = "+sensor.getID()                        );        //   Выводим адрес модуля HTL.
             Serial.println((String) "Версия   = "+sensor.getVersion()                   );        //   Выводим версию прошивки модуля HTL.
}                                                                                                  //
                                                                                                   //
void loop(){                                                                                       //
//   Мигаем светодиодом обнаружения устройства (на разъёме):                                       //
     sensor.setIDLED(false); delay(1000);                                                          //
     sensor.setIDLED(true ); delay(1000);                                                          //
}                                                                                                  //
