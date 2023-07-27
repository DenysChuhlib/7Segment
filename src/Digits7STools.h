#ifndef Digit7STools_H
#define Digit7STools_H

/*

Денис Чухліб, https://github.com/DenysChuhlib
MIT License

*/

//  Digit scheme
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D
//  XGFEDCBA        // X - Dot
//  76543210

//  Digits and dots
//
//  0.000       first digit with dot
//  00.00       second digit
//  000.0       third digit
//  0000.       fourth digit
//  0.0.0.0.    all four digits with dot
//
//  For displays with just a colon:
//  00:00       second digit with dot
//
//  For displays with dots and colons colon:
//  0.0:0.0.    all four digits with dot

struct Digit7SData {
    uint8_t value = 0;
    
    Digit7SData() {}
    
    Digit7SData(uint8_t rhs) { value = rhs; }
    Digit7SData(const Digit7SData& rhs) = default;
    
    operator uint8_t() const { return value; }
    Digit7SData& operator=(uint8_t rhs) { value = rhs; return *this; }
    
    bool equalWithoutDot(const Digit7SData& rhs) const {
        return (value & 0b01111111) == (rhs.value & 0b01111111);
    }
    
    bool equal(const Digit7SData& rhs) const {
        return value == rhs.value;
    }
    
    bool operator == (const Digit7SData& rhs) const {
        return equal(rhs);
    }
    bool operator != (const Digit7SData& rhs) const {
        return !equal(rhs);
    }
    
    Digit7SData& setBit(uint8_t bit, bool f = true) {
        bit = constrain(bit, 0, 7);
        f? value |= (1 << bit) : value &= ~(1 << bit);
        return *this;
    }

    Digit7SData& setA(bool f = true) {setBit(0, f); return *this; }
    Digit7SData& setB(bool f = true) {setBit(1, f); return *this; }
    Digit7SData& setC(bool f = true) {setBit(2, f); return *this; }
    Digit7SData& setD(bool f = true) {setBit(3, f); return *this; }
    Digit7SData& setE(bool f = true) {setBit(4, f); return *this; }
    Digit7SData& setF(bool f = true) {setBit(5, f); return *this; }
    Digit7SData& setG(bool f = true) {setBit(6, f); return *this; }
    
    Digit7SData& setDot(bool f = true) {setBit(7, f); return *this; }
    
    Digit7SData& setUp      (bool f = true) { setA(f); return *this; }
    Digit7SData& setUp_R    (bool f = true) { setB(f); return *this; }
    Digit7SData& setUp_L    (bool f = true) { setF(f); return *this; }
    Digit7SData& setDown_R  (bool f = true) { setC(f); return *this; }
    Digit7SData& setDown_L  (bool f = true) { setE(f); return *this; }
    Digit7SData& setDown    (bool f = true) { setD(f); return *this; }
    Digit7SData& setCenter  (bool f = true) { setG(f); return *this; }
    
    Digit7SData& clear() {
        value = 0;
        return *this;
    }
    
    bool getBit(uint8_t bit) const {
        bit = constrain(bit, 0, 7);
        return (value >> bit) & 1;
    }
    
    bool getA() const     { return getBit(0); }
    bool getB() const     { return getBit(1); }
    bool getC() const     { return getBit(2); }
    bool getD() const     { return getBit(3); }
    bool getE() const     { return getBit(4); }
    bool getF() const     { return getBit(5); }
    bool getG() const     { return getBit(6); }
    
    bool getDot() const   { return getBit(7); }

    bool getUp()     const { return getA(); }
    bool getUp_R()   const { return getB(); }
    bool getUp_L()   const { return getF(); }
    bool getDown_R() const { return getC(); }
    bool getDown_L() const { return getE(); }
    bool getDown()   const { return getD(); }
    bool getCenter() const { return getG(); }
    
    Digit7SData& setNumber(uint8_t n) {
        switch (n % 10) {
            case 0: value = 0b00111111; return *this; // 0
            case 1: value = 0b00000110; return *this; // 1
            case 2: value = 0b01011011; return *this; // 2
            case 3: value = 0b01001111; return *this; // 3
            case 4: value = 0b01100110; return *this; // 4
            case 5: value = 0b01101101; return *this; // 5
            case 6: value = 0b01111101; return *this; // 6
            case 7: value = 0b00000111; return *this; // 7
            case 8: value = 0b01111111; return *this; // 8
            case 9: value = 0b01101111; return *this; // 9
        }
        return *this;
    }
    
