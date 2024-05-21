import serial
from Adafruit_IO import Client
import time

#Conexión con AdaFruit_IO
dashboard = Client('vel22788','aio_uXPQ70EZXBMb12idUB62fTwflRlz')
#Conexión con ATMEGA328P
arduino=serial.Serial(port='COM3',baudrate=9600,timeout=None)

datos=[0,0,0,0]
memoria1=[0,0,0,0]
memoria2=[0,0,0,0]
memoria3=[0,0,0,0]
memoria4=[0,0,0,0]

while True:
    activo = arduino.read()
    print (activo)

    if (activo==b'S'):
        #Garra
        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        print("Garra: ", num)
        dashboard.send('servo3',int(num))

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        print("PARTE B: ", num)
        dashboard.send('servo2',int(num))

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        print("PARTE A: ", num)
        dashboard.send('servo1',int(num))

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        print("BASE: ", num)
        dashboard.send('servo',int(num))


        servo_base=dashboard.receive('servo')
        servo_a=dashboard.receive('servo1')
        servo_b=dashboard.receive('servo2')
        servo_garra=dashboard.receive('servo3')

        datos[0]=int(servo_base.value)
        datos[1]=int(servo_a.value)
        datos[2]=int(servo_b.value)
        datos[3]=int(servo_garra.value)

        #M1

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        memoria1[0]=int(num)

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        memoria1[1]=int(num)

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        memoria1[2]=int(num)

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        memoria1[3]=int(num)
        print("Memoria1: ",memoria1)
        #M2

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        memoria2[0]=int(num)

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        memoria2[1]=int(num)

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        memoria2[2]=int(num)

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        memoria2[3]=int(num)
        print("Memoria2: ",memoria2)
        
        #M3

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        memoria3[0]=int(num)

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        memoria3[1]=int(num)

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        memoria3[2]=int(num)

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        memoria3[3]=int(num)
        print("Memoria3: ",memoria3)
        #M4

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        memoria4[0]=int(num)

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        memoria4[1]=int(num)

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(4)
        memoria4[2]=int(num)

        n1=arduino.read().decode('utf-8')
        n2=arduino.read().decode('utf-8')
        n3=arduino.read().decode('utf-8')
        num=str(n1+n2+n3).zfill(3)
        memoria4[3]=int(num)
        print("Memoria4: ",memoria4)

        dashboard.send('memoria-1',str(memoria1))
        dashboard.send('memoria2',str(memoria2))
        dashboard.send('memoria3',str(memoria3))
        dashboard.send('memoria4',str(memoria4))

    else:
        

        
        servo_base=dashboard.receive('servo')
        servo_a=dashboard.receive('servo1')
        servo_b=dashboard.receive('servo2')
        servo_garra=dashboard.receive('servo3')
        boton=dashboard.receive('boton')

        print(boton.value)

        if (int(servo_base.value)!=int(datos[0])):
                arduino.write("1".encode('utf-8'))
                arduino.write(str((servo_base.value).zfill(3)).encode('utf-8'))
                datos[0]=int(servo_base.value)
                print("Base nuevo :",str((servo_base.value).zfill(3)).encode('utf-8'))
        elif (int(servo_a.value)!=int(datos[1])):
                arduino.write("2".encode('utf-8'))
                arduino.write(str((servo_a.value).zfill(3)).encode('utf-8'))
                datos[1]=int(servo_a.value)
                print("A nuevo:",str((servo_a.value).zfill(3)).encode('utf-8'))
        elif (int(servo_b.value)!=datos[2]):
                arduino.write("3".encode('utf-8'))
                arduino.write(str((servo_b.value).zfill(3)).encode('utf-8'))
                datos[2]=int(servo_b.value)
                print("B nuevo:",str((servo_b.value).zfill(3)).encode('utf-8'))
        elif (int(servo_garra.value)!=datos[3]):
                arduino.write("4".encode('utf-8'))      
                arduino.write(str((servo_garra.value).zfill(3)).encode('utf-8'))
                datos[3]=int(servo_garra.value)
                print("Garra nuevo:",str((servo_garra.value).zfill(3)).encode('utf-8'))
        else:
            arduino.write("0".encode('utf-8'))

        if (int(boton.value)==1):
                print("Guardar")
                dashboard.send('boton',int(0))
                arduino.write("G".encode('utf-8'))
                espacio=int(dashboard.receive('memoria').value)
                print("Espacio en memoria: ",espacio)
                if (espacio==1):
                        arduino.write(str(espacio).encode('utf-8'))
                if (espacio==2):
                    arduino.write(str(espacio).encode('utf-8'))
                if (espacio==3):
                    arduino.write(str(espacio).encode('utf-8'))
                if (espacio==4):
                    arduino.write(str(espacio).encode('utf-8'))
        if (int(boton.value)==2):
            print("Cargar")
            dashboard.send('boton',int(0))
            arduino.write("C".encode('utf-8'))
            espacio=int(dashboard.receive('memoria').value)
            if (espacio==1):
                arduino.write(str(espacio).encode('utf-8'))
            if (espacio==2):
                    arduino.write(str(espacio).encode('utf-8'))
            if (espacio==3):
                    arduino.write(str(espacio).encode('utf-8'))
            if (espacio==4):
                    arduino.write(str(espacio).encode('utf-8'))

            n1=arduino.read().decode('utf-8')
            while (n1=='P'):
                n1=arduino.read().decode('utf-8')
            n2=arduino.read().decode('utf-8')
            while (n2=='P'):
                n2=arduino.read().decode('utf-8')
            n3=arduino.read().decode('utf-8')
            while (n3=='P'):
                n3=arduino.read().decode('utf-8')
            num=str(n1+n2+n3).zfill(3)
            print("Garra: ", num)
            dashboard.send('servo3',int(num))

            n1=arduino.read().decode('utf-8')
            n2=arduino.read().decode('utf-8')
            n3=arduino.read().decode('utf-8')
            num=str(n1+n2+n3).zfill(3)
            print("PARTE B: ", num)
            dashboard.send('servo2',int(num))

            n1=arduino.read().decode('utf-8')
            n2=arduino.read().decode('utf-8')
            n3=arduino.read().decode('utf-8')
            num=str(n1+n2+n3).zfill(3)
            print("PARTE A: ", num)
            dashboard.send('servo1',int(num))

            n1=arduino.read().decode('utf-8')
            n2=arduino.read().decode('utf-8')
            n3=arduino.read().decode('utf-8')
            num=str(n1+n2+n3).zfill(3)
            print("BASE: ", num)
            dashboard.send('servo',int(num))
        if (int(boton.value)==3):
            print("Salir")
            dashboard.send('boton',int(0))
            arduino.write("Q".encode('utf-8'))
        