CXX     = g++
CXXFLAGS = -Wall -Wextra -L. -g 
LDFLAGS = -fpic -shared

LIB_SRC = string.cpp field.cpp ip.cpp port.cpp
APP_SRC = main.cpp
DST_APP = firewall.exe
DST_LIB = firewall
OTHER = input

all:${DST_APP}

$(DST_LIB):
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIB_SRC) -o lib$(DST_LIB).so

$(DST_APP) : $(DST_LIB)
	$(CXX) $(CXXFLAGS) $(APP_SRC) -o $(DST_APP) -l$(DST_LIB) -l$(OTHER)

