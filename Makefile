test_sem:comm.c test_sem.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f test_sem

