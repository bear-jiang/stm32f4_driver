$(shell mkdir ./obj 2>/dev/null )
include ./makefile.common

SRCDIR = ./USART
SRCDIR += ./PWM
SRCDIR += ./LED
SRCDIR += ./MPU6050


INCDIR = $(SRCDIR)
INCDIR += ./stm32f4_lib/STM32F4xx_StdPeriph_Driver/inc
INCDIR += ./stm32f4_lib/CMSIS/Device/ST/STM32F4xx/Include
INCDIR += ./stm32f4_lib/CMSIS/Include


SRC := $(shell ls $(SRCDIR))
SRC := $(notdir $(SRC)) 
SRC := $(filter %.c,$(SRC))
OBJ = $(subst .c,.o,$(SRC))



VPATH = $(SRCDIR)

vpath %.o ./obj
vpath %.a ./stm32f4_lib/obj

INCLUDEDIR = $(addprefix -I,$(INCDIR))

# test:
# 	@echo $(SRC)
# 	@echo $(OBJ)

driver:$(OBJ) libst.a

libst.a:
	cd stm32f4_lib&&make&&cd ..

$(OBJ):%.o:%.c
	$(CC)  $(STFLAGS) $< -o ./obj/$@


.PHONY:driver clean clean_st clean_all
clean:
	@-rm -r ./obj	
	@echo "clean drivers"

clean_st:
	@cd stm32f4_lib&&make clean&&cd ..

clean_all:clean clean_st
