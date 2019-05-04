/*********************************************************************
Библиотека дла работы с OLED дисплеем на чипсете SSD1306
ВерсиЯ 1.00

Функции библиотеки
	setUp();	- задать установки дисплея
	begin();	- инициализация дисплея
	clear();	- очистка дисплея
	fill();		- заливка дисплея

	вывод строки aStr на дисплей в позицию aCol,aRow шрифтом aFont
	print(const char* aStr, const uint8_t aCol, const uint8_t aRow, const uint8_t aFont, const bool aInverse = false);

Все мои проекты собраны здесь
http://xn--b1adda5bp2i.xn--g1achdice.xn--p1ai/avtomatizatsiya
*********************************************************************/

#include "ask_ssd1306.h"
#include <Wire.h>

// -====================      ИНИЦИАЛИЗАЦИЯ КЛАССА      ====================-//

ask_ssd1306::ask_ssd1306() {
}

// -====================          РАЗДЕЛ PRIVATE        ====================-//

void ask_ssd1306::writeCommand(uint8_t aCommand) {
	Wire.beginTransmission(I2C_ADDR_SSD);

	Wire.write(0x00);
	Wire.write(aCommand);
	Wire.endTransmission();
} // ask_ssd1306::writeCommand(uint8_t aCommand)
void ask_ssd1306::writeData(uint8_t aData) {
	Wire.beginTransmission(I2C_ADDR_SSD);

	Wire.write(0x40);
	Wire.write(aData);
	Wire.endTransmission();
} // ask_ssd1306::writeData(uint8_t aData)

void ask_ssd1306::setCursor(const uint8_t aCol, const uint8_t aRow) {

	writeCommand(0xB0 + aRow);

	uint8_t lCol = aCol + H_OFFSET;

	writeCommand(lCol & 0xf);

	writeCommand(0x10 | (lCol >> 4));
} // setCursor(const uint8_t aCol, const uint8_t aRow)

// -====================          КОНЕЦ PRIVATE         ====================-//

// -====================          РАЗДЕЛ PUBLIC         ====================-//

void ask_ssd1306::setUp() {
	writeCommand(0xAE);
	writeCommand(0x81);
	writeCommand(0x8F);
	writeCommand(0xA4);
	writeCommand(0xA6);
	writeCommand(0x20);
	writeCommand(0x02);
	writeCommand(0x40);
	writeCommand(0xA1);
	writeCommand(0xC8);
	writeCommand(0xA8);
	writeCommand(0x3F);
	writeCommand(0xD3);
	writeCommand(0x00);
	writeCommand(0xDA);
	writeCommand(0x12);
	writeCommand(0xD5);
	writeCommand(0x80);
	writeCommand(0xD9);
	writeCommand(0x22);
	writeCommand(0xDB);
	writeCommand(0x20);
	writeCommand(0x8D);
	writeCommand(0x14);
	writeCommand(0xAF);
}// ask_ssd1306::setUp()

void ask_ssd1306::begin() {
	mDisplayActivated = true;
	Wire.begin();
	Wire.beginTransmission(I2C_ADDR_SSD);
	if (Wire.endTransmission() != 0) {
		mDisplayActivated = false;
		return;
	}

	setUp();

} //ask_ssd1306::begin()

bool ask_ssd1306::displayActivated() {
	return mDisplayActivated;
} // ask_ssd1306::displayActivated() {

void ask_ssd1306::clear(uint8_t aStrStart, uint8_t aStrEnd) {

	if (aStrStart > 8) { aStrStart = 8; }
	if (aStrEnd > 8) { aStrEnd = 8; }

	for (byte i = aStrStart; i < aStrEnd; i++) {

		writeCommand(0xB0 + i);

		writeCommand(0x00 + H_OFFSET);
		writeCommand(0x10);     

		for (byte j = 0; j < 8; j++) {

			Wire.beginTransmission(I2C_ADDR_SSD);
			Wire.write(0x40); 
			for (byte k = 0; k < 16; k++) {

				Wire.write(0);
			}
			Wire.endTransmission();
		}
	}
} // ask_ssd1306::clear()

