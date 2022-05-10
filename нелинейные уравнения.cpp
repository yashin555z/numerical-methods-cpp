//
//  main.cpp
//  3отчет
//
//  Created by Евгений on 19/12/2020.
//  Copyright © 2020 Евгений. All rights reserved.
//



 #include <iostream>
 #include <math.h>
#include <iomanip>

  using namespace std;

  double f(double x){//заданная функция1
      return exp(x)+log(x)-10*x;
  }

  double f1(double x){//первая производная1
      return exp(x)+(1/x)-10;
  }

  double f2 (double x){//вторая производная1
      return exp(x)+(1/(x*x));
  }
double f4(double x){//заданная функция2
    return ((x)*tan(x)-0.33333333);
}

double f5(double x){//первая производная2
    return x*(1 + (tan(x))*tan(x)) + tan(x);
}

double f6 (double x){//вторая производная2
    return 2*(1 + tan(x)*tan(x) + x*(1 + tan(x)*tan(x))*tan(x));
}
    double f7(double x){//заданная функция3
         return 3*log(x)*log(x)+6*log(x)-5;
     }

     double f8(double x){//первая производная3
         return 6*log(x)/x+6/x;
     }

     double f9 (double x){//вторая производная3
         return -6*log(x)/(x*x);
     }


 void check(double a){
      if (f(a)*f2(a) >0){
          cout << "Проверка на условие выполнимости не было пройдено. ";
          while (true){
              char a;
              cin >> a;
          }
      }
  }


  
  void sh( double a, double b, double n,double e){//Шаговый метод
      if (a > b){
          double c = a;
          a = b;
          b = c;
      }
      double h = (b - a)/n;
      bool minus = f(a) < 0;
      a -= h;
      while (a < b){
          a += h;
          cout << "x = " << a << "\tf(x) = " << f(a) << endl;
          bool tempMinus = f(a) < 0;
          if (tempMinus != minus){
              a -= h;
              
              cout << "Отрезок,на котором помнялся знак: " << setprecision(7) << "[" << a <<"; "<< a + h <<"]"<< "; e="<<e<<endl;
              break;
          }
      }
  }


  double half(double a, double b, double e){//половинной деление
      int counter(1);
      if (a > b){
          double c = a;
          a = b;
          b = c;
      }
      check(a);
      double xc = (a + b)/2;
      while (abs(f(xc)) > abs(e)){
          counter++;
          if (f(a)*f(xc) < 0){
              b = xc;
          } else {a = xc;}
          xc = (a + b)/2;
      }
      cout << "Метод половинного деления: " << xc;
      cout<<"; Количество действий: "<<counter<<endl;
      return xc;
  }


  double newton(double a, double e){// Метод Нютона
      int counter(1);
      check(a);
      while (abs(f(a)) > abs(e)){
          counter++;
          a = a - f(a)/f1(a);

      }
      cout << "Метод Ньютона: " << a;
      cout<<"; Количество действий: "<<counter<<endl;
      return 0;
  }


  double hord(double a, double b,  double e){  //Метод простой хорд
      int counter(1);
      check(a);
      double prevx = a;
      double x = prevx - (f(prevx)*(prevx - b))/(f(prevx) - f(b));
      while (abs(f(x)) > abs(e)){
          counter++;
          prevx = x;
          x = prevx - (f(prevx)*(prevx - b))/(f(prevx) - f(b));

      }
      cout << "Метод хорд: " << x ;
      cout<<"; Количество действий: "<<counter<<endl;
       return x;
   }


   
   double it(double a, double b, double e){//метод простой итерации
       a=0.1;
       double counter(1);
       b=3.5;
       if (a > b){
           double c = a;
           a = b;
           b = c;
       }
   while (abs(f(a)) > abs(e) && abs(f(b)) > abs(e)){
       counter++;
          double c = a;
          bool minus = f(a) < 0;
          double h = (b - a)/10;
          while (c < b){
              c += h;
              bool tempMinus = f(c) < 0;
              if (minus != tempMinus){
                  a = c-h;
                  b = c;
                  break;
              }
          }
      }
       cout << "Метод простой итерации: " << a;
       cout<<"; Количество действий: "<<counter<<endl;
      return a;
  }




    void check2(double a){
         if (f4(a)*f6(a) >0){
             cout << "Проверка на условие выполнимости не было пройдено. ";
             while (true){
                 char a;
                 cin >> a;
             }
         }
     }


     
     void sh2( double a, double b, double n,double e){//Шаговый метод
         if (a > b){
             double c = a;
             a = b;
             b = c;
         }
         double h = (b - a)/n;
         bool minus = f4(a) < 0;
         a -= h;
         while (a < b){
             a += h;
             cout << "x = " << a << "\tf(x) = " << f4(a) << endl;
             bool tempMinus = f4(a) < 0;
             if (tempMinus != minus){
                 a -= h;
                 cout << "Отрезок,на котором помнялся знак: " << setprecision(7) << "[" << a <<"; "<< a + h <<"]"<< "; e="<<e<<endl;
                 break;
             }
         }
     }


     double half2(double a, double b, double e){//половинной деление
         int counter(1);
         if (a > b){
             double c = a;
             a = b;
             b = c;
         }
         check(a);
         double xc = (a + b)/2;
         while (abs(f4(xc)) > abs(e)){
             counter++;
             if (f4(a)*f4(xc) < 0){
                 b = xc;
             } else {a = xc;}
             xc = (a + b)/2;
         }
         cout << "Метод половинного деления: "<<setprecision(7) << xc;
         cout<<"; Количество действий: "<<counter<<endl;
         return xc;
     }


     double newton2(double a, double e){// Метод Нютона
         int counter(1);
         check(a);
         while (abs(f4(a)) > abs(e)){
             counter++;
             a = a - f4(a)/f5(a);

         }
         cout << "Метод Ньютона: " << a;
         cout<<"; Количество действий: "<<counter<<endl;
         return 0;
     }


     double hord2(double a, double b,  double e){  //Метод простой хорд
         int counter(1);
       //  check2(a);
         double prevx = a;
         double x = prevx - (f4(prevx)*(prevx - b))/(f4(prevx) - f4(b));
         while (abs(f4(x)) > abs(e)){
             counter++;
             prevx = x;
             x = prevx - (f4(prevx)*(prevx - b))/(f4(prevx) - f4(b));

         }
         cout << "Метод хорд: " << x ;
         cout<<"; Количество действий: "<<counter<<endl;
          return x;
      }


      
      double it2(double a, double b, double e){//метод простой итерации
          a=0.1;
          double counter(1);
          b=0.52;
          if (a > b){
              double c = a;
              a = b;
              b = c;
          }
      while (abs(f4(a)) > abs(e) && abs(f4(b)) > abs(e)){
          counter++;
             double c = a;
             bool minus = f4(a) < 0;
             double h = (b - a)/10;
             while (c < b){
                 c += h;
                 bool tempMinus = f4(c) < 0;
                 if (minus != tempMinus){
                     a = c-h;
                     b = c;
                     break;
                 }
             }
         }
          cout << "Метод простой итерации: " << a;
          cout<<"; Количество действий: "<<counter<<endl;
         return a;
     }
    
