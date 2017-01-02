/*
  Author: Seytonic
          https://twitter.com/seytonic
          https://www.youtube.com/seytonic
  GIT:
          https://github.com/Seytonic/Duckduino-microSD
*/


#include <SD.h>


boolean first = true;
int defaultdelay = 0;

void setup() {
  if (!SD.begin(BUILTIN_SDCARD)) {
    return;
  }
  File myFile = SD.open("script.txt");
  if (myFile) {
    Keyboard.begin();
    String line = "";
    while (myFile.available()) {
      char m = myFile.read();
      if (m == '\n') {
        Line(line);
        delay(defaultdelay);
        line = "";
      }
      else if ((int) m != 13) {
        line += m;
      }
    }
    Line(line);
    myFile.close();
  }
  Keyboard.end();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void Line(String l) {
  int space_1 = l.indexOf(" ");
  String current = l.substring(0, space_1);
  String prev;
  if (first) {
    first = false;
    if (current == "DEFAULT_DELAY" || current == "DEFAULTDELAY") {
      defaultdelay = l.substring(space_1 + 1).toInt();
      return;
    }
  }
  if (space_1 == -1) {
    Press(l);
  }
  else if (current == "STRING") {
    Keyboard.print(l.substring(space_1 + 1));
  }
  else if (current == "DELAY") {
    int delaytime = l.substring(space_1 + 1).toInt();
    delay(delaytime);
  }
  else if (current == "REM");
  else if (current == "REPLAY") {
    int repeatcounter = l.substring(space_1 + 1).toInt();
    for (int i = 0; i <= repeatcounter; i++) {
      Line(prev);
    }
  }
  else {
    String remain = l;
    while (remain.length() > 0) {
      int latest_space = remain.indexOf(" ");
      if (latest_space == -1) {
        Press(remain);
        remain = "";
      }
      else {
        Press(remain.substring(0, latest_space));
        remain = remain.substring(latest_space + 1);
      }
      delay(5);
    }
  }
  Keyboard.releaseAll();
}
void Press(String b) {
  Press(b, "");
}

void Press(String b, String prev) {
  if (b.length() == 1) {
    char c = b[0];
    Keyboard.press(c);
  }
  else if (b.equals("DRIVERDELAY")) {
    while ((int(keyboard_leds) & 2) != 2) {
      Keyboard.press(KEY_CAPS_LOCK);
      delay(10);
      Keyboard.releaseAll();
    }
    if ((int(keyboard_leds) & 2) == 2) {
      Keyboard.press(KEY_CAPS_LOCK);
      delay(10);
      Keyboard.releaseAll();
    }
  }
  else if (b.equals("ENTER")) {
    Keyboard.press(KEY_RETURN);
  }
  else if (b.equals("CTRL") || b.equals("CONTROL")) {
    Keyboard.press(KEY_LEFT_CTRL);
  }
  else if (b.equals("SHIFT")) {
    Keyboard.press(KEY_LEFT_SHIFT);
  }
  else if (b.equals("ALT")) {
    Keyboard.press(KEY_LEFT_ALT);
  }
  else if (b.equals("GUI") || b.equals("WINDOWS")) {
    Keyboard.press(KEY_LEFT_GUI);
  }
  else if (b.equals("UP") || b.equals("UPARROW")) {
    Keyboard.press(KEY_UP_ARROW);
  }
  else if (b.equals("DOWN") || b.equals("DOWNARROW")) {
    Keyboard.press(KEY_DOWN_ARROW);
  }
  else if (b.equals("LEFT") || b.equals("LEFTARROW")) {
    Keyboard.press(KEY_LEFT_ARROW);
  }
  else if (b.equals("RIGHT") || b.equals("RIGHTARROW")) {
    Keyboard.press(KEY_RIGHT_ARROW);
  }
  else if (b.equals("DELETE")) {
    Keyboard.press(KEY_DELETE);
  }
  else if (b.equals("PAGEUP")) {
    Keyboard.press(KEY_PAGE_UP);
  }
  else if (b.equals("PAGEDOWN")) {
    Keyboard.press(KEY_PAGE_DOWN);
  }
  else if (b.equals("HOME")) {
    Keyboard.press(KEY_HOME);
  }
  else if (b.equals("ESC") || b.equals("ESCAPE")) {
    Keyboard.press(KEY_ESC);
  }
  else if (b.equals("INSERT")) {
    Keyboard.press(KEY_INSERT);
  }
  else if (b.equals("TAB")) {
    Keyboard.press(KEY_TAB);
  }
  else if (b.equals("END")) {
    Keyboard.press(KEY_END);
  }
  else if (b.equals("CAPSLOCK")) {
    Keyboard.press(KEY_CAPS_LOCK);
  }
  else if (b.equals("F1")) {
    Keyboard.press(KEY_F1);
  }
  else if (b.equals("F2")) {
    Keyboard.press(KEY_F2);
  }
  else if (b.equals("F3")) {
    Keyboard.press(KEY_F3);
  }
  else if (b.equals("F4")) {
    Keyboard.press(KEY_F4);
  }
  else if (b.equals("F5")) {
    Keyboard.press(KEY_F5);
  }
  else if (b.equals("F6")) {
    Keyboard.press(KEY_F6);
  }
  else if (b.equals("F7")) {
    Keyboard.press(KEY_F7);
  }
  else if (b.equals("F8")) {
    Keyboard.press(KEY_F8);
  }
  else if (b.equals("F9")) {
    Keyboard.press(KEY_F9);
  }
  else if (b.equals("F10")) {
    Keyboard.press(KEY_F10);
  }
  else if (b.equals("F11")) {
    Keyboard.press(KEY_F11);
  }
  else if (b.equals("F12")) {
    Keyboard.press(KEY_F12);
  }
  else if (b.equals("NUMLOCK")) {
    Keyboard.press(KEY_NUM_LOCK);
  }
  else if (b.equals("PRINTSCREEN")) {
    Keyboard.press(KEY_PRINTSCREEN);
  }
  else if (b.equals("SCROLLLOCK")) {
    Keyboard.press(KEY_SCROLL_LOCK);
  }
  else if (b.equals("PAUSE") || b.equals("BREAK")) {
    Keyboard.press(KEY_PAUSE);
  }
  else if (b.equals("MENU") || b.equals("APP")) {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_F10);
  }
  else if (b.equals("CTRL-ALT")) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
  }
  else if (b.equals("CTRL-SHIFT")) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
  }
  else if (b.equals("SPACE")) {
    Keyboard.press(' ');
  }
  else {
    Serial.begin(9600);
    Serial.println("unrecognised command \"" + b + "\"");
  }
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
}

