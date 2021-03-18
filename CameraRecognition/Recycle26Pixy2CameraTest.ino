
// Recycle Project FG26 --- 28th Feb
// https://docs.pixycam.com/wiki/doku.php?id=wiki:v2:hooking_up_pixy_to_a_microcontroller_-28like_an_arduino-29
//

#include <Pixy2.h>
#include <Servo.h>
#include "HX711.h"

//---------
int pin = 6;
Servo mySer;
float plasticWeight = 0;
int points = 0;
//float consWeight = 0;

//---------
HX711 scale(6, 5);
//---------

// This is the main Pixy object
Pixy2 pixy;

void setup()
{
    Serial.begin(115200);
    Serial.print("Starting...\n");
    //----------
    mySer.attach(pin);
    //----------

    Serial.println("Initializing the scale");

    Serial.println("Before setting up the scale:");
    Serial.print("read: \t\t");
    Serial.println(scale.read()); // print a raw reading from the ADC

    Serial.print("read average: \t\t");
    Serial.println(scale.read_average(20)); // print the average of 20 readings from the ADC

    Serial.print("get value: \t\t");
    Serial.println(scale.get_value(5)); // print the average of 5 readings from the ADC minus the tare weight (not set yet)

    Serial.print("get units: \t\t");
    Serial.println(scale.get_units(5), 1); // print the average of 5 readings from the ADC minus tare weight (not set) divided
    // by the SCALE parameter (not set yet)

    scale.set_scale(2280.f); // this value is obtained by calibrating the scale with known weights; see the README for details
    scale.tare();            // reset the scale to 0

    Serial.println("After setting up the scale:");

    Serial.print("read: \t\t");
    Serial.println(scale.read()); // print a raw reading from the ADC

    Serial.print("read average: \t\t");
    Serial.println(scale.read_average(20)); // print the average of 20 readings from the ADC

    Serial.print("get value: \t\t");
    Serial.println(scale.get_value(5)); // print the average of 5 readings from the ADC minus the tare weight, set with tare()

    Serial.print("get units: \t\t");
    Serial.println(scale.get_units(5), 1); // print the average of 5 readings from the ADC minus tare weight, divided
    // by the SCALE parameter set with set_scale

    Serial.println("Readings:");

    //-----------

    pixy.init();
}

void loop()
{
    int i;
    // grab blocks from camera!
    pixy.ccc.getBlocks();

    // If there are detect blocks, print them!
    if (pixy.ccc.numBlocks)
    {
        Serial.print("Detected");
        Serial.println(pixy.ccc.numBlocks);

        for (i = 0; i < pixy.ccc.numBlocks; i++)
        {
            if (pixy.ccc.blocks[i].m_signature == 1 || pixy.ccc.blocks[i].m_signature == 2 || pixy.ccc.blocks[i].m_signature == 3)
            {
                Serial.print("Plastic Detected");
                Serial.println("");
                mySer.write(180);
                delay(1000);
                mySer.write(90);
            }
            else if (pixy.ccc.blocks[i].m_signature == 4 || pixy.ccc.blocks[i].m_signature == 5 || pixy.ccc.blocks[i].m_signature == 6)
            {
                Serial.print("Cons Detected");
                Serial.println("");
                mySer.write(0);
                delay(1000);
                mySer.write(90);
            }
        }
    }

    if (Serial.available() > 1)
    {
        calculateWeight(); // end of recogination and start calculate the weight
    }

    delay(500);
}

void calculateWeight()
{
    // testing only on one basket
    Serial.print("\t| average:\t");
    Serial.println(scale.get_units(5), 2);
    plasticWeight = scale.get_units(10), 1;

    Serial.print(plasticWeight);

    // calcualte points later .........


    scale.power_down(); // put the ADC in sleep mode
    delay(1000);
    scale.power_up();
}