#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>

enum {int_type, int_type2, long_int_type, unsigned_long_type, long_long_type,
      unsigned_long_long_type, char_type, float_type, double_type, unsigned_type, string_type};

void str_rev(char *s)
{
    int len = strlen (s);
    char s2[100];

    int contor = 0;
    for (int i = len - 1; i>= 0; i --)
        s2[contor++] = s[i];
    s2[contor] = 0;
    strcpy(s,s2);
}

void i_toa (char *str, int n)
{
    int i = 0;
    int neg_sw = 0;

    if (n < 0)
        neg_sw = 1;

    n = abs(n);

    while (n)
    {
        str[i++] = n % 10 + '0';
        n = n/10;
    }

    if (neg_sw)
        str[i++] = '-';

    str[i] = 0;

    str_rev(str);
}

void u_toa (char *str, unsigned n)
{
    int i = 0;

    while (n)
    {
        str[i++] = n % 10 + '0';
        n = n/10;
    }
    str[i] = 0;

    str_rev(str);
}

void longlong_toa (char *str, long long n)
{
    int i = 0;
    int neg_sw = 0;

    if (n < 0)
        neg_sw = 1;

    n = llabs(n);

    while (n)
    {
        str[i++] = n % 10 + '0';
        n = n/10;
    }

    if (neg_sw)
        str[i++] = '-';

    str[i] = 0;

    str_rev(str);
}

void ulonglong_toa (char *str, unsigned long long n)
{
    int i = 0;

    while (n)
    {
        str[i++] = n % 10 + '0';
        n = n/10;
    }

    str[i] = 0;

    str_rev(str);
}

void int_tp (int n)
{
    char s[12];
    i_toa(s, n);
    for (int i = 0; s[i]; i++)
        putchar(s[i]);
}


void litp (long long n)
{
    char s[50];
    longlong_toa(s, n);
    for (int i = 0; s[i]; i++)
        putchar(s[i]);
}

void ultp (unsigned long long n)
{
    char s[50];
    ulonglong_toa(s, n);
    for (int i = 0; s[i]; i++)
        putchar(s[i]);
}

void uns_tp (unsigned n)
{
    char s[15];
    u_toa(s,n);
    for (int i = 0; s[i]; i++)
        putchar(s[i]);

}
int cmp_arg(char *s, int n, char **types)
{
    for (int j = 0; j < n; j++)
        if (strcmp(s, types[j]) == 0)
            return 1;

    return 0;
}

void char_tp(char c)
{
    putchar(c);
}

void string_tp(char *s)
{
    for (int i = 0; s[i]; i++)
        putchar(s[i]);
}

void f_to_a(float n)
{
    long long int x = (int) n;
    int virgula_contor = 0;
    char s[50];

    while (fabs(n-x) > 0.001)
    {
        n*=10;
        x=n;
        virgula_contor++;
    }

    longlong_toa(s, n);
    int len = strlen (s);

    memcpy(s + len - virgula_contor + 1, s + len - virgula_contor, len);

    s[len-virgula_contor] = '.';

    for (int i = 0; s[i]; i++)
        putchar(s[i]);

}

void lf_to_a(double n)
{
    long long int x = (long int) n;
    int virgula_contor = 0;
    char s[50];

    while (fabs(n-x) > 0.001)
    {
        n*=10;
        x=n;
        virgula_contor++;
    }

    longlong_toa(s, n);
    int len = strlen (s);

    memcpy(s + len - virgula_contor + 1, s + len - virgula_contor, len);

    s[len-virgula_contor] = '.';

    for (int i = 0; s[i]; i++)
        putchar(s[i]);

}

int custom_printf(char *format, ...)
{
    va_list valist;

    va_start (valist, format);

    int num_of_formatting_types = 11;

    int processing_arguments = 0;

    char current_arg[10];
    int length = strlen(format);
    int contor;

    char *types[] = {"%d", "%i", "%ld", "%lu", "%lld", "%llu", "%c", "%f", "%lf", "%u", "%s"};

    for (int i = 0; format[i]; i++)
    {
        if (format[i] == '%' && format[i-1] != '\\')
        {
            contor = 0;

            while ( (cmp_arg(current_arg, num_of_formatting_types, types) == 0) && (i < length))
            {
                current_arg[contor++] = format[i];
                i++;
                current_arg[contor] = 0;
            }

            i--;
            current_arg[contor] = 0;

            for (int j = 0; j < num_of_formatting_types; j++)
            {
                if (strcmp(current_arg, types[j]) == 0)
                {
                    processing_arguments++;

                    switch (j)
                    {
                    case int_type:
                        int_tp(va_arg(valist, int));
                        break;

                    case int_type2:
                        int_tp(va_arg(valist, int));
                        break;

                    case long_int_type:
                        litp(va_arg(valist, long));
                        break;

                    case long_long_type:
                        litp(va_arg(valist, long long));
                        break;

                    case unsigned_type:
                        uns_tp(va_arg(valist, unsigned));
                        break;

                    case unsigned_long_long_type:
                        ultp(va_arg(valist, unsigned long long));
                        break;

                    case char_type:
                        char_tp(va_arg(valist, int));
                        break;

                    case string_type:
                        string_tp(va_arg(valist, char*));
                        break;

                    case float_type:
                        f_to_a(va_arg(valist, double));
                        break;

                    case double_type:
                        lf_to_a(va_arg(valist, double));
                        break;
                    }
                }
            }
        }
        else
            putchar(format[i]);
    }

    va_end(valist);

    return processing_arguments;
}

int main()
{
    custom_printf("%d si %lld\n%ld %u %llu %c %s\n", -30, 922337203685477580, 2223232, 70,
                  184467440737095516, 'c', "eva");
    custom_printf("%f %lf\n", 3.14, -3.141592);

    int x = 1;
    double y = 2.2;

    custom_printf("In this custom printf we processed %d arguments",custom_printf("%d\n%lf\n", x,y));

    return 0;
}
