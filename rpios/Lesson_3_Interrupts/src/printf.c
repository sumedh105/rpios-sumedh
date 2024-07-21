#include <stdarg.h>
#include "printf.h"

typedef void (*putcf)(void *, char);
static putcf stdout_putf;
static void *stdout_putp;

void init_printf(void *putp, void (*putf)(void *, char))
{
	stdout_putf = putf; 
	stdout_putp = putp;
}

int getStringLength(char *str)
{
	int length = 0;

	while (*str) {
		++length;
		str++;
	}
	
	return length;
}

void reverse(char str[])
{
	int temp;
	int leftIndex = 0;
	int rightIndex = getStringLength(str) - 1;

	while (leftIndex < rightIndex) {
		temp = str[leftIndex];
		str[leftIndex] = str[rightIndex];
		str[rightIndex] = temp;

		++leftIndex;
		--rightIndex;
	}
}

int print_octal_number(int ival, void *putp, putcf putf)
{
	int no_of_chars = 0;
	char str[8];
	int index = 0;
	int num = ival;

	while (num) {
		str[index++] = (num % 8) + '0';
		num = num / 8;
	}

	str[index] = '\0';

	reverse(str);

	for (index = 0; str[index] != '\0'; index++) {
		//write(1, &str[index], 1);
		//putchar(str[index])
		putf(putp, str[index]);
		no_of_chars++;
	}

	return no_of_chars;
}

int print_hex_number(int ival, void *putp, putcf putf)
{
	int no_of_chars = 0;
	char str[16];
	int index = 0;
	int num = ival;

	while (num) {
		if ((num % 16) > 9) {
			str[index++] = (num % 16) - 10 + 'a';
		}
		else {
			str[index++] = (num % 16) + '0';
		}

		num = num / 16;
	}

	str[index] = '\0';

	reverse(str);

	for (index = 0; str[index] != '\0'; index++) {
		//write(1, &str[index], 1);
		putf(putp, str[index]);
		no_of_chars++;
	}

	return no_of_chars;
}

int print_decimal_number(int ival, void *putp, putcf putf)
{
	int no_of_chars = 0;
	int c;
	char str[10];
	int index = 0;
	int num = ival;

	if (num < 0) {
		//putchar('-');
		c = '-';
		//write(1, &c, 1);
		putf(putp, c);
		num = num * -1;
		no_of_chars++;
	}
	while (num) {
		str[index] = (num % 10) + '0';
		num = num / 10;
		index++;
	}
	str[index] = '\0';

	reverse(str);

	for (index = 0; str[index] != '\0'; index++) {
		//putchar(str[index]);
		//write(1, &str[index], 1);
		putf(putp, str[index]);
		no_of_chars++;
	}

	return no_of_chars;
}

int printf(char *fmt, ...)
{
	va_list ap;
	char *p;
	char *cval;
	char *sval;
	int ival;
	//double dval;
	int no_of_chars = 0;

	va_start(ap, fmt);

	for (p = fmt; *p; p++) {
		if (*p != '%') {
			//write(1, p, 1);
			//putchar(*p);
			stdout_putf(stdout_putp, *p);
			no_of_chars++;
			continue;
		}
		switch(*++p) {
			case 'c':
				cval = va_arg(ap, char *);
				//write(1, cval, 1);
				stdout_putf(stdout_putp, *cval);
				no_of_chars++;
				break;
			case 'd':
			case 'i':
				ival = va_arg(ap, int);
				no_of_chars += print_decimal_number(ival, stdout_putp, stdout_putf);					
				break;
			case 'x':
			case 'X':
				ival = va_arg(ap, int);
				no_of_chars += print_hex_number(ival, stdout_putp, stdout_putf);
				break;
			case 'o':
				ival = va_arg(ap, int);
				no_of_chars += print_octal_number(ival, stdout_putp, stdout_putf);
				break;
#if 0
			case 'p':
				break;
#endif
			case 's':
				sval = va_arg(ap, char *);
				while (*sval) {
					//putchar(*sval);
					//write(1, sval, 1);
					stdout_putf(stdout_putp, *sval);
					sval++;
					no_of_chars++;
				}
				break;
#if 0
			case 'f':
				dval = va_arg(ap, double);
				//no_of_chars += print_double_number(dval);
				break;
			case 'u':
				ival = va_arg(ap, int);
				//no_of_chars += print_unsigned_number(ival);
				break;
#endif
			default:
				break;
		}
	}

	va_end(ap);

	return no_of_chars;
}

#if 0
int main()
{
	int no_of_bytes = 0;
	int age = -37;
	int age_hex = 174;
	int age_octal = 48;
	char c = 'a';
	char *str = "Sumedh W. Jambekar";

	myPrintf("This is Sumedh and c: %c\n", c);
	myPrintf("This is Sumedh and str: %s\n", str);
	myPrintf("Age is: %d\n", age);
	myPrintf("Age in hex is: %x\n", age_hex);
	myPrintf("Age in octal is: %o\n", age_octal);

	return 0;
}
#endif


