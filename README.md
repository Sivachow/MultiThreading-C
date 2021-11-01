NAME    :   SIVA CHOWDESWAR NANDIPATI
ID      :   1631148
FILES   :   prodcon.c trans_sleep.c logging.c thread.c and *.h files
Make    :   'make optim' for optimization flag
RUN     :   ./prodcon 3 4 <input.txt

prodcon.c:  Contains main()
            This file manages and calls other files to start threading, takes input and logs with the summary

logging.c:  
            This file creates the *.log file and helps to log to the file using semaphores, so there will be no clash

threading.c:
            This file is core for this Assignemnt. startThreading(), starts all the threads, calls input() to take input until
            EOF is reached. If 'T' or 'S' is the character we read, it goes to the input_t_s() to manage change the status of 
            the status[] for the thread needs to get work in a Queue way. Stalls until one of them gets the work done and logs it out. Everything happens synchronously using semaphores.

I declare this code is done by me with no collaboration of others, Reference: Stack overflow. 

SIVA CHOWDESWAR NANDIPATI