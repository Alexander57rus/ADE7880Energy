/* *********************************************************************************** */
/* /*********************************************************************************** */
#include "ADE7880.h"
#include "SPI.h"

SPIClass spi;
ADE7880_SPI::ADE7880_SPI()
{
    spi = SPIClass();
    settings();
}

void ADE7880_SPI::begin(int8_t sck, int8_t miso, int8_t mosi, int8_t ss)
{
    #ifdef ARDUINO_ARCH_ESP32
    spi.begin(sck, miso, mosi, ss);
    #else
    spi.begin();
    #endif
    _ss = ss;
    pinMode(_ss, OUTPUT);
    digitalWrite(_ss, HIGH);
    delay(1);
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(_ss, LOW);
        delayMicroseconds(10);
        digitalWrite(_ss, HIGH);
        delayMicroseconds(10);
    }
}

void ADE7880_SPI::settings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode)
{
    _clock = clock;
    _bitOrder = bitOrder;
    _dataMode = dataMode;
}
void ADE7880_SPI::write8Register(uint16_t reg, uint8_t val)
{
    uint8_t fba = 0x0;
    uint8_t hba = reg >> 8;
    uint8_t lba = reg & 0xff;
    uint8_t hbv = val;
	digitalWrite(_ss, LOW);
    spi.beginTransaction(SPISettings(_clock, _bitOrder, _dataMode));
    spi.transfer(fba);
    spi.transfer(hba);
    spi.transfer(lba);
    spi.transfer(hbv);
    spi.endTransaction();
    digitalWrite(_ss, HIGH);
}

void ADE7880_SPI::write16Register(uint16_t reg, uint16_t val)
{
    uint8_t fba = 0x0;
    uint8_t hba = reg >> 8;
    uint8_t lba = reg & 0xff;
    uint8_t hbv = val >> 8;
    uint8_t lbv = val & 0xff;
    digitalWrite(_ss, LOW);
    spi.beginTransaction(SPISettings(_clock, _bitOrder, _dataMode));
    spi.transfer(fba);
    spi.transfer(hba);
    spi.transfer(lba);
    spi.transfer(hbv);
    spi.transfer(lbv);
    spi.endTransaction();
    digitalWrite(_ss, HIGH);
}
void ADE7880_SPI::write32Register(uint16_t reg, uint32_t val)
{
    uint8_t fba = 0x0;
    uint8_t hba = reg >> 8;
    uint8_t lba = reg & 0xff;
    uint8_t hbv = (val >> 24);
   uint8_t tbv = (val >> 16);
   uint8_t cbv = (val >> 8);
   uint8_t zbv = val & 0xff;
     digitalWrite(_ss, LOW);
    spi.beginTransaction(SPISettings(_clock, _bitOrder, _dataMode));
    spi.transfer(fba);
    spi.transfer(hba);
    spi.transfer(lba);
	spi.transfer(hbv);
	spi.transfer(tbv);
	spi.transfer(cbv);
    spi.transfer(zbv);
	
    spi.endTransaction();
    digitalWrite(_ss, HIGH);
}
/* void ADE7880_SPI::write24Register(uint16_t reg, uint32_t val)
{
    uint8_t fba = 0x0;
    uint8_t hba = reg >> 8;
    uint8_t lba = reg & 0xff;
    uint8_t hbv = (val >> 24)& 0xff;
   uint8_t tbv = (val >> 16)& 0xff;
   uint8_t zbv = val & 0xff;
     digitalWrite(_ss, LOW);
    spi.beginTransaction(SPISettings(_clock, _bitOrder, _dataMode));
    spi.transfer(fba);
    spi.transfer(hba);
    spi.transfer(lba);
	
    spi.transfer(hbv);
	spi.transfer(tbv);
    spi.transfer(zbv);
    spi.endTransaction();
    digitalWrite(_ss, HIGH);
} */
uint8_t ADE7880_SPI::read8Register(uint16_t reg)
{
    uint8_t fba = 0x1;
    uint8_t hba = reg >> 8;
    uint8_t lba = reg & 0xff;
    uint8_t res = 0;
    digitalWrite(_ss, LOW);
    spi.beginTransaction(SPISettings(_clock, _bitOrder, _dataMode));
    spi.transfer(fba);
    spi.transfer(hba);
    spi.transfer(lba);
    uint8_t rb0 = spi.transfer(0x0); 
    res= rb0;   
    spi.endTransaction();
    digitalWrite(_ss, HIGH);
    return res;
}

int16_t ADE7880_SPI::read16Register(uint16_t reg)
{
    uint8_t fba = 0x1;
    uint8_t hba = reg >> 8;
    uint8_t lba = reg & 0xff;
    int16_t res = 0;
    digitalWrite(_ss, LOW);
    spi.beginTransaction(SPISettings(_clock, _bitOrder, _dataMode));
    spi.transfer(fba);
    spi.transfer(hba);
    spi.transfer(lba);
    uint8_t rb0 = spi.transfer(0x0);
    uint8_t rb1 = spi.transfer(0x0);
   
    res |= rb0;
    res = (res << 8) | rb1;
    
    spi.endTransaction();
    digitalWrite(_ss, HIGH);
    return res;
}

int32_t ADE7880_SPI::read32Register(uint16_t reg)
{
    uint8_t fba = 0x1;
    uint8_t hba = reg >> 8;
    uint8_t lba = reg & 0xff;
    int32_t res = 0;
    digitalWrite(_ss, LOW);
    spi.beginTransaction(SPISettings(_clock, _bitOrder, _dataMode));
    spi.transfer(fba);
    spi.transfer(hba);
    spi.transfer(lba);
    uint8_t rb0 = spi.transfer(0x0);
    uint8_t rb1 = spi.transfer(0x0);
    uint8_t rb2 = spi.transfer(0x0);
    uint8_t rb3 = spi.transfer(0x0);
    res |= rb0;
    res = (res << 8) | rb1;
    res = (res << 8) | rb2;
    res = (res << 8) | rb3;
    spi.endTransaction();
    digitalWrite(_ss, HIGH);
    return res;
}



void ADE7880_SPI::runDsp()
{
    ADE7880_SPI::write16Register(Run, 1);
}
void ADE7880_SPI::stopDsp()
{
    write16Register(Run, 0);
}

int ADE7880_SPI::_write16Register(const unsigned int reg, const unsigned int val){
    return 0;
}
int ADE7880_SPI::_write8Register(const unsigned int reg, const uint8_t val){
    return 0;
}
int ADE7880_SPI::_write32Register(const unsigned int reg, const uint32_t val){
    return 0;
}
int ADE7880_SPI::_read32Register(const unsigned int reg){
    return 0;
}
int ADE7880_SPI::_read16Register(const unsigned int reg){
    return 0;
}
int ADE7880_SPI::_read8Register(const uint8_t reg){
    return 0;
}