CC=gcc
CFLAGS=-Wall -pedantic -g -DUNIX_HOST -DVER=\"2.1\" -DPERSOPORT
LIBS=-lm -lreadline

TARGET	= picoc
SRCS	= picoc.c table.c lex.c parse.c expression.c heap.c type.c \
	variable.c clibrary.c platform.c include.c debug.c \
	platform/platform_unix.c platform/library_unix.c \
	cstdlib/stdio.c cstdlib/math.c cstdlib/string.c cstdlib/stdlib.c \
	cstdlib/time.c cstdlib/errno.c cstdlib/ctype.c cstdlib/stdbool.c \
	cstdlib2/main.o cstdlib2/types.o cstdlib2/stat.o cstdlib2/dirent.o cstdlib2/popen.o cstdlib2/tools_h.o cstdlib2/various.o cstdlib2/regex.o cstdlib2/socket.o \
	cstdlib/unistd.c
OBJS	:= $(SRCS:%.c=%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

test:	all
	(cd tests; make test)

clean:
	rm -f $(TARGET) $(OBJS) *~ *.o

count:
	@echo "Core:"
	@cat picoc.h interpreter.h picoc.c table.c lex.c parse.c expression.c platform.c heap.c type.c variable.c include.c debug.c | grep -v '^[ 	]*/\*' | grep -v '^[ 	]*$$' | wc
	@echo ""
	@echo "Everything:"
	@cat $(SRCS) *.h */*.h | wc

.PHONY: clibrary.c

picoc.o: picoc.c picoc.h
table.o: table.c interpreter.h platform.h
lex.o: lex.c interpreter.h platform.h
parse.o: parse.c picoc.h interpreter.h platform.h
expression.o: expression.c interpreter.h platform.h
heap.o: heap.c interpreter.h platform.h
type.o: type.c interpreter.h platform.h
variable.o: variable.c interpreter.h platform.h
clibrary.o: clibrary.c picoc.h interpreter.h platform.h
platform.o: platform.c picoc.h interpreter.h platform.h
include.o: include.c picoc.h interpreter.h platform.h
debug.o: debug.c interpreter.h platform.h
platform/platform_unix.o: platform/platform_unix.c picoc.h interpreter.h platform.h
platform/library_unix.o: platform/library_unix.c interpreter.h platform.h
cstdlib/stdio.o: cstdlib/stdio.c interpreter.h platform.h
cstdlib/math.o: cstdlib/math.c interpreter.h platform.h
cstdlib/string.o: cstdlib/string.c interpreter.h platform.h
cstdlib/stdlib.o: cstdlib/stdlib.c interpreter.h platform.h
cstdlib/time.o: cstdlib/time.c interpreter.h platform.h
cstdlib/errno.o: cstdlib/errno.c interpreter.h platform.h
cstdlib/ctype.o: cstdlib/ctype.c interpreter.h platform.h
cstdlib/stdbool.o: cstdlib/stdbool.c interpreter.h platform.h
cstdlib/unistd.o: cstdlib/unistd.c interpreter.h platform.h

# Ajout PERSOPORT
cstdlib2/build.h: 
	printf "#define BUILD_TIME \""`date +'%d/%m/%Y-%H:%M:%S'`"\"\n" > cstdlib2/build.h
cstdlib2/main.o: cstdlib2/main.c cstdlib2/build.h
cstdlib2/tools.o: cstdlib2/tools.c cstdlib2/tools.h
cstdlib2/tools_h.o: cstdlib2/tools_h.c cstdlib2/tools.c cstdlib2/tools.h cstdlib2/bc_eval.c cstdlib2/base64.c cstdlib2/md5.c cstdlib2/bcrypt.c cstdlib2/mini_h.c interpreter.h platform.h
cstdlib2/dirent.o: cstdlib2/dirent.c
cstdlib2/popen.o: cstdlib2/popen.c
cstdlib2/types.o: cstdlib2/types.c
cstdlib2/stat.o: cstdlib2/stat.c
cstdlib2/various.o: cstdlib2/various.c
cstdlib2/regex.o: cstdlib2/regex.c cstdlib2/regex.h
cstdlib2/socket.o: cstdlib2/socket.c

CP	= cp

pcc: $(TARGET)
	$(CP) $(TARGET) pcc
