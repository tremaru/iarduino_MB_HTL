//	Библиотека для работы с модулем датчиков влажности (H), температуры (T) и освещённости (L) по шине Modbus: https://iarduino.ru
//  Версия: 1.0.0
//  Последнюю версию библиотеки Вы можете скачать по ссылке: https://iarduino.ru
//  Подробное описание функции бибилиотеки доступно по ссылке: https://wiki.iarduino.ru
//  Библиотека является собственностью интернет магазина iarduino.ru и может свободно использоваться и распространяться!
//  При публикации устройств или скетчей с использованием данной библиотеки, как целиком, так и её частей,
//  в том числе и в некоммерческих целях, просим Вас опубликовать ссылку: http://iarduino.ru
//  Автор библиотеки: Панькин Павел
//  Если у Вас возникли технические вопросы, напишите нам: shop@iarduino.ru

#ifndef iarduino_MB_HTL_h
#define iarduino_MB_HTL_h

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

	#include <iarduino_Modbus.h>												//	Подключаем файл iarduino_Modbus.h - для работы по протоколу Modbus.
																				//
	#define DEF_MODEL_HTL					5									//	Идентификатор модели (2 датчика SHT,    LTR) - константа.
																				//
	#define SENSOR_ALL						0									//	Аргумент функций checkSensor(), setPeriod(), getPeriod() - все датчики.
	#define SENSOR_SHT						1									//	Аргумент функций checkSensor(), setPeriod(), getPeriod() - датчик температуры и влажности.
//	#define SENSOR_SGP						2									//	Аргумент функций checkSensor(), setPeriod(), getPeriod() - датчик углекислого газа.
	#define SENSOR_LTR						3									//	Аргумент функций checkSensor(), setPeriod(), getPeriod() - датчик освещенности.
																				//
	#define ERROR_SHT_INIT					0b00000001							//	Ошибка возвращаемая функцией checkSensor() - ошибка инициализации датчика влажности и температуры SHT20.
	#define ERROR_SHT_DATA					0b00000010							//	Ошибка возвращаемая функцией checkSensor() - ошибка чтения данных датчика влажности и температуры SHT20.
//	#define ERROR_SGP_INIT					0b00000100							//	Ошибка возвращаемая функцией checkSensor() - ошибка инициализации датчика углекислого газа SGP30.
//	#define ERROR_SGP_DATA					0b00001000							//	Ошибка возвращаемая функцией checkSensor() - ошибка чтения данных датчика углекислого газа SGP30.
	#define ERROR_LTR_INIT					0b00010000							//	Ошибка возвращаемая функцией checkSensor() - ошибка инициализации датчика освещенности и приближения LTR-553ALS-01.
	#define ERROR_LTR_DATA					0b00100000							//	Ошибка возвращаемая функцией checkSensor() - ошибка чтения данных датчика освещенности и приближения LTR-553ALS-01.
																				//
