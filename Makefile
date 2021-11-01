CC       	= gcc
CFLAGS   	= -Wall -pthread
OBJFILES 	= prodcon.o trans_sleep.o logging.o thread.o
TARGET		= prodcon

all:		$(TARGET)

$(TARGET):	$(OBJFILES)
			$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)
			@clear

optim:		$(OBJFILES)
			$(CC) $(CFLAGS) -O -o $(TARGET) $(OBJFILES)
			@clear

clean:
			@rm -f $(OBJFILES) $(TARGET) *.log
			
