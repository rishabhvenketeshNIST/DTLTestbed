#!/usr/bin/python
import socket
from time import sleep

def check(s: bytes, expect):
    print(s.decode())
    assert(s.startswith(expect))

# Allow 60 seconds for ursim to start
s = None
while True:
    try:
        s = socket.create_connection(("192.168.56.101", 29999), 60)
        break
    except KeyboardInterrupt:
        exit()
    except Exception:
        print("Could not connect, retrying in 1 second...")
        sleep(1)

check(s.recv(128), b"Connected: Universal Robots Dashboard Server")
sleep(2)
s.send(b"power on\n")
check(s.recv(128), b"Powering on")
s.send(b"brake release\n")
check(s.recv(128), b"Brake releasing")
s.send(b"stop\n")
check(s.recv(128), b"Stopped")
s.close()