    Digit7SData& setChar(char t) {
        switch (t) {
            default: value = 0b00000000; return *this;
            
            case  32: value = 0b00000000; return *this; // 032 (Space)
            case  33: value = 0b00110000; return *this; // 033 !
            case  34: value = 0b00100010; return *this; // 034 "
            case  35: value = 0b01000001; return *this; // 035 #
            case  36: value = 0b01101101; return *this; // 036 $
            case  37: value = 0b01010010; return *this; // 037 %
            case  38: value = 0b01111100; return *this; // 038 &
            case  39: value = 0b00100000; return *this; // 039 '
            case  40: value = 0b00111001; return *this; // 040 (
            case  41: value = 0b00001111; return *this; // 041 )
            case  42: value = 0b00100001; return *this; // 042 *
            case  43: value = 0b01110000; return *this; // 043 +
            case  44: value = 0b00001000; return *this; // 044 ,
            case  45: value = 0b01000000; return *this; // 045 -
            case  46: value = 0b00001000; return *this; // 046 .
            case  47: value = 0b01010010; return *this; // 047 /
            case  48: value = 0b00111111; return *this; // 048 0
            case  49: value = 0b00000110; return *this; // 049 1
            case  50: value = 0b01011011; return *this; // 050 2
            case  51: value = 0b01001111; return *this; // 051 3
            case  52: value = 0b01100110; return *this; // 052 4
            case  53: value = 0b01101101; return *this; // 053 5
            case  54: value = 0b01111101; return *this; // 054 6
            case  55: value = 0b00000111; return *this; // 055 7
            case  56: value = 0b01111111; return *this; // 056 8
            case  57: value = 0b01101111; return *this; // 057 9
            case  58: value = 0b01001000; return *this; // 058 :
            case  59: value = 0b01001000; return *this; // 059 ;
            case  60: value = 0b00111001; return *this; // 060 <
            case  61: value = 0b01001000; return *this; // 061 =
            case  62: value = 0b00001111; return *this; // 062 >
            case  63: value = 0b01010011; return *this; // 063 ?
            case  64: value = 0b01011111; return *this; // 064 @
            case  65: value = 0b01110111; return *this; // 065 A
            case  66: value = 0b01111100; return *this; // 066 B
            case  67: value = 0b00111001; return *this; // 067 C
            case  68: value = 0b01011110; return *this; // 068 D
            case  69: value = 0b01111001; return *this; // 069 E
            case  70: value = 0b01110001; return *this; // 070 F
            case  71: value = 0b00111101; return *this; // 071 G
            case  72: value = 0b01110110; return *this; // 072 H
            case  73: value = 0b00000110; return *this; // 073 I
            case  74: value = 0b00011110; return *this; // 074 J
            case  75: value = 0b01110110; return *this; // 075 K
            case  76: value = 0b00111000; return *this; // 076 L
            case  77: value = 0b00010101; return *this; // 077 M
            case  78: value = 0b00110111; return *this; // 078 N
            case  79: value = 0b00111111; return *this; // 079 O
            case  80: value = 0b01110011; return *this; // 080 P
            case  81: value = 0b01100111; return *this; // 081 Q
            case  82: value = 0b00110001; return *this; // 082 R
            case  83: value = 0b01101101; return *this; // 083 S
            case  84: value = 0b01111000; return *this; // 084 T
            case  85: value = 0b00111110; return *this; // 085 U
            case  86: value = 0b00011100; return *this; // 086 V
            case  87: value = 0b00101010; return *this; // 087 W
            case  88: value = 0b01110110; return *this; // 088 X
            case  89: value = 0b01101110; return *this; // 089 Y
            case  90: value = 0b01011011; return *this; // 090 Z
            case  91: value = 0b00111001; return *this; // 091 [
            case  92: value = 0b01100100; return *this; // 092 (backslash)
            case  93: value = 0b00001111; return *this; // 093 ]
            case  94: value = 0b00100011; return *this; // 094 ^
            case  95: value = 0b00001000; return *this; // 095 _
            case  96: value = 0b00100000; return *this; // 096 `
            case  97: value = 0b01110111; return *this; // 097 a
            case  98: value = 0b01111100; return *this; // 098 b
            case  99: value = 0b01011000; return *this; // 099 c
            case 100: value = 0b01011110; return *this; // 100 d
            case 101: value = 0b01111001; return *this; // 101 e
            case 102: value = 0b01110001; return *this; // 102 f
            case 103: value = 0b01101111; return *this; // 103 g
            case 104: value = 0b01110100; return *this; // 104 h
            case 105: value = 0b00000100; return *this; // 105 i
            case 106: value = 0b00011110; return *this; // 106 j
            case 107: value = 0b01110110; return *this; // 107 k
            case 108: value = 0b00011000; return *this; // 108 l
            case 109: value = 0b00010101; return *this; // 109 m
            case 110: value = 0b01010100; return *this; // 110 n
            case 111: value = 0b01011100; return *this; // 111 o
            case 112: value = 0b01110011; return *this; // 112 p
            case 113: value = 0b01100111; return *this; // 113 q
            case 114: value = 0b01010000; return *this; // 114 r
            case 115: value = 0b01101101; return *this; // 115 s
            case 116: value = 0b01111000; return *this; // 116 t
            case 117: value = 0b00011100; return *this; // 117 u
            case 118: value = 0b00011100; return *this; // 118 v
            case 119: value = 0b00101010; return *this; // 119 w
            case 120: value = 0b01110110; return *this; // 120 x
            case 121: value = 0b01101110; return *this; // 121 y
            case 122: value = 0b01011011; return *this; // 122 z
            case 123: value = 0b00111001; return *this; // 123 {
            case 124: value = 0b00110000; return *this; // 124 |
            case 125: value = 0b00001111; return *this; // 125 }
            case 126: value = 0b01000000; return *this; // 126 ~
            //case 127: value = 0b00000000; return *this; // 127 
            
            case 176: value = 0x63; return *this; //degree, use char(176)
        }
        return *this;
    }

