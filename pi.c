double pi_leibniz (int n);
double pi_bbp (int n);

// calculates pi using Leibniz series

double pi_leibniz (int n)
{
    int i;
    double p = 0.;
    double s = 1.;

    for (i = 0; i < n; i++)
    {
        p += s / (2 * i + 1.);
        s = -s;
    }
    return 4 * p;
}

// calculates pi using Bailey-Borwein-Plouffe series

double pi_bbp (int n)
{
    int k, k8;
    double j = 0.;
    double l = 1.;  

    for (k = 0; k < n; k++)
    {
        k8 = 8*k;
        j += ((4. / (k8 + 1)) - (2. / (k8 + 4)) - (1. / (k8 + 5)) -
            (1. / (k8 + 6)))/l;
        l *= 16.;
    }
    return j;
}

