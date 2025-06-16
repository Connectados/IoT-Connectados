from machine import ADC, Pin
import time

# Configurar fotoresistencia en ADC0 (GP26)
ldr = ADC(26)

# LEDs en GPIO 14 y 15
led1 = Pin(14, Pin.OUT)
led2 = Pin(15, Pin.OUT)

# Umbral de luz (ajústalo según tus valores)
UMBRAL = 200  # Por ejemplo, si >2000 hay mucha luz

while True:
    luz = ldr.read_u16()  # Valor de 0 a 65535
    luz = luz >> 4        # Escalamos a 12 bits (0-4095) como referencia

    print("Luz:", luz)

    if luz < UMBRAL:
        # Si hay poca luz → encender LEDs
        led1.value(1)
        led2.value(1)
    else:
        # Si hay suficiente luz → apagar LEDs
        led1.value(0)
        led2.value(0)

    time.sleep(1)
