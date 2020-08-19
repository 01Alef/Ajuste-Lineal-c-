// Copyright 2020 Fichero

// Aquí mi proyecto: Ajuste Lineal y sus parametros estadisticos.

/*
Este proyecto consiste en hacer un ajuste lineal de la forma
Y = A + BX
Calcula la cosntantes A y B, junto con su incertidumbre sigma_A y sigma_B.
*/


#include<iostream>
#include<math.h>


// Prototipo de funciones

// calcula la parte del denominador
float Delta(float x[10000], double n );

//calcula el valor de la consta A
float A(float x[10000], float y[10000], double n, float delta );

//calcula el valor de la consta B
float B(float x[10000], float y[10000], double n, float delta);

//calcula la incertidumbre en de Y
float sigma_y(float x[10000], float y[10000], double n, float delta);

// Calcula la incertidumbre de A
float sigma_A(float x[10000], float y[10000], float delta, double n);

// calcula la incertidumbre de B
float sigma_B(float x[10000], float y[10000], float delta, double n);


int main(int argc, char const *argv[]) {

  size_t d;
  double n;
  float x[10000], y[10000];
  float s_y, s_A, s_B, a, b, delta;

    do {
      std::cout << "Calculo de las constates A y B (junto con su incertidumbre ) de un ajuste lineal del tipo: Y = A + BX \n " << '\n';
      std::cout << "Ingrese la tamaño N de sus datos: " << '\n';
      std::cin >> n;
      std::cout << "Ingreses los datos de X:" << '\n';
      for (size_t i = 0; i < n; i++) {
        std::cin >> x[i];
      }

      std::cout << "Ingrese los datos de Y:" << '\n';
      for (size_t i = 0; i < n; i++) {
        std::cin >> y[i];
      }

    // Declaracion de las funciones

      delta = Delta(x, n);

      std::cout << '\n';
      std::cout << "resultados" << '\n';
      std::cout << '\n';

      std::cout << "El valor de la constante A es: " << "A = " <<A(x, y, n, delta)<< '\n';
      std::cout << "El valor de la constante B es: " << "B = " << B(x, y, n, delta) << '\n';
      std::cout << '\n';
      std::cout << "Error estándar residual: " << '\n';

      std::cout << "El valor de la sigma_y es: " << "s_y = " << sigma_y(x, y, n, delta) << '\n'<<'\n';

      std::cout << "La incertidumbre de las constantes A y B es:" << '\n';
      std::cout << "El valor de sigma_A es: "<< sigma_A(x, y, delta, n) << '\n';
      std::cout << "El valor de sigma_B es: "<< sigma_B(x, y, delta, n) << '\n';
      std::cout << '\n';
      std::cout << "Por tanto, su modelo de Ajuste lineal es el siguiente:" << '\n';
      std::cout << "Modelo: " << '\n';
      std::cout << "Y = " << A(x, y, n, delta) << " + " <<"(" << B(x, y, n, delta) << ")"<< "X" << '\n';
      std::cout << '\n';

      std::cout << "¿Desea ingresar otro conjunto de datos? (1 para si, 0 para no) :" << '\n';
      std::cin >> d;
      system("clear"); //este comando es para Linux
      // Si usa windows cambiarlo a system("CLS"); se usa para limpiar la pantalla.
    } while(d == 1);


  return 0;
}

// funciones

float Delta(float x[10000], double n ){

  float Delta, suma_x, suma_x2;
  for (size_t i = 0; i < n; i++) {
    suma_x += x[i];
  }
  for (size_t i = 0; i < n; i++) {
    suma_x2 += n*(pow(x[i], 2));
  }
  Delta = suma_x2 - pow(suma_x, 2);

  return Delta;
}

