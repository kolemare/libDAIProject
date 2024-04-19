CXX := g++
CXXFLAGS := -std=c++11 -IlibDAI/include -ICImg -Isrc
LDFLAGS := -LlibDAI/lib
LDLIBS := -ldai -lX11 -lgmpxx -lgmp  # Reorder to ensure GMP is linked after libDAI

# Specify the path of libdai.a here
LIBDAI_PATH := libDAI/lib/libdai.a

# Automatically find source files from src directory and subdirectories
SRCS := $(shell find src -name '*.cpp')
OBJS := $(SRCS:.cpp=.o)
TARGET := libDAIApp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)