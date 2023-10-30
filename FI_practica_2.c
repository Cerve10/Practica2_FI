#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N 512

float Mat[N][N], MatDD[N][N];

float V1[N], V2[N], V3[N], V4[N];

void InitData(){
        int i,j;
        srand(8824553);
        for( i = 0; i < N; i++ )
         for( j = 0; j < N; j++ ){
                Mat[i][j]=(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
                if ( (abs(i - j) <= 3) && (i != j))
                        MatDD[i][j] = (((i*j)%3) ? -1 : 1)*(rand()/(1.0*RAND_MAX));
                else if ( i == j )
                        MatDD[i][j]=(((i*j)%3)?-1:1)*(10000.0*(rand()/(1.0*RAND_MAX)));
                else MatDD[i][j] = 0.0;
        }
        for( i = 0; i < N; i++ ){
                V1[i]=(i<N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
                V2[i]=(i>=N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
                V3[i]=(((i*j)%5)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
        }
}

void PrintVect( float vect[N],int from, int numel ){
	for (int i = from; i<from+numel; i++){
		printf("%f", vect[i]);
	}
	printf("\n");

}

void PrintRow(float mat[N][N], int row, int from, int numel) {
    for (int i = from; i < from + numel && i < N; i++) {
        printf("%f ", mat[row][i]);
    }
    printf("\n");
}

void MultEscalar( float vect[N], float vectres[N], float alfa ) {
	 for (int i = 0; i < N; i++) {
        vectres[i] = alfa * vect[i];
    }
}

float Scalar( float vect1[N], float vect2[N] ){
	for (int i = 0; i < N; i++) {
		float vect3 = vect1[i] * vect2[i];
		}
}




int main() {
	InitData();
	PrintVect(V1, 5, 9);
	PrintRow(Mat, 6, 1, 7);
    return 0;
}
