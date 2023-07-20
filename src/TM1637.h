#ifndef _7SegmentTM1637_h
#define _7SegmentTM1637_h

/*
#define ADDR_AUTO  0x40
#define ADDR_FIXED 0x44
#define STARTADDR  0xc0
*/
class TM1637 : public Digits7SDisplayWithColon<> {
public:
    TM1637(uint8_t clk, uint8_t dio) {
        clkPin = clk;
        dataPin = dio;
        pinMode(clkPin, OUTPUT);
        pinMode(dataPin, OUTPUT);
    }
    
    void setBrightness(uint8_t brightness) override {
        brightness = (brightness & 0x07);
        start();
        writeByte(0x88 + brightness);
        stop();
    }
    uint8_t getBrightness() override { return brightness; }
    
private:
    void start() {
        digitalWrite(clkPin, HIGH);
        digitalWrite(dataPin, HIGH);
        digitalWrite(dataPin, LOW);
        digitalWrite(clkPin, LOW);
    }
    
    void stop() {
        digitalWrite(clkPin, LOW);
        digitalWrite(dataPin, LOW);
        digitalWrite(clkPin, HIGH);
        digitalWrite(dataPin, HIGH);
    }
    
    uint8_t writeByte(uint8_t wr_data){
        uint8_t i;
        for (i = 0; i < 8; i++) //sent 8bit data
        {
            digitalWrite(clkPin, LOW);
            if (wr_data & 0x01)digitalWrite(dataPin, HIGH); //LSB first
            else digitalWrite(dataPin, LOW);
            wr_data >>= 1;
            digitalWrite(clkPin, HIGH);
    
        }
        digitalWrite(clkPin, LOW); //wait for the ACK
        digitalWrite(dataPin, HIGH);
        digitalWrite(clkPin, HIGH);
        pinMode(dataPin, INPUT);
    
        delayMicroseconds(50);
        uint8_t ack = digitalRead(dataPin);
        if (ack == 0)
        {
            pinMode(dataPin, OUTPUT);
            digitalWrite(dataPin, LOW);
        }
        delayMicroseconds(50);
        pinMode(dataPin, OUTPUT);
        delayMicroseconds(50);
    
        return ack;
    }
    
    void sendByte(uint16_t pos, const Digit7SData& sendData) override {
        pos = constrain(pos, 0, 3);
        
        start();
        writeByte(0x44/*ADDR_FIXED*/);
        stop();
        start();
        writeByte(pos | 0xc0/*STARTADDR*/);
        writeByte(sendData);
        stop();
    }
    
    void sendArray(const Digits7SArray<>& sendData) override {
        start();
        writeByte(0x40/*ADDR_AUTO*/);
        stop();
        start();
        writeByte(0xc0/*STARTADDR*/);
        for (byte i = 0; i < 4; i ++) {
            writeByte(sendData[i]);
        }
        stop();
    }
    
    uint8_t brightness;

    uint8_t clkPin;
    uint8_t dataPin;
};

#endif