    int8_t getNumber() const {
        for(uint8_t i = 0; i < 10; i++) {
            if (value == Digit7SData().setNumber(i)) return i;
        }
        return -1; //value not number
    }
    
    int16_t getChar() const {
        for(uint8_t i = 32; i < 127; i++) {
            if (value == Digit7SData().setChar(i)) return i;
        }
        
        if (value == Digit7SData().setChar(176)) return 176;
        
        return -1; //value not char
    }
};

template <uint16_t DigitsSize = 4>
class Digits7SArray {
protected:
    Digit7SData digits[DigitsSize] = {0};
public:
    Digits7SArray() {}
    Digits7SArray(uint8_t newDigits[DigitsSize]) {for (uint16_t i = 0; i < DigitsSize; i++) digits[i] = newDigits[i]; }
    Digits7SArray(Digit7SData newDigits[DigitsSize]) {for (uint16_t i = 0; i < DigitsSize; i++) digits[i] = newDigits[i]; }
    Digits7SArray(const Digits7SArray<DigitsSize>& newDigits) = default;
    
    Digit7SData& operator[](uint16_t index) { index = constrain(index, 0, DigitsSize - 1);  return digits[index];   }
    const Digit7SData& operator[](uint16_t index) const { index = constrain(index, 0, DigitsSize - 1);  return digits[index];   }
    
    uint16_t size() { return DigitsSize; }

    Digits7SArray& operator = (uint8_t newDigits[DigitsSize]) {for (uint16_t i = 0; i < DigitsSize; i++) digits[i] = newDigits[i]; return *this; }
    Digits7SArray& operator = (Digit7SData newDigits[DigitsSize]) {for (uint16_t i = 0; i < DigitsSize; i++) digits[i] = newDigits[i]; return *this; }
    
    Digits7SArray& clear() {    for (uint16_t i = 0; i < DigitsSize; i++) digits[i].clear(); return *this; }
    
    template <uint16_t size, uint16_t pos = 0, uint16_t num = size> 
    Digits7SArray& setDigits(const Digits7SArray<size>& newDigits) {
        for(uint16_t i = 0; i < size && i + pos < DigitsSize; i++)
            digits[i + pos] = newDigits[i];
        return *this;
    }
    
    template <uint16_t size, uint16_t num = size>
    Digits7SArray& setDigitsFist(const Digits7SArray<size>& newDigits) {
        return setDigits<size, 0, num>(newDigits);
    }
    
    template <uint16_t size, uint16_t num = size>
    Digits7SArray& setDigitsLast(const Digits7SArray<size>& newDigits) {
        return setDigits<size, DigitsSize - size, num>(newDigits);
    }
};

class Digits7S_Math {
public:
    
