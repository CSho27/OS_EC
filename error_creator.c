//Christopher Shorter
//HW 6 Problem 1a

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

// Compute Shubert value for x1,x2 combination
double shubert(double x1, double x2) {
	double sum1 = 0; 
	double sum2 = 0;
	int i;
	for (i = 1; i <= 5; i++) {
		sum1 += i * cos((double)(i + 1) * x1 + i);
		sum2 += i * cos(((double)i + 1) * x2 + i);
	}
	return sum1 * sum2;
}

int main () { 
	struct timeval start_time, stop_time, elapsed_time;  // timers
  	gettimeofday(&start_time,NULL); // Unix timer
	
	int i;
	double x1, x2, y, min = 0, err_min = 0;
	const double xvals[5] = {-500, -250, 0, 250, 500};
	
	#pragma omp parallel for
	for (i = 0; i <= 4; i++) {
		int begin = xvals[i];
		int end  = xvals[i+1];
		for (x1 = begin; x1 <= end; x1 += 0.5) { // x1 parameter of Shubert function
			for (x2 = begin; x2 <= end; x2 += 0.5) { // x2 parameter of Shubert function
				y = shubert(x1, x2); // Evaluate Shubert function defined below
				if (y < min){ // Check for global minimum
					#pragma omp critical
					min = y;
				}
			}
		}
	}

	#pragma omp parallel for
	for (i = 0; i <= 1000; i++) {
		int new_i = i%4;
		int index1 = 0;
		int index2 = 0;
		switch(new_i){
			case 0:
				index1 = 0;
				index2 = 1;
				break;
			case 1:
				index1 = 1;
				index2 = 2;
				break;
			case 2:
				index1 = 2;
				index2 = 3;
				break;
			case 3:
				index1 = 3;
				index2 = 4;
				break;
			default:
				break;
		}

		int begin = xvals[index1];
		int end  = xvals[index2];
		for (x1 = begin; x1 <= end; x1 += 0.5) { // x1 parameter of Shubert function
			for (x2 = begin; x2 <= end; x2 += 0.5) { // x2 parameter of Shubert function
				y = shubert(x1, x2); // Evaluate Shubert function defined below
				if (y < err_min){ // Check for global minimum
					err_min = y;
				}
			}
		}
	}
	gettimeofday(&stop_time,NULL);
	timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine;
	printf("Total time was %f seconds.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
	printf("Minimum: %lf\n", min);
	printf("Second Attempt: %lf\n", min);
	fflush(stdout);
	return 0;
}