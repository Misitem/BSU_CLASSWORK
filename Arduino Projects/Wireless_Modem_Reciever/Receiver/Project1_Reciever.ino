#define SAMPLES 32    // number of samples
#define SAMPLE_RATE 1000   // microsecond delay between samples

#define TABLELENGTH 128   //1/2 times max samples

#include <avr/pgmspace.h>

double wave[SAMPLES];     //input goes here
double freqmag[SAMPLES];      // output is placed here
int pitchVal = 0;
double t = 0.0;

const double costable[] PROGMEM={1.0, 0.9997, 0.9988, 0.9973, 0.9952, 0.9925, 0.9892, 0.9853, 0.9808, 0.9757, 0.97, 0.9638, 0.9569, 0.9495, 0.9415, 0.933, 0.9239, 0.9142, 0.904, 0.8932, 0.8819, 0.8701, 0.8577, 0.8449, 0.8315, 0.8176, 0.8032, 0.7883, 0.773, 0.7572, 0.741, 0.7242, 0.7071, 0.6895, 0.6716, 0.6532, 0.6344, 0.6152, 0.5957, 0.5758, 0.5556, 0.535, 0.5141, 0.4929, 0.4714, 0.4496, 0.4276, 0.4052, 0.3827, 0.3599, 0.3369, 0.3137, 0.2903, 0.2667, 0.243, 0.2191, 0.1951, 0.171, 0.1467, 0.1224, 0.098, 0.0736, 0.0491, 0.0245, 0.0, -0.0245, -0.0491, -0.0736, -0.098, -0.1224, -0.1467, -0.171, -0.1951, -0.2191, -0.243, -0.2667, -0.2903, -0.3137, -0.3369, -0.3599, -0.3827, -0.4052, -0.4276, -0.4496, -0.4714, -0.4929, -0.5141, -0.535, -0.5556, -0.5758, -0.5957, -0.6152, -0.6344, -0.6532, -0.6716, -0.6895, -0.7071, -0.7242, -0.741, -0.7572, -0.773, -0.7883, -0.8032, -0.8176, -0.8315, -0.8449, -0.8577, -0.8701, -0.8819, -0.8932, -0.904, -0.9142, -0.9239, -0.933, -0.9415, -0.9495, -0.9569, -0.9638, -0.97, -0.9757, -0.9808, -0.9853, -0.9892, -0.9925, -0.9952, -0.9973, -0.9988, -0.9997};
const double sintable[] PROGMEM={-0.0, -0.0245, -0.0491, -0.0736, -0.098, -0.1224, -0.1467, -0.171, -0.1951, -0.2191, -0.243, -0.2667, -0.2903, -0.3137, -0.3369, -0.3599, -0.3827, -0.4052, -0.4276, -0.4496, -0.4714, -0.4929, -0.5141, -0.535, -0.5556, -0.5758, -0.5957, -0.6152, -0.6344, -0.6532, -0.6716, -0.6895, -0.7071, -0.7242, -0.741, -0.7572, -0.773, -0.7883, -0.8032, -0.8176, -0.8315, -0.8449, -0.8577, -0.8701, -0.8819, -0.8932, -0.904, -0.9142, -0.9239, -0.933, -0.9415, -0.9495, -0.9569, -0.9638, -0.97, -0.9757, -0.9808, -0.9853, -0.9892, -0.9925, -0.9952, -0.9973, -0.9988, -0.9997, -1.0, -0.9997, -0.9988, -0.9973, -0.9952, -0.9925, -0.9892, -0.9853, -0.9808, -0.9757, -0.97, -0.9638, -0.9569, -0.9495, -0.9415, -0.933, -0.9239, -0.9142, -0.904, -0.8932, -0.8819, -0.8701, -0.8577, -0.8449, -0.8315, -0.8176, -0.8032, -0.7883, -0.773, -0.7572, -0.741, -0.7242, -0.7071, -0.6895, -0.6716, -0.6532, -0.6344, -0.6152, -0.5957, -0.5758, -0.5556, -0.535, -0.5141, -0.4929, -0.4714, -0.4496, -0.4276, -0.4052, -0.3827, -0.3599, -0.3369, -0.3137, -0.2903, -0.2667, -0.243, -0.2191, -0.1951, -0.171, -0.1467, -0.1224, -0.098, -0.0736, -0.0491, -0.0245};

void _myfft(double* x, double* rv, int N)
{
  int k,i;
  double wr,wi;

  if (N<=1)
  {
    rv[0]=x[0];
    rv[1]=0;
    return;
  }

  double xx[N/2];
  for (i=0; i<N/2; i++)
    xx[i]=x[i*2];
  double evens[N];
  _myfft(xx,evens,N/2);

  for (i=0; i<N/2; i++)
    xx[i]=x[i*2+1];
  double odds[N];
  _myfft(xx,odds,N/2);

  double Tr[N/2];
  double Ti[N/2];

  for(k=0; k<N/2; k++)
  {
    int index=2*k*TABLELENGTH/N;
    if(index<TABLELENGTH)
    {
        wr=pgm_read_float_near(costable+index);
        wi=pgm_read_float_near(sintable+index);
    }
    else
    {
      wr=-costable[index-TABLELENGTH];
      wi=-sintable[index-TABLELENGTH];
    }
    Tr[k]=odds[k]*wr - odds[k+N/2]*wi;
    Ti[k]=odds[k+N/2]*wr + odds[k]*wi;
  }
  for(k=0; k<N/2; k++)
  {
    rv[k]=evens[k]+Tr[k];
    rv[k+N]=evens[k+N/2]+Ti[k];
    rv[k+N/2]=evens[k]-Tr[k];
    rv[k+N+N/2]=evens[k+N/2]-Ti[k];
  }
}


void myfft()
{
  double F[SAMPLES*2];
  _myfft(wave,F,SAMPLES);

  for(int n=0; n<SAMPLES; n++)
  {
    freqmag[n]=F[n]*F[n] + F[n+SAMPLES]*F[n+SAMPLES];
  }
}

void setup() {
  Serial.begin(9600);
    
}

 int getPitch(){
  myfft();
  double highest = 0.01;
  double test[SAMPLES];
  
  for(int i=0; i < 32; i++){
    test[i] = analogRead(0) / 1024.0;
    
    while(micros()-t<SAMPLE_RATE);
      t=micros();

  }
  

  for(int i=0; i<SAMPLES; i++)
  {
    wave[i]=test[i];
  }

 /** for(int i=0;i < SAMPLES/2; i++){
    Serial.println(i);
    Serial.println(freqmag[i]);
  }
  **/

  
  for(int i=1; i < SAMPLES/2; i++)
  {
    if(freqmag[i] > highest)
    {
      highest = freqmag[i];
      pitchVal = i;
    }
    
    else
    {
      pitchVal = -1;
    }
  }
return pitchVal;

}

void loop(){
  //getPitch();
  Serial.println(getPitch());
   delay(1000);
}

