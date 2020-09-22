basic: lab0.c
	gcc -g -Wall -Wextra lab0.c -o lab0

check: lab0.c test.sh
	gcc -g -Wall -Wextra lab0.c -o lab0
	chmod +x test.sh
	./test.sh

clean:
	rm lab0
	rm unreadable.txt -f
	rm unwritable.txt -f
	rm readable.txt -f
	rm writable.txt -f
	rm file.txt -f
	rm lab0-205095030.tar.gz

dist:
	tar -czf lab0-205095030.tar.gz lab0.c test.sh Makefile README *.png
