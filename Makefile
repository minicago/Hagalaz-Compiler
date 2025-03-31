TEST_DIR = test/functional
SRC_SY = $(wildcard $(TEST_DIR)/*.sy)
CC = arm-linux-gnueabihf-gcc
LD = arm-linux-gnueabihf-gcc
BUILD_DIR = build
LIB_DIR = test
LIB = $(LIB_DIR)/libsysy.a


QEMU = qemu-arm-static

OBJS = $(patsubst $(TEST_DIR)/%.sy, $(BUILD_DIR)/% ,$(SRC_SY) )

$(BUILD_DIR)/% : $(TEST_DIR)/%.sy
	@if [ ! -d $(BUILD_DIR) ]; then \
		mkdir -p $(BUILD_DIR); \
	fi
	@echo "Compiling $< to $@"
	$(CC) -o $@ -xc $< -I$(LIB_DIR) -L$(LIB_DIR) -lsysy -static

.PHONY: all clean run

all: $(OBJS) 
	@echo "All tests compiled successfully."

clean:
	@echo "Cleaning up..."
	@rm -f $(BUILD_DIR)/*
	@echo "Cleaned up."

run: all
	@echo "Running tests..."
	@for test_sy in $(SRC_SY); do \
		test=$${test_sy##*/} ; \
		echo $(BUILD_DIR)/$${test%.sy} ; \
		obj=$(BUILD_DIR)/$${test%.sy} ; \
		input=$(TEST_DIR)/$${test%.sy}.in ; \
		output=$(BUILD_DIR)/$${test%.sy}.out ; \
		ans=$(TEST_DIR)/$${test%.sy}.out ; \
		if [ ! -f $${obj} ]; then \
			continue ; \
		fi ; \
		if [ ! -f $${input} ]; then \
			$(QEMU) $${obj} > $${output} ; \
		else \
			$(QEMU) $${obj} < $${input} > $${output}; \
		fi ; \
		echo $$? >> $${output} ; \
		diff $${output} $${ans} > /dev/null ; \
		if [ $$? -ne 0 ]; then \
			echo "Test $${test} failed. Output not matched." ; \
		else \
			echo "Test $${test} passed." ; \
		fi ; \
		done
	@echo "All tests completed."




