/* ADE7880 */

#ifndef __ADE7880_H__
#define __ADE7880_H__

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#define ADE7880_ADDR (0x38)  // адрес I2C

// колибровочные константы эти константы посволяют на прямую изменять значения и пред усиления по умолчанию имеют 0x000000 см. даташид
#define AIGAIN (0x4380)       //регулирование усиления по току фазы А
#define AVGAIN (0x4381)      // регулирование усиления по напряжению  фазы А
#define BIGAIN (0x4382)      // регулирование усиления по току фазы B
#define BVGAIN (0x4383)      // регулирование усиления по напряжению  фазы B
#define CIGAIN (0x4384)      // регулирование усиления по току фазы C
#define CVGAIN (0x4385)      // регулирование усиления по напряжению  фазы C
#define NIGAIN (0x4386)      // регулирование усиления по току нейтрали
#define Reserved (0x4387)    // не записывать этот регистр
#define DICOFF (0x4388)      // Регистр, используемый в алгоритме цифрового интегратора.Если интегратор включен, он должен быть установлен на0xFF8000. На практике он передается как 0xFFF8000.

#define APGAIN (0x4389) 	 // Регулирование усиления мощности фазы А.
#define AWATTOS (0x438A)	 // Регулирование смещения полной активной мощности фазы А.
#define BPGAIN (0x438B)	     // Регулирование усиления мощности по фазы В.
#define BWATTOS (0x438c)     // Регулирование смещения полной активной мощности фазы В.
#define CPGAIN (0x438D)      // Регулирование усиления мощности фазы С.
#define CWATTOS (0x438E)     // Регулирование смещения полной активной мощности фазы C
#define AIRMSOS (0x438F)     // Смещение среднеквадратичного значения тока фазы А
#define AVRMSOS (0x4390)     // Смещение среднеквадратичного значения напряжения фазы А
#define BIRMSOS (0x4391)     // Смещение среднеквадратичного значения тока фазы В
#define BVRMSOS (0x4392)     // Смещение среднеквадратичного значения напряжения фазы В
#define CIRMSOS (0x4393)     // Смещение среднеквадратичного значения тока фазы С
#define CVRMSOS (0x4394)     // Смещение среднеквадратичного значения напряжения фазы С
#define NIRMSOS (0x4395)     // Смещение среднеквадратичного значения тока N

#define HPGAIN (0x4398)      // Регулирование усилиния гармонических мощностей
#define ISUMLVL (0x4399)     // Порог, используемый для сравнения суммы фазных токов и тока нейтрали
#define VLEVEL (0x439F)      // Регистр, используемый в алгоритме вычисления основныхактивных и реактивных мощностей. Установите этот регистр всоответствии с уравнением 22 для правильногофункционирования основных мощностей и гармоническихвычислений.

#define AFWATTOS (0x43A2)    // смещения активной мощности основной гармоники фазы A. Регулировк
#define BFWATTOS (0x43A3)    // смещения активной мощности основной гармоники фазы B. Регулировка
#define CFWATTOS (0x43A4)    // смещения активной мощности основной гармоники фазы C. Регулировка

#define AFVAROS (0x43A5)     //Регулировка смещения основной реактивной мощности фазы A. Регулировка
#define BFVAROS (0x43A6)     //Регулировка смещения основной реактивной мощности фазы B. Регулировка
#define CFVAROS (0x43A7)     //Регулировка смещения основной реактивной мощности фазы C. Регулировка

#define AFIRMSOS (0x43A8)     //Смещение среднеквадратичного значения основного тока фазы A
#define BFIRMSOS (0x43A9)    //Смещение среднеквадратичного значения основного тока фазы B
#define CFIRMSOS (0x43AA)    //Смещение среднеквадратичного значения основного тока фазы C

#define AFVRMSOS (0x43AB)  //Среднеквадратичное смещение основного напряжения фазы А
#define BFVRMSOS (0x43AC)  //Среднеквадратичное смещение основного напряжения фазы B
#define CFVRMSOS (0x43AD)  //Среднеквадратичное смещение основного напряжения фазы C