    static uint64_t fast10Pow(uint8_t exp) {
        switch (exp) {
            case 0: return 1;
            case 1: return 10;
            case 2: return 100;
            case 3: return 1000ul;
            case 4: return 10000ul;
            case 5: return 100000ul;
            case 6: return 1000000ul;
            case 7: return 10000000ul;
            case 8: return 100000000ul;
            case 9: return 1000000000ul;
            //uint32_t can have a maximum of 9 zeros
            default:
            {
                if (exp > 38) return 1;
                
                uint64_t a = 1;
                for (uint8_t i = 0; i < exp; i++) {
                    a *= 10;
                }
                return a;
            }
        }
        return 1;
    }
    
    static uint8_t getNumberInInt(int32_t n, uint8_t pos) {
        return (abs(n) / fast10Pow(pos)) % 10;
    }
    
    static uint8_t getNumberInInt(uint32_t n, uint8_t pos) {
        return (n / fast10Pow(pos)) % 10;
    }
    
    static uint8_t getNumberInInt(int64_t n, uint8_t pos) {
        return (abs(n) / fast10Pow(pos)) % 10;
    }
    
    static uint8_t getNumberInInt(uint64_t n, uint8_t pos) {
        return (n / fast10Pow(pos)) % 10;
    }
};

template <uint16_t DigitsSize = 4>
class Digits7S {
protected:
    Digits7SArray<DigitsSize> digits;
public:
    Digits7S() {}
    
    Digits7S(const Digits7SArray<DigitsSize>& newDigits) { digits = newDigits; }
    Digits7S(const Digits7S<DigitsSize>& newDigits) = default;
            
    Digit7SData& operator[](uint16_t index) { index = constrain(index, 0, DigitsSize - 1);  return digits[index];   }
    const Digit7SData& operator[](uint16_t index) const { index = constrain(index, 0, DigitsSize - 1);  return digits[index];   }
    
    uint16_t size() { return DigitsSize; }
    
    operator Digits7SArray<DigitsSize>&() { return digits; }
    Digits7S& operator = (const Digits7SArray<DigitsSize>& newDigits) { digits = newDigits; return *this; }
    
    Digits7S& clear() { digits.clear(); return *this; }
    
    template <uint16_t size, uint16_t pos = 0, uint16_t num = size> 
    Digits7S& setDigits(const Digits7SArray<size>& newDigits) {
        for(uint16_t i = 0; i < size && i + pos < DigitsSize; i++)
            digits[i + pos] = newDigits[i];
        return *this;
    }
    
    template <uint16_t size, uint16_t num = size>
    Digits7S& setDigitsFist(const Digits7SArray<size>& newDigits) {
        return setDigits<size, 0, num>(newDigits);
    }
    
    template <uint16_t size, uint16_t num = size>
    Digits7S& setDigitsLast(const Digits7SArray<size>& newDigits) {
        return setDigits<size, DigitsSize - size, num>(newDigits);
    }
    
    
    Digits7S& setInt(int64_t n) {
        clear();
        
        bool neg = 0;
        
        if (n < 0) neg = true;
        n = abs(n);
        
        uint8_t numbers = 1; //кількість чисел
        while (n / Digits7S_Math::fast10Pow(numbers) > 0)
            numbers++;
        
        if (numbers > DigitsSize) 
            setString(F(" OVF"));
        else if (numbers > DigitsSize - 1 && neg)
            setString(F("-OVF"));
        else {
            for (uint8_t i = 0; i < numbers; i++) {
                digits[DigitsSize - i - 1].setNumber(Digits7S_Math::getNumberInInt(n, i));
            }
            if (neg) digits[DigitsSize - numbers - 1].setChar('-');
        }
        return *this;
    }
    
    Digits7S& setClock(uint8_t h, uint8_t m, bool noFirstZero = 1) {
        if (DigitsSize < 4) return *this;
        h = constrain(h, 0, 60);//можна буде ставити хвилини а наступне секунди
        m = constrain(m, 0, 60);
        clear();
        for (uint8_t i = 0; i < 2; i++) {
            digits[1 - i].setNumber(Digits7S_Math::getNumberInInt(h, i));

            digits[3 - i].setNumber(Digits7S_Math::getNumberInInt(m, i));
        }
        if (noFirstZero && digits[0].equalWithoutDot(Digit7SData().setNumber(0))) digits[0] = 0;
        return *this;
    }
    
