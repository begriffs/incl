#include <stdio.h>

void display(FILE *);
void include(FILE *);

void display(FILE *fp)
{
	int c;
	size_t partial = 0;
	static const char match[] = "#incl(";

	while ((c = getc(fp)) != EOF)
	{
		if (c == match[partial])
		{
			if (++partial == sizeof(match)-1)
			{
				partial = 0;
				include(fp);
			}
		}
		else if (partial > 0)
		{
			printf("%.*s", (int)partial-1, match);
			partial = 0;
		}
		else
			putchar(c);
	}
}

void include(FILE *fp)
{
	char fn[FILENAME_MAX];
	size_t i;
	int c;
	FILE *inner;

	for (i = 0;
	     i < FILENAME_MAX-1 && (c = getc(fp)) != EOF && c != ')';
	     ++i)
		fn[i] = (char)c;
	fn[i] = '\0';

	if (c == ')' && (inner = fopen(fn, "r")) != NULL)
	{
		display(inner);
		fclose(inner);
	}
}

int main(void)
{
	display(stdin);
	return 0;
}
