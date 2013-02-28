CC=gcc
FILE=strips
EXEC=strips

all:
	bison -d $(FILE).y
	flex $(FILE).l
	$(CC) main.c $(FILE).tab.c lex.yy.c -lfl -o ${EXEC}
	rm lex.yy.c
	rm $(FILE).tab.c
	rm $(FILE).tab.h


debug:
	bison --report=state,solved --report-file=bison.debug -d $(FILE).y
	flex $(FILE).l &> flex.debug
	$(CC) main.c $(FILE).tab.c lex.yy.c -lfl -o ${EXEC}
	

clean:
#	rm lex.yy.c
#	rm $(FILE).tab.c
#	rm $(FILE).tab.h
	rm ${EXEC}
#	rm bison.debug
#	rm flex.debug
