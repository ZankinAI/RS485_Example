# RS485_Example
Пример реализации протокола связи RS-485.

Реализован на базе МК STM32F407VET.

Среда разработки - CubeIDE 1.7.0.

Файлы реализации протокола находятся в папке "RS485Module".

Канальный уровень реализован в папке "portserial".
Для портирования на другую платформу необходимо внести изменения в файлы "portserial.c" и "port_timer.c" согласно комментариям.

Реализация транспортного уровня находится в папке "protocol".

Реализация прикладного  уровня находится в папке "rs_app".

UART настроен на работу со следующими параметрами:
cкорость - 115200;
длина слова - 8;
четность - NONE;
стоп бит - 1.

В примере реализован опрос датчиков с частотой 100Гц.

