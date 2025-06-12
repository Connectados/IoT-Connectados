import network
import socket
from machine import Pin
import time

# WiFi
ssid = 'INFINITUM29AE'
password = 'GMmtWz9N3t'

# Pines
led1 = Pin(15, Pin.OUT)
led2 = Pin(16, Pin.OUT)
led3 = Pin(17, Pin.OUT)
motor = Pin(18, Pin.OUT)

# WiFi conexión
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)

print("Conectando al WiFi...", end="")
while not wlan.isconnected():
    time.sleep(1)
    print(".", end="")
print("\nConectado!")
ip = wlan.ifconfig()[0]
print("IP:", ip)

# Página web con botones
def web_page():
    estados = {
        "LED 1": "ON" if led1.value() else "OFF",
        "LED 2": "ON" if led2.value() else "OFF",
        "LED 3": "ON" if led3.value() else "OFF",
        "Motor": "ON" if motor.value() else "OFF",
    }

    html = f"""<!DOCTYPE html>
<html>
<head>
  <title>Control Pico W</title>
  <meta charset="UTF-8">
  <style>
    body {{ font-family: sans-serif; text-align: center; margin-top: 40px; background-color: #f0f0f0; }}
    h1 {{ color: #333; }}
    button {{ padding: 15px 30px; margin: 10px; font-size: 18px; background-color: #008CBA; color: white; border: none; border-radius: 5px; }}
    button:hover {{ background-color: #005f6a; }}
    .status {{ margin: 5px; font-weight: bold; }}
  </style>
</head>
<body>
  <h1>Panel de Control</h1>
  <div class="status">LED 1: {estados['LED 1']}</div>
  <form action="/toggle1"><button>Encender/Apagar LED 1</button></form>
  
  <div class="status">LED 2: {estados['LED 2']}</div>
  <form action="/toggle2"><button>Encender/Apagar LED 2</button></form>
  
  <div class="status">LED 3: {estados['LED 3']}</div>
  <form action="/toggle3"><button>Encender/Apagar LED 3</button></form>
  
  <div class="status">Motor: {estados['Motor']}</div>
  <form action="/toggle_motor"><button>Encender/Apagar Motor</button></form>
</body>
</html>"""
    return html

# Servidor
addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]
s = socket.socket()
s.bind(addr)
s.listen(1)

print("Servidor listo en http://" + ip)

# Loop del servidor
while True:
    try:
        cl, addr = s.accept()
        print('Conexión desde', addr)
        request = cl.recv(1024).decode()
        print("Solicitud:", request)

        if '/toggle1' in request:
            led1.toggle()
        elif '/toggle2' in request:
            led2.toggle()
        elif '/toggle3' in request:
            led3.toggle()
        elif '/toggle_motor' in request:
            motor.toggle()

        response = web_page()
        cl.sendall('HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n'.encode())
        cl.sendall(response.encode())
        cl.close()

    except Exception as e:
        print("Error:", e)
