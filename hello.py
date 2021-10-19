import time
print('Hello World')
print('Testando o push')
def funcionalidade_1(quantidade_HW):
    hello_world = True
    contador_HW = 0 
    while hello_world : 
        time.sleep(1)
        print("Hello World")
        contador_HW += 1
        if contador_HW == quantidade_HW:
            hello_world = False
funcionalidade_1(25)