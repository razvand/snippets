#ifndef MEASURE_H_
#define MEASURE_H_	1

/* Return a timestamp for use to measure the start of a run. */
__attribute__ ((always_inline)) static inline uint64_t bench_start(void)
{
	unsigned int cycles_low, cycles_high;

	asm volatile( "CPUID\n\t" // serialize
			"RDTSC\n\t" // read clock
			"MOV %%edx, %0\n\t"
			"MOV %%eax, %1\n\t"
			: "=r" (cycles_high), "=r" (cycles_low)
			:: "%rax", "%rbx", "%rcx", "%rdx" );

	return ((uint64_t) cycles_high << 32) | cycles_low;
}

/* Return a timestamp for use to measure the end of a run. */
__attribute__ ((always_inline)) static inline uint64_t bench_end(void)
{
	unsigned int cycles_low, cycles_high;

	asm volatile( "RDTSCP\n\t" /* read clock + serialize */
			"MOV %%edx, %0\n\t"
			"MOV %%eax, %1\n\t"
			"CPUID\n\t" /* serialize -- but outside clock region! */
			: "=r" (cycles_high), "=r" (cycles_low)
			:: "%rax", "%rbx", "%rcx", "%rdx" );

	return ((uint64_t) cycles_high << 32) | cycles_low;
}

#endif
