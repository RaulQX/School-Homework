#include <stdio.h>
#include <stdarg.h>
#include <float.h>

typedef struct minmaxim
{
    double minim;
    double maxim;

}minmaxim;

minmaxim find_mm(unsigned n, ...)
{
    va_list valist;
    minmaxim num = {DBL_MAX, DBL_MIN};
    double current_no;

    va_start(valist, n);

    for (int i=0; i<n; i++)
    {
        current_no = va_arg(valist, double);
        if (current_no < num.minim)
            num.minim = current_no;
        if (current_no > num.maxim)
            num.maxim = current_no;
    }

    va_end(valist);

    return num;
}


int main()
{
    minmaxim x = find_mm(5, 2.3, -55.222, 99.629, 302.0, -420.6);
    printf("Max value: %lf\nMin value: %lf", x.maxim, x.minim);
    return 0;
}