    Digits7S& setClock(uint8_t h, uint8_t m, uint8_t s, bool noFirstZero = 1) {
        if (DigitsSize < 6) return *this;
        h = constrain(h, 0, 24);
        m = constrain(m, 0, 60);
        s = constrain(s, 0, 60);
        clear();
        for (uint8_t i = 0; i < 2; i++) {
            digits[1 - i].setNumber(Digits7S_Math::getNumberInInt(h, i));
        
            digits[3 - i].setNumber(Digits7S_Math::getNumberInInt(m, i));
        
            digits[5 - i].setNumber(Digits7S_Math::getNumberInInt(s, i));
        }
        if (noFirstZero && digits[0].equalWithoutDot(Digit7SData().setNumber(0))) digits[0] = 0;
        return *this;
    }
    
    Digits7S& setString(const String& str) {
        clear();
        for (uint16_t i = 0; i < DigitsSize && i < str.length(); i++) digits[i].setChar(str[DigitsSize - i]);
        return *this;
    }
    String& getString() {
        String s;
        for (uint16_t i = 0; i < DigitsSize; i++) {
            if (digits[i].getChar() != -1)
                s += digits[i].getChar();
            else
                s += ' ';
        }
        return s;
    }
    
};

template <uint16_t DigitsSize = 4>
class Digits7SAnimator : public Digits7S<DigitsSize> {
public:
    Digits7SAnimator() {}
    
    void setDel(uint16_t pos, uint16_t delay) {
        pos = constrain(pos, 0, DigitsSize - 1);
        
        del[pos] = delay;
    }
    
    void setAllDel(uint16_t delay) {
        for (uint16_t i = 0; i < DigitsSize; i++) del[i] = delay;
    }
    
    uint16_t getDel(uint16_t pos) {
        pos = constrain(pos, 0, DigitsSize - 1);
        
        return del[pos];
    }

    bool tickAnimation() {
        bool show = 0;
        for (uint16_t i = 0; i < DigitsSize; i++) {
            if ((millis() & 0xFFFF) - timer[i] >= del[i]) {
                
                if (animationId[i]) show = true;
                else continue;
                
                showFrame(i);
                
                if (animationId[i]) {
                    frame[i]++;
                    timer[i] = millis() & 0xFFFF;
                }
            }
        }
        return show;
    }
    
    bool isAnimation() {
        for (uint16_t i = 0; i < DigitsSize; i++) {
            if (animationId[i]) return true;
        }
        return false;
    }
    bool isAnimation(uint16_t pos) {
        pos = constrain(pos, 0, DigitsSize - 1);
        
        if (animationId[pos]) return true;
        return false;
    }
    
    void startAllAnimation(uint8_t id, const Digits7SArray<DigitsSize>& nData, bool resetData, bool stopAnimation) {
        if (isAnimation() && !stopAnimation) return;
        
        if (resetData) {
            newDigits = nData;
        
            timer[0] = millis() & 0xFFFF;
            for (uint16_t i = 0; i < DigitsSize; i++) {
                animationId[i] = id;
                frame[i] = 0;
                timer[i] = timer[0];
            }
        } else for (uint16_t i = 0; i < DigitsSize; i++) {
            startAnimation(id, i, nData[i], false, stopAnimation);
        }
    }
    
    void startAnimation(uint8_t id, uint16_t pos, const Digit7SData& nData, bool resetData, bool stopAnimation) { 
        pos = constrain(pos, 0, DigitsSize - 1);
        
        if (isAnimation(pos) && !stopAnimation) return;
        
        if (resetData || 
            (!isAnimation(pos) && !this->digits[pos].equalWithoutDot(nData)) ||
            (isAnimation(pos) && !newDigits[pos].equalWithoutDot(nData)) ) {
                
            newDigits[pos] = nData;
        
            animationId[pos] = id;
            frame[pos] = 0;
            timer[pos] = millis() & 0xFFFF;
        }
    }
    
    void stopAnimation(uint16_t pos) {
        pos = constrain(pos, 0, DigitsSize - 1);
        
        if (isAnimation(pos))
            this->digits[pos] = newDigits[pos];
        
        animationId[pos] = 0;
        frame[pos] = 0;
    }
    
    void stopAllAnimation() { 
        for (uint16_t i = 0; i < DigitsSize; i++) {
            stopAnimation(i);
        }
    }
    
