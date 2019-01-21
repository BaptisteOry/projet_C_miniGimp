CC     = gcc
CFLAGS = -Wall -O2 -Wno-unused-result -g
LIB    = -lm
OBJ    = src/main.o src/mathf.o src/image.o src/lut.o src/ihm.o src/histogram.o
RM     = rm -f
BIN    = bin/minigimp
DIRNAME = $(shell basename $$PWD)
BACKUP  = $(shell date +`basename $$PWD`-%m.%d.%H.%M.zip)
STDNAME = $(DIRNAME).zip

all : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(BIN)
	@echo "--------------------------------------------------------------"
	@echo "            to execute type: $(BIN) &"
	@echo "--------------------------------------------------------------"

main.o : main.c image.c image.h lut.c lut.h ihm.c ihm.h
	@echo "compile main"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

image.o : image.c image.h
	@echo "compile image"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

mathf.o : mathf.c mathf.h
	@echo "compile mathf"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

lut.o : mathf.c mathf.h image.c image.h lut.c lut.h ihm.c ihm.h
	@echo "compile lut"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

ihm.o : image.c image.h lut.c lut.h ihm.c ihm.h
	@echo "compile ihm"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

histo.o : mathf.c mathf.h image.c image.h histo.c histo.h lut.c lut.h
	@echo "compile ihm"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

clean :	
	@echo "**************************"
	@echo "CLEAN"
	@echo "**************************"
	$(RM) *~ $(OBJ) $(BIN)    

bigclean :
	@echo "**************************"
	@echo "BIG CLEAN"
	@echo "**************************"
	find . -name '*~' -exec rm -fv {} \;
	$(RM) *~ $(OBJ) $(BIN)

zip : clean 
	@echo "**************************"
	@echo "ZIP"
	@echo "**************************"
	cd .. && zip -r $(BACKUP) $(DIRNAME)