void check3(double a){
        if (f7(a)*f9(a) >0){
            cout << "Проверка на условие выполнимости не было пройдено. ";
            while (true){
                char a;
                cin >> a;
            }
        }
    }


    
    void sh3( double a, double b, double n,double e){//Шаговый метод
        if (a > b){
            double c = a;
            a = b;
            b = c;
        }
        double h = (b - a)/n;
        bool minus = f7(a) < 0;
        a -= h;
        while (a < b){
            a += h;
            cout << "x = " << a << "\tf(x) = " << f7(a) << endl;
            bool tempMinus = f7(a) < 0;
            if (tempMinus != minus){
                a -= h;
                cout << "Отрезок,на котором помнялся знак: " << setprecision(7) << "[" << a <<"; "<< a + h <<"]"<< "; e="<<e<<endl;
                break;
            }
        }
    }


    double half3(double a, double b, double e){//половинной деление
        int counter(1);
        if (a > b){
            double c = a;
            a = b;
            b = c;
        }
        check(a);
        double xc = (a + b)/2;
        while (abs(f7(xc)) > abs(e)){
            counter++;
            if (f7(a)*f7(xc) < 0){
                b = xc;
            } else {a = xc;}
            xc = (a + b)/2;
        }
        cout << "Метод половинного деления: "<<setprecision(7) << xc;
        cout<<"; Количество действий: "<<counter<<endl;
        return xc;
    }


    double newton3(double a, double e){// Метод Нютона
        int counter(1);
        check(a);
        while (abs(f7(a)) > abs(e)){
            counter++;
            a = a - f7(a)/f8(a);

        }
        cout << "Метод Ньютона: " << a;
        cout<<"; Количество действий: "<<counter<<endl;
        return 0;
    }


    double hord3(double a, double b,  double e){  //Метод простой хорд
        int counter(1);
      //  check2(a);
        double prevx = a;
        double x = prevx - (f7(prevx)*(prevx - b))/(f7(prevx) - f7(b));
        while (abs(f7(x)) > abs(e)){
            counter++;
            prevx = x;
            x = prevx - (f7(prevx)*(prevx - b))/(f7(prevx) - f7(b));

        }
        cout << "Метод хорд: " << x ;
        cout<<"; Количество действий: "<<counter<<endl;
         return x;
     }


     
     double it3(double a, double b, double e){//метод простой итерации
         a=0.1;
         double counter(1);
         b=1.8;
         if (a > b){
             double c = a;
             a = b;
             b = c;
         }
     while (abs(f7(a)) > abs(e) && abs(f7(b)) > abs(e)){
         counter++;
            double c = a;
            bool minus = f7(a) < 0;
            double h = (b - a)/10;
            while (c < b){
                c += h;
                bool tempMinus = f7(c) < 0;
                if (minus != tempMinus){
                    a = c-h;
                    b = c;
                    break;
                }
            }
        }
         cout << "Метод простой итерации: " << a;
         cout<<"; Количество действий: "<<counter<<endl;
        return a;
    }








    int main() {
        //указываем отрезки, количество шагов и точность
        
        double e=0.0000001;
        cout<< "Первая функция: f(x)=exp(x)+log(x)-10*x"<<endl;
       sh(4,3, 10, e);
        half(3.5, 3.6, e);
        newton(3.5, e);
        hord(3.5, 3.6, e);
        it(3.5, 3.6, e);
        cout<<endl;
        cout<< "Вторая функция: f(x)=(x)*tan(x)-0.33"<<endl;
        sh2(1,0.2, 10, e);
        half2(0.52, 0.6, e);
        newton2(0.52, e);
        hord2(0.52, 0.6, e);
        it2(0.52, 0.6, e);
        cout<<endl;
        cout<< "Третья функция: f(x)=3*log(x)*log(x)+6*log(x)-5"<<endl;
        sh3(3, 1, 10, e);
        half3(1.8, 2, e);
        newton3(1.8, e);
        hord3(1.8, 2, e);
        it3(1.8, 2, e);
        
      
    }

