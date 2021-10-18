# Ambrosio é um cara folgado que sempre te pede para desenvolver aplicações de graça para ele.
# Ele também acredita que numa mercearia só devem existir 4 produtos.

mercearia_ambrosio = {1: 5.30, 2: 6.00, 3: 3.20, 4: 2.50}

cod_produto = int(input())
quant_produto = int(input())

total = quant_produto * mercearia_ambrosio[cod_produto]

if total >= 40.0 or quant_produto >= 15:
    desconto = total * 0.15
    total_pagar = total - desconto

else:
    total_pagar = total

print(f"R$ {total_pagar:.2f}")