CXX := g++
# Include directories for libDAI and CImg, and the source directory
CXXFLAGS := -std=c++11 -IlibDAI/include -ICImg -Isrc
CXXFLAGS += $(shell pkg-config --cflags libgvc)

# Library paths for libDAI and the graphviz libraries
LDFLAGS := -LlibDAI/lib
LDFLAGS += $(shell pkg-config --libs libgvc)
# Additional flags can be added if necessary

# Libraries to link against
LDLIBS := -ldai -lX11 -lgmpxx -lgmp
# You can also let pkg-config list the proper library flags
LDLIBS += $(shell pkg-config --libs libgvc)

LIBDAI_PATH := libDAI/lib/libdai.a

SRCS := $(shell find src -name '*.cpp')
OBJS := $(SRCS:.cpp=.o)
TARGET := libDAIApp

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)