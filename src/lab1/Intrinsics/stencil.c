#include <stdio.h>
#include <stdlib.h>
#include "stencil.h"
#include <immintrin.h>

void ApplyStencil(unsigned char *img_in, unsigned char *img_out, int width, int height) 
{
	
	//Caracter sin signo
	unsigned char val_out;
	
	//Declaracion de i/j fuera del bucle for
	int i, j;
	
	//Variables de transicion para almacenar los datos
	__m256i valor, nodo1, nodo2, nodo3, nodo4, nodo5, nodo6, nodo7, nodo8, nodoCentro;

	for (i = 1; i < height-1; i++) 
	{
		for (j = 1; j < width-1; j+=8) 
		{
			
            //Carga de la imagen
			nodoCentro = _mm256_loadu_si256((const __m256i *) &img_in[(i ) * width + j]);//centro
			nodo1 = _mm256_loadu_si256((const __m256i *) &img_in[(i-1) * width + j-1]);//arriba-izquierda
			nodo2 = _mm256_loadu_si256((const __m256i *) &img_in[(i-1) * width + j]);//arriba
			nodo3 = _mm256_loadu_si256((const __m256i *) &img_in[(i-1) * width + j+1]);//arriba-derecha
			nodo4 = _mm256_loadu_si256((const __m256i *) &img_in[(i  ) * width + j-1]);//izquierda
			nodo5 = _mm256_loadu_si256((const __m256i *) &img_in[(i  ) * width + j+1]);//derecha
			nodo6 = _mm256_loadu_si256((const __m256i *) &img_in[(i+1) * width + j-1]);//abajo-izquierda
			nodo7 = _mm256_loadu_si256((const __m256i *) &img_in[(i+1) * width + j]);//abajo
			nodo8 = _mm256_loadu_si256((const __m256i *) &img_in[(i+1) * width + j+1]);//abajo-derecha

            //Operaciones entre los datos, resta
			valor = _mm256_subs_epu8(nodoCentro, nodo1);
			valor = _mm256_subs_epu8(valor, nodo2);//valor - arriba
			valor = _mm256_subs_epu8(valor, nodo3);//valor - (arriba-derecha)
			valor = _mm256_subs_epu8(valor, nodo4);//valor - izquierda
			valor = _mm256_subs_epu8(valor, nodo5);//valor - derecha
			valor = _mm256_subs_epu8(valor, nodo6);//valor - (abajo-izquierda)
			valor = _mm256_subs_epu8(valor, nodo7);//valor - (abajo)
			valor = _mm256_subs_epu8(valor, nodo8);//valor - (abajo-derecha)

			//Operaciones entre los datos, suma
			valor = _mm256_adds_epu8(valor, nodoCentro);
			valor = _mm256_adds_epu8(valor, nodoCentro);
			valor = _mm256_adds_epu8(valor, nodoCentro);
			valor = _mm256_adds_epu8(valor, nodoCentro);
			valor = _mm256_adds_epu8(valor, nodoCentro);
			valor = _mm256_adds_epu8(valor, nodoCentro);
			valor = _mm256_adds_epu8(valor, nodoCentro);

            //Escritura del dato
			_mm256_storeu_si256((__m256i *)&img_out[i*width + j], valor);

		}
	}
}

void CopyImage(unsigned char *img_in, unsigned char *img_out, int width, int height) 
{
	//Este bucle for podría paralelizarse con alguna otra tecnologia
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			img_in[i*width + j] = img_out[i*width + j];
}
