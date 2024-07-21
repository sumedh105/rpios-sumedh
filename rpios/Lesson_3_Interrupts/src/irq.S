.globl irq_init_vectors
irq_init_vectors:
	adr x0, vectors
	msr vbar_el1, x0
	ret

.globl enable_irq
enable_irq:
	msr daifclr, #2
	ret

.globl disable_irq
disable_irq:
	msr daifset, #2
	ret
