// This #include statement was automatically added by the Spark IDE.
#include "LiquidCrystal/LiquidCrystal.h"

LiquidCrystal lcd(D0, D1, D2, D3, D4, D5);

int backlight = A7;

// called once on startup
void setup() {
    // For simplicity, we'll format our weather data as text, and pipe it to serial.
    // but you could just as easily display it in a webpage or pass the data to another system.

    // Learn more about the serial commands here http://docs.particle.io/firmware/#communication-serial
    // You can also watch what's sent over serial with the particle cli with
    //  spark serial monitor
    //Serial.begin(115200);

    lcd.begin(16,2);
    //lcd.print("Namaste");
    pinMode(backlight,OUTPUT);
    digitalWrite(backlight,LOW);


    // Lets listen for the hook response
    Spark.subscribe("hook-response/get_weather", gotWeatherData, MY_DEVICES);
    Spark.subscribe("hook-response/get_sf_weather", gotSFWeatherData, MY_DEVICES);

    // Lets give ourselves 10 seconds before we actually start the program.
    // That will just give us a chance to open the serial monitor before the program sends the request
    for(int i=0;i<10;i++) {
        //Serial.println("waiting " + String(10-i) + " seconds before we publish");
        delay(1000);
    }
}


// called forever really fast
void loop() {

    // Let's request the weather, but no more than once every 60 seconds.
    //Serial.println("Requesting Weather!");

    // publish the event that will trigger our webhook
    Spark.publish("get_weather");
    delay(5000);
    Spark.publish("get_sf_weather");
    delay(5000);
}

// This function will get called when weather data comes in
void gotSFWeatherData(const char *name, const char *data) {
    // Important note!  -- Right now the response comes in 512 byte chunks.
    //  This code assumes we're getting the response in large chunks, and this
    //  assumption breaks down if a line happens to be split across response chunks.
    //
    // Sample data:
    //  <location>Minneapolis, Minneapolis-St. Paul International Airport, MN</location>
    //  <weather>Overcast</weather>
    //  <temperature_string>26.0 F (-3.3 C)</temperature_string>
    //  <temp_f>26.0</temp_f>


    String str = String(data);
    String locationStr = tryExtractString(str, "<location>", "</location>");
    String weatherStr = tryExtractString(str, "<weather>", "</weather>");
    String tempStr = tryExtractString(str, "<temp_f>", "</temp_f>");
    String windStr = tryExtractString(str, "<wind_string>", "</wind_string>");

    if (locationStr != NULL) {
        //Serial.println("At location: " + locationStr);
        

    }

    if (weatherStr != NULL) {
        //Serial.println("The weather is: " + weatherStr);
    }

    if (tempStr != NULL) {
        //Serial.println("The temp is: " + tempStr + String(" *F"));
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("San Francisco");
        
        lcd.setCursor(0, 1);
        lcd.print("Temp: ");
        lcd.print(tempStr);
        lcd.print(" *F");
        digitalWrite(backlight,HIGH);
        delay(500);
        digitalWrite(backlight,LOW);

    }

    if (windStr != NULL) {
        //Serial.println("The wind is: " + windStr);
    }
}

// This function will get called when weather data comes in
void gotWeatherData(const char *name, const char *data) {
    // Important note!  -- Right now the response comes in 512 byte chunks.
    //  This code assumes we're getting the response in large chunks, and this
    //  assumption breaks down if a line happens to be split across response chunks.
    //
    // Sample data:
    //  <location>Minneapolis, Minneapolis-St. Paul International Airport, MN</location>
    //  <weather>Overcast</weather>
    //  <temperature_string>26.0 F (-3.3 C)</temperature_string>
    //  <temp_f>26.0</temp_f>


    String str = String(data);
    String locationStr = tryExtractString(str, "<location>", "</location>");
    String weatherStr = tryExtractString(str, "<weather>", "</weather>");
    String tempStr = tryExtractString(str, "<temp_f>", "</temp_f>");
    String windStr = tryExtractString(str, "<wind_string>", "</wind_string>");

    if (locationStr != NULL) {
        //Serial.println("At location: " + locationStr);
        
    }

    if (weatherStr != NULL) {
        //Serial.println("The weather is: " + weatherStr);
    }

    if (tempStr != NULL) {
        //Serial.println("The temp is: " + tempStr + String(" *F"));
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Minneapolis");
        
        lcd.setCursor(0, 1);
        lcd.print("Temp: ");
        lcd.print(tempStr);
        lcd.print(" *F");
        digitalWrite(backlight,HIGH);
        delay(500);
        digitalWrite(backlight,LOW);

    }

    if (windStr != NULL) {
        //Serial.println("The wind is: " + windStr);
    }
}

// Returns any text found between a start and end string inside 'str'
// example: startfooend  -> returns foo
String tryExtractString(String str, const char* start, const char* end) {
    if (str == NULL) {
        return NULL;
    }

    int idx = str.indexOf(start);
    if (idx < 0) {
        return NULL;
    }

    int endIdx = str.indexOf(end);
    if (endIdx < 0) {
        return NULL;
    }

    return str.substring(idx + strlen(start), endIdx);
}
