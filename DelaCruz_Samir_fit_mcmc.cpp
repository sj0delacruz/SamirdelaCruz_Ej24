#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include <random>

using namespace std; 

int leerArchivo(string nombreArchivo, double* &z);
float f(double* c, int gradoPoli, float x_obs);
float logProbabilidad(double* c, int gradoPoli);
void MCMC_polinominal(int n_pasos, int gradoPoli);

double* x = NULL;
double* y = NULL;
int n_xy;

int main(){
  long double t=214.232424531253624345362;
  cout << t;
  n_xy=leerArchivo("valores_x.txt", x);
  n_xy=leerArchivo("valores_y.txt", y);
  srand48(time(0));
  MCMC_polinominal(1000000,3);
  
  return 0;
}

float f(double* c, int gradoPoli, float x_obs){
  float y_ajust=0;
  for (int n=0; n<gradoPoli+1;n++){
    y_ajust+=c[n]*pow(x_obs,n);
  }
  return y_ajust;
}
float logProbabilidad(double* c, int gradoPoli){
  float logprobabilidad=0;
  for (int i=0;i<n_xy;i++){
    logprobabilidad+=-0.5*pow(y[i]-f(c, gradoPoli, x[i]), 2);
  }
  return logprobabilidad;
}
void MCMC_polinominal(int n_pasos, int gradoPoli){
  float dp=0.1;
  float alpha,r;
  double* antPaso=new double[gradoPoli+1];
  for (int j=0;j<n_pasos;j++){
    double* sigPaso=new double[gradoPoli+1];
    for (int k=0;k<gradoPoli+1;k++){
      sigPaso[k]=antPaso[k] + 2*(drand48()-0.5)*dp;
    }
    alpha=drand48();
    r=exp(logProbabilidad(sigPaso,3)-logProbabilidad(antPaso,3));
    if (r>1){
      r=1;
    }
    if (alpha<r){
      antPaso=sigPaso;
    }
    cout << antPaso[0];
    for (int k=1;k<gradoPoli+1;k++){
      cout << " " << antPaso[k];
    }
    cout << endl;
  }
}

int leerArchivo(string nombreArchivo, double* &z){
  ifstream infile; 
  string line;
  int n = 0;

  infile.open(nombreArchivo);
  while(infile){
    n+=1;
    getline(infile, line);
  }
  infile.close();

  infile.open(nombreArchivo);
  z=new double[n];
  for (int i=0; i<n;i++){
    getline(infile,line);
    z[i]=atof(line.c_str());
  }
  infile.close();

  return n;
}