OUT = fork.out
SRC = fork.c

$(OUT): $(SRC)
	gcc  $< -o $@ -std=c99 -Wall -Werror

run: $(OUT)
	./$<

clean:
	rm -f *.out
