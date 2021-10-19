from datetime import datetime

print("Oh shit here we go again\n")

print("Vou adivinhar sua idade!\n")

ano = int(input('Em que ano nasceu?\n'));

atual = datetime.today().year;

if ano > atual:
    print("\nBlz terminator, vai brincar nn\nhasta la vista baby\n")
else:
    resp = input('Já fez aniversário esse ano?\n')
    idade = atual - ano

    if(idade > 70):
        print("\nO idosinho chegou!")

    if resp[0] == "s" or resp[0] == "S" or resp == 'Já':
        print("Tu tem", (atual - ano), "anos hehe\n")
    else:
        print("Tu tem", (atual - ano - 1), "anos hehe")
