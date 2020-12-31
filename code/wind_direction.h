// Imports
#include "esphome.h"

// Sensors PINs
#define PIN_POT 34 // Wind Direction Sensor - Potentiometer

// Constants Global variables
const unsigned float adc_per_degree = 4096. / 300.;
const unsigned int NSEW_delta = 30 * adc_per_degree;
const unsigned int NWNOSOSW_delta = 60 * adc_per_degree;
const unsigned long UPDATE_TIME = 30000; // Update time in milliseconds

class WindDirectionSensor : public PollingComponent, public TextSensor
{
public:
    WindDirectionSensor() : PollingComponent(UPDATE_TIME) {}

    void setup() override
    {
        pinMode(PIN_POT, INPUT);
    }

    void update() override
    {
        // ANENOMETER WIND DIRECTION
        int pot_reading = analogRead(PIN_POT);
        std::string direction = "??";
        ESP_LOGD("custom", "Pot reading: %d", pot_reading);
        if ((pot_reading < (1 * NSEW_delta) + (0 * NWNOSOSW_delta)) && (pot_reading > 0))
        {
            direction = "Norte";
        }
        else if (pot_reading < (1 * NSEW_delta) + (1 * NWNOSOSW_delta))
        {
            direction = "Nordeste";
        }
        else if (pot_reading < (2 * NSEW_delta) + (1 * NWNOSOSW_delta))
        {
            direction = "Leste";
        }
        else if (pot_reading < (2 * NSEW_delta) + (2 * NWNOSOSW_delta))
        {
            direction = "Suldeste";
        }
        else if (pot_reading < (3 * NSEW_delta) + (2 * NWNOSOSW_delta))
        {
            direction = "Sul";
        }
        else if (pot_reading < (3 * NSEW_delta) + (3 * NWNOSOSW_delta))
        {
            direction = "Sudoeste";
        }
        else if (pot_reading < (4 * NSEW_delta) + (3 * NWNOSOSW_delta))
        {
            direction = "Oeste";
        }
        else
        {
            direction = "Noroeste";
        }
        publish_state(direction);
    }
};