#define HXWATTOS (0x43AE)  //Active power offset adjust on harmonic X (see Harmonics Calculations section for details).
#define HYWATTOS  (0x43AF) //   Active power offset adjust on harmonic Y (see Harmonics Calculations section for details).
#define HZWATTOS  (0x43B0) //  Active power offset adjust on harmonic Z (see Harmonics Calculations section for details).
#define HXVAROS  (0x43B1) //
#define HYVAROS  (0x43B2) //
#define HZVAROS  (0x43B3) //
#define HXIRMSOS  (0x43B4) //
#define HYIRMSOS  (0x43B5) //
#define HZIRMSOS  (0x43B6) //

// действующие значения забираем с АЦП ADE7880

#define AIRMS (0x43C0)       // Среднеквадратичное значение тока фазы А rms
#define AVRMS (0x43C1)        // Среднеквадратичное значение напряжения фазы А
#define BIRMS (0x43C2)        // Среднеквадратичное значение тока фазы В rms
#define BVRMS (0x43C3)        // Среднеквадратичное значение напряжения фазы В
#define CIRMS (0x43C4)        // Среднеквадратичное значение тока фазы С rms
#define CVRMS (0x43C5)        // Среднеквадратичное значение напряжения фазы С
#define NIRMS (0x43C6)        // Среднеквадратичное значение тока фазы N rms
#define ISUM  (0x43C7)        // Сумма регистров токов IAWV, IBWV и ICWV.
     


// Run Register
#define Run (0xE228) // Регистр запуска запускает и останавливает DSP

// 
#define AWATTHR (0xE400) // Накопление полной активной энергии фазы А.
#define BWATTHR (0xE401) // Накопление полной активной энергии фазы B.
#define CWATTHR (0xE402) // Накопление полной активной энергии фазы С.

#define AFWATTHR (0xE403) // Накопление основной активной энергии фазы А.
#define BFWATTHR (0xE404) // Накопление основной активной энергии фазы В.
#define CFWATTHR (0xE405) // Накопление основной активной энергии фазы С.

#define AFVARHR (0xE409)  // Фаза А накопление основной реактивной энергии.
#define BFVARHR (0xE40A)  // Фаза В накопление основной реактивной энергии.
#define CFVARHR (0xE40B)  // Фаза С накопление основной реактивной энергии.

#define AVAHR (0xE40C) // накопление полной энергии фаза А.
#define BVAHR (0xE40D) // накопление полной энергии фаза В.
#define CVAHR (0xE40E) // накопление полной энергии фаза С.



// Регистры конфигурации и качества электроэнергии
#define IPEAK (0xE500)     // Токовый регстр пиков.
#define VPEAK (0xE501)     // Пиковый регистр напряжения .

#define STATUS0 (0xE502)   // регистр состояния  0 см.табл 36 .
#define STATUS1 (0xE503)   // регистр состояния  1 см.табл 36 .

#define AIMAV (0xE504) //Среднее абсолютное значение тока фазы A, вычисленное в режимах PSM0 и PSM1.
#define BIMAV (0xE505) //Среднее абсолютное значение тока фазы В, вычисленное в режимах PSM0 и PSM1.
#define CIMAV (0xE506) //Среднее абсолютное значение тока фазы С, вычисленное в режимах PSM0 и PSM1.


#define OILVL (0xE507)     // Порог перегрузки по току.
#define OVLVL (0xE508)     // Порог перегрузки по напряжению
#define SAGLVL (0xE509)    // Порг уровня просидания напряжения.

#define MASK0 (0xE50A)     // Регистр разрешения прирывания  Register 0.
#define MASK1 (0xE50B)     // Регистр разрешения прирывания 1. таблица 38

#define IAWV (0xE50C) // 1. См. Таблицу 39. Мгновенное значение тока фазы А.
#define IBWV (0xE50D) // 1. См. Таблицу 39. Мгновенное значение тока фазы B.
#define ICWV (0xE50E) // 1. См. Таблицу 39. Мгновенное значение тока фазы C.
#define INWV (0xE50F)  //  1. См. Таблицу 39. Мгновенное значение тока N.
#define VAWV (0xE510)       // Мгновенное значение напряжения фазы А.
#define VBWV (0xE511) //Мгновенное значение напряжения фазы B
#define VCWV (0xE512) // Мгновенное значение напряжения фазы C.

