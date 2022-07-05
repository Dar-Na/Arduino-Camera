## Arduino-Camera

W tym projekcie połączyłem wykrywacz twarzy (face detection) i system śledzenia (tracking system).
Kamera internetowa zamontowana na mechanizmie obrotowym jest połączona z komputerem z systemem operacyjnym Windows i zainstalowanym oprogramowaniem OpenCV. Jeśli program wykryje twarz w polu widzenia kamery internetowej, obliczany jest środek twarzy.
Współrzędne X i Y są przesyłane do kontrolera Arduino, który jest podłączony do komputera przez USB. Z kolei kontroler Arduino, zgodnie z otrzymanymi poleceniami, steruje dwoma siłownikami: wzdłuż współrzędnej X oraz wzdłuż współrzędnej Y, tj. zapewniony jest system monitoringu.