    uint8_t getAnimationId(uint16_t pos) {
        pos = constrain(pos, 0, DigitsSize - 1);
        
        return animationId[pos]; 
    }
    uint8_t getAnimationId() {
        uint8_t id = animationId[0];
        for (uint16_t i = 1; i < DigitsSize; i++) {
            if (id != animationId[i]) return DIFFERENT_MODS;
        }
        return id;
    }
    
    uint16_t getFrame(uint16_t pos) {
        pos = constrain(pos, 0, DigitsSize - 1);
        
        return frame[pos];
    }
    
    bool nextFrame(uint16_t pos) {
        pos = constrain(pos, 0, DigitsSize - 1);
        
        if (!animationId[pos]) return false;

        showFrame(pos);
        
        if (animationId[pos]) {
            frame[pos]++;
            timer[pos] = millis() & 0xFFFF;
        }
        
        return true;
    }
    
    static uint16_t getAnimationFrames(uint8_t id) {
        switch (id) {
            case NONE:      return 0;
            case SCROLL:    return 6;
            case SCROLL_UP: return 6;
            case TWIST:     return 26;
        }
        return 0;
    }
    
    enum {
        NONE,
        SCROLL,
        SCROLL_UP,
        TWIST,
        DIFFERENT_MODS = 255
    };
    
    //=============================================================================================
    // animation pos
    
    void scroll (uint16_t pos, const Digit7SData& nData, bool resetData = false, bool stopAnimation = false) {
        startAnimation(SCROLL, pos, nData, resetData, stopAnimation);
    }
    
    void scrollUp(uint16_t pos, const Digit7SData& nData, bool resetData = false, bool stopAnimation = false) {
        startAnimation(SCROLL_UP, pos, nData, resetData, stopAnimation);
    }
    
    void twist  (uint16_t pos, const Digit7SData& nData, bool resetData = false, bool stopAnimation = false) {
        startAnimation(TWIST, pos, nData, resetData, stopAnimation);
    }
    
    //=============================================================================================
    // animation all
    
    void scroll (const Digits7SArray<DigitsSize>& nData, bool resetData = false, bool stopAnimation = false) {
        startAllAnimation(SCROLL, nData, resetData, stopAnimation);
    }
    
    void scrollUp(const Digits7SArray<DigitsSize>& nData, bool resetData = false, bool stopAnimation = false) {
        startAllAnimation(SCROLL_UP, nData, resetData, stopAnimation);
    }
    
    void twist  (const Digits7SArray<DigitsSize>& nData, bool resetData = false, bool stopAnimation = false) {
        startAllAnimation(TWIST, nData, resetData, stopAnimation);
    }
    
    //=============================================================================================
    // animation all int
    
    void scrollInt  (int64_t n, bool resetData = false, bool stopAnimation = false) {
        Digits7S<DigitsSize> data;
        scroll(data.setInt(n), resetData, stopAnimation);
    }
    
    void scrollUpInt(int64_t n, bool resetData = false, bool stopAnimation = false) {
        Digits7S<DigitsSize> data;
        scrollUp(data.setInt(n), resetData, stopAnimation);
    }
    
    void twistInt   (int64_t n, bool resetData = false, bool stopAnimation = false) {
        Digits7S<DigitsSize> data;
        twist(data.setInt(n), resetData, stopAnimation);
    }
    
    //=============================================================================================
    // animation all clock 4-dig
    
    void scrollClock    (uint8_t h, uint8_t m, bool noFirstZero = 1, bool resetData = false, bool stopAnimation = false) {
        Digits7S<DigitsSize> data;
        scroll(data.setClock(h, m, noFirstZero), resetData, stopAnimation);
    }
    
    void scrollUpClock  (uint8_t h, uint8_t m, bool noFirstZero = 1, bool resetData = false, bool stopAnimation = false) {
        Digits7S<DigitsSize> data;
        scrollUp(data.setClock(h, m, noFirstZero), resetData, stopAnimation);
    }
    
    void twistClock     (uint8_t h, uint8_t m, bool noFirstZero = 1, bool resetData = false, bool stopAnimation = false) {
        Digits7S<DigitsSize> data;
        twist(data.setClock(h, m, noFirstZero), resetData, stopAnimation);
    }
    
    //=============================================================================================
    // animation all clock 6-dig
    
    void scrollClock    (uint8_t h, uint8_t m, uint8_t s, bool noFirstZero = 1, bool resetData = false, bool stopAnimation = false) {
        Digits7S<DigitsSize> data;
        scroll(data.setClock(h, m, s, noFirstZero), resetData, stopAnimation);
    }
    
