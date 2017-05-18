$(shell mkdir ./obj 2>/dev/null )
# built-in rules variable ------------------------------------------------------------
CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar
CFLAGS = -g -mtune=cortex-m4 -mthumb -std=c99 -fdata-sections -mfloat-abi=soft \
 -march=armv7-m -mthumb-interwork -mapcs-frame
CPPFLAGS = -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F407xx $(INCLUDEDIR)
TARGET_ARCH = 
OUTPUT_OPTION = -o ./obj/$@
ARFLAGS = rcs
# ------------------------------------------------------------------------------------

SRCDIR = ./USART
SRCDIR += ./PWM
SRCDIR += ./LED
SRCDIR += ./MPU6050


INCDIR = $(shell find -name *stm32f4*.h)
INCDIR += $(shell find -name core*.h)
INCDIR :=$(dir $(INCDIR))
INCDIR :=$(sort $(INCDIR))


SRC := $(shell ls $(SRCDIR))
SRC := $(notdir $(SRC)) 
SRC := $(filter %.c,$(SRC))
OBJ = $(subst .c,.o,$(SRC))



VPATH = $(SRCDIR)

vpath %.o ./obj
vpath %.a ./obj
vpath %.a ./stm32f4_lib/obj

INCLUDEDIR = $(addprefix -I,$(INCDIR))

all:libdriver.a

include $(SRC:%.c=obj/%.d)

libdriver.a:$(OBJ) libst.a 
	$(AR) $(ARFLAGS) ./obj/$@ ./obj/*.o 

libst.a:$(shell ls stm32f4_lib/obj/*.o)
	cd stm32f4_lib&&make&&cd ..

obj/%.d:%.c 
	$(CC) -M $(CPPFLAGS) $< >> $@

.PHONY:clean clean_all
clean:
	@-rm -r ./obj	
	@echo "clean drivers"

clean_all:clean
	@cd stm32f4_lib&&make clean&&cd ..


