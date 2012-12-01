.SUFFIXES : .c .o

CC		= gcc
ASM		=
LINK		=
LIBCC		= ar
RM		= rm

#----------------------------------------------------------------------------------------------
INCPATH		=
LIBPATH		= 
OBJPATH		= .
OUTPATH		= .
SOURCEPATH	= .

LDFLAGS		= -L$(LIBPATH) 
#LFLAGS		= -lm
ASFLAGS		=
ARFLAGS		= -ruv
CFLAGS		= -o

LIBS =

#---------------------------------------------------------------------------------------
SOURCES = $(OBJECTS:.o=.c)

all:
	$(CC) $(CFLAGS)	mkbl2 V310-EVT1-mkbl2.c 
	$(CC) $(CFLAGS)	sd_fdisk sd_fdisk.c
	$(CC) $(CFLAGS)	c210-mkbl1 c210-mkbl1.c 
	./create_4412_sd_image.sh ../sd_image.bin

#---------------------------------------------------------------------------------------
.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

dep:
		gccmakedep	$(SOURCES)

#---------------------------------------------------------------------------------------
clean:
		$(RM)		-rf sd_fdisk
		$(RM)		-rf mkbl2

new:
		$(MAKE)		clean
		$(MAKE)

