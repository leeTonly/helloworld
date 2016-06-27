###########################################  
#Makefile for simple programs  
###########################################  
INC=  
LIB=  
  
CC=gcc
CC_FLAG=-Wall  
  
PRG=diff  
OBJ=diff.o
  
$(PRG):$(OBJ)  
	$(CC) $(INC) $(LIB) -o $@ $(OBJ)  
      
.SUFFIXES: .c .o  
.o:  	
	$(CC) $(CC_FLAG) $(INC) -c $*.c -o $*.o  
  
.PRONY:clean  
clean:  
	@echo "Removing linked and compiled files......"  
	rm -f $(OBJ) $(PRG) 
