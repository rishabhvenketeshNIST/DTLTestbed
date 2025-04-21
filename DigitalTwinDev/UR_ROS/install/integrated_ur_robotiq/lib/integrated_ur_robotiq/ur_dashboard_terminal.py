#!/usr/bin/python
import sys
import socket
from time import sleep

if __name__ == "__main__":
    ip = "192.168.56.101" # default for URSim
    for item in sys.argv:
        if item.startswith("ip:="):
            ip = item[4:]
    # Allow 60 seconds for ursim to start
    s = None
    while True:
        try:
            s = socket.create_connection((ip, 29999), 60)
            break
        except KeyboardInterrupt:
            exit()
        except Exception:
            print("Could not connect, retrying in 1 second...")
            sleep(1)
    s.setblocking(True)
    assert(s.recv(128).startswith(b"Connected: Universal Robots Dashboard Server"))
    sleep(2)
    s.send(b"power on\n")
    assert(s.recv(128).startswith(b"Powering on"))
    s.send(b"brake release\n")
    assert(s.recv(128).startswith(b"Brake releasing"))
    print("Robot is powered on an ready to receive commands:")
    while True:
        line = ""
        try:
            line = input("> ").lstrip()
        except:
            break
        if (line.startswith("exit") or line.startswith("quit")):
            break
        cmd = "" + line + "\n"
        s.send(cmd.encode())
        msg = s.recv(1024)
        print(msg.decode(), end="")
        s.setblocking(False)
        while True:
            msg = None
            try:
                msg = s.recv(1024)
            except:
                pass
            if msg:
                print(msg.decode(), end="")
            else:
                break
        s.setblocking(True)

    s.close()
