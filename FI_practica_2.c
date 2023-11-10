#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define N 512

float Mat[N][N], MatDD[N][N];
float V1[N], V2[N], V3[N], V4[N];

void InitData() {
        int i,j;
        srand(4422543);
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
    for (int i = from; i < from + numel; i++) {
        printf("%f ", mat[row][i]);
    }
    printf("\n");
}

void MultEscalar( float vect[N], float vectres[N], float alfa ) {
	 for (int i = 0; i < N; i++) {
		 vectres[i] = vect[i] * alfa;
    }
}

float Scalar( float vect1[N], float vect2[N] ){
	float vect3;
	for (int i = 0; i < N; i++) {
		vect3 += vect1[i] * vect2[i];
		}
	return vect3;
}

float Magnitude(float vect[N]) {
    float sumaCuadrados = 0;

    for (int i = 0; i < N; i++) {
        sumaCuadrados += vect[i] * vect[i];
    }

    return sqrt(sumaCuadrados);
}

int Ortogonal(float vect1[N], float vect2[N]) {
    float esc = 0;
    for (int i = 0; i < N; i++) {
        esc += vect1[i] * vect2[i];
    }
    if (esc == 0) {
        return 1; // ortogonales
    } else {
        return 0; // No ortogonales
    }
}

void Projection( float vect1[N], float vect2[N], float vectres[N] ){
	float numerador = Scalar(vect1, vect2);
	float denominador = Magnitude(vect2);
	float res = numerador / denominador; 
	MultEscalar(vect2, vectres, res);


}

float Infininorm(float M[N][N]) {
    float max_sum = 0;

    for (int i = 0; i < N; i++) {
        float suma_fila= 0;

        for (int j = 0; j < N; j++) {
            suma_fila += fabs(M[i][j]); // Suma abs de la fila i
        }

        if (suma_fila > max_sum) {
            max_sum = suma_fila; // Actualiza el máximo si hay suma mayor
        }
    }
    return max_sum; 
}

float Onenorm(float M[N][N]) {
    float max_sum = 0;

    for (int j = 0; j < N; j++) {
        float col_sum = 0;

        for (int i = 0; i < N; i++) {
            col_sum += fabs(M[i][j]); // Suma abs de la columna j
        }

        if (col_sum > max_sum) {
            max_sum = col_sum; // Actualiza el máximo si hay suma mayor
        }
    }
    return max_sum;
}

float NormFrobenius(float M[N][N]) {
    float suma_cuadrados = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            suma_cuadrados += M[i][j] * M[i][j]; // suma dels quadrar de coeficients
        }
    }
    return sqrt(suma_cuadrados); // arrel quadrada de suma de cuadrados
}

int DiagonalDom(float M[N][N]) {
    for (int i = 0; i < N; i++) {
        float val_diagonal = fabs(M[i][i]);
        float suma_fila = 0;

        for (int j = 0; j < N; j++) {
            if (j != i) {
                suma_fila += fabs(M[i][j]);
            }
        }

        if (val_diagonal < suma_fila) {
            return 0; // matriu no diagonal
        }
    }    return 1; // matriu diagonal
}

int Jacobi( float M[N][N] , float vect[N], float vectres[N], unsigned int iter ){
	if (!DiagonalDom(M)) {
	printf("Matriu no diagonal dominant. No es pot aplicar Jacobi");
	return 0;
	}
	float temp[N];
	unsigned int k;
	for (k=0; k< iter;k++){
		for (int i = 0; i < N; i++) {
			temp[i]=vect[i];
			for (int j=0; j < N; j++) {
				if (j!=i){
					temp[i]=M[i][j]*vectres[j];
				}
			}
			temp[i] /= M[i][i];
		}
		for (int i=0; i<N; i++){
			vectres[i]=temp[i];
		}
	}
	return 1;
}

