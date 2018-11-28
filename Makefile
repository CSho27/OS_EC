all: global_omp_shubert.o local_omp_shubert.o error_creator.o
	gcc -o global_omp_shubert global_omp_shubert.o -lm -fopenmp
	gcc -o local_omp_shubert local_omp_shubert.o -lm -fopenmp
	gcc -o error_creator error_creator.o -lm -fopenmp

global_omp_shubert.o: global_omp_shubert.c
	gcc -Wall -Werror -g -c global_omp_shubert.c -fopenmp
	
local_omp_shubert.o: local_omp_shubert.c
	gcc -Wall -Werror -g -c local_omp_shubert.c -fopenmp

error_creator.o: error_creator.c
	gcc -Wall -Werror -g -c error_creator.c -fopenmp
	
clean:
	rm -f *.o
	rm -f global_omp_shubert
	rm -f local_omp_shubert
	rm -f error_creator