/*********************************************************************
Библиотека дла работы с OLED дисплеем на чипсете SSD1306
ВерсиЯ 1.00

Функции библиотеки
	setUp();			- задать установки дисплея
	begin();			- инициализация дисплея
	displayActivated();	- возвращает статус модуля, активирован или нет
	clear();			- очистка дисплея
	fill();				- заливка дисплея
	
	вывод строки aStr на дисплей в позицию aCol,aRow шрифтом aFont
	print(const char* aStr, const uint8_t aCol, const uint8_t aRow, const uint8_t aFont, const bool aInverse = false); 

Все мои проекты собраны здесь
http://xn--b1adda5bp2i.xn--g1achdice.xn--p1ai/avtomatizatsiya
*********************************************************************/

#ifndef ask_ssd1306_h
#define ask_ssd1306_h

#include "Arduino.h"
#include <Wire.h>

//# подключим шрифты
#include "font8.h"		//# символы 8 пикселов высотой, буквы только заглавные
//#include "font16d.h"	//# цифры и символы 16 пикселов высотой
#include "font16.h"		//# символы 16 пикселов высотой, буквы только заглавные
#include "fontSym.h"	//# специальные символы
#include "logo.h"		//# логотип

//# I2C адрес дисплея
#define I2C_ADDR_SSD   0x3C
//# некоторым дисплеям необходимо сдвигать начальный адрес строки на 2 символа
#define H_OFFSET   0x2

class ask_ssd1306 {
public:							//# функции доступные для вызова 
	ask_ssd1306();				//# действия при инициализации класса
	void setUp();				//# задать установки дисплея
	void begin();				//# инициализация дисплея
	bool displayActivated();	//# возвращает статус модуля, активирован или нет
	void clear(uint8_t aStrStart = 0, uint8_t aStrEnd = 8);				//# очистка дисплея
	void fill();				//# заливка дисплея
	//# вывод строки aStr на дисплей в позицию aCol,aRow шрифтом aFont
	void print(const char* aStr, const uint8_t aCol, const uint8_t aRow, const uint8_t aFont, const bool aInverse = false); 
	void logo();				//# выводим на дисплей логотип
	void sleep();				//# выключаем дисплей
	void wakeUp();				//# включаем дисплей

private:                            // переменные и функции не доступные вызова вне библиотеки
	bool mDisplayActivated;									//# признак активности модуля
	void writeCommand(uint8_t aCommand);					//# передаем команду дисплею
	void writeData(uint8_t aData);							//# передаем данные дисплею
	void setCursor(const uint8_t aCol, const uint8_t aRow);	//# установка курсора в позицию col, row
	
};
#endif // ask_ssd1306_h

