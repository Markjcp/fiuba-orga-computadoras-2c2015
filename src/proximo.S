#include <mips/regdef.h>
#include <sys/syscall.h>

# proximo.s : 	Devuelve el estado del elemento en la proxima iteracion
#
# Parametros: 
#				- a0 -> dir del array
#				- a1 -> int i (fila)
#				- a2 -> int j (columna)
#				- a3 -> regla
# Auxiliares:
#				- t0 -> N (tamanio de la matriz cuadrada)
#				- t1 -> dir inicial de la fila que necesito
#				- t2 -> direccion bloque izq
#				- t3 -> direccion bloque
#				- t4 -> direccion bloque der
#				- t5 ->	aux
#				- t6 -> bloque izq
# 				- t7 -> bloque 
#				- t8 -> bloque der
#				- t9 -> regla

.text
.align 2
.globl proximo
.ent proximo


proximo:		subu sp, sp, 16 # Se crea el SRA 16 y LTA 0 y ABA 0 = 16 bytes
				sw ra, 8(sp)
		        sw $fp, 4(sp)
		        sw gp, 0(sp)
		        move $fp, sp

		        #Obtengo el valor de N
	        	lw t0, 32(sp) # t0 = N

	        	#Guardo la regla en t9
				addu t9, zero, a3 # t9 = regla
		        
		        #Obtengo la fila que necesito
		        subu t1, t0, zero # t1 = N
		        mul t1, a1, t1 # t1 = i * N
		        mul t1, t1, 8 # t1 = i * N * 8
		        addu t1, t1, a0 # t1 = a + [i * N]

	        	#Guardo el numero de bloque en cuestion
	        	addu t3, a2, zero # t3 = j

        		#Si estoy al inicio del bloque, el hno izquierdo esta en el bloque anterior
        		beqz a2, faltaHnoIzq

        		#Si estoy al final del bloque, necesito al hno derecho que esta en el bloque siguiente
        		subu t5, t0, 1 # t5 = N - 1
        		beq a2, t5, faltaHnoDer

        		#Si estoy en el medio del bloque, tengo los hnos que necesito
        		b tengoLosHnos

faltaHnoIzq:	#En t4 guardo el ultimo nro de bloque
				subu t2, t0, 1 # t2 = N - 1
				addu t4, t3, 1 # t4 = 1
				b obtenerBloque # Voy a obtener el bloque

faltaHnoDer:	#En t4 guardo el primer nro de bloque
				subu t2, t3, 1 # t2 = N - 2
				addu t4, zero, zero # t4 = 0
				b obtenerBloque # Voy a obtener el bloque

tengoLosHnos:	#Guardo los hnos
				subu t2, t3, 1 # t2 = t3 - 1
				addu t4, t3, 1 # t4 = t3 + 1
				b obtenerBloque # Voy a obtener el bloque

obtenerBloque:	mul t2, t2, 8 # t2 = t2 * 8 -> Dir del bloque
				addu t5, t2, t1 # t5 = dir del bloque + inicio de la fila de matriz
				lb t6, 0(t5) # t6 = el bloque izquierdo
				sll t6, t6, 2 # Corro a donde necesito al hno izq

				mul t3, t3, 8 # t3 = t3 * 8 -> Dir del bloque
				addu t5, t3, t1 # t5 = dir del bloque + inicio de la fila de matriz
				lb t7, 0(t5) # t7 = el bloque en cuestion
				sll t7, t7, 1 # Corro a donde necesito al bit en cuestion

				mul t4, t4, 8 # t4 = t4 * 8 -> Dir del bloque
				addu t5, t4, t1 # t5 = dir del bloque + inicio de la fila de matriz
				lb t8, 0(t5) # t8 = el bloque derecho

				#Uno a los 3 elementos en 1 para despues buscar la regla
				or t5, t6, t7
				or t5, t5, t8

aplicarRegla:	# Hay que aplicar la regla
				srl t9, t9, 1 # me quedo en el bit menos significativo el dato que necesito
				subu t5, t5, 1 # t5 = t5 - 1
				bne t5, zero, aplicarRegla
				and t9, t9, 1 # pongo el resto en 0

devuelvoRes:	addu v0, t9, zero # v0 = estado de la proxima iteracion
				
salir:			lw ra, 8(sp)
		        lw $fp, 4(sp)
		        lw gp, 0(sp)
		        addu sp, sp, 16
		        jr ra
.end			proximo

