PROG	= main
SRC	= main.cpp test.cpp ido.cpp allomas.cpp jegy.cpp kocsi.cpp memtrace.cpp menetrend.cpp utvonal.cpp vonat.cpp
OBJ	= $(SRC:.cpp=.o)
HEAD	= test.h ido.h jegy.h allomas.h serializable.h memtrace.h menetrend.h utvonal.h vonat.h kocsi.h
TEST	= # testekhez
DATA	= # sajat adathoz

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror -g -DMEMTRACE

all:	$(PROG)

$(PROG): $(OBJ)
	$(CXX) -o $(PROG) $(OBJ)

%.o: %.cpp $(HEAD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test:	$(PROG) $(TEST)
	# Add your test commands here if needed

clean:	
	rm -f $(PROG) $(OBJ)

tar:	
	tar -czf $(PROG).tgz $(SRC) $(HEAD) $(TEST) $(DATA)

zip:	
	zip $(PROG).zip $(SRC) $(HEAD) $(TEST) $(DATA)