#define AWATT (0xE513) //Мгновенное значение полной активной мощности фазы А.
#define BWATT (0xE514) //Мгновенное значение полной активной мощности фазы B.
#define CWATT (0xE515) //Мгновенное значение полной активной мощности фазы C.
#define AVA (0xE519) //Мгновенное значение полной мощности фазы А.
#define BVA (0xE51A) //Мгновенное значение полной мощности фазы B.
#define CVA (0xE51B) //Мгновенное значение полной мощности фазы C/

#define CHECKSUM (0xE51F) //Проверка контрольной суммы. См. Подробности в разделе «Регистр контрольной суммы».
#define VNOM (0xE520) //Номинальное действующее значение фазного напряжения, используемое при альтернативном вычислении полной мощности. Когда бит VNOMxEN установлен, приложенное входное напряжение в соответствующей фазе игнорируется, и все соответствующие экземпляры действующего напряжения заменяются значением в регистре VNOM.

#define LAST_RWDATA_24bit 0xE5FF
#define PHSTATUS (0xE600)  // Регистр пиков фазы. См. Таблицу 40.
#define ANGLE0 (0xE601)    // Временная задержка 0. Подробную информацию см. В разделе «Интервал времени между фазами».
#define ANGLE1 (0xE602)    // Временная задержка 1. Подробную информацию см. В разделе «Интервал времени между фазами».
#define ANGLE2 (0xE603)    // Временная задержка 2. Подробную информацию см. В разделе «Интервал времени между фазами».

#define PHNOLOAD (0xE608)  // Фаза без нагрузки регистр. См. Таблицу 41.
#define LINECYC (0xE60C)   // Счетчик режима накопления цикла линии.
#define ZXTOUT (0xE60D)    // Счетчик тайм-аута перехода через ноль.
#define COMPMODE (0xE60E)  // Регистр вычислительного режима. См. Таблицу 42.
#define Gain (0xE60F)      // Коэффициенты усиления PGA на входах АЦП. См.Таблицу 43.

#define CFMODE (0xE610) //Регистр конфигурации CFx. См. Таблицу 44.
#define CF1DEN (0xE611) // CF1.
#define CF2DEN (0xE612) //CF2.
#define CF3DEN (0xE613) //CF3.
#define APHCAL (0xE614) //Калибровка фазы фазы A. См. Таблицу 45.
#define BPHCAL (0xE615) //Калибровка фазы фазы В. См. Таблицу 45.
#define CPHCAL (0xE616) //Калибровка фазы фазы С. См. Таблицу 45.

#define PHSIGN (0xE617)    // Регистр знака мощности. См. Таблицу 46.
#define CONFIG (0xE618)    // ADE7880 регистр конфигурации. См.Таблицу 47.
#define MMODE (0xE700)     // Регистр режима измерения. См. Таблицу 48.
#define ACCMODE (0xE701)   // Регистр режима накопления. См.Таблицу 49.
#define LCYCMODE (0xE702)  // Поведение в режиме накопления строк.
#define PEAKCYC (0xE703)   // Половина циклов обнаружения пиков.
#define SAGCYC (0xE704)    // Половина циклов обнаружения провисания
#define CFCYC (0x705) //Количество импульсов CF между двумя последовательными защелками энергии. См. Раздел «Синхронизация регистров энергии с выходами CFx». 
#define HSDC_CFG (0xE706)  // Регистр конфигурации HSDC. См. Таблицу 52.
#define Version (0xE707)   // Версия матрицы.

