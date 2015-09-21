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
#				- t2 -> Nro de bloque de 8 bits: cociente(j / 8)
#				- t3 -> Posicion adentro del bloque: resto (j / 8)
#				- t4 -> direccion del bloque hno
#				- t5 ->	aux
#				- t6 -> bloque hno
# 				- t7 -> bool: necesito al hno o no
#				- t8 -> bloque ppal donde esta mi elemento
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
		        
		        #Obtengo la fila que necesito
		        mul t1, a1, t0 # t1 = i * N
		        addu t1, t1, a0 # t1 = a + (i * N)

	        	#Busco la columna
	        	divu a1, 8 # en 'lo' guardo el cociente de i / 8 y en 'hi' guardo el resto
	        	#Obtengo el nro de bloque de 8 bits
	        	mfhi t2 # t2 = resto(i / 8)
	        	divu a2, 8 # en 'lo' guardo el cociente de j / 8 y en 'hi' guardo el resto
	        	#Adentro del bloque, busco la posicion de mi dato
	        	mfhi t3 # t3 = resto(j / 8)

	        	#Marco en t7 que no necesito hnos
	        	addu t7, zero, zero

        		#Si estoy al inicio del bloque, el hno izquierdo esta en el bloque anterior
        		beqz t3, faltaHnoIzq

        		#Si estoy en el medio del bloque, tengo los hnos que necesito
        		ble t3, 6, tengoLosHnos

        		#Si estoy al final del bloque, necesito al hno derecho que esta en el bloque siguiente
        		beq t3, 7, faltaHnoDer

faltaHnoIzq:	#Si estoy en el primer bloque, necesito el ultimo bloque tambien
				beqz t2, ultimoBloque

				#Sino, necesito el anterior
				subu t4, t2, zero # t4 = nro bloque
				b obtenerBloque # Voy a obtener el bloque

ultimoBloque:	divu t0, 8 # en 'lo' guardo el cociente de N / 8 y en 'hi' guardo el resto
	        	#Obtengo el nro de bloque de 8 bits
	        	mfhi t4 # t4 = ultimo bloque
				b obtenerBloque # Voy a obtener el bloque

faltaHnoDer:	#Si estoy en el ultimo bloque, necesito el primero tambien
				divu t0, 8 # en 'lo' guardo el cociente de N / 8 y en 'hi' guardo el resto
	        	#Obtengo el nro de bloque de 8 bits
	        	mflo t5 # t5 = ultimo bloque
				beq t2, t5, primerBloque

				#Sino, necesito el siguiente
				addu t4, t2, zero # t4 = nro bloque 
				b obtenerBloque # Voy a obtener el bloque

primerBloque:	addu t4, zero, zero # t4 = primer bloque
				b obtenerBloque # Voy a obtener el bloque

obtenerBloque:	mul t4, t4, 8 # t4 = t4 * 8 -> Dir del bloque
				lb t6, t4 + a0 # t6 = el bloque que necesito extra
	
				#Muevo a los bit menos significativos los bit que necesito
				beqz t3, esElPrimero
				b esElUltimo
esElPrimero:	sll t6, t6, 2 # Es el hno izquierdo, lo muevo donde debe ir
				and t6, t6, 4 # Dejo el resto en 0
				b marcar

esElUltimo:		srl t6, t6, 7 # Dejo en los bits menos significativos al bit que necesito
				and t6, t6, 1 # Dejo el resto en 0

marcar:			addu t7, 1, zero # Marco en t7 si utilizo t2 o no

tengoLosHnos:	mul t5, t2, 8 # t5 = nro de bloque * 8 -> dir del bloque
				lb t8, t5 + a0 # t8 = bloque que tiene mi elemento

				#Muevo a los bit menos significativos los bit que necesito
				beq t3, 7, ultimo
				subu t5, 6, t3 # Busco cuanto tengo que correr el valor de t8
				srl t8, t8, t5 # Dejo en los bits menos significativos al bit que necesito
				and t8, t8, 7 # Dejo el resto en 0
				b necesitoHno

ultimo: 		addu t5, zero, 1 # t5 = 1
				sll t8, t8, t5 # Dejo en los bits menos significativos al bit que necesito
				and t8, t8, 6 # Dejo el resto en 0

				#Si necesito al otro hno, hago un and logico
necesitoHno:	beqz t7, todoEnBloque
				and t8, t8, t6 # t8 = los 3 bits que necesito

todoEnBloque:	# Hay que aplicar la regla
				addu t9, zero, a3 # t9 = regla
				srl t9, t9, t8 # me quedo en el bit menos significativo el dato que necesito
				and t9, t9, 1 # pongo el resto en 0

devuelvoRes:	addu v0, t9, zero # v0 = estado de la proxima iteracion
				
salir:			lw ra, 8(sp)
		        lw $fp, 4(sp)
		        lw gp, 0(sp)
		        addu sp, sp, 16
		        jr ra
.end			proximo
