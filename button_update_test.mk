
all: test

.PHONY:test
test: button_update_test
	@./button_update_test
	@echo $< SUCCESS

button_update_test:button_update_test.c button_update.c
	$(CC) -std=c99 -o $@ $^

.PHONY:clean
clean:
	rm -f button_update_test
