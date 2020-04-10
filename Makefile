Name = exe
Warrnings =-Wall
xl0 =45019824
xr0 =51023321
xl1 =00D7818E
xr1 =72AF039A
bl0 =45019424
br0 =51023421
bl1 =00D4818E
br1 =76AF039A
run:compile  
	./$(Name) $(xl0) $(xr0) $(xl1) $(xr1)
attack:Cattack
	./a.out $(xl0) $(xr0) $(xl1) $(xr1) $(bl0) $(br0) $(bl1) $(br1)
Cattack:Oattack
	$(CC)   $(Warnings) attack.o  
compile:object 
	$(CC)   $(Warnings) Main.o -o $(Name) 
object:Main.c 
	$(CC)  -c $(Warnings)  Main.c 
Oattack:attack.c 
	$(CC)  -c $(Warnings)  attack.c
clean: 
	rm -rf *.o $(Name) a.out
	clear 