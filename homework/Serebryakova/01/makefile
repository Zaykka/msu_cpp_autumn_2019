ifeq (run,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif
all: calc

.PHONY: run
run : calc
	./calc  $(RUN_ARGS)
test: calc
	python3 ./test.py

calc: calc.cpp
	g++ -o calc calc.cpp -std=c++14