#define FVRMS (0xE880)    // Действующее значение основной составляющей фазного напряжения
#define FIRMS (0xE881)    // Действующее значение основной составляющей фазного тока
#define FWATT (0xE882)    // Активная мощность основного компонента
#define FVAR (0xE883)     // Реактивная мощность основной состовляющей
#define FVA (0xE884)		// Кажущаяся мощность основного компонента
#define FPF (0xE885)		// Коэффициент мощности основного
#define VTHDN (0xE886)	// Суммарные гармонические искажения фазного напряжения
#define ITHDN (0xE887)	// Суммарные гармонические искажения фазного тока
#define HXVRMS (0xE888)	// Действующее значение гармоники фазного напряжения Х
#define HXIRMS (0xE889)	// Действующее значение гармоники фазного тока Х
#define HXWATT (0xE88A)	// Активная мощность гармоники X.
#define HXVAR (0xE88B)	// Реактивная мощность гармоники X.
#define HXVA (0xE88C)		// Полная мощность гармоники X.
#define HXPF (0xE88D)		// Коэффициент мощности гармоники X.
#define HXVHD (0xE88E)	// Гармонические искажения гармоники фазного напряжения X относительно основной гармоники.
#define HXIHD (0xE88F)	// Гармонические искажения гармоники фазного тока X относительно основной гармоники.
#define HYVRMS (0xE890)   // Действующее значение гармоники фазного напряжения Y.
#define HYIRMS (0xE891)	// Действующее значение гармоники фазного тока Y.
#define HYWATT (0xE892)	// Активная мощность гармоники Y.
#define HYVAR (0xE893)	// Реактивная мощность гармоники Y.
#define HYVA (0xE894)		// Полная мощность гармоники Y.
#define HYPF (0xE895)		// Коэффициент мощности гармоники Y.
#define HYVHD (0xE896)	// Гармонические искажения гармоники фазного напряжения Y относительно основной гармоники.
#define HYIHD (0xE897)	// Гармонические искажения гармоники фазного тока Y относительно основной гармоники.
#define HZVRMS (0xE898)	// Действующее значение гармоники фазного напряжения Z.
#define HZIRMS (0xE899)	// Действующее значение гармоники фазного тока Z.
#define HZWATT (0xE89A)	// Активная мощность гармоники Z.
#define HZVAR (0xE89B)	// Реактивная мощность гармоники Z.
#define HZVA (0xE89C)		// Полная мощность гармоники Z.
#define HZPF (0xE89D)		// Коэффициент мощности гармоники Z.
#define HZVHD (0xE89E)	// Гармонические искажения гармоники фазного напряжения Z относительно основной гармоники.
#define HZIHD (0xE89F)	// Гармонические искажения гармоники фазного тока Z относительно основной гармоники.


#define LAST_RWDATA_8bit (0xE7FD)
// #define Reserved 	(0xE7E3)   // Register protection (see the Register Protection section).
// #define Reserved 	(0xE7FE)   // Register protection key (see the Register Protection section).
// #define Reserved 	(0xEBFF)   // This address can be used in manipulating the SS/HSA pin when SPI is chosen as the active port (see the Communication section for details)   //.
//#define CONFIG2 (0xEC01) // Configuration register (see Table 29).



#define HCONFIG (0xE900) 	//Регистр конфигурации гармоническ вычеслений си. табл 54
// коэффицент мощности 
#define APF (0xE902)  		//Коэффициент мощности фазы А.
#define BPF (0xE903) 		//Коэффициент мощности фазы В.
#define CPF (0xE904) 		//Коэффициент мощности фазы С.

#define APERIOD (0xE905)		//Период линии на фазе А напряжения.
#define BPERIOD (0xE906)		//Период линии на фазе В напряжения.
#define CPERIOD (0xE907)		//Период линии на фазе С напряжения.

#define APNOLOAD (0xE908)		// Отсутствие порога нагрузки в трактах данных полной / основной активной мощности. Не записывайте 0xFFFF в этот регистр.
#define VARNOLOAD (0xE909)	//Отсутствие порога нагрузки в тракте данных полной / основной реактивной мощности. Не записывайте 0xFFFF в этот регистр
#define VANOLOAD (0xE90A)		//Нет порога нагрузки в тракте данных полной мощности. Не записывайте 0xFFFF в этот регистр.
#define LAST_ADD (0xE9FE)		// Адрес регистра, к которому был успешно осуществлен доступ во время последней операции чтения / записи.

#define LAST_RWDATA_16bit (0xE9FF) // Содержит данные последней успешной передачи 16-битного регистра.

