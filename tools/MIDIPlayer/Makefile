PATH := $(DEVKITARM)/bin:$(PATH)

#  Project settings

NAME       := MIDIPlayer
SOURCE_DIR := src
LIB_DIR    := lib
SPECS      := -specs=gba.specs

# Compilation settings

CROSS	?= arm-none-eabi-
AS	:= $(CROSS)as
CC	:= $(CROSS)gcc
LD	:= $(CROSS)gcc
OBJCOPY	:= $(CROSS)objcopy

ARCH	:= -mthumb-interwork -mthumb

INCFLAGS := -I$(LIB_DIR)/libtonc/include
LIBFLAGS := -L$(LIB_DIR)/libtonc/lib -ltonc
ASFLAGS	:= -mthumb-interwork
CFLAGS	:= $(ARCH) -O2 -Wall -fno-strict-aliasing $(INCFLAGS) $(LIBFLAGS)
LDFLAGS	:= $(ARCH) $(SPECS) $(LIBFLAGS)

.PHONY : build clean

# Find and predetermine all relevant source files

APP_MAIN_SOURCE := $(shell find $(SOURCE_DIR) -name '*main.c')
APP_MAIN_OBJECT := $(APP_MAIN_SOURCE:%.c=%.o)
APP_SOURCES     := $(shell find $(SOURCE_DIR) -name '*.c' ! -name "*main.c"  ! -name "*.test.c")
APP_OBJECTS     := $(APP_SOURCES:%.c=%.o)

# Build commands and dependencies

build : $(NAME)-no_content.gba

$(NAME)-no_content.gba : $(NAME).elf
	$(OBJCOPY) -v -O binary $< $@
	-@gbafix $@ -t$(NAME)
	padbin 256 $@

$(NAME).elf : $(APP_OBJECTS) $(APP_MAIN_OBJECT)
	$(LD) $^ $(LDFLAGS) -o $@

$(APP_OBJECTS) : %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(APP_MAIN_OBJECT) : $(APP_MAIN_SOURCE)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -fv *.gba
	@rm -fv *.elf
	@rm -fv *.sav
	@rm -fv *.gbfs
	@rm -rf $(APP_OBJECTS)
	@rm -rf $(APP_MAIN_OBJECT)