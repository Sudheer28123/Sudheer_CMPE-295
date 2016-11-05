/*
 ===============================================================================
 Name        : LaplaceofGaussian.c
 Version     : 1.0
 Author      : Sudheer Doddapaneni
 Description : This is the source code for the Laplace of Gaussian filter used to 
               enhance the AGV’s sensor data.
 ===============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define KERNEL_SIZE		3

#define SIGMA  1.0

void computeLoGKernel()
{
    double r, s = 2.0 * SIGMA * SIGMA,num,denum;
    double G_factor[3];
    double LoG[3];

    // sum is for normalization
    double sum = 0.0, sum1 = 0.0;
    int x = 0;

    printf("Building a 1-D Gaussian Kernl with Standard Deviation(SIGMA) = %f\n",SIGMA);
    printf("\nThe Gaussian kernel is: \n");
    for ( x = 0; x < KERNEL_SIZE; x++)
    {
        //considering a 1-D(1x3) kernel => -1,0,1
    	r = x - 1;
        num = exp(-(r*r)/s);
        denum = sqrt(M_PI * s);
        G_factor[x] = num/denum;
        printf("%f  ",G_factor[x]);
        LoG[x] = G_factor[x]*(r*r - (s/2))/(s*s/4);
        sum += G_factor[x];
        sum1 += LoG[x];
    }

	printf("\n\nThe normalized Gaussian kernel is: \n");
    for(x = 0; x < KERNEL_SIZE; x++)
    {
	//normalization Gaussianof kernel
	G_factor[x] = G_factor[x]/sum;
    printf("%f  ",G_factor[x]);
	}

	printf("\n\nThe Laplace of Gaussian kernel is: \n");
    for(x = 0; x < KERNEL_SIZE; x++)
    {
    printf("%f  ",LoG[x]);
	}

	printf("\n\nThe normalized Laplace of Gaussian kernel is: \n");
    for(x = 0; x < KERNEL_SIZE; x++)
    {
	//normalization of Laplace of Gaussian kernel
	LoG[x] = LoG[x]/sum1;
    printf("%f  ",LoG[x]);
	}
}

int main()
{
    printf("Hello the world!!\n");
    computeLoGKernel();
    return 0;
}
