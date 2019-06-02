#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS 65536

typedef struct {
	char digits[MAX_DIGITS];
	unsigned int nrDigits;
}Number;

Number create_number(char *s)
{
	Number n;
	int l = strlen(s);

	n.nrDigits = l;

	for (int i = 0; i < l; i++)
		n.digits[i] = s[l - i - 1] - '0';

	for (int i = l; i < MAX_DIGITS; i++)
		n.digits[i] = 0;

	return n;
}

Number int_to_number(unsigned int x)
{
	Number n;

	for (int i = 0; i < MAX_DIGITS; i++)
		n.digits[i] = 0;

	if (x == 0)
		n.nrDigits = 1;
	else
	{
		unsigned int i = 0;

		while (x != 0)
		{
			n.digits[i++] = x % 10;
			x /= 10;
		}

		n.nrDigits = i;
	}

	return n;
}

void print_number(Number n)
{
	printf("%u'd", n.nrDigits);
	for (int i = n.nrDigits - 1; i >= 0; i--)
		printf("%u", n.digits[i]);
	printf("\n");
}

Number add(Number a, Number b)
{
	Number c;
	unsigned int m = max(a.nrDigits, b.nrDigits);
	char carry = 0, aux;

	for (int i = 0; i < MAX_DIGITS; i++)
	{
		aux = a.digits[i] + b.digits[i] + carry;

		if (aux >= 10)
		{
			carry = 1;
			c.digits[i] = aux - 10;
		}
		else
		{
			carry = 0;
			c.digits[i] = aux;
		}

		if (i == m - 1)
			c.nrDigits = m + carry;
	}

	return c;
}

Number fibonacci(int n)
{
	Number nr1, nr2, nr3;

	nr1 = int_to_number(0);
	nr2 = int_to_number(1);

	while (n > 1)
	{
		nr3 = add(nr1, nr2);
		nr1 = nr2;
		nr2 = nr3;

		n--;
	}

	return nr3;
}

unsigned int nrLines(FILE *f)
{
	unsigned int n = 0;
	char c;

	while ((c = fgetc(f)) != EOF)
		if (c == '\n')
			n++;

	rewind(f);

	return n;
}

void generateNextFibo(FILE *f, unsigned int top)
{
	unsigned int i = 0;
	char aux[MAX_DIGITS];
	Number nr1, nr2, nr3;

	while (i < top - 1)
	{
		fgets(aux, MAX_DIGITS, f);
		i++;
	}
	aux[strlen(aux) - 1] = '\0';
	nr1 = create_number(aux);

	fgets(aux, MAX_DIGITS, f);
	aux[strlen(aux) - 1] = '\0';
	nr2 = create_number(aux);

	nr3 = add(nr1, nr2);
	for (int i = nr3.nrDigits - 1; i >= 0; i--)
		fputc(nr3.digits[i] + '0', f);
	fputc('\n', f);

	rewind(f);
}

int main()
{
	FILE *f;

	f = fopen("fibo.txt", "r+");
	if (!f)
	{
		printf("Error opening input file!");
		exit(1);
	}
	/*
	for (int i = 0; i < 100; i++)
	{
		system("cls");
		printf("%2.4f %%", (i / 100.) * 100.);
		generateNextFibo(f, nrLines(f));
	}
	*/

	generateNextFibo(f, nrLines(f));

	printf("\nGATA");
	getchar();
	return 0;
}