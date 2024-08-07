#makefile 
include common.mk 

TARGET := $(BIN)main 
TEST := $(BIN)test
CPPFILES := $(wildcard $(SOURCE)*.cpp)
OBJECTS := $(patsubst $(SOURCE)%.cpp, $(BUILD)%.o, $(CPPFILES))
TEST_MT := $(BIN)test_sport_truck
.PHONY: dirs clean install uninstall all info 

all: $(TARGET) $(TEST) $(TEST_MT)


info: 
	@echo "[Description]"
	@echo "Makefile for Car Simulator\n"
	@echo "Date: 2024-07-09\n"
	@echo "Author: Emil Carmegren\n"
	@echo "\n\n"
	@echo "[Commands]\n"
	@echo "install    :  install project\n"
	@echo "all        :  build all targets\n"
	@echo "clean      :  clean $(BUILD) and $(BIN) dir\n"
	@echo "uninstall  :  uninstall project\n"
	@echo "info       :  file info (this)\n"
	@echo "\n\n"
	@echo "[Built-in and User Defined variables]"
	@echo " CC        : $(CC)\n" 
	@echo " CXXFLAGS  : $(CXXFLAGS)\n" 
	@echo " CPPFLAGS  : $(CPPFLAGS)\n"
	@echo " SRC       : $(SOURCE)\n"
	@echo " HEADERS   : $(HEADERS)\n"
	@echo " LIBS      : $(LIBRARIES)\n"
	@echo " Binaries  : $(BIN)\n" 
	@echo " Build     : $(BUILD)\n"
	@echo " Target:   : $(TARGET)\n"
	@echo " Test      : $(TEST)\n"

#$<, $@ generic usage, automatic variables 
$(TEST_MT): $(BUILD)Sport_Truck.o $(BUILD)Test_Sport_Truck.o
	$(CC) $(CXXFLAGS) $^ -o $@ 

$(BUILD)Sport_Truck.o: Sport_Truck.cpp Simulator.h
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ 

$(BUILD)Test_Sport_Truck.o: Test_Sport_Truck.cpp Simulator.h 
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ 
#$<, $@ generic usage, automatic variables 
$(TARGET): $(filter-out $(BUILD)test.o $(BUILD)Test_Sport_Truck.o,$(OBJECTS))
	$(CC) $(CXXFLAGS) $^ -o $@ 

$(TEST): $(filter-out $(BUILD)main.o $(BUILD)Test_Sport_Truck.o, $(OBJECTS)) 
	$(CC) $(CXXFLAGS) $^ -o $@ 

$(BUILD)test.o: test.cpp Simulator.h 
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ 

#with header file
#order-only prerequisite
$(BUILD)%.o: $(SOURCE)%.cpp $(HEADERS)%.h | $(dirs)       
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ 

#without header files 
$(BUILD)%.o: $(SOURCE)%.cpp | $(dirs)       
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ 

#explicit rule for main
$(BUILD)main.o: main.cpp Simulator.h Monster_Truck.h | $(dirs)       
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ 

#out-of-source build 
dirs: 
	@mkdir -p $(SOURCE)
	@mkdir -p $(BUILD)
	@mkdir -p $(BIN)
	@mkdir -p $(LIBS) 
	@mkdir -p $(HEADERS) 

clean: 
	rm -rf $(wildcard $(BUILD)*) $(wildcard $(BIN)*)

#supress recipe lines to terminal 
#invoke commands that are dependent on $abspath in same subshell 
#use $wildcard for potential empty expansion 
install: 
	@read -p "Do you want to proceed installing the project (Y/N): " answer; \
	if [ "$$answer" = "Y" ] || [ "$$answer" = "y" ]; then \
		echo "Starting installation..."; \
		mkdir -p $(BIN) $(HEADERS) $(BUILD) $(SOURCE) $(LIBRARIES); \
		cp $(wildcard install/*.cpp) $(SOURCE); \
		cp $(wildcard install/*.h) $(HEADERS); \
		echo "Install Complete"; \
	else \
		echo "Installation aborted"; \
	fi

	

uninstall: 
	rm -rf $(BIN) $(HEADERS) $(BUILD) $(SOURCE) $(LIBRARIES)
	@echo "Uninstall Complete"

	 
	


