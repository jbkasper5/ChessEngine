MAIN=$(shell find $(PWD) -name main.py)
PYTARGETS=$(filter-out $(MAIN), $(shell find $(PWD) -name \*.py))
CC=python3.9

run:
	$(CC) $(MAIN) $(PYTARGETS)