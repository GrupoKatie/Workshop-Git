import time
print('Hello World')
print('Testando o push')
hello_world = True
quantidade_HW = int(input("quantos ' Hello World's ' você quer que apareça ? \n"))
contador_HW = 0 
while hello_world : 
    time.sleep(1)
    print("Hello World")
    contador_HW += 1
    if contador_HW == quantidade_HW:
        hello_world = False