    void scrollUpClock  (uint8_t h, uint8_t m, uint8_t s, bool noFirstZero = 1, bool resetData = false, bool stopAnimation = false) {
        Digits7S<DigitsSize> data;
        scrollUp(data.setClock(h, m, s, noFirstZero), resetData, stopAnimation);
    }
    
    void twistClock     (uint8_t h, uint8_t m, uint8_t s, bool noFirstZero = 1, bool resetData = false, bool stopAnimation = false) {
        Digits7S<DigitsSize> data;
        twist(data.setClock(h, m, s, noFirstZero), resetData, stopAnimation);
    }
    
protected:
    uint16_t del[DigitsSize] = {30};
    uint16_t timer[DigitsSize];
    
    uint16_t frame[DigitsSize];
    uint8_t animationId[DigitsSize] = {NONE};
    
    Digits7SArray<DigitsSize> newDigits;

    virtual void showFrame(uint16_t pos) {
        pos = constrain(pos, 0, DigitsSize - 1);
        
        switch (animationId[pos]) {
            case NONE: 
            break;
            case SCROLL:
                scrollFrame(pos);
                if (frame[pos] >= getAnimationFrames(SCROLL) - 1) {
                    stopAnimation(pos);
                }
            break;
            case SCROLL_UP:
                scrollUpFrame(pos);
                if (frame[pos] >= getAnimationFrames(SCROLL_UP) - 1) {
                    stopAnimation(pos);
                }
            break;
            case TWIST:
                twistFrame(pos);
                if (frame[pos] >= getAnimationFrames(TWIST) - 1) {
                    stopAnimation(pos);
                }
            break;
            default:
                stopAnimation(pos);
            break;
        }
    }

    void scrollFrame(uint16_t pos) {
        pos = constrain(pos, 0, DigitsSize - 1);
        
        Digit7SData step = 0;
        switch (frame[pos]) {
            case 0:
                step.setBit(6, this->digits[pos].getBit(0));
                step.setBit(2, this->digits[pos].getBit(1));
                step.setBit(4, this->digits[pos].getBit(5));
                step.setBit(3, this->digits[pos].getBit(6));
                
                this->digits[pos] = step;
            break;
            case 1:
                step.setBit(3, this->digits[pos].getBit(6));
            
                this->digits[pos] = step;
            break;
            case 2:
                this->digits[pos] = 0;
            break;
            case 3:
                step.setBit(0, newDigits[pos].getBit(3));
            
                this->digits[pos] = step;
            break;
            case 4:
                step.setBit(0, newDigits[pos].getBit(6));
                step.setBit(1, newDigits[pos].getBit(2));
                step.setBit(5, newDigits[pos].getBit(4));
                step.setBit(6, newDigits[pos].getBit(3));
                
                this->digits[pos] = step;
            break;
            case 5:
                this->digits[pos] = newDigits[pos];
            break;
        }
    }
    void scrollUpFrame(uint16_t pos) {
        pos = constrain(pos, 0, DigitsSize - 1);
        
        Digit7SData step = 0;
        switch (frame[pos]) {
            case 0:
                step.setBit(0, this->digits[pos].getBit(6));
                step.setBit(1, this->digits[pos].getBit(2));
                step.setBit(5, this->digits[pos].getBit(4));
                step.setBit(6, this->digits[pos].getBit(3));
                
                this->digits[pos] = step;
            break;
            case 1:
                step.setBit(6, this->digits[pos].getBit(3));
            
                this->digits[pos] = step;
            break;
            case 2:
                this->digits[pos] = 0;
            break;
            case 3:
                step.setBit(3, newDigits[pos].getBit(0));
            
                this->digits[pos] = step;
            break;
            case 4:
                step.setBit(6, newDigits[pos].getBit(0));
                step.setBit(2, newDigits[pos].getBit(1));
                step.setBit(4, newDigits[pos].getBit(5));
                step.setBit(3, newDigits[pos].getBit(6));
                
                this->digits[pos] = step;
            break;
            case 5:
                this->digits[pos] = newDigits[pos];
            break;
        }
    }
    
