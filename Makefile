CC       	= gcc
CFLAGS   	= -Wall
OBJFILES 	= prodcon.o trans_sleep.o logging.o  
TARGET		= prodcon

all:		$(TARGET)

$(TARGET):	$(OBJFILES)
			$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
			@rm -f $(OBJFILES) $(TARGET)
			