class iarduino_MB_HTL{															//
	public:																		//
	/**	Конструктор класса **/													//
		iarduino_MB_HTL					(ModbusClient&	);						//	Объявляем конструктор класса.											Параметры: ссылка на объект работы по протоколу Modbus.
	/**	Пользовательские функции **/											//
		bool			begin			(uint8_t id=0	);						//	Объявляем  функцию инициализации модуля датчиков.						Параметры функции: ID модуля датчиков. Функция возвращает результат инициализации: true-успех / false-провал.
		bool			reset			(void			);						//	Объявляем  функцию перезагрузки модуля датчиков.						Параметры функции: нет. Функция возвращает результат перезагрузки: true-успех / false-провал.
		bool			changeID		(uint8_t new_id	);						//	Объявляем  функцию смены ID модуля датчиков (выполняется >120мс).		Параметры функции: новый ID. Функция возвращает результат смены ID: true-успех / false-провал.
		bool			setSpeedMB		(uint32_t speed	);						//	Объявляем  функцию смены скорости передачи данных.						Параметры функции: новая скорость. Функция возвращает результат смены скорости: true-успех / false-провал. Скорость необходимо подтвердить в течении 2 секунд.
		bool			ackSpeedMB		(void			);						//	Объявляем  функцию подтверждения скорости (выполняется >50мс).			Параметры функции: нет. Функция возвращает результат подтверждения скорости: true-успех / false-провал. 
		bool			setTypeMB		(uint8_t type	);						//	Объявляем  функцию смены типа протокола Modbus.							Параметры функции: MODBUS_RTU/MODBUS_ASCII. Функция возвращает результат смены типа протокола Modbus: true-успех / false-провал. Тип необходимо подтвердить в течении 2 секунд.
		bool			ackTypeMB		(void			);						//	Объявляем  функцию подтверждения типа протокола (выполняется >50мс).	Параметры функции: нет. Функция возвращает результат подтверждения типа протокола Modbus: true-успех / false-провал. 
		bool			writeFlash		(uint16_t data	);						//	Объявляем  функцию записи пользовательского значения в Flash память.	Параметры функции: целое беззнаковое число от 0 до 65535. Функция возвращает результат записи: true-успех / false-провал. 
		int32_t			readFlash		(void			);						//	Объявляем  функцию чтения пользовательского значения из Flash памяти.	Параметры функции: нет. Функция возвращает прочитанное значение, или -1 при провале чтения.
		uint8_t			getID			(void			){ return valID;	}	//	Определяем функцию получения текущего ID (адрес модуля на шине).		Параметры функции: нет. Функция возвращает текущий ID модуля датчиков, или 0 если модуль не определён.
		uint8_t			getVersion		(void			){ return valVers;	}	//	Определяем функцию получения текущей версии прошивки модуля датчиков.	Параметры функции: нет. Функция возвращает версию прошивки модуля датчиков, или 0 если модуль не определён.
		float			getPWR			(void			);						//	Объявляем  функцию получения напряжения питания.						Параметры функции: нет. Функция возвращает напряжение питания в Вольтах, или -1 при провале чтения.
		bool			setIDLED		(bool on		);						//	Объявляем  функцию смены состояния светодиода обнаружения устройства.	Параметры функции: состояние светодиода true/false. Функция возвращает результат изменения состояния: true-успех / false-провал.
		int32_t			getErr			(void			);						//	Объявляем  функцию получения флагов ошибок из регистра диагностики.		Параметры функции: нет. Функция возвращает значение регистра диагностики, каждый из 16 бит которого является флагом ошибки, или -1 при провале чтения.
		int8_t			checkSensor		(uint8_t sens	);						//	Объявляем  функцию проверки датчика модуля.								Параметры функции: SENSOR_ALL/SHT/LTR. Функция возвращает ERROR_(SHT/LTR)_INIT, ERROR_(SHT/LTR)_DATA, 0 если ошибок нет, или -1 при провале чтения.
		float			getTEM			(void			);						//	Объявляем  функцию получения температуры.								Параметры функции: нет. Функция возвращает температуру в °С со знаком ( -40,0...+125,0°C ), или -100 при провале чтения.
		float			getHUM			(void			);						//	Объявляем  функцию получения относительной влажности.					Параметры функции: нет. Функция возвращает влажность в % ( 0,0...100,0% ), или -1 при провале чтения.
		float			getHUMA			(void			);						//	Объявляем  функцию получения абсолютной влажности.						Параметры функции: нет. Функция возвращает влажность в г/м3 ( 0,00...655,35г/м3 ), или -1 при провале чтения.
		float			getLUX			(void			);						//	Объявляем  функцию получения освещённости.								Параметры функции: нет. Функция возвращает освещённость в люксах ( 0...65535лк ), или -1 при провале чтения.
		bool			setPeriod		(uint8_t sens, float sec);				//	Объявляем  функцию смены периода опроса датчика.						Параметры функции: SENSOR_ALL/SHT/LTR, период опроса в секундах ( 0,1...6553,5с ). Функция возвращает результат изменения периода опроса: true-успех / false-провал.
		float			getPeriod		(uint8_t sens			);				//	Объявляем  функцию получения периода опроса датчика.					Параметры функции: SENSOR_SHT/LTR. Функция возвращает период опроса в секундах ( 0,1...6553,5с ), или -1 при провале чтения.
																				//	
	private:																	//	
	/**	Внутренние переменные **/												//
		ModbusClient*	objModbus;												//	Объявляем  указатель на объект работы по протоколу Modbus.				Указатель получит адрес объекта в конструкторе класса.
		uint8_t			valID			= 0;									//	Определяем переменную для хранения ID модуля который был проверен.
		uint8_t			valVers			= 0;									//	Определяем переменную для хранения версии прошивки модуля.
};

#endif