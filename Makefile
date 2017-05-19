$(shell mkdir ./obj 2>/dev/null )
# built-in rules variable ------------------------------------------------------------
CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar
ifneq "$(origin CFLAGS)" "environment"
CFLAGS = -g -mtune=cortex-m4 -mthumb -std=c99 -fdata-sections -mfloat-abi=soft \
 -march=armv7-m -mthumb-interwork -mapcs-frame
endif
ifneq "$(origin CPPFLAGS)" "environment"
CPPFLAGS = -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F407xx 
endif
TARGET_ARCH = 
OUTPUT_OPTION = -o ./obj/$@
ARFLAGS = rcs
CPPFLAGS := $(filter-out -I%, $(CPPFLAGS) )
export CFLAGS CPPFLAGS
# ------------------------------------------------------------------------------------

SRCDIR = ./USART
SRCDIR += ./PWM
SRCDIR += ./LED
SRCDIR += ./MPU6050
SRCDIR += ./AK8975


INCDIR = $(shell find -name *stm32f4*.h)
INCDIR += $(shell find -name core*.h)
INCDIR := $(dir $(INCDIR))
INCDIR := $(sort $(INCDIR))
INCDIR += ./

SRC := $(shell ls $(SRCDIR))
SRC := $(notdir $(SRC)) 
SRC := $(filter %.c,$(SRC))
OBJ = $(subst .c,.o,$(SRC))



VPATH = $(SRCDIR)

vpath %.o ./obj
vpath %.a ./obj
vpath %.a ./stm32f4_lib/obj

CPPFLAGS += $(addprefix -I,$(INCDIR))

all:libdriver.a libst

sinclude $(SRC:%.c=obj/%.d)

libdriver.a:$(OBJ) 
	$(AR) $(ARFLAGS) ./obj/$@ ./obj/*.o 

libst:
	cd stm32f4_lib&&make&&cd ..

obj/%.d:%.c 
	@$(CC) -M $(CPPFLAGS) $< >> $@

.PHONY:clean clean_st distclean
clean:
	@-rm -r ./obj/*.o ./obj/*.a	
	@echo "clean drivers"

distclean:
	@-rm -r ./obj
	@echo "clean drivers"
	@cd stm32f4_lib&&make distclean&&cd ..
clean_st:clean
	@cd stm32f4_lib&&make clean&&cd ..


