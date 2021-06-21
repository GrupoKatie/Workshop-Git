def campeonato():
	aux = 0
	comp = 0
	voce = 0
	while(aux < 3):
		print("**** Rodada", aux+1, "****\n")
		q_pecas = int(input("Quantas peças? "))
		limite = int(input("Limite de peças por jogada? "))
		voce_ganhou = False
		computador_ganhou = False
		div = limite+1
		if(q_pecas % div == 0):
			print("\nVoce começa!\n")
			while(q_pecas > 0):
				usuario = usuario_escolhe_jogada(q_pecas, limite)
				q_pecas -= usuario
				if(q_pecas > 0):
					if(q_pecas == 1):
						print("Agora resta apenas uma peça no tabuleiro.\n")
					else:
						print("Agora restam", q_pecas, "peças no tabuleiro.\n")
					computador = computador_escolhe_jogada(q_pecas, limite)
					q_pecas -= computador
					if(q_pecas > 0):
						if(q_pecas == 1):
							print("Agora resta apenas uma peça no tabuleiro.\n")
						else:
							print("Agora restam", q_pecas, "peças no tabuleiro.\n")
					else:
						computador_ganhou = True
				else:
					voce_ganhou = True
			if(computador_ganhou == True):
				print("Fim do jogo! O computador ganhou!\n")
				comp += 1
			else:
				print("Fim do jogo! Voce ganhou!\n")
				voce += 1
		else:
			print("\nComputador começa!\n")
			while(q_pecas > 0):
				computador = computador_escolhe_jogada(q_pecas, limite)
				q_pecas -= computador
				if(q_pecas > 0):
					if(q_pecas == 1):
						print("Agora resta apenas uma peça no tabuleiro.\n")
					else:
						print("Agora restam", q_pecas, "peças no tabuleiro.\n")
					usuario = usuario_escolhe_jogada(q_pecas, limite)
					q_pecas -= usuario
					if(q_pecas > 0):
						if(q_pecas == 1):
							print("Agora resta apenas uma peça no tabuleiro.\n")
						else:
							print("Agora restam", q_pecas, "peças no tabuleiro.\n")
					else:
						voce_ganhou = True
				else:
					computador_ganhou = True
			if(computador_ganhou == True):
				print("Fim do jogo! O computador ganhou!\n")
				comp += 1
			else:
				print("Fim do jogo! Voce ganhou!\n")
				voce += 1
		aux += 1
	print("**** Final do campeonato! ****\n")
	print("Placar: Voce", voce, "X", comp, "Computador")

def partida():
	q_pecas = int(input("Quantas peças? "))
	limite = int(input("Limite de peças por jogada? "))
	voce_ganhou = False
	computador_ganhou = False
	div = limite+1
	if(q_pecas % div == 0):
		print("\nVoce começa!\n")
		while(q_pecas > 0):
			usuario = usuario_escolhe_jogada(q_pecas, limite)
			q_pecas -= usuario
			if(q_pecas > 0):
				if(q_pecas == 1):
					print("Agora resta apenas uma peça no tabuleiro.\n")
				else:
					print("Agora restam", q_pecas, "peças no tabuleiro.\n")
				computador = computador_escolhe_jogada(q_pecas, limite)
				q_pecas -= computador
				if(q_pecas > 0):
					if(q_pecas == 1):
						print("Agora resta apenas uma peça no tabuleiro.\n")
					else:
						print("Agora restam", q_pecas, "peças no tabuleiro.\n")
				else:
					computador_ganhou = True
			else:
				voce_ganhou = True
		if(computador_ganhou == True):
			print("Fim do jogo! O computador ganhou!")
		else:
			print("Fim do jogo! Voce ganhou!")
	else:
		print("\nComputador começa!\n")
		while(q_pecas > 0):
			computador = computador_escolhe_jogada(q_pecas, limite)
			q_pecas -= computador
			if(q_pecas > 0):
				if(q_pecas == 1):
					print("Agora resta apenas uma peça no tabuleiro.\n")
				else:
					print("Agora restam", q_pecas, "peças no tabuleiro.\n")
				usuario = usuario_escolhe_jogada(q_pecas, limite)
				q_pecas -= usuario
				if(q_pecas > 0):
					if(q_pecas == 1):
						print("Agora resta apenas uma peça no tabuleiro.\n")
					else:
						print("Agora restam", q_pecas, "peças no tabuleiro.\n")
				else:
					voce_ganhou = True
			else:
				computador_ganhou = True
		if(computador_ganhou == True):
			print("Fim do jogo! O computador ganhou!")
		else:
			print("Fim do jogo! Voce ganhou!")

def usuario_escolhe_jogada(n, m):
	jogada = int(input("Quantas peças você vai tirar? "))
	while(jogada > m or jogada <= 0 or n <= m):
		print("\nOops! Jogada inválida! Tente de novo.\n")
		jogada = int(input("Quantas peças você vai tirar? "))
	else:
		if(jogada == 1):
			print("\nVocê tirou uma peça.")
		else:
			print("\nVocê tirou", jogada, "peças.")
	return jogada

def computador_escolhe_jogada(n, m):
	aux = m+1
	tirar = 1
	achei = False
	while (tirar <= m) and (achei == False):
		if((n - tirar) % aux == 0):
			achei = True
		else:
			tirar += 1
	if achei == False:
		tirar = m
	if(tirar == 1):
		print("O computador tirou uma peça.")
	else:
		print("O computador tirou", tirar, "peças.")
	return tirar

print("Bem-vindo ao jogo do NIM! Escolha:\n")
print("1 - para jogar uma partida isolada")
print("2 - para jogar um campeonato\n")

escolha = int(input())

if escolha == 1:
	print("Voce escolheu uma partida isolada!\n")
	partida()
elif escolha == 2:
	print("Voce escolheu um campeonato!\n")
	campeonato()