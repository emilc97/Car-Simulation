#simply expanded variables 
CC := g++ 
OPT := -O0 
STD := -std=c++17 
CXXFLAGS = $(OPT) $(STD) -Wall -Werror #compiler flags 
HEADERS := headers/
SOURCE := source/
BIN := bin/
BUILD := build/
LIBRARIES := libs/
ARG :=                       #command line preprocessor macro
CPPFLAGS := -I$(HEADERS) $(ARG) 
VPATH := $(BIN) $(HEADERS) $(SOURCE) $(BUILD) $(LIBRARIES) 