int main(){
    InitData();
    


    // print vect
    // A
    PrintVect(V1, 0, 10);
    PrintVect(V1, 256, 10);
    PrintVect(V2, 0, 10);
    PrintVect(V2, 256, 10);
    PrintVect(V3, 0, 10);
    PrintVect(V3, 256, 10);
    printf("\n");

    // print row
    // B
    PrintRow(Mat, 0, 0, 10);
    PrintRow(Mat, 100, 0, 10);
    printf("\n");
    // C
    PrintRow(MatDD,0, 0,10);
    PrintRow(MatDD,100, 90,10);
    printf("\n");
    // D Infininorm
    float INMat = Infininorm(Mat);
    printf("Infininorma de Mat = %f\n", INMat);
    float INMatDD = Infininorm(MatDD);
    printf("Infininorma de MatDD = %f\n", INMatDD);
    printf("\n");
    // D norma ú
    float OnenormMat = Onenorm(Mat);
    printf("Norma ú de Mat = %f\n", OnenormMat);
    float OnenormMatDD = Onenorm(MatDD);
    printf("Norma ú de MatDD = %f\n", OnenormMatDD);
    printf("\n");
    //D NormFrobenius
    float NormFrobeniusMat = NormFrobenius(Mat);
    printf("Norma de Frobenius de Mat = %f\n", NormFrobeniusMat);
    float NormFrobeniusMatDD = NormFrobenius(MatDD);
    printf("Norma de Frobenius de MatDD = %f\n", NormFrobeniusMatDD);
    printf("\n");
    // D DIagonalDom
    int isDiagonalDom = DiagonalDom(Mat);
        
    if (isDiagonalDom) {
        printf("Mat és diagonal dominant.\n");
    } else {
        printf("Mat no és diagonal dominant.\n");
    }

    int isDiagonalDomDD = DiagonalDom(MatDD);

    if (isDiagonalDomDD) {
        printf("MatDD és diagonal dominant.\n");
    } else {
        printf("MatDD no és diagonal dominant.\n");
    }
	printf("\n");
    // E
    float Scalar1 = Scalar(V1, V2);
    printf("Escalar V1, V2 =  %f\n", Scalar1);
    float Scalar2 = Scalar(V1, V3);
    printf("Escalar V1, V3 =  %f\n", Scalar2);
    float Scalar3 = Scalar(V2, V3);
    printf("Escalar V2, V3 =  %f\n", Scalar3);
	printf("\n");
    // F Magnitud 
    float result,result2,result3;
    result = Magnitude(V1);
    printf("Magnitud de V1: %f\n", result);
    result2 = Magnitude(V2);
    printf("Magnitud de V2: %f\n", result2);
    result3 = Magnitude(V3);
    printf("Magnitud de V3: %f\n", result3);
	printf("\n");
    // G ortognal v1v2
    int Ortogonal12 = Ortogonal(V1, V2);
    int Ortogonal13 = Ortogonal(V1, V3);
    int Ortogonal23 = Ortogonal(V2, V3);
    if (Ortogonal12) {
	    printf("V1 i V2 són ortogonals \n");
    } else {
	    printf("V1 i V2 són ortogonals \n");
    }

    if (Ortogonal13) {
            printf("V1 i V3 són ortogonals \n");
    } else {
            printf("V1 i V3 són ortogonals \n");
    }

    if (Ortogonal23) {
            printf("V2 i V3 són ortogonals \n");
    } else {
            printf("V2 i V3 són ortogonals \n");
    }
    printf("\n");

    // H MultEscalar 
    MultEscalar(V3, V3, 2.0);
    PrintVect(V3, 0, 10);
    PrintVect(V3, 256, 10);
    printf("\n");
    
    // I `prjeccio
    Projection(V2, V3, V4);
    PrintVect(V4, 0 ,10);
    Projection(V1, V2, V4);
    PrintVect(V4, 0, 10);
    printf("\n");

    // Jacob
    Jacobi(MatDD,V3,V4,1);
    printf("ELs elements 0 a 9 de la solució (1 iter) del sistema d'equacions són: \n");
    for (int i = 0; i < 10; i++){
	    printf("%f ", V4[i]);
	    	}
    Jacobi(MatDD,V3,V4,1000);
    printf("ELs elements 0 a 9 de la solució (1000 iter) del sistema d'equacions són: ");
	    for (int i = 0; i < 10; i++){
            printf("%f ", V4[i]);
                }
    printf("\n");
}



