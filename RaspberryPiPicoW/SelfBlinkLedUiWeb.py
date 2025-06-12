import network
import socket
from machine import Pin
import time

# Credenciales WiFi
ssid = 'INFINITUM29AE'
password = 'GMmtWz9N3t'

# LED en GPIO 25 (LED interno)
led = Pin("LED", Pin.OUT)

# Conectar al WiFi
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

# Página HTML
def web_page():
    estado = "ON" if led.value() else "OFF"
    html = f"""<!DOCTYPE html>
<html>
<head>
  <title>Pico W LED</title>
  <meta charset="UTF-8">
  <style>
    body {{ font-family: sans-serif; text-align: center; margin-top: 50px; }}
    button {{ padding: 15px 30px; font-size: 20px; }}
  </style>
</head>
<body>
  <h1>LED: {estado}</h1>
  <form action="/toggle">
    <button type="submit">Encender / Apagar</button>
  </form>
</body>
</html>"""
    return html

# Crear socket y escuchar
addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]
s = socket.socket()
s.bind(addr)
s.listen(1)

print("Servidor listo en http://" + ip)

# Ciclo principal del servidor
while True:
    try:
        cl, addr = s.accept()
        print('Cliente conectado desde', addr)
        request = cl.recv(1024).decode()
        print("Solicitud:", request)

        if "/toggle" in request:
            led.toggle()

        response = web_page()
        cl.sendall('HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n'.encode())
        cl.sendall(response.encode())
        cl.close()

    except Exception as e:
        print("Error:", e)
