Библитека для работы  с многофазной многофункциональной ИС ADE7880 для измерения энергии совместима Arduino IDE.

-Библиотека умеет работать с 8,16,32 битными ригистрами чтение, зпись 

-Методы работы и калибровки ищите в инструкциях от производителя  [AN-1171](https://docs.yandex.ru/docs/view?tm=1726738266&tld=ru&lang=en&name=articles-app-notes-files-calibrating-a-three-phase-energy-meter-based-on-the-ade7880-1364230154.pdf&text=AN-1171%20ade7880&url=https%3A%2F%2Fwww.eeweb.com%2Fwp-content%2Fuploads%2Farticles-app-notes-files-calibrating-a-three-phase-energy-meter-based-on-the-ade7880-1364230154.pdf&lr=10&mime=pdf&l10n=ru&sign=53df0ae35fd8c4c012808b0ed12c72b3&keyno=0&nosw=1&serpParams=tm%3D1726738266%26tld%3Dru%26lang%3Den%26name%3Darticles-app-notes-files-calibrating-a-three-phase-energy-meter-based-on-the-ade7880-1364230154.pdf%26text%3DAN-1171%2Bade7880%26url%3Dhttps%253A%2F%2Fwww.eeweb.com%2Fwp-content%2Fuploads%2Farticles-app-notes-files-calibrating-a-three-phase-energy-meter-based-on-the-ade7880-1364230154.pdf%26lr%3D10%26mime%3Dpdf%26l10n%3Dru%26sign%3D53df0ae35fd8c4c012808b0ed12c72b3%26keyno%3D0%26nosw%3D1), [ADE7880](https://www.alldatasheet.com/datasheet-pdf/pdf/455853/AD/ADE7880.html) схемы [UG-356](https://docs.yandex.ru/docs/view?tm=1726739689&tld=ru&lang=en&name=da-EVAL-ADE7880EBZ.pdf&text=UG-356&url=https%3A%2F%2Fwww.infinite-electronic.ru%2Fdatasheet%2Fda-EVAL-ADE7880EBZ.pdf&lr=10&mime=pdf&l10n=ru&sign=29c2149626ff59425dbd9381acb842d6&keyno=0&nosw=1&serpParams=tm%3D1726739689%26tld%3Dru%26lang%3Den%26name%3Dda-EVAL-ADE7880EBZ.pdf%26text%3DUG-356%26url%3Dhttps%253A%2F%2Fwww.infinite-electronic.ru%2Fdatasheet%2Fda-EVAL-ADE7880EBZ.pdf%26lr%3D10%26mime%3Dpdf%26l10n%3Dru%26sign%3D29c2149626ff59425dbd9381acb842d6%26keyno%3D0%26nosw%3D1)
<a id="init"></a>
## Инициализация
```cpp
// SPI
ADE7880_SPI eic = ADE7880_SPI();    //CS-по умолчанию
// в void setup()
eic.begin();         // инициализация
 eic.runDsp();       // запускает интегратор преобразований можно разово запускать в loop

```
<a id="usage"></a>
## Использование
```cpp
// ===== СЕРВИС =====
// запись настроек как правило необходимо проводить в void setup() и последний любой регистр записать 3 раза для точного сохранения последнего регистра
// запись 8 бит
eic.write8Register(x1, x2);            // x1- имя регистра, х2- необходимое значение в HEX для записи калибровки и т.д
eic.write16Register(x1, x2);            // x1- имя регистра, х2- необходимое значение в HEX для записи калибровки и т.д
eic.write32Register(x1, x2);            // x1- имя регистра, х2- необходимое значение в HEX для записи калибровки и т.д
// чтение производим в функции void loop() накопление интегратора может состовлять разное время см. инструкции по ADE7880
eic.stopDsp();       // остановка интегратора преобразований  в loop все измерения будут остановлены для повторного измерения необходимо вызвать eic.runDsp(); 
eic.read8Register(x1);            // x1- имя регистра которое нужно считать
eic.read16Register(x1);            // x1- имя регистра которое нужно считать
eic.read32Register(x1);            // x1- имя регистра которое нужно считать

```
## Пример чтения в переменную
```cpp
float urms_l1=eic.read32Register(AVRMS); // считываем значение в переменную
```
примеры приведены в папке examples
-все имена регистров совподают с листом приведенным в инструкции ADE7880
также необходимо  провести соглосование каналов АЦП по инструкции  AN-1171
