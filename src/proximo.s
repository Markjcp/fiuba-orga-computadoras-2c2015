# proximo.s : 	Evalua dos strings para ver si son equivalentes o no.
# 				No toma en cuenta mayusculas y minusculas para la evaluacion.
#
# Variables: 
#				- a0 -> dir del array
#				- a1 -> int i (fila)
#				- a2 -> int j (columna)
#				- a3 -> regla
# Auxiliares:
#				- t0 -> N (tamanio de la matriz cuadrada)
#				- t1 -> dir inicial de la fila que necesito
#				- t2 -> Elemento hermano (derecha o izq). En el bit necesario esta el dato y desp todos 0
#				- t3 -> puntero para avanzar de a bytes en la fila
#				- t4 -> j (va decrementando)
#				- t5 -> aux
#				- t6 -> Si t2 tiene valor util o no
# 				- t7 -> El elemento que necesito

.text
.align 2
.globl proximo


proximo:		subu sp, sp, 16 # Se crea el SRA 16 y LTA 0 y ABA 0 = 16 bytes
				sw ra, 8(sp)
		        sw fp, 4(sp)
		        sw gp, 0(sp)
		        move fp, sp

		        #Obtengo el valor de N
	        	lw t0, 32(sp) # t0 = N
		        
		        #Obtengo la fila que necesito
		        mul t1, a1, t0 # t1 = i * N
		        addu t1, t1, a1 # t1 = a + (i * N)

	        	#Busco la columna
	        	#En caso de que busco el ultimo elemento, me quedo con el primer byte que contiene al hno derecho
	        	bne sig, t0, a2 # Si (j == N) me quedo con el byte de la primer columna
				addu t6, 1, zero # Marco en t6 si utilizo t2 o no
				lw t2, (t1) # t2 = 1er byte de la fila
				srl t2, t2, 7 # Dejo en el bit menos significativo el valor de la matriz

sig:			addu t3, t1, zero # t3 = t1
				addu t4, a2, zero # t4 = j

				#En caso de que busco al primer elemento, tambien necesito al ultimo de la fila que tiene al hno izq
				bge loop, t4, 8 # si (j >= 8) loop. Osea no necesito el 1er byte
				lw t2, (t3) # t2 = 1er byte. Necesito el 1er byte
				addu t6, 1, zero # Marco en t6 si utilizo t2 o no
				
				#Me fijo si tengo que buscar el ultimo valor de la fila o no
				bne sig2, t4, zero # si (j == 0) me falta el hno izquierdo que esta al final de la fila
				addu t4, t0, zero # Guardo en t4 el valor de N, para buscar hasta el final de la fila

sig2:			#Muevo a los bit menos significativos los bit que necesito
				subu t5, 6, a2 # Busco cuanto tengo que correr el valor de t2
				srl t2, t2, t5 # Dejo en los bits menos significativos a los bit que necesito

loop:			subu t4, t4, 8 # j = j - 8 -> Decremento 'j' (que esta en copiado en t4)
				addu t3, t3, 8 # a = a + 8 -> Aumento 'a' (que esta copiado en t3)
				bgt loop, t4, 8 # si (j > 8) sigo buscando

				lw t7, (t3) # t7 = el byte que tiene mi dato
				#Muevo a los bit menos significativos los bit que necesito
				subu t5, 6, t4 # Busco cuanto tengo que correr el valor de t2
				srl t2, t2, t5 # Dejo en los bits menos significativos a los bit que necesito

				bne sig3, t6, zero # Si (t6 == 0), osea uso a t2, guardo en un registro el valor de los 3 elementos
				and t7, t7, t2 # Guardo en t7 al elemento completo

sig3:			#Hay que buscar la regla que corresponde ahora