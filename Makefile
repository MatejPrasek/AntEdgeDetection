CC=g++
FLAGS=-w -g -O3
LIBS=`pkg-config opencv --cflags --libs`

RESULTSDIR=RESULTS

build:
	$(CC) $(FLAGS) EXP1/*.h EXP1/*.cpp -o EXP1/EXP1.o $(LIBS)
	$(CC) $(FLAGS) EXP2/*.h EXP2/*.cpp -o EXP2/EXP2.o $(LIBS)
	$(CC) $(FLAGS) EXP3/*.h EXP3/*.cpp -o EXP3/EXP3.o $(LIBS)
	$(CC) $(FLAGS) EXP4/*.h EXP4/*.cpp -o EXP4/EXP4.o $(LIBS)
	$(CC) $(FLAGS) EXP5/*.h EXP5/*.cpp -o EXP5/EXP5.o $(LIBS)

test: exp1 exp2 exp3 exp4 exp3 exp4 exp5

clean:
	find . -name "*.o" -type f -delete
	rm -rf ./RESULTS

exp1: exp1.1 exp1.2 exp1.3 exp1.4 exp1.5 exp1.6

exp2: exp2.1 exp2.2 exp2.3 exp2.4

exp3: exp3.1 exp3.2 exp3.3 exp3.4

exp4: exp4.1 exp4.2 exp4.3 exp4.4

exp5: exp5.1 exp5.2 exp5.3 exp5.4 

exp1.1:
	mkdir -p $(RESULTSDIR)/1.1
	./EXP1/EXP1.o --tauini 0.1 --iter 10 --cons 40 --ants 512 --q0 0.7 --alpha 1 --beta 1 --rho 0.1 --phi 0.05 --mem 8 --image ./standard_test_images/lena_color.tif --random
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/1.1 \;

exp1.2:
	mkdir -p $(RESULTSDIR)/1.2
	./EXP1/EXP1.o --tauini 0.1 --iter 10 --cons 40 --ants 512 --q0 0.7 --alpha 1 --beta 1 --rho 0.1 --phi 0.05 --mem 8 --image ./standard_test_images/lena_color.tif
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/1.2 \;
 
exp1.3:
	mkdir -p $(RESULTSDIR)/1.3
	./EXP1/EXP1.o --tauini 0.0001 --iter 20 --cons 10 --ants 100 --q0 0.7 --alpha 1 --beta 1 --rho 0.1 --phi 0.05 --mem 8 --image ./standard_test_images/lena_color.tif --random
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/1.3 \;

exp1.4:
	mkdir -p $(RESULTSDIR)/1.4
	./EXP1/EXP1.o --tauini 0.0001 --iter 20 --cons 10 --ants 100 --q0 0.7 --alpha 1 --beta 1 --rho 0.1 --phi 0.05 --mem 8 --image ./standard_test_images/lena_color.tif
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/1.4 \;

exp1.5:
	mkdir -p $(RESULTSDIR)/1.5
	./EXP1/EXP1.o --tauini 0.0001 --iter 5 --cons 40 --ants 1500 --q0 0.7 --alpha 2.5 --beta 2 --rho 0.1 --phi 0.05 --mem 8 --image ./standard_test_images/lena_color.tif --random
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/1.5 \;

exp1.6:
	mkdir -p $(RESULTSDIR)/1.6
	./EXP1/EXP1.o --tauini 0.0001 --iter 5 --cons 40 --ants 1500 --q0 0.7 --alpha 2.5 --beta 2 --rho 0.1 --phi 0.05 --mem 8 --image ./standard_test_images/lena_color.tif
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/1.6 \;

exp2.1:
	mkdir -p $(RESULTSDIR)/2.1
	./EXP2/EXP2.o --tauini 0.0001 --iter 15 --cons 80 --ants 512 --q0 0.7 --alpha 1 --beta 1 --rho 0.1 --phi 0.05 --mem 8 --image ./standard_test_images/lena_color.tif --random --skip 5
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/2.1 \;

exp2.2:
	mkdir -p $(RESULTSDIR)/2.2
	./EXP2/EXP2.o --tauini 0.0001 --iter 15 --cons 80 --ants 512 --q0 0.7 --alpha 1 --beta 1 --rho 0.1 --phi 0.05 --mem 8 --image ./standard_test_images/rad.png --random --skip 5
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/2.2 \;

exp2.3:
	mkdir -p $(RESULTSDIR)/2.3
	./EXP2/EXP2.o --tauini 0.0001 --iter 15 --cons 80 --ants 512 --q0 0.7 --alpha 1 --beta 1 --rho 0.1 --phi 0.05 --mem 8 --image ./standard_test_images/peppers_color.bmp --random --skip 5
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/2.3 \;

exp2.4:
	mkdir -p $(RESULTSDIR)/2.4
	./EXP2/EXP2.o --tauini 0.0001 --iter 15 --cons 80 --ants 512 --q0 0.7 --alpha 1 --beta 1 --rho 0.1 --phi 0.05 --mem 8 --image ./standard_test_images/mandril_color.ppm --random --skip 5
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/2.4 \;

exp3.1:
	mkdir -p $(RESULTSDIR)/3.1
	./EXP3/EXP3.o --tauini 0.0001 --iter 30 --cons 40 --ants 1200 --q0 0.4 --alpha 1 --beta 1.5 --rho 0.15 --phi 0.5 --mem 8 --image ./standard_test_images/lena_color.tif --random --threshold 7
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/3.1 \;

exp3.2:
	mkdir -p $(RESULTSDIR)/3.2
	./EXP3/EXP3.o --tauini 0.0001 --iter 20 --cons 40 --ants 1200 --q0 0.4 --alpha 1 --beta 1.5 --rho 0.15 --phi 0.5 --mem 8 --image ./standard_test_images/rad.png --random --threshold 7
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/3.2 \;

exp3.3:
	mkdir -p $(RESULTSDIR)/3.3
	./EXP3/EXP3.o --tauini 0.0001 --iter 30 --cons 40 --ants 1200 --q0 0.4 --alpha 1 --beta 1.5 --rho 0.15 --phi 0.5 --mem 8 --image ./standard_test_images/peppers_color.bmp --random --threshold 7
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/3.3 \;

exp3.4:
	mkdir -p $(RESULTSDIR)/3.4
	./EXP3/EXP3.o --tauini 0.0001 --iter 30 --cons 40 --ants 1200 --q0 0.4 --alpha 1 --beta 1.5 --rho 0.15 --phi 0.5 --mem 8 --image ./standard_test_images/mandril_color.ppm --random --threshold 7
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/3.4 \;

exp4.1:
	mkdir -p $(RESULTSDIR)/4.1
	./EXP4/EXP4.o --tauini 0.0001 --iter 30 --cons 40 --ants 1200 --q0 0.4 --alpha 1 --beta 1.5 --rho 0.15 --phi 0.5 --mem 8 --image ./standard_test_images/lena_color.tif --random --threshold 7
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/4.1 \;

exp4.2:
	mkdir -p $(RESULTSDIR)/4.2
	./EXP4/EXP4.o --tauini 0.0001 --iter 20 --cons 40 --ants 1200 --q0 0.4 --alpha 1 --beta 1.5 --rho 0.15 --phi 0.5 --mem 8 --image ./standard_test_images/rad.png --random --threshold 7
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/4.2 \;

exp4.3:
	mkdir -p $(RESULTSDIR)/4.3
	./EXP4/EXP4.o --tauini 0.0001 --iter 30 --cons 40 --ants 1200 --q0 0.4 --alpha 1 --beta 1.5 --rho 0.15 --phi 0.5 --mem 8 --image ./standard_test_images/peppers_color.bmp --random --threshold 7
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/4.3 \;

exp4.4:
	mkdir -p $(RESULTSDIR)/4.4
	./EXP4/EXP4.o --tauini 0.0001 --iter 30 --cons 40 --ants 1200 --q0 0.4 --alpha 1 --beta 1.5 --rho 0.15 --phi 0.5 --mem 8 --image ./standard_test_images/mandril_color.ppm --random --threshold 7
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/4.4 \;

exp5.1:
	mkdir -p $(RESULTSDIR)/5.1
	./EXP5/EXP5.o --tauini 0.0001 --iter 30 --cons 40 --ants 1200 --q0 0.4 --alpha 1 --beta 1.5 --rho 0.15 --phi 0.5 --mem 8 --image ./standard_test_images/lena_color.tif --random --threshold 7
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/5.1 \;

exp5.2:
	mkdir -p $(RESULTSDIR)/5.2
	./EXP5/EXP5.o --tauini 0.0001 --iter 20 --cons 40 --ants 1200 --q0 0.4 --alpha 1 --beta 1.5 --rho 0.15 --phi 0.5 --mem 8 --image ./standard_test_images/rad.png --random --threshold 7
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/5.2 \;

exp5.3:
	mkdir -p $(RESULTSDIR)/5.3
	./EXP5/EXP5.o --tauini 0.0001 --iter 30 --cons 40 --ants 1200 --q0 0.4 --alpha 1 --beta 1.5 --rho 0.15 --phi 0.5 --mem 8 --image ./standard_test_images/peppers_color.bmp --random --threshold 7
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/5.3 \;

exp5.4:
	mkdir -p $(RESULTSDIR)/5.4
	./EXP5/EXP5.o --tauini 0.0001 --iter 30 --cons 40 --ants 1200 --q0 0.4 --alpha 1 --beta 1.5 --rho 0.15 --phi 0.5 --mem 8 --image ./standard_test_images/mandril_color.ppm --random --threshold 7
	find $(RESULTSDIR) -maxdepth 1 -type f -exec mv {} $(RESULTSDIR)/5.4 \;



