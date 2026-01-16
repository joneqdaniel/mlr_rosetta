#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdalign.h>
#include <sys/param.h>

#define cnt(a) sizeof(typeof((a)))/sizeof(typeof((a)[0]))
#define vec(T,N) typeof(T __attribute__((vector_size(N * sizeof(T)))))
#define sum(a) \
({ \
typeof((a)[0]) dst = 0; \
_Pragma("omp simd reduction(+:dst)") \
for(size_t i = 0; i < cnt(a); i++) \
	dst += (a)[i]; \
dst; \
})

#define dot(a,b) \
({ \
typeof((a)[0]) dst = 0; \
_Pragma("omp simd reduction(+:dst)") \
for(size_t i = 0; i < MIN(cnt(a),cnt(b)); i++) \
	dst += (a)[i] * (b)[i]; \
dst; \
})


int main(int argc, char** argv)
{
	vec(double,4) a = { 1,2,3,4 };
	vec(double,8) b = { 1,2,3,4 };
	printf("%f %f: %zu/%zu\n", dot(a,b), sum(a), alignof(a), sizeof(a));
	exit(EXIT_SUCCESS);
}
