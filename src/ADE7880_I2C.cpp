/*I2C variant of the ADE7880  */
/***********************************************************************/

#include "ADE7880.h"
#include "Wire.h"

ADE7880_I2C::ADE7880_I2C(int addr)
{
    _addr = addr;
    i2c.setClock(400000);
}

void ADE7880_I2C::begin()
{
    i2c.begin();
}

void ADE7880_I2C::write8Register(uint16_t reg, uint8_t val)
{
    
    uint8_t hba = reg >> 8;
    uint8_t lba = reg & 0xff;
    uint8_t hbv = val;
	i2c.beginTransmission(_addr);
    i2c.write(hba);
    i2c.write(lba);
    i2c.write(hbv);
    i2c.endTransmission();
}

void ADE7880_I2C::write16Register(uint16_t reg, uint16_t val)
{
    uint8_t hba = reg >> 8;
    uint8_t lba = reg & 0xff;
    uint8_t hbv = val >> 8;
    uint8_t lbv = val & 0xff;
    i2c.beginTransmission(_addr);
    i2c.write(hba);
    i2c.write(lba);
    i2c.write(hbv);
    i2c.write(lbv);
    i2c.endTransmission();
}
void ADE7880_I2C::write32Register(uint16_t reg, uint32_t val)
{
    
    uint8_t hba = reg >> 8;
    uint8_t lba = reg & 0xff;
    uint8_t hbv = (val >> 24);
   uint8_t tbv = (val >> 16);
   uint8_t cbv = (val >> 8);
   uint8_t zbv = val & 0xff;
   i2c.beginTransmission(_addr);
   i2c.write(hba);
   i2c.write(lba);
   i2c.write(hbv);
   i2c.write(tbv);
   i2c.write(cbv);
   i2c.write(zbv);
   i2c.endTransmission();
}
uint8_t ADE7880_I2C::read8Register(uint16_t reg)
{
    uint8_t hba = reg >> 8;
    uint8_t lba = reg & 0xff;
    uint8_t res = 0;
	uint8_t rb0=0;
    i2c.beginTransmission(_addr);
    i2c.write(hba);
    i2c.write(lba);
    i2c.endTransmission(false);
    i2c.requestFrom((uint8_t)_addr, (uint8_t)4, (uint8_t) true);
    if (i2c.available() >= 1)
    {
    rb0 = i2c.read(); 
	}
    res= rb0;   
    return res;
}

int16_t ADE7880_I2C::read16Register(uint16_t reg)
{
    uint8_t hba = reg >> 8;
    uint8_t lba = reg & 0xff;
    int16_t res = 0;
	uint8_t rb0 = 0;
    uint8_t rb1 = 0;
    i2c.beginTransmission(_addr);
    i2c.write(hba);
    i2c.write(lba);
    i2c.endTransmission(false);
    i2c.requestFrom((uint8_t)_addr, (uint8_t)4, (uint8_t) true);
    if (i2c.available() >= 1)
    {
     rb0 = i2c.read();
     rb1 = i2c.read();
	}
   
    res |= rb0;
    res = (res << 8) | rb1;
    
    return res;
}

int32_t ADE7880_I2C::read32Register(uint16_t reg)
{
    uint8_t rb0 = 0;
    uint8_t rb1 = 0;
    uint8_t rb2 = 0;
    uint8_t rb3 = 0;
    uint8_t hba = reg >> 8;
    uint8_t lba = reg & 0xff;
    int32_t res = 0;
    i2c.beginTransmission(_addr);
    i2c.write(hba);
    i2c.write(lba);
    i2c.endTransmission(false);
    i2c.requestFrom((uint8_t)_addr, (uint8_t)4, (uint8_t) true);
    if (i2c.available() >= 1)
    {
        rb0 = i2c.read();
        rb1 = i2c.read();
        rb2 = i2c.read();
        rb3 = i2c.read();
    }
    res |= rb0;
    res = (res << 8) | rb1;
    res = (res << 8) | rb2;
    res = (res << 8) | rb3;
    return res;
}

void ADE7880_I2C::runDsp()
{
    ADE7880_I2C::write16Register(Run, 1);
}

void ADE7880_I2C::stopDsp()
{
    write16Register(Run, 0);
}

int ADE7880_I2C::_write8Register(const unsigned int reg, const uint8_t val)
{
    return 0;
}

int ADE7880_I2C::_write16Register(const unsigned int reg, const unsigned int val)
{
    return 0;
}

int ADE7880_I2C::_write32Register(const unsigned int reg, const uint32_t val)
{
    return 0;
}

int ADE7880_I2C::_read32Register(const unsigned  int reg)
{
    return 0;
}
int ADE7880_I2C::_read16Register(const unsigned int reg){
    return 0;
}
int ADE7880_I2C::_read8Register(const uint8_t reg){
    return 0;
}