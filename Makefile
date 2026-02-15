TARGET = stusys.out

.PHONY:
	build run clean debug

build: $(TARGET)

$(TARGET): input.o system.o daostr.o myalloc.o
	gcc $^ -o $@

input.o: input.h myalloc.h
system.o: conio.c daostr.h input.h myalloc.h darry.h
daostr.o: daostr.h input.h myalloc.h
myalloc.o: myalloc.h

%.o: %.c
	gcc -g -c $< -o $@

run: build
	./$(TARGET)

debug: build
	gdb ./$(TARGET)

clean:
	rm -rf *.o *.out


