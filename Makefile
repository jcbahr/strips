CC=gcc
BISON=bison
FILE=strips
EXEC=strips
BISON_DEBUG=bison.debug
FLEX_DEBUG=flex.debug

default:
	$(BISON) -d $(FILE).y
	flex $(FILE).l
	$(CC) main.c memory.c $(FILE).tab.c lex.yy.c -lfl -o ${EXEC}
	rm lex.yy.c
	rm $(FILE).tab.c
	rm $(FILE).tab.h

debug:
	$(BISON) --report=state,solved --report-file=$(BISON.DEBUG) -d $(FILE).y
	flex $(FILE).l &> $(FLEX.DEBUG)
	$(CC) main.c memory.c $(FILE).tab.c lex.yy.c -lfl -o ${EXEC}
	

clean:
#	rm lex.yy.c
#	rm $(FILE).tab.c
#	rm $(FILE).tab.h
	rm ${EXEC}
#	rm $(BISON).debug
#	rm flex.debug
