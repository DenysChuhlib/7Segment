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
        Clkpin = clk;
        Datapin = dio;
        pinMode(Clkpin, OUTPUT);
        pinMode(Datapin, OUTPUT);
    }
    
    void setBrightness(uint8_t brightness) {
        Brightness = (brightness & 0x07);
        start();
        writeByte(0x88 + brightness);
        stop();
    }
    uint8_t getBrightness() { return Brightness; }
    
private:
    void start() {
        digitalWrite(Clkpin, HIGH);
        digitalWrite(Datapin, HIGH);
        digitalWrite(Datapin, LOW);
        digitalWrite(Clkpin, LOW);
    }
    
    void stop() {
        digitalWrite(Clkpin, LOW);
        digitalWrite(Datapin, LOW);
        digitalWrite(Clkpin, HIGH);
        digitalWrite(Datapin, HIGH);
    }
    
    uint8_t writeByte(uint8_t wr_data){
        uint8_t i;
        for (i = 0; i < 8; i++) //sent 8bit data
        {
            digitalWrite(Clkpin, LOW);
            if (wr_data & 0x01)digitalWrite(Datapin, HIGH); //LSB first
            else digitalWrite(Datapin, LOW);
            wr_data >>= 1;
            digitalWrite(Clkpin, HIGH);
    
        }
        digitalWrite(Clkpin, LOW); //wait for the ACK
        digitalWrite(Datapin, HIGH);
        digitalWrite(Clkpin, HIGH);
        pinMode(Datapin, INPUT);
    
        delayMicroseconds(50);
        uint8_t ack = digitalRead(Datapin);
        if (ack == 0)
        {
            pinMode(Datapin, OUTPUT);
            digitalWrite(Datapin, LOW);
        }
        delayMicroseconds(50);
        pinMode(Datapin, OUTPUT);
        delayMicroseconds(50);
    
        return ack;
    }
    
    void sendByte(uint16_t BitAddr, const Digit7SData& sendData) {
        BitAddr = constrain(BitAddr, 0, 3);
        
        start();
        writeByte(0x44/*ADDR_FIXED*/);
        stop();
        start();
        writeByte(BitAddr | 0xc0/*STARTADDR*/);
        writeByte(sendData);
        stop();
    }
    
    void sendArray(const Digits7SArray<>& sendData) {
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
    
    uint8_t Brightness;

    uint8_t Clkpin;
    uint8_t Datapin;
};

#endif