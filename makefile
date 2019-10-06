all: sum_by_rows sum_by_cols

sum_by_rows: sum_by_rows.cpp
	g++ sum_by_rows.cpp -o sum_by_rows --std=c++11 -O2
sum_by_cols: sum_by_cols.cpp
	g++ sum_by_cols.cpp -o sum_by_cols --std=c++11 -O2
run: sum_by_rows sum_by_cols
	./sum_by_rows 
	./sum_by_cols
.PHONY: all run