CXX := g++
CXXFLAGS := -std=c++11 -IlibDAI/include
LDFLAGS := -LlibDAI/lib
LDLIBS := -ldai -lgmp

# Specify the path of libdai.a here
LIBDAI_PATH := libDAI/lib/libdai.a

SRCS := $(wildcard *.cpp)
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