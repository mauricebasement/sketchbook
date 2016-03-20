//
//    FILE: dht22_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.03
// PURPOSE: DHT library test sketch for DHT22 && Arduino
//     URL:
// HISTORY:
// 0.1.03 extended stats for all errors
// 0.1.02 added counters for error-regression testing.
// 0.1.01
// 0.1.00 initial version
//
// Released to the public domain
//

#include <dht.h>

dht DHT;

#define DHT22_PIN 5

void setup()
{
    Serial.begin(9600);
    Serial.println("GrowControl");
}

void loop()
{
    // READ DATA
    Serial.print("DHT22, \t");

    DHT.read22(DHT22_PIN);


    // DISPLAY DATA
    Serial.print(DHT.humidity, 1);
    Serial.print("\t");
    Serial.println(DHT.temperature, 1);

    delay(2000);
}
//
// END OF FILE
//
