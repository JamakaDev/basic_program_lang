exec 		= main.myx
flags 	= -g
bin_dir = "C:\Users\jamak\MyProgammingLang\bin"
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	sudo cp $(exec) $(bin_dir)

clean:
	-rm *.myx
	-rm *.o
	-rm src/*.o

test:
	./$(exec) examples/main.my

