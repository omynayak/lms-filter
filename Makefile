CXX = clang++
CXXFLAGS = -Wall -Wextra -O2

TARGET = main
SRC = ./cpp_files/main.cpp ./cpp_files/lms.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
