// в библиотеке не реализована работа с 24 бит ригистрами
#include <SPI.h>
#include <ADE7880.h>

/*------------константы-------------*/
const float VLSB = 1;          //константа множителя напряжени, расчет соглано митодике
const float ILSB = 1;          // константа множителя тока,
const float PLSB = 1;          // константа множетеля мгновенной мощности,
const float WLSB = 1;          // константа множетеля накопленной электроэнергии Вт*ч
const float WrLSB = 1;         // константа множетеля накопленной электроэнергии Вар*ч
const float SaLSB = 1;         // константа множетеля мгновенной электроэнергии ВА
const float SahLSB = 1;        // константа множетеля накопленной электроэнергии ВА*ч
const float CLSB = 0.0000305;  // константа множетеля cosf

/*-----------переменные---------------*/
// напряжение среднеквадратичное 
float urms_l1 = 0;
float urms_l2 = 0;
float urms_l3 = 0;
// ток среднеквадратичный
float Irms_l1 = 0;
float Irms_l2 = 0;
float Irms_l3 = 0;
float Irms_N = 0;
// мнгновенная мощность
float Pwatt_l1 = 0;
float Pwatt_l2 = 0;
float Pwatt_l3 = 0;
float Sva_l1 = 0;
float Sva_l2 = 0;
float Sva_l3 = 0;
// косинус f
float cosfL1 = 0;
float cosfL2 = 0;
float cosfL3 = 0;

ADE7880_I2C eic = ADE7880_I2C();
bool flag0 = 1;  // флаг первого запуска накопления
void setup() {

  /* initialisation the serial port to host */
  Serial.begin(9600);
  //initialisation with default I2C pins
  //Serial.println(SDA);
  //Serial.println(SCL);

  delay(100);  // ждем чтоб успела загрузиться ADE

  //   константы конфигурации настройки согласно метод
  eic.write8Register(WTHR, 3);            // пороговый регистр активной энерги
  eic.write8Register(VARTHR, 3);          // пороговый регистр реактивной энергии
  eic.write8Register(VATHR, 3);           // пороговый регистр полной энергии
  eic.write16Register(COMPMODE, 0x01FF);  //  настройка регистра и выбор частоты 50 Гц для фондументальных вычислений
  eic.write32Register(VLEVEL, 0x38000);   // Регистр, используемый в алгоритме вычисления основныхактивных и реактивных мощностей

  // колибровка уселения каналов тока см. методику  водим в hex
  eic.write32Register(AIGAIN, 0x000000);  // по умолчанию 0x000000
  eic.write32Register(BIGAIN, 0x000000);
  eic.write32Register(CIGAIN, 0x000000);
  // колибровка уселения каналов напряжения см. методику
  eic.write32Register(AVGAIN, 0x000000);
  eic.write32Register(BVGAIN, 0x000000);
  eic.write32Register(CVGAIN, 0x000000);
  // колибровка уселения каналов мгновенной активной мощности см. методику
  eic.write32Register(APGAIN, 0x000000);
  eic.write32Register(BPGAIN, 0x000000);
  eic.write32Register(CPGAIN, 0x000000);
  // колибровка частотных изменений и погрешностей см.методику
  eic.write16Register(CF1DEN, 0x000000);
  eic.write16Register(CF2DEN, 0x000000);
  eic.write16Register(CF3DEN, 0x000000);

  //  // колибровка ошибок накопления активной энергии
  eic.write32Register(AWATTOS, 0x000000);
  eic.write32Register(BWATTOS, 0x000000);
  eic.write32Register(CWATTOS, 0x000000);

  // три раза записывем чтоб точно записалось
  eic.write32Register(AIRMSOS, 0x000000);
  eic.write32Register(AIRMSOS, -0x000000);
  eic.write32Register(AIRMSOS, -0x000000);

  delay(100);
}

void loop() {
  if (flag0) {
    eic.runDsp();  // запуск интегратора преоброзований
    flag0 = 0;     // сбрасываем
    Serial.println("Старт!!!");
  }
  
  // записываем  значения
  urms_l1 = eic.read32Register(AVRMS) * VLSB;
  urms_l2 = eic.read32Register(BVRMS) * VLSB;
  urms_l3 = eic.read32Register(CVRMS) * VLSB;

  Irms_l1 = eic.read32Register(AIRMS) * ILSB;
  Irms_l2 = eic.read32Register(BIRMS) * ILSB;
  Irms_l3 = eic.read32Register(CIRMS) * ILSB;

  Pwatt_l1 = eic.read32Register(AWATT) * PLSB;
  Pwatt_l2 = eic.read32Register(BWATT) * PLSB;
  Pwatt_l3 = eic.read32Register(CWATT) * PLSB;

  Sva_l1 = eic.read32Register(AVA) * SaLSB;
  Sva_l2 = eic.read32Register(BVA) * SaLSB;
  Sva_l3 = eic.read32Register(CVA) * SaLSB;

  cosfL1 = eic.read16Register(APF) * CLSB;
  cosfL2 = eic.read16Register(BPF) * CLSB;
  cosfL3 = eic.read16Register(CPF) * CLSB;

  // вываодим в сериал
  Serial.println(F("Urms:"));
  Serial.print(F("L1="));
  Serial.println(urms_l1, 4);
  Serial.print(F("L2="));
  Serial.println(urms_l2, 4);
  Serial.print(F("L3="));
  Serial.println(urms_l3, 4);
  
  Serial.println(F("Irms:"));
  Serial.print(F("L1="));
  Serial.println(Irms_l1, 4);
  Serial.print(F("L2="));
  Serial.println(Irms_l2, 4);
  Serial.print(F("L3="));
  Serial.println(Irms_l3, 4);
  //
  Serial.println(F("Pwatt:"));
  Serial.print(F("L1="));
  Serial.println(Pwatt_l1);
  Serial.print(F("L2="));
  Serial.println(Pwatt_l2);
  Serial.print(F("L3="));
  Serial.println(Pwatt_l3);
  //
  Serial.println(F("Sva:"));
  Serial.print(F("L1="));
  Serial.println(Sva_l1);
  Serial.print(F("L2="));
  Serial.println(Sva_l2);
  Serial.print(F("L3="));
  Serial.println(Sva_l3);

  Serial.println(F("CosF:"));
  Serial.print(F("L1="));
  Serial.println(cosfL1);
  Serial.print(F("L2="));
  Serial.println(cosfL2);
  Serial.print(F("L3="));
  Serial.println(cosfL3);

  delay(1000);
}


