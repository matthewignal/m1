#include <stdio.h>
#include <math.h>

#include "timer.h"

double pi_leibniz (int n);
double pi_bbp (int n);
int adjust_rep_count (int count, double time, double tmin, double tmax);

int main (void)
{
    int i, ileibniz;
    int k, kbbp;
    double tol = 1.e-6, pi, abserr;
    double abserr2, pi2;
    
    // calculation of absolute error for pi using Leibniz series

    i = 1;
    do
    {
        pi = pi_leibniz (i);
        abserr = fabs (pi - M_PI);
        printf ("Leibniz pi = %8d %20.15f %20.15f\n", i, pi, abserr);
        i *= 2;
    }
    while (abserr > tol);
    ileibniz = i / 2;

    k = 1;
   
    // calculation of absolute error for pi using BBP series
    do
    {
        pi2 = pi_bbp (k);
        abserr2 = fabs (pi2 - M_PI);
        printf ("BBP pi =     %8d %20.15f %20.15f\n", k, pi2, abserr2);
        k *= 2;
    }
    while (abserr2 > tol);
    kbbp = k / 2;

    double time, time1, time2, tmin = 1., tmax = 2.;
    int count = 1000;

    // timer of Leibinz calculation

    do
    {

        timer_start ();
        for (i = 0; i < count; i++)
        {
            pi = pi_leibniz (ileibniz);
        }
        time = timer_stop ();

        time1 = time / count;
        printf ("Leibniz: %10.2f usec %10.6f sec %10d\n", time1 * 1.e6, time, count);
        /*
         * adjust count such that cpu time is between
         * tmin and tmax
         */
        count = adjust_rep_count (count, time, tmin, tmax);
    }
    while ((time > tmax) || (time < tmin));

    count = 1000;

    // timer of BBP calculation

    do
    {
        timer_start ();
        for (i = 0; i < count; i++)
        {
            pi = pi_bbp (kbbp);
        }
        time = timer_stop ();

        time2 = time / count;
        printf ("BBP: %10.2f usec %10.6f sec %10d\n", time1 * 1.e6, time, count);
        /*
         * adjust count such that cpu time is between
         * tmin and tmax
         */
        count = adjust_rep_count (count, time, tmin, tmax);
    }
    while ((time > tmax) || (time < tmin));

    // calculates ratio of Leibniz/BBP

    printf ("Speedup: %.2f\n", time1 / time2);

    return 0;
}