void ask_ssd1306::fill() {

	for (byte i = 0; i < 8; i++) {
		writeCommand(0xB0 + i);
		writeCommand(0x00 + H_OFFSET);	//младший адрес 0x00
		writeCommand(0x10);     		//старший адрес 0x10

		for (byte j = 0; j < 8; j++) {
			Wire.beginTransmission(I2C_ADDR_SSD);
			Wire.write(0x40); 
			for (byte k = 0; k < 16; k++) {
				Wire.write(255);
			}
			Wire.endTransmission();
		}
	}
}  // ask_ssd1306::fill()

void ask_ssd1306::print(const char* aStr, const uint8_t aCol, const uint8_t aRow, const uint8_t aFont, const bool aInverse) {
	uint8_t lCol = aCol;
	uint8_t lCharWidth = 0;
	uint8_t lCharHeight = 0;
	uint16_t lCharPos = 0;
	uint8_t lCharCode = 0;

	uint8_t lFontData = 0;

	const uint8_t *lFontArray = nullptr;
	const uint16_t *lFontPos = nullptr;

	if (aFont == 1) {
		lFontArray = &font8[0];
		lFontPos = &font8Pos[0][0];
	}
	else if (aFont == 2) {
		lFontArray = &font16[0];
		lFontPos = &font16Pos[0][0];
	}
	else if (aFont == 3) {
		lFontArray = &font16s[0];
		lFontPos = &font16sPos[0][0];
	}
	for (uint8_t lStrPos = 0; lStrPos <= strlen(aStr) - 1; lStrPos++) {

		lCharCode = aStr[lStrPos];
		if (lCharCode == 208) {
			lStrPos++;
			lCharCode = aStr[lStrPos];
			lCharCode = lCharCode - 34;
		}
		else if (lCharCode == 209) {
			lStrPos++;
			lCharCode = aStr[lStrPos];
			lCharCode = lCharCode + 30;
		}
		else {
			lCharCode = lCharCode - 32;
		}

		lCharWidth = pgm_read_byte(&lFontPos[lCharCode * 3]);
		lCharHeight = ((pgm_read_byte(&lFontPos[lCharCode * 3 + 1]) - 1) / 8);
		lCharPos = pgm_read_word(&lFontPos[lCharCode * 3 + 2]);

		if (lCol + lCharWidth > 127) {
			return;
		}
		for (uint8_t h = 0; h <= lCharHeight; h++) {

			setCursor(lCol, aRow + h);
			for (uint8_t w = 0; w < (lCharWidth); w++) {
				lFontData = pgm_read_byte(&lFontArray[lCharPos]);
				if (aInverse) {
					writeData(~lFontData);
				}
				else {
					writeData(lFontData);
				}
				lCharPos++;
			}

			if (aInverse) {
				writeData(255);
			}
			else {
				writeData(0);
			}
		}

		lCol = lCol + lCharWidth + 1;
		if (aFont == 3){
			lCol++;
		}
	}
} // ask_ssd1306::print(const char* aStr, const uint8_t aCol, const uint8_t aRow, const uint8_t aFont, const bool aInverse);

void ask_ssd1306::logo() {
	uint16_t lLogoSize = logoSize;
	uint16_t lLogoPos = 0;
	for (byte i = 0; i < 8; i++) {

		writeCommand(0xB0 + i);

		writeCommand(0x00 + H_OFFSET);	//младший адрес 0x00
		writeCommand(0x10);     		//старший адрес 0x10

		for (byte j = 0; j < 8; j++) {
			Wire.beginTransmission(I2C_ADDR_SSD);
			Wire.write(0x40); 
			for (byte k = 0; k < 16; k++) {

				Wire.write(pgm_read_byte(&logoData[lLogoPos]));
				if (lLogoPos >= lLogoSize) {
					return;
				}
				lLogoPos++;
			}
			Wire.endTransmission();
		}
	}
}// ask_ssd1306::logo() 
 
void ask_ssd1306::sleep() {
	writeCommand(0xAE);
}// void ask_ssd1306::sleep()
 
void ask_ssd1306::wakeUp() {
	writeCommand(0xAF);
}// void ask_ssd1306::wakeUp()
 
