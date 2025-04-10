# Oled_Reloj_NTP

Este código, es un simple ejemplo de como hacer un reloj en una pantalla SSD1306 utilizando la librería U8g2. Este ejemplo está preparado para un ESP32 que en este caso es un NodeMCU. La conexiones del la pantalla con la placa son las siguientes:

| ESP32  | OLED |
| ------ |:----:|
| 3,3V   | VCC  |
| GND    | GND  |
| pin 21 | SDA  |
| pin 22 | SCL  |

Para coger la hora usamos un servicio NTP al que nos conectamos para saber la hora y mostrarla en la pantalla.

Espero que os sirva como ejemplo simple para hacer proyectos mucho más ambiciosos.
