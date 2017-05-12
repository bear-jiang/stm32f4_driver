$(shell mkdir ./obj 2>/dev/null )
include ../makefile.common

SRCDIR = ./USART
SRCDIR += ./PWM
SRCDIR += ./LED


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

INCLUDEDIR = $(addprefix -I,$(INCDIR))

# test:
# 	@echo $(SRC)
# 	@echo $(OBJ)

driver:$(OBJ)

$(OBJ):%.o:%.c
	$(CC)  $(STFLAGS) $< -o ./obj/$@


.PHONY:bsp clean
clean:
	@-rm -r ./obj	
	@echo "clean obj"
