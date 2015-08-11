OPATH = obj
HPATHS = -I/usr/local/lib/systemc-2.3.1/include
CC = gcc
CFLAGS = -c -g3 -Wall -std=c++11 $(HPATHS) -o $@

SCMAP_PATH = sc_map

# -------------------------------------------------------------------------

sc_map: $(OPATH)/sc_map_key.o \
        $(OPATH)/sc_map_linear_key.o $(OPATH)/sc_map_linear_range.o \
        $(OPATH)/sc_map_square_key.o $(OPATH)/sc_map_square_range.o \
        $(OPATH)/sc_map_cube_key.o $(OPATH)/sc_map_cube_range.o \
        $(OPATH)/sc_map_4d_key.o $(OPATH)/sc_map_4d_range.o \

$(OPATH)/sc_map_key.o : $(SCMAP_PATH)/sc_map_key.cpp $(SCMAP_PATH)/sc_map_key.hpp
	$(CC) $(CFLAGS) $(SCMAP_PATH)/sc_map_key.cpp

$(OPATH)/sc_map_regular_key.o : $(SCMAP_PATH)/sc_map_regular/sc_map_regular_key.cpp $(SCMAP_PATH)/sc_map_regular/sc_map_regular_key.hpp
	$(CC) $(CFLAGS) $(SCMAP_PATH)/sc_map_regular/sc_map_regular_key.cpp

# sc_map_linear -----------------------------------------------------------

$(OPATH)/sc_map_linear_key.o : $(SCMAP_PATH)/sc_map_linear/sc_map_linear_key.cpp $(SCMAP_PATH)/sc_map_linear/sc_map_linear_key.hpp \
                               $(OPATH)/sc_map_regular_key.o
	$(CC) $(CFLAGS) $(SCMAP_PATH)/sc_map_linear/sc_map_linear_key.cpp

$(OPATH)/sc_map_linear_range.o : $(SCMAP_PATH)/sc_map_linear/sc_map_linear_range.cpp $(SCMAP_PATH)/sc_map_linear/sc_map_linear_range.hpp \
                               $(OPATH)/sc_map_regular_key.o $(OPATH)/sc_map_linear_key.o
	$(CC) $(CFLAGS) $(SCMAP_PATH)/sc_map_linear/sc_map_linear_range.cpp

# sc_map_square ----------------------------------------------------------

$(OPATH)/sc_map_square_key.o : $(SCMAP_PATH)/sc_map_square/sc_map_square_key.cpp $(SCMAP_PATH)/sc_map_square/sc_map_square_key.hpp \
                               $(OPATH)/sc_map_regular_key.o
	$(CC) $(CFLAGS) $(SCMAP_PATH)/sc_map_square/sc_map_square_key.cpp

$(OPATH)/sc_map_square_range.o : $(SCMAP_PATH)/sc_map_square/sc_map_square_range.cpp $(SCMAP_PATH)/sc_map_square/sc_map_square_range.hpp \
                               $(OPATH)/sc_map_regular_key.o $(OPATH)/sc_map_square_key.o
	$(CC) $(CFLAGS) $(SCMAP_PATH)/sc_map_square/sc_map_square_range.cpp

# sc_map_cube -----------------------------------------------------------

$(OPATH)/sc_map_cube_key.o : $(SCMAP_PATH)/sc_map_cube/sc_map_cube_key.cpp $(SCMAP_PATH)/sc_map_cube/sc_map_cube_key.hpp \
                               $(OPATH)/sc_map_regular_key.o
	$(CC) $(CFLAGS) $(SCMAP_PATH)/sc_map_cube/sc_map_cube_key.cpp

$(OPATH)/sc_map_cube_range.o : $(SCMAP_PATH)/sc_map_cube/sc_map_cube_range.cpp $(SCMAP_PATH)/sc_map_cube/sc_map_cube_range.hpp \
                               $(OPATH)/sc_map_regular_key.o $(OPATH)/sc_map_cube_key.o
	$(CC) $(CFLAGS) $(SCMAP_PATH)/sc_map_cube/sc_map_cube_range.cpp

# sc_map_4d -----------------------------------------------------------

$(OPATH)/sc_map_4d_key.o : $(SCMAP_PATH)/sc_map_4d/sc_map_4d_key.cpp $(SCMAP_PATH)/sc_map_4d/sc_map_4d_key.hpp \
                               $(OPATH)/sc_map_regular_key.o
	$(CC) $(CFLAGS) $(SCMAP_PATH)/sc_map_4d/sc_map_4d_key.cpp 

$(OPATH)/sc_map_4d_range.o : $(SCMAP_PATH)/sc_map_4d/sc_map_4d_range.cpp $(SCMAP_PATH)/sc_map_4d/sc_map_4d_range.hpp \
                               $(OPATH)/sc_map_regular_key.o $(OPATH)/sc_map_4d_key.o
	$(CC) $(CFLAGS) $(SCMAP_PATH)/sc_map_4d/sc_map_4d_range.cpp

# sc_analyzer -----------------------------------------------------------

sc_analyzer: $(OPATH)/sc_analyzer.o

$(OPATH)/sc_analyzer.o : sc_analyzer/sc_analyzer.cpp sc_analyzer/sc_analyzer.hpp
	$(CC) $(CFLAGS) sc_analyzer/sc_analyzer.cpp

# other targets ---------------------------------------------------------

.PHONY: clean

clean:
	rm -f $(OPATH)/*.o *~