#define CONFIG3 (0xEA00)	//Регистр конфигурации. См. Таблицу 53.
#define LAST_OP (0xEA01)	//Указывает тип последней успешной операции чтения / записи: чтение или запись.
#define WTHR (0xEA02)		//Пороговое значение, используемое в тракте данных полной / основной активной мощности фазы.
#define VARTHR (0xEA03)	//Пороговое значение, используемое в тракте данных полной / основной реактивной мощности фазы.
#define VATHR (0xEA04)	//Пороговое значение, используемое в тракте данных полной мощности фазы.
#define HX_reg (0xEA08)	// Выбирает индекс гармоники, контролируемой гармоническими вычислениями.
#define HY_reg (0xEA09)	//Выбирает индекс гармоники, контролируемой гармоническими вычислениями.
#define HZ_reg (0xEA0A)	//Выбирает индекс гармоники, контролируемой гармоническими вычислениями.
#define LPOILVL (0xEC00)	//Порог перегрузки по току, используемый в режиме PSM2. См. Таблицу 55, в которой подробно описан регистр.
#define CONFIG2 (0xEC01)  // Регистр конфигурации, используемый в режиме PSM1. См. Таблицу 56.



class ADE7880
{
public:
    /* int init();
    int getEnergyRegisters(float *energyRegVal);
    int getVoltageRegisters(float *voltageRegVal);
    int getCurrentRegisters(float *currentRegVal);
    int writeCalConstants();
    int writeMultipleRegisters();
    int readMultipleRegisters();*/ 

protected:
    virtual int _write16Register(const unsigned int reg, const unsigned int val) = 0;
    virtual int _read32Register(const unsigned int reg) = 0;
	virtual int _write8Register(const unsigned int reg, const uint8_t val) = 0;
	virtual int _write32Register(const unsigned int reg, const uint32_t val) = 0;
    virtual int _read16Register(const unsigned int reg) = 0;
	virtual int _read8Register(const uint8_t reg)= 0;
};

class ADE7880_SPI : public virtual ADE7880
{
public:
    ADE7880_SPI();
    void begin(int8_t sck = SCK, int8_t miso = MISO, int8_t mosi = MOSI, int8_t ss = SS);
    void settings(uint32_t clock = 200000, uint8_t bitOrder = MSBFIRST, uint8_t dataMode = SPI_MODE3);
    void runDsp();
    void stopDsp();
    void write16Register(uint16_t reg, uint16_t val);
	void write8Register(uint16_t reg, uint8_t val);
	void write32Register(uint16_t reg, uint32_t val);
	int32_t read32Register(uint16_t reg);
	int16_t read16Register(uint16_t reg);
	uint8_t read8Register(uint16_t reg);
	
    uint32_t _clock;
    uint8_t _bitOrder;
    uint8_t _dataMode;
    uint8_t _ss;

protected:
    int _write16Register(const unsigned int reg, const unsigned int val);
    int _read32Register(const unsigned int reg);
	int _write8Register(const unsigned int reg, const uint8_t val);
	int _write32Register(const unsigned int reg, const uint32_t val);
    int _read16Register(const unsigned int reg);
	int _read8Register(const uint8_t reg);
	
};

class ADE7880_I2C : public virtual ADE7880
{
public:
    ADE7880_I2C(int addr = ADE7880_ADDR);
    void begin();
    void runDsp();
    void stopDsp();
    void write16Register(uint16_t reg, uint16_t val);
	void write8Register(uint16_t reg, uint8_t val);
	void write32Register(uint16_t reg, uint32_t val);
	int32_t read32Register(uint16_t reg);
	int16_t read16Register(uint16_t reg);
	uint8_t read8Register(uint16_t reg);

protected:
     int _write16Register(const unsigned int reg, const unsigned int val);
    int _read32Register(const unsigned int reg);
	int _write8Register(const unsigned int reg, const uint8_t val);
	int _write32Register(const unsigned int reg, const uint32_t val);
    int _read16Register(const unsigned int reg);
	int _read8Register(const uint8_t reg);

private:
    int _addr;
#ifdef ARDUINO_ARCH_ESP32
    TwoWire i2c = TwoWire(0);
#else
    TwoWire i2c = TwoWire();
#endif
};

#endif