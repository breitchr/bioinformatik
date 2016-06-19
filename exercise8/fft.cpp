#include <iostream>
#include <complex>
#include <cmath>
#include <iterator>

using namespace std;

const double PI = 3.1415926536;


//based on
// https://www.safaribooksonline.com/library/view/c-cookbook/0596007612/ch11s18.html
unsigned int bitReverse(unsigned int x, int log2n) {
  int n = 0;
  int mask = 0x1;
  for (int i=0; i < log2n; i++) {
    n <<= 1;
    n |= (x & 1);
    x >>= 1;
  }
  return n;
}

template<class Iter_T>
void fft(Iter_T a, Iter_T b, int log2n)
{
  typedef typename iterator_traits<Iter_T>::value_type complex;
  const complex J(0, 1);
  int n = 1 << log2n;
  for (unsigned int i=0; i < n; ++i) {
    b[bitReverse(i, log2n)] = a[i];
  }
  for (int s = 1; s <= log2n; ++s) {
    int m = 1 << s;
    int m2 = m >> 1;
    complex w(1, 0);
    complex wm = exp(-J * (PI / m2));
    for (int j=0; j < m2; ++j) {
      for (int k=j; k < n; k += m) {
        complex t = w * b[k + m2];
        complex u = b[k];
        b[k] = u + t;
        b[k + m2] = u - t;
      }
      w *= wm;
    }
  }
}

int main(int argc, char* argv[]){
  
  //building the arrays
  complex<double> sinus[16];
  complex<double> cosinus[16];
  complex<double> e_fkt[16];

  //result arrays
  complex<double> sinus_fft[16];
  complex<double> cosinus_fft[16];
  complex<double> e_fkt_fft[16];
  complex<double> sin_cos_con[16];

  //step-array
  double steps[16] = {-PI, -PI*6.0/7, -PI*5.0/7,  -PI*4.0/7, -PI*3.0/7,  -PI*2.0/7, -PI*1.0/7, 0, PI*1.0/7, PI*2.0/7,  PI*3.0/7, PI*4.0/7,  PI*5.0/7, PI*6.0/7, PI*7.0/8, PI};
  double steps_e[16] = {0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875, 1, 1.125, 1.25, 1.375,  1.5, 1.75, 1.875, 2};

  //filling arrays
  for(int i = 0; i < 16; i++){

    sinus[i] = complex<double>(sin(steps[i]), 0);
    cosinus[i] = complex<double>(cos(steps[i]), 0);
    e_fkt[i] = complex<double>(exp(steps_e[i]), 0);

  }

  //calculating ffts
  fft(sinus, sinus_fft, 4);
  fft(cosinus, cosinus_fft, 4);
  fft(e_fkt, e_fkt_fft, 4);

  //calculating convolution16
  for(int i = 0; i < 16; i++){

    sin_cos_con[i] = sinus_fft[i] * cosinus_fft[i];

  }
 
  //printing results
  for(int i = 0; i < 16; i++){

    cout << sinus_fft[i] << ' ';

  }

  cout << "\n\n";

  for(int i = 0; i < 16; i++){

    cout << cosinus_fft[i] << ' ';

  }

  cout << "\n\n";

  for(int i = 0; i < 16; i++){

    cout << e_fkt_fft[i] << ' ';

  }
   
  cout << "\n\n";

  for(int i = 0; i < 16; i++){

    cout << sin_cos_con[i] << ' ';

  }

  cout << '\n';
  
  return 0;
}
