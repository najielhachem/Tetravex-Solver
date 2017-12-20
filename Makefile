# Setting C++ compiler and flags
CPP = g++ 
CPPFLAGS= --std=c++11 

CPPLIBS = 

##############################################################################

# Sources

# Setting library files and dir
LDIR = lib
_LIB = 

LIB = $(parsubst %, $(LDIR)/%, $(_LIB))

# Setting src files and dir
SDIR = src
_SRC = main.cpp \
			 tetravex.cpp \
			 solver.cpp 

SRC = $(patsubst %, $(SDIR)/%, $(_SRC))

##############################################################################

# Objects

ODIR = obj
_OBJ = $(_SRC:.cpp=.o)
_OBJ += $(_LIB:.cpp=.o)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

##############################################################################
			######################################################

BIN = solver.out

all: $(ODIR) $(BIN)
	
$(ODIR): 
	mkdir -p $(ODIR)

$(BIN): $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJ) $(CPPLIBS) -o $(BIN)

##############################################################################
			######################################################

$(ODIR)/main.o: $(SDIR)/main.cpp 
	$(CPP) $(CPPFLAGS) $(CPPLIBS) -c $< -o $@

$(ODIR)/tetravex.o: $(SDIR)/tetravex.cpp $(SDIR)/tetravex.hpp  
	$(CPP) $(CPPFLAGS) $(CPPLIBS) -c $< -o $@

$(ODIR)/solver.o: $(SDIR)/solver.cpp $(SDIR)/solver.hpp  
	$(CPP) $(CPPFLAGS) $(CPPLIBS) -c $< -o $@

##############################################################################

run: build
	$(EXEC) ./$(BIN)

RM = rm -rf

clean:
	$(RM) $(ODIR) $(BIN) 

.PHONY: clean

##############################################################################