float A(float x[10000], float y[10000], double n, float delta){

  float A, suma_x, suma_x2, suma_xy, suma_y;

  for (size_t i = 0; i < n; i++) {
    suma_x2 += (pow(x[i], 2));
  }

  for (size_t i = 0; i < n; i++) {
    suma_y += y[i];
  }

  for (size_t i = 0; i < n; i++) {
    suma_x += x[i];
  }

  for (size_t i = 0; i < n; i++) {
    suma_xy += x[i]*y[i];
  }

  A = (suma_x2*suma_y - suma_x*suma_xy)/(delta);

  return A;

}


float B(float x[10000], float y[10000], double n, float delta){

  float B, suma1_x, suma1_xy, suma1_y;

  for (size_t i = 0; i < n; i++) {
    suma1_y += y[i];
  }

  for (size_t i = 0; i < n; i++) {
    suma1_x += x[i];
  }

  for (size_t i = 0; i < n; i++) {
    suma1_xy += x[i]*y[i];
  }

  B = (n*suma1_xy - suma1_x*suma1_y)/(delta);

  return B;

}


float sigma_y(float x[10000], float y[10000], double n, float delta){

  float A1, B1, suma2_x, suma2_x2, suma2_xy, suma2_y, suma, sig_y, m;

  for (size_t i = 0; i < n; i++) {
    suma2_x2 += (pow(x[i], 2));
  }

  for (size_t i = 0; i < n; i++) {
    suma2_y += y[i];
  }

  for (size_t i = 0; i < n; i++) {
    suma2_x += x[i];
  }

  for (size_t i = 0; i < n; i++) {
    suma2_xy += x[i]*y[i];
  }

  A1 = (suma2_x2*suma2_y - suma2_x*suma2_xy)/(delta);
  B1 = (n*suma2_xy - suma2_x*suma2_y)/(delta);

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      m = y[i] - A1 - B1*x[i];
    }
    suma += pow(m, 2);
  }

  sig_y = sqrt((1)/(n-2)*suma);

  return sig_y;
}

float sigma_A(float x[10000], float y[10000], float delta, double n){

  float A1, B1, suma2_x, suma2_x2, suma2_xy, suma2_y, suma, sig_y, m, sig_a;

  for (size_t i = 0; i < n; i++) {
    suma2_x2 += (pow(x[i], 2));
  }

  for (size_t i = 0; i < n; i++) {
    suma2_y += y[i];
  }

  for (size_t i = 0; i < n; i++) {
    suma2_x += x[i];
  }

  for (size_t i = 0; i < n; i++) {
    suma2_xy += x[i]*y[i];
  }

  A1 = (suma2_x2*suma2_y - suma2_x*suma2_xy)/(delta);
  B1 = (n*suma2_xy - suma2_x*suma2_y)/(delta);

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      m = y[i] - A1 - B1*x[i];
    }
    suma += pow(m, 2);
  }

  sig_y = sqrt((1)/(n-2)*suma);

  sig_a = sig_y*sqrt((suma2_x2)/(delta));

  return sig_a;

}


float sigma_B(float x[10000], float y[10000], float delta, double n){

  float A1, B1, suma2_x, suma2_x2, suma2_xy, suma2_y, suma, sig_y, m, sig_b;

  for (size_t i = 0; i < n; i++) {
    suma2_x2 += (pow(x[i], 2));
  }

  for (size_t i = 0; i < n; i++) {
    suma2_y += y[i];
  }

  for (size_t i = 0; i < n; i++) {
    suma2_x += x[i];
  }

  for (size_t i = 0; i < n; i++) {
    suma2_xy += x[i]*y[i];
  }

  A1 = (suma2_x2*suma2_y - suma2_x*suma2_xy)/(delta);
  B1 = (n*suma2_xy - suma2_x*suma2_y)/(delta);

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      m = y[i] - A1 - B1*x[i];
    }
    suma += pow(m, 2);
  }

  sig_y = sqrt((1)/(n-2)*suma);

  sig_b = sig_y*sqrt((n)/(delta));

  return sig_b;

}

// fin del proyecto.