    void twistFrame(uint16_t pos) {
        pos = constrain(pos, 0, DigitsSize - 1);
        
        Digit7SData step = 0;
        switch (frame[pos]) {
            case 0:
                this->digits[pos].setCenter(0);
                this->digits[pos].setDot(0);
            case 1:
            case 2:
            case 3:
            case 4:
                this->digits[pos].setBit(frame[pos]);
            break;
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
                step.setCenter(1);
                step.setDot(1);
            
                step.setBit(frame[pos] - 5);
                step.setBit(frame[pos] - 6);
                this->digits[pos] = ~step;
            break;
            case 12:
                step.setCenter(1);
                step.setDot(1);
            
                step.setA(1);
                
                this->digits[pos] = ~step;
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
                this->digits[pos].setBit(frame[pos] - 12, 0);
            break;
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
                this->digits[pos].setBit(frame[pos] - 18, newDigits[pos].getBit(frame[pos] - 18));
            break;
        }
    }

};

template <uint16_t DigitsSize = 4>
class Digits7SRunningString : public Digits7S<DigitsSize> {
public:

    Digits7SRunningString() {}
    
    void setDel(uint16_t del_) {del = del_;}
    uint16_t getDel() {return del;}
    
    bool tickAnimation() {
        bool show = 0;
        if (isAnimation()) {
            if ((millis() & 0xFFFF) - timer >= del) {
                show = true;
                
                nextFrame();
            }
        }
        return show;
    }
    
    bool nextFrame() {
        if (!isAnimation()) return false;
        
        this->clear();
        if (frame < getAnimationFrames()) {
            for (uint16_t i = 0; i < DigitsSize; i++) 
                this->digits[i].setChar(str[(reverse ? str.length() - frame + 4 : frame - 4) + i]);
            
        } else /*if (frame >= getAnimationFrames())*/ {
            frame = 0;
            str = String("");
            return true;
        }
        
        frame++;
        timer = millis() & 0xFFFF;
        
        return true;
    }
    
    uint32_t getFrame() {
        return frame;
    }
    
    uint32_t getAnimationFrames() {
        return str.length() + 8;
    }
    
    bool isAnimation() {return str.length();}
    
    void stopAnimation() {
        this->clear();
        frame = 0;
        str = String("");
    }
    
    void runningString(const String& s, bool stopAnimation = false) {
        if (isAnimation() && !stopAnimation) return;
        reverse = 0;
        str = s;
        timer = millis() & 0xFFFF;
        frame = 0;
    }
    
    void runningReverseString(const String& s, bool stopAnimation = false) {
        if (isAnimation() && !stopAnimation) return;
        reverse = 1;
        str = s;
        timer = millis() & 0xFFFF;
        frame = 0;
    }

protected:
    bool reverse = 0;
    uint16_t del = 200;
    uint16_t timer;

    String str;
    
    uint32_t frame;
};
//======================================================================================
template <uint16_t DigitsSize = 4>
class Digits7SDisplay : public Digits7SAnimator<DigitsSize> {
public:
    Digits7SDisplay() {}
    
    virtual void setBrightness(uint8_t brightness) = 0;
    virtual uint8_t getBrightness() = 0;
    
    void show() {display();}
    
    bool tickDisplay() {
        if (this->tickAnimation()) {
            display();
            return true;
        }
        return false;
    }
    
    void display() {
        displayMain(); 
        sendArray(this->digits);
    }
    void display(const Digits7SArray<DigitsSize>& newDigits) {
        this->digits = newDigits;
        display();
    }
    
    void display(uint16_t pos) {
        pos = constrain(pos, 0, DigitsSize - 1);
        
        displayMain(pos);
        sendByte(pos, this->digits[pos]);
    }
    void display(uint16_t pos, const Digit7SData& val) {
        pos = constrain(pos, 0, DigitsSize - 1);
        
        this->digits[pos] = val;
        
        display(pos);
    }
    
protected:

    virtual void displayMain() = 0;
    virtual void displayMain(uint16_t pos) { displayMain(); };
    
    virtual void sendByte(uint16_t pos, const Digit7SData& sendData) = 0;
    
    virtual void sendArray(const Digits7SArray<DigitsSize>& sendData) = 0;
    
};

//======================================================================================
template <uint16_t DigitsSize = 4>
class Digits7SDisplayWithColon : public Digits7SDisplay<DigitsSize> {
public:

    void setColon(bool f = true) {colon = f;}
    bool getColon() { return colon; }
    
    void setUseColon(bool f) {useColon = f;}
    bool getUseColon() {return useColon;}
    
protected:

    bool colon;
    bool useColon = 1;
    
    virtual void colonMain() {
        if (useColon) this->digits[1].setDot(colon);
    }
    
    virtual void displayMain() override {
        colonMain();
    }
};

#endif