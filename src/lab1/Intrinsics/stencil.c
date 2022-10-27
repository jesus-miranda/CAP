#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include "stencil.h"

void ApplyStencil(unsigned char *img_in, unsigned char *img_out, int width, int height) {
	
	//Caracter sin signo
	unsigned char val_out;
	
	//Declaracion de i/j fuera del bucle for
	int i, j;
	
	//Variables de transicion para almacenar los datos
	__m256i val, m1, m2, m3, m4, m5, m6, m7, m8, a;

	for (i = 1; i < height-1; i++) {
		for (j = 1; j < width-1; j+=8) {
			
            //Carga de la imagen
			a = _mm256_loadu_si256((const __m256i *) &img_in[(i ) * width + j]);
			m1 = _mm256_loadu_si256((const __m256i *) &img_in[(i-1) * width + j-1]);
			m2 = _mm256_loadu_si256((const __m256i *) &img_in[(i-1) * width + j]);
			m3 = _mm256_loadu_si256((const __m256i *) &img_in[(i-1) * width + j+1]);
			m4 = _mm256_loadu_si256((const __m256i *) &img_in[(i  ) * width + j-1]);
			m5 = _mm256_loadu_si256((const __m256i *) &img_in[(i  ) * width + j+1]);
			m6 = _mm256_loadu_si256((const __m256i *) &img_in[(i+1) * width + j-1]);
			m7 = _mm256_loadu_si256((const __m256i *) &img_in[(i+1) * width + j]);
			m8 = _mm256_loadu_si256((const __m256i *) &img_in[(i+1) * width + j+1]);

            //Operaciones entre los datos, resta
			val = _mm256_subs_epu8(a, m1);
			val = _mm256_subs_epu8(val, m2);
			val = _mm256_subs_epu8(val, m3);
			val = _mm256_subs_epu8(val, m4);
			val = _mm256_subs_epu8(val, m5);
			val = _mm256_subs_epu8(val, m6);
			val = _mm256_subs_epu8(val, m7);
			val = _mm256_subs_epu8(val, m8);

			//Operaciones entre los datos, suma
            //Esta operacion deberiamos buscar una manera de realizarlo en una unica operacion sin generar dependencia de val con su valor anterior
			val = _mm256_adds_epu8(val, a);
			val = _mm256_adds_epu8(val, a);
			val = _mm256_adds_epu8(val, a);
			val = _mm256_adds_epu8(val, a);
			val = _mm256_adds_epu8(val, a);
			val = _mm256_adds_epu8(val, a);
			val = _mm256_adds_epu8(val, a);

            //Escritura del dato
			_mm256_storeu_si256((__m256i *)&img_out[i*width + j], val);

		}
	}
}

void CopyImage(unsigned char *img_in, unsigned char *img_out, int width, int height) {
	//Declaracion de i/j fuera del bucle for
	int i, j;
	
	//Este bucle for podrían paralelizarse con alguna otra tecnologia
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			img_in[i*width + j] = img_out[i*width + j];
}
