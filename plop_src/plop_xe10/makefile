rDFLAGS = -Duse_gd_graphics

stuff: plate grid_gen plot plop

plate_d: plate.cpp plate_global.cpp global.h
	gcc -g -o plate_d -Ddebug -Dstandalone plate.cpp

plate_band: plate_band.o
	gcc -g -o plate plate_band.o

plate_band.o: plate.cpp plate_global.cpp global.h
	gcc -g -c -o plate_band.o -Dstandalone plate.cpp

plate.o: plate.cpp plate_global.cpp global.h
	gcc -g -Duse_sparse -Dstandalone $(GDFLAGS) -c plate.cpp

plate_plop.o: plate.cpp plate_global.cpp global.h
	gcc -g -Duse_sparse -c -o plate_plop.o plate.cpp

sparsemat.o: sparsemat.cpp
	gcc -g -c sparsemat.cpp

plate: plate.o sparsemat.o plate_global.o alloc_plate_globals.o
	gcc -g -o plate plate.o sparsemat.o plate_global.o alloc_plate_globals.o

plot.o: plot.cpp
	gcc -g -c -Dstandalone plot.cpp

plot: plot.o plate_global.o alloc_plate_globals.o
	gcc -g -o plot -Dstandalone plot.cpp plate_global.o alloc_plate_globals.o -lm

plot_plop.o: plot.cpp plate_global.cpp global.h gd.h
	gcc -g -c $(GDFLAGS) -o plot_plop.o plot.cpp

grid_gen.o: grid_gen.cpp global.h
	gcc -g -c -Dstandalone grid_gen.cpp

grid_gen: grid_gen.o plate_global.o alloc_plate_globals.o
	gcc -g -o grid_gen grid_gen.o plate_global.o alloc_plate_globals.o -lm

grid_gen_plop.o: grid_gen.cpp plate_global.cpp global.h
	gcc -g -c $(GDFLAGS) -o grid_gen_plop.o grid_gen.cpp

alloc_plate_globals.o: alloc_plate_globals.cpp plate_global.cpp plate_global.h
	gcc -g -c alloc_plate_globals.cpp

gd.o: gd.cpp mtables.c
	gcc -g -c gd.cpp

plate_global.o: plate_global.cpp
	gcc -g -c plate_global.cpp

plop: grid_gen_plop.o plate_plop.o plot_plop.o sparsemat.o alloc_plate_globals.o plate_global.o gd.o
	gcc -g -o plop grid_gen_plop.o plate_plop.o plot_plop.o sparsemat.o alloc_plate_globals.o plate_global.o gd.o -lm

src.tar: plot.cpp
	echo making src.tar
	tar cvf src.tar *.c *.cpp *.h gui_plop/*.cpp gui_plop/*.h makefile plop.ide gui_plop/gui_plop.bpr gui_plop/*.dfm gui_plop/*.ico gui_plop/*.res RCS/* gui_plop/RCS/*

