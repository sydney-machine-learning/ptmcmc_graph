#include <iostream>
#include<math.h>
#include<omp.h>

using namespace std;

double f(double x, double y)
{
    double result = 0.002;
    for(int i = -2; i <= 2; i++)
    {
        for(int j = -2; j<=2; j++)
        {
            double temp_res = 1 / (5*(i+2) + j + 3 + std::pow(x - 16*j, 6) + std::pow(y - 16*i, 6));
            result += std::abs(temp_res);
        }
    }
    return 1.0 / result;
}

double integrate(double x_from, double x_to, double y_from, double y_to, double precision){
    int threads = omp_get_max_threads();
    double xInterval = std::abs((x_from - x_to)) / (double)threads;
    double result = 0;
    #pragma omp parallel for
    for(int i = 0; i < threads; i++){
        double x_from_val = i * xInterval;
        double x_to_val = (i + 1) * xInterval;
        double y_from_val = y_from; // we create these variables, to avoid race condtions between different threads and moreover braking the data. Now, this is a thread-local variable.
        double y_to_val = y_to;
        double sum = 0;
        while(x_from_val <= x_to_val)
        {
            double y0 = y_from_val;
            while(y0 <= y_to_val) {
                sum += f((2 * x_from_val + precision) / 2, (2 * y0 + precision) / 2) * precision * precision;
                y0 += precision;
            }
            x_from_val += precision;
        }
        #pragma omp critical
            result += sum;
    }
    return result;
}


int main()
{
    cout << integrate(0, 0, 0, 0, 0.01) << endl;
    return 0;
}
