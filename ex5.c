
#include <stdio.h>
#include <math.h>

double e_x(double x){
    const int N = 100000;
    int counter = 2;
    double sum, factorial;
    factorial = x;
    sum = 1.0;
    while (counter<=N)
    {
        sum+= factorial;
        factorial*= x / counter;
        counter++;
    }
    return  sum;

}

double fab(double x){
    if (x > 0)
        return x;
    else return x * -1;
}
int test(void ){
    int r = 0;

    r = r || (fab((e_x(1.00)) - (exp(1.00))) > 0.0002);
    r = r || (fab((e_x(2.5)) - (exp(2.50))) > 0.0002);
    r = r || (fab((e_x(3.00)) - (exp(3.00))) > 0.0002);
    r = r || (fab((e_x(6.50)) - (exp(6.50))) > 0.0002);

    return r;

}

int main(void)
{
    return test();
}

