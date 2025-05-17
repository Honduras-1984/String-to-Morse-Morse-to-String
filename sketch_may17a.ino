int audio8 = 8;              // Зуммер
int buttonPin = 7;           // Кнопка
int note = 1200;             // Частота зуммера
int dotLen = 200;            // Длительность точки
int dashLen = dotLen * 3;    // Длительность тире

char inChar = 0;
char inData[100] = "";
String variable = "";
unsigned long lastPressTime = 0;
unsigned long pressStart = 0;
bool isPressed = false;
String morseInput = "";
unsigned long letterTimeout = 2000;  // Время между буквами (для кнопки)

// ==== Настройка ====
void setup() {
  pinMode(audio8, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Кнопка с подтяжкой
  Serial.begin(9600);
  Serial.println("=== Morse Code Ready ===");
  Serial.println("1. Введите текст в Serial Monitor");
  Serial.println("2. Или введите букву через кнопку:");
  Serial.println("   Короткое нажатие = . (точка), долгое >500мс = - (тире)");
}

// ==== Основной цикл ====
void loop() {
  readSerialToMorse();      // Воспроизводит текст в Морзе
  handleButtonInput();      // Обрабатывает ввод через кнопку
}

// ===== Функции =====

// 1. Преобразование строки из Serial и воспроизведение Морзе
void readSerialToMorse() {
  int index1 = 0;

  if ( Serial.available() > 0 ) {
    while (Serial.available() > 0 && index1 < 100) {
      delay(10);  // небольшая задержка для устойчивости
      inChar = Serial.read();
      inData[index1] = inChar;
      index1++;
      inData[index1] = '\0'; // null-terminator
    }

    variable = "";
    for (byte i = 0; i < 100; i++) {
      variable.concat(String(inData[i]));
    }
    variable.toLowerCase(); // приводим к нижнему регистру

    Serial.print("Ввод: ");
    Serial.println(variable);

    for (int i = 0; i < variable.length(); i++) {
      char tmpChar = variable[i];
      GetChar(tmpChar);
    }
  }
}

// 2. Обработка ввода с кнопки и декодирование
void handleButtonInput() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && !isPressed) {
    pressStart = millis();
    isPressed = true;
    delay(10); // debounce
  }

  if (buttonState == HIGH && isPressed) {
    unsigned long pressDuration = millis() - pressStart;
    isPressed = false;

    if (pressDuration < 500) {
      morseInput += ".";
      Serial.print(".");
      tone(audio8, note, dotLen);
    } else {
      morseInput += "-";
      Serial.print("-");
      tone(audio8, note, dashLen);
    }

    lastPressTime = millis();
  }

  if (morseInput.length() > 0 && millis() - lastPressTime > letterTimeout) {
    char decoded = decodeMorse(morseInput);
    Serial.print(" -> ");
    Serial.println(decoded);
    morseInput = "";
  }
}

// 3. Декодирование Морзе-кода в символ
char decodeMorse(String code) {
  if (code == ".-") return 'A';
  if (code == "-...") return 'B';
  if (code == "-.-.") return 'C';
  if (code == "-..") return 'D';
  if (code == ".") return 'E';
  if (code == "..-.") return 'F';
  if (code == "--.") return 'G';
  if (code == "....") return 'H';
  if (code == "..") return 'I';
  if (code == ".---") return 'J';
  if (code == "-.-") return 'K';
  if (code == ".-..") return 'L';
  if (code == "--") return 'M';
  if (code == "-.") return 'N';
  if (code == "---") return 'O';
  if (code == ".--.") return 'P';
  if (code == "--.-") return 'Q';
  if (code == ".-.") return 'R';
  if (code == "...") return 'S';
  if (code == "-") return 'T';
  if (code == "..-") return 'U';
  if (code == "...-") return 'V';
  if (code == ".--") return 'W';
  if (code == "-..-") return 'X';
  if (code == "-.--") return 'Y';
  if (code == "--..") return 'Z';
  return '?';
}

// 4. Генерация звука Морзе
void MorseDot() {
  tone(audio8, note, dotLen);
  delay(dotLen);
}

void MorseDash() {
  tone(audio8, note, dashLen);
  delay(dashLen);
}

// 5. Преобразование символа в Морзе и воспроизведение
void GetChar(char tmpChar) {
  switch (tmpChar) {
    case 'a': MorseDot(); delay(100); MorseDash(); break;
    case 'b': MorseDash(); delay(100); MorseDot(); delay(100); MorseDot(); delay(100); MorseDot(); break;
    case 'c': MorseDash(); delay(100); MorseDot(); delay(100); MorseDash(); delay(100); MorseDot(); break;
    case 'd': MorseDash(); delay(100); MorseDot(); delay(100); MorseDot(); break;
    case 'e': MorseDot(); break;
    case 'f': MorseDot(); delay(100); MorseDot(); delay(100); MorseDash(); delay(100); MorseDot(); break;
    case 'g': MorseDash(); delay(100); MorseDash(); delay(100); MorseDot(); break;
    case 'h': MorseDot(); delay(100); MorseDot(); delay(100); MorseDot(); delay(100); MorseDot(); break;
    case 'i': MorseDot(); delay(100); MorseDot(); break;
    case 'j': MorseDot(); delay(100); MorseDash(); delay(100); MorseDash(); delay(100); MorseDash(); break;
    case 'k': MorseDash(); delay(100); MorseDot(); delay(100); MorseDash(); break;
    case 'l': MorseDot(); delay(100); MorseDash(); delay(100); MorseDot(); delay(100); MorseDot(); break;
    case 'm': MorseDash(); delay(100); MorseDash(); break;
    case 'n': MorseDash(); delay(100); MorseDot(); break;
    case 'o': MorseDash(); delay(100); MorseDash(); delay(100); MorseDash(); break;
    case 'p': MorseDot(); delay(100); MorseDash(); delay(100); MorseDash(); delay(100); MorseDot(); break;
    case 'q': MorseDash(); delay(100); MorseDash(); delay(100); MorseDot(); delay(100); MorseDash(); break;
    case 'r': MorseDot(); delay(100); MorseDash(); delay(100); MorseDot(); break;
    case 's': MorseDot(); delay(100); MorseDot(); delay(100); MorseDot(); break;
    case 't': MorseDash(); break;
    case 'u': MorseDot(); delay(100); MorseDot(); delay(100); MorseDash(); break;
    case 'v': MorseDot(); delay(100); MorseDot(); delay(100); MorseDot(); delay(100); MorseDash(); break;
    case 'w': MorseDot(); delay(100); MorseDash(); delay(100); MorseDash(); break;
    case 'x': MorseDash(); delay(100); MorseDot(); delay(100); MorseDot(); delay(100); MorseDash(); break;
    case 'y': MorseDash(); delay(100); MorseDot(); delay(100); MorseDash(); delay(100); MorseDash(); break;
    case 'z': MorseDash(); delay(100); MorseDash(); delay(100); MorseDot(); delay(100); MorseDot(); break;
    default: break;
  }
  delay(300); // пауза между буквами
}
