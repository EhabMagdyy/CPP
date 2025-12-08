#include <iostream>
#include <memory>
#include <fstream>
#include <unistd.h>
#include <wiringPi.h>

constexpr uint32_t SLEEP_DURATION{2}; // 2 seconds
constexpr uint32_t LOGGING_INTERVAL{2}; // 2*SLEEP_DURATION = 2*2 = 4 seconds  (Small count for testing)

/* ----------------------------------------------------
        Shared Temperature + Humidity Data
---------------------------------------------------- */
struct SensorData {
    float temperature{0.0f};
    float humidity{0.0f};
};

/* ----------------------------------------------------
        DHT22 Sensor Class
---------------------------------------------------- */
class DHT22 {
private:
    int gpioPin;

public:
    explicit DHT22(int pin) : gpioPin(pin){
        wiringPiSetup();
    }
    ~DHT22() = default;

    bool read(float& humidity, float& temperature){
        uint8_t data[5] = {0};
        uint8_t last = HIGH;
        uint8_t counter = 0;

        pinMode(gpioPin, OUTPUT);
        digitalWrite(gpioPin, LOW);
        delay(18);
        digitalWrite(gpioPin, HIGH);
        delayMicroseconds(40);
        pinMode(gpioPin, INPUT);

        for(int i = 0; i < 85; i++){
            counter = 0;
            while(digitalRead(gpioPin) == last){
                counter++;
                delayMicroseconds(1);
                if (counter == 255) break;
            }
            last = digitalRead(gpioPin);

            if(counter == 255) break;

            if((i >= 4) && (i % 2 == 0)){
                data[(i - 4) / 16] <<= 1;

                if (counter > 50)
                    data[(i - 4) / 16] |= 1;
            }
        }

        // Checksum
        if((uint8_t)(data[0] + data[1] + data[2] + data[3]) != data[4]){
            return false;
        }

        humidity = ((data[0] << 8) + data[1]) * 0.1f;
        temperature = (((data[2] & 0x7F) << 8) + data[3]) * 0.1f;
        if(data[2] & 0x80) temperature = -temperature;

        return true;
    }
};

/* ----------------------------------------------------
   Display Class
---------------------------------------------------- */
class Display {
public:
    void show(std::weak_ptr<SensorData>& d) {
        if(auto sharedData = d.lock()) {
            std::cout << "Temp: " << sharedData->temperature << " °C, Humidity: " << sharedData->humidity << " %" << std::endl;
        }
    }
};

/* ----------------------------------------------------
   Logger Class
---------------------------------------------------- */
class Logger {
public:
    Logger() { logfile.open("sensor.log", std::ios::app); }

    void log(const std::weak_ptr<SensorData>& d) {
        if (auto sharedData = d.lock()) {
            logfile << "Temp: " << sharedData->temperature << " °C, Humidity: " << sharedData->humidity << " %" << std::endl;
            logfile.flush();
        }
    }

private:
    std::ofstream logfile;
};


int main() {
    std::unique_ptr<DHT22> sensor = std::make_unique<DHT22>(3); // 3 -> GPIO22
    std::shared_ptr<SensorData> sharedData = std::make_shared<SensorData>();
    std::weak_ptr<SensorData> weakData = sharedData;

    std::unique_ptr<Display> display = std::make_unique<Display>();
    std::unique_ptr<Logger> logger = std::make_unique<Logger>();

    float humidity{0.0f};
    float temperature{0.0f};

    uint32_t counter{0};        // Count for logging interval

    std::cout << "DHT22 Sensor Reading Starting..." << std::endl;
    sleep(4);                            // initial delay
    sensor->read(humidity, temperature);    // discard first reading

    while(true){
        sleep(SLEEP_DURATION);
        counter++;

        if(sensor->read(humidity, temperature) && humidity != 0.0f && temperature != 0.0f) {
            sharedData->humidity = humidity;
            sharedData->temperature = temperature;
        }
        else{
            // Invalid Reading > Work with the last valid reading
        }

        display->show(weakData);

        if(counter == LOGGING_INTERVAL){
            logger->log(weakData);
            counter = 0;
        }
    }

    return 0;
}
