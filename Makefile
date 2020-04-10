CC = gcc 
Name = exe
Warrnings =-Wall
#fonction de filtrage 8 bits 
F =11110011
#les lfsr 16 bits 
#L0=0000000010010011
#L1=0000100010000011
#L2=0000000000101101
L0=1110001011100100
L1=0000110100010011
L2=0000110100010011

#suiteaattaquer
S =1111111111111111000011000110111100101100101100001001101110011011111101110010111110100101011111100110

run:compile  
	./$(Name) $(F) $(L0) $(L1) $(L2)
attack:Cattack
	./attack  $(S)
compile:object 
	$(CC)   $(Warnings) Main.o -o $(Name) 
Cattack:Cobject 
	$(CC) $(Warnings) Attack_Diviser.o -o attack
Cobject: 
	$(CC) $(Warnings) -c Attack_Diviser.c 
object:Main.c 
	$(CC)  -c $(Warnings)  Main.c 
clean: 
	rm -rf *.o $(Name) a.out
	clear 