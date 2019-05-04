#include <ask_ssd1306.h>

ask_ssd1306 askOled;

void setup() {
	Serial.begin(115200);
	// инициализируем дисплей
	askOled.begin();
	if (askOled.displayActivated()) {}
	delay(1000);
	// заполним экран
	askOled.fill();
	delay(1000);
	// очистим экран
	askOled.clear();
	delay(1000);

	
	askOled.print(" !\"#$%&'()*+,-./", 0, 0, 1);
	askOled.print("0123456789:;<=>?@", 0, 1, 1);
	askOled.print("abcdefghijklmnopq", 0, 2, 1);
	askOled.print("rstuvwxyz{|}~", 0, 3, 1);
	askOled.print("ABCDEFGHIJKLMNOPQ", 0, 4, 1);
	askOled.print("RSTUVWXYZ[\\]^_`", 0, 5, 1);
	delay(5000);
	askOled.clear();

	askOled.print("АБВГДЕЁЖЗИЙКЛМНО", 0, 0, 1);
	askOled.print("ПРСТУФХЦЧШЩЪЫЬЭЮЯ", 0, 1, 1);
	askOled.print("абвгдеёжзийклмно", 0, 3, 1);
	askOled.print("прстуфхцчшщъыьэюя", 0, 4, 1);
	delay(5000);
	askOled.clear();
	

	askOled.print(" !\"#$%&'", 0, 0, 3);
	askOled.print("()*+,-./", 0, 2, 3);
	askOled.print("89:;<=>?@A", 0, 4, 3);
	askOled.print("B", 0, 5, 3);
	delay(5000);
}

void loop() {
	delay(1000);
}