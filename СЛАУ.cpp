//
//  main.cpp
//  отчет №2
//
//  Created by Евгений on 23/10/2020.
//  Copyright © 2020 Евгений. All rights reserved.
//



#include <iostream>
#include <cmath>
#include <ctype.h>
#include <fstream>
using namespace std;

void privet(){
    cout << "Здравствуйте, добрый день! "<<endl;
    cout << "1. Вычисление определителя методом приведения к треугольному виду "<<endl;
    cout << "2. Вычисление определителя по строкам"<<endl;
     cout << "3. СЛАУ методом простой итерации"<<endl;
     cout << "4. СЛАУ методом Зейделя"<<endl;
     cout << "5. СЛАУ через метод Гаусса"<<endl;
     cout << "6. СЛАУ через метод LU - разложения"<<endl;
    cout <<"7. Метод отражения"<<endl;
}

    

void t() {
   /* int counter=0;
    if(counter==0){
    privet();
        counter++;
    }*/
 
    cout<< "Выберите метод и введите его порядковый номер:  ";
    
    int size (0), a(0), b(0), position(0), qus(0);
    char input[1000];
    cin >> input;
    bool in = true;
    for (int i = 0; i < strlen(input); i ++){
        in = in && isdigit(input[i]);
    }
    if (in == true){
        position = atof(input);
    } else {position = 0;}
    if (position < 1 || position > 8){
        a = 0; b = 0; size = 0;
        cout << "В списке такого номера нет."<<endl;
        
        
            cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
            cin>>qus;
            if (qus==1){
                t();
            }else if(qus==2){
                return;
            }
        
    }
    ifstream inputfile;
    inputfile.open("/Users/Evgenij/Documents/otchet2/Untitled.txt");
    bool file = false;
    cout << "Выберите способ ввода матрицы: \n1. Из файла \n2. Вручную "<<endl;
    cin >> input;
    in = true;
    
    for (int i = 0; i < strlen(input); i ++){
        in = in && isdigit(input[i]);
    } if (in == true){
        int intFile = atof(input);
        if (intFile == 1){
            file = true;
        }
    }
    if (file == true){
        cout << "Данные будут переданны из файла"<<endl;
    }
 if (position == 1 || position == 2){
        cout << "Введите порядок определителя матрицы: ";
        cin >> a;
        b = a+1;
        size = a;
        if (!file){
            cout << "Введите определитель: "<<endl;
        }
    } else {
        cout << "Введите количество неизвестных  в системе: ";
        cin >> a;
        b = a;
        if (!file){
            cout << "Введите матрицу по строкам"<< endl;;
        }
    }
    double matrix[a][b];
    bool minus = false;
    for (int i = 0; i < a; i++){
        bool errorHappened = false;
        for (int j = 0; j < b; j++){
            char input[1000] = "";
            if (file){
                inputfile >> input;
            } else {
                cin >> input;
            }
            bool isNumber = true;
            for (int k = 0; k < strlen(input); k++){
                isNumber = isNumber*(isdigit(input[k]) || input[k] == '.' || input[k] == '-');
                if (isNumber == false){
                    errorHappened = true;
                }
            }
            matrix[i][j] = atof(input);
        }
        if (errorHappened) {
            cout << "Вы ввели неверное значение."<<endl;
            cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
            cin>>qus;
            if (qus==1){
                t();
            }else if(qus==2){
                return;
            }
        }
    }
    
    if (!file){
        ofstream outFile;
        outFile.open("/Users/Evgenij/Documents/otchet2/Untitled.txt");
        for (int i = 0; i < a; i++){
            for (int j = 0; j < b; j++){
                outFile << matrix[i][j] << " ";
            }
            outFile << endl;
        }
    }
    
    if(position==7){
        int M(a);
        int N(a+1);
         double S[M]; // вектор столбец
           double e1[M]; // еденичный вектор
           double w[M]; // вектор омега
           double E[M][M]; // еденичная матрица
           double V[M][M]; // матрица отражений V
           double ww[M][M];
        

               // приведение к треугольному виду
           for (int k(0); k < M - 1; k++) {

               for (int i(0); i < M; i++) {
                   (i == k) ? e1[i] = 1 : e1[i] = 0;
                   (i <= k - 1) ? S[i] = 0 : S[i] = matrix[i][k];
               }

               for (int i(0); i < M; i++)
                   for (int j(0); j < M; j++)
                       i == j ? E[i][j] = 1 : E[i][j] = 0;

               double normS(0);    // норма вектора S
               for (int i(0); i < M; i++) normS += S[i] * S[i];
               normS = sqrt(normS);
               for (int i(0); i < M; i++) w[i] = S[i] - normS * e1[i];

               double normW(0);    // норма вектора W
               for (int i(0); i < M; i++) normW += w[i] * w[i];
               normW = sqrt(normW);
               for (int i(0); i < M; i++) w[i] /= normW;
               for (int i(0); i < M; i++)
                   for (int j(0); j < M; j++) ww[i][j] = w[i] * w[j];
               for (int i(0); i < M; i++)
                   for (int j(0); j < M; j++) V[i][j] = E[i][j] - 2 * ww[i][j];

               double tmpForMultiply[M][N];
               for(int i = 0; i < M; i++)
                   for(int j = 0; j < N; j++)
                       for(int k = 0; k < M; k++)
                           tmpForMultiply[i][j] += V[i][k] * matrix[k][j];
                           
               for(int i = 0; i < M; i++)
                   for(int j = 0; j < N; j++)
                       matrix[i][j] = tmpForMultiply[i][j];
           }
           // находим переменные системы
           double x[M];
           for (int i(0); i < M; i++) x[i] = matrix[i][M] / matrix[i][i];
           for (int k = M - 1; k >= 0; k--) {
               x[k] = matrix[k][M];
               double sum = 0;
               for (int i = k + 1; i < M; i++) sum += matrix[k][i] * x[i];
               x[k] -= sum;
               x[k] /= matrix[k][k];
           }
           //заполнение матрицы и вывод вектора значений
           for(int i = 0; i < M; i++)
               for(int j = 0; j < N; j++)
                   matrix
                   [i][j] = matrix[i][j];
           for (int i(0); i < M; i++)
               std::cout << x[i] << endl;
                   

    }
    if (position == 1){ //Вычисление определителя методом приведения к треугольному виду
        double mnozh = 1;
        for (int i = 0; i < size; i++){
            if (matrix[i][i] != 0){
                mnozh = mnozh*matrix[i][i];
            }
            if (matrix[i][i] == 0){
                bool done = false;
                int k = i;
                while (k < size && done == false){
                    if (k != 0){
                        for (int p = 0; p < size; p++){
                            double spare = matrix[p][i];
                            matrix[p][i] = matrix[p][k];
                            matrix[p][k] = spare;
                        }
                        minus = !minus;
                        done = true;
                        mnozh = mnozh*matrix[i][i];
                    }
                    k ++;
                }
                if (done == false){
                    cout << "В определителе 2 одинаковые строки. Значение равно 0"<<endl;
                    cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
                    cin>>qus;
                    if (qus==1){
                        t();
                    }else if(qus==2){
                        return;
                    }
                }
            }
            if (matrix[i][i] != 0){
                double startNumber = matrix[i][i];
                for (int j = 0; j < size; j++){
                    matrix[i][j] = matrix[i][j]/startNumber;
                }
                for (int k = 0; k < size; k++){
                    if (k > i){
                        double kf = matrix[k][i]/matrix[i][i];
                        for (int j = 0; j < size; j++){
                            matrix[k][j] = matrix[k][j] - matrix[i][j]*kf;
                        }
                    }
                }
            } else {
                cout << "В определителе 2 одинаковые строки. Значение равно 0"<<endl;
                cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
                cin>>qus;
                if (qus==1){
                    t();
                }else if(qus==2){
                    return;
                }
            }
   
        }
        
        double result = 1;
        for (int i = 0; i < size; i++){
            result *= matrix[i][i];
        }
        result *= mnozh;
        if (minus){
            result = -result;
        }
        
        cout << endl <<"Результат определителя:"<<endl;
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                if (matrix[i][j] == -0){
                    matrix[i][j] = 0;
                }
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        
        cout << endl << "Ответ: " << result << endl;
     cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
        cin>>qus;
        if (qus==1){
            t();
        }else if(qus==2){
            return;
        }
    }
    
    else if (position == 2){ //определитель по строке
        for (int i = 0; i < size - 2; i++){
            if (matrix[i][i] == 0){
                bool done = false;
                int k = i;
                while (k < size && done == false){
                    if (k != 0){
                        for (int p = 0; p < size; p++){

                            double spare = matrix[p][i];
                            matrix[p][i] = matrix[p][k];
                            matrix[p][k] = spare;
                        }
                        minus = !minus;
                        done = true;
                    }
                    k ++;
                }
                if (done == false){
                    cout << "В определителе 2 одинаковые строки. Значение равно 0"<<endl;
                    cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
                    cin>>qus;
                    if (qus==1){
                        t();
                    }else if(qus==2){
                        return;
                    }
                }
            }
            if (matrix[i][i] != 0){
                for (int k = 0; k < size; k++){
                    if (k > i){
                        double kf = matrix[k][i]/matrix[i][i];
                        for (int j = 0; j < size; j++){
                            matrix[k][j] = matrix[k][j] - matrix[i][j]*kf;
                        }
                    }
                }
            } else {
                cout << "В определителе 2 одинаковые строки. Значение равно 0"<<endl;
                cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
                cin>>qus;
                if (qus==1){
                    t();
                }else if(qus==2){
                    return;
                }
            }
   
        }
        
        double result = 1;
        result = matrix[size-1][size-1]*matrix[size-2][size-2] - matrix[size - 1][size - 2]*matrix[size - 2][size - 1];
        if (size != 2){
            int i = size - 3;
            while (i >= 0){
                result *= matrix[i][i];
                i --;
            }
        }
        if (minus) {result = -result;}
        
        cout << endl <<"Изменённый определитель: "<<endl;
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                if (matrix[i][j] == -0){
                    matrix[i][j] = 0;
                }
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        
        cout << endl << "Результат: " << result << endl;
        cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
        cin>>qus;
        if (qus==1){
            t();
        }else if(qus==2){
            return;
        }
    }
   
    else if (position == 3){ //простая итерация 
        double checkMatrix[a][b];
        
        for (int i = 0; i < a; i++){
            for (int j = 0; j < b; j++){
                checkMatrix[i][j] = matrix[i][j];
            }
        }
        int swappableCols[a];
        for (int i = 0; i < a; i++){
            swappableCols[i] = i+1;
        }
        
        bool appeals = true;
        int col = 0;
        
        while (appeals == true && col < b - 1){
            double left = abs(matrix[col][col]);
            double right = 0;
            for (int i = 0; i < b - 1; i++){
                if (i != col) {right += abs(matrix[col][i]);}
            }
            if (right == 0 && left == 0){
                cout << "Введеннные данные не соответсвуют условиям применимости метода простой итерации"<<endl;
               cout<<"Хотите продолжить работу с программой? 1-да 2-нет: ";
                cin>>qus;
                if (qus==1){
                    t();
                }else
                    return;
                
            }
            if (right >= left){
                bool possible = false;
                for (int i = 0; i < b - 1; i++){
                    if (i != col) {
                        double rowRight = 0;
                        double rowLeft = abs(matrix[col][i]);
                        for (int j = 0; j < b - 1; j++){
                            if (j != i){rowRight += abs(matrix[col][j]);}
                        }
                        if (rowLeft > rowRight) {
                            bool swappable = true;
                            for (int j = 0; j < a; j++){
                                double newRight = 0;
                                double newLeft = abs(matrix[j][i]);
                                for (int k = 0; k < b - 1; k++){
                                    if (k != j){newRight += abs(matrix[j][k]);}
                                }
                                swappable = swappable && (newLeft <= newRight);
                                possible = possible || swappable;
                            }
                            if (swappable == true){
                                for (int j = 0; j < a; j++){
                                    double temp = matrix[j][i];
                                    matrix[j][i] = matrix[j][col];
                                    matrix[j][col] = temp;
                                }
                                int temp = swappableCols[i];
                                swappableCols[i] = swappableCols[col];
                                swappableCols[col] = temp;
                                
                                
                                cout << "Вывод замененых столбцов"<<endl;
                                for (int p = 0; p < a; p++){
                                    for (int r = 0; r < b; r++){
                                        cout << matrix[p][r] << " ";
                                    }
                                    cout << endl;
                                }
                                cout << endl;
                            }
                        }
                    }
                }
                if (possible == false){
                    cout << "Введеннные данные не соответсвуют условиям применимости метода простой итерации"<<endl;
                    
                     cout<<"Хотите продолжить работу с программой? 1-да 2-нет: ";
                            cin>>qus;
                                   if (qus==1){
                                       t();
                                       }else return;
                }
            }
            col++;
        }
        
        cout << "Введите нужную точность приближения: ";
        double e;
        cin >> e;
        
        
        double xp[a];
        
        for (int i = 0; i < a; i++){
            xp[i] = 0;
        }
        
        double x[a];
        
        for (int i = 0; i < a; i++){
            x[i] = matrix[i][b-1] / matrix[i][i]; //нулевое приближение
        }
        
        bool done = true;
        for (int i = 0; i < a; i++){
            bool oneIsDone = abs(xp[i]-x[i]) < e;
            done = done && oneIsDone;
        }
        
        for (int i = 0; i < a; i++){
            xp[i] = x[i];
        }
       
        
        while (done == false){
            for (int i = 0; i < a; i++){
                x[i] = matrix[i][b-1];
                double result = x[i];
                for (int j = 0; j < b - 1; j++){
                    if (j != i){
                        result = result - matrix[i][j]*xp[j];
                    }
                }
                x[i] = result/matrix[i][i];
            }
            done = true;
            for (int i = 0; i < a; i++){
                bool oneIsDone = abs(xp[i]-x[i]) < e;
                done = done && oneIsDone;
            }
            for (int i = 0; i < a; i++){
                xp[i] = x[i];
            }
        }
        
        for (int i = 0; i < a; i++){
            int temp = swappableCols[i];
            for (int j = i; j < a; j++){
                if (temp > swappableCols[j]){
                    int spare = swappableCols[j];
                    swappableCols[j] = swappableCols[i];
                    swappableCols[i] = spare;

                    double spareX = x[j];
                    x[j] = x[i];
                    x[i] = spareX;
                    break;
                }
            }
        }
        
        for (int i = 0; i < a; i++){
            cout << "x" << swappableCols[i] << " = " <<x[i] << endl;
            
            //проверка
            double sum = 0;
            for (int j = 0; j < a; j++){
                sum += checkMatrix[i][j]*x[j];
            }
            cout << "Погрешность: " << abs(checkMatrix[i][b-1] - sum) << endl << endl;
        }
        
       cout<<"Хотите продолжить работу с программой? 1-да 2-нет: ";
                   cin>>qus;
                   if (qus==1){
                       t();
                   }else if(qus==2){
                       return;
                   }
    }

    else if (position == 4){ //метод зейделя
        double checkMatrix[a][b];
        
        for (int i = 0; i < a; i++){
            for (int j = 0; j < b; j++){
                checkMatrix[i][j] = matrix[i][j];
            }
        }
        int swappableCols[a];
        for (int i = 0; i < a; i++){
            swappableCols[i] = i+1;
        }
        
        bool appeals = true;
        int col = 0;
        
        while (appeals == true && col < b - 1){
            double left = abs(matrix[col][col]);
            double right = 0;
            for (int i = 0; i < b - 1; i++){
                if (i != col) {right += abs(matrix[col][i]);}
            }
            if (right == 0 && left == 0){
                cout << "Введеннные данные не соответсвуют условиям применимости метода Зейделя";
                cout<<"Хотите продолжить работу с программой? 1-да 2-нет: ";
                            cin>>qus;
                            if (qus==1){
                                t();
                            }else if(qus==2){
                                return;
                            }
                
            }
            if (right >= left){
                bool possible = false;
                for (int i = 0; i < b - 1; i++){
                    if (i != col) {
                        double rowRight = 0;
                        double rowLeft = abs(matrix[col][i]);
                        for (int j = 0; j < b - 1; j++){
                            if (j != i){rowRight += abs(matrix[col][j]);}
                        }
                        if (rowLeft > rowRight) {
                            bool swappable = true;
                            for (int j = 0; j < a; j++){
                                double newRight = 0;
                                double newLeft = abs(matrix[j][i]);
                                for (int k = 0; k < b - 1; k++){
                                    if (k != j){newRight += abs(matrix[j][k]);}
                                }
                                swappable = swappable && (newLeft <= newRight);
                                possible = possible || swappable;
                            }
                            if (swappable == true){
                                for (int j = 0; j < a; j++){
                                    double temp = matrix[j][i];
                                    matrix[j][i] = matrix[j][col];
                                    matrix[j][col] = temp;
                                }
                                int temp = swappableCols[i];
                                swappableCols[i] = swappableCols[col];
                                swappableCols[col] = temp;
                                cout << "Вывод замененых столбцов: "<<endl;
                                for (int p = 0; p < a; p++){
                                    for (int r = 0; r < b; r++){
                                        cout << matrix[p][r] << " ";
                                    }
                                    cout << endl;
                                }
                                cout << endl;
                            }
                        }
                    }
                }
                if (possible == false){
                    cout << "Введеннные данные не соответсвуют условиям применимости метода Зейделя"<<endl;
                    
                    cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
                              cin>>qus;
                              if (qus==1){
                                  t();
                              }else if(qus==2){
                                  return;
                              }
                }
            }
            col++;
        }
        cout << "Введите нужную точность приближения: ";
        double e;
        cin >> e;
        
        
        double xp[a];
        
        for (int i = 0; i < a; i++){
            xp[i] = 0;
        }
        
        double x[a];
        
        for (int i = 0; i < a; i++){
            x[i] = matrix[i][b-1] / matrix[i][i]; //нулевое приближение
        }
        
        bool done = true;
        for (int i = 0; i < a; i++){
            bool oneIsDone = abs(xp[i]-x[i]) < e;
            done = done && oneIsDone;
        }
        
        for (int i = 0; i < a; i++){
            xp[i] = x[i];
        }
        cout << endl;
        
        while (done == false){
            for (int i = 0; i < a; i++){
                x[i] = matrix[i][b-1];
                double result = x[i];
                for (int j = 0; j < b - 1; j++){
                    if (j > i){
                        result = result - matrix[i][j]*xp[j];
                    } else if (j < i){
                        result = result - matrix[i][j]*x[j];
                    }
                }
                x[i] = result/matrix[i][i];
            }
            done = true;
            for (int i = 0; i < a; i++){
                bool oneIsDone = abs(xp[i]-x[i]) < e;
                done = done && oneIsDone;
            }
            for (int i = 0; i < a; i++){
                xp[i] = x[i];
            }
        }
        
        for (int i = 0; i < a; i++){
            int temp = swappableCols[i];
            for (int j = i; j < a; j++){
                if (temp > swappableCols[j]){
                    int spare = swappableCols[j];
                    swappableCols[j] = swappableCols[i];
                    swappableCols[i] = spare;

                    double spareX = x[j];
                    x[j] = x[i];
                    x[i] = spareX;
                    break;
                }
            }
        }
        
        for (int i = 0; i < a; i++){
            cout << "x" << swappableCols[i] << " = " <<x[i] << endl;
            
            //проверка
            double sum = 0;
            for (int j = 0; j < a; j++){
                sum += checkMatrix[i][j]*x[j];
            }
            cout << "Погрешность= " << abs(checkMatrix[i][b-1] - sum) << endl << endl;
        }

        cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
                  cin>>qus;
                  if (qus==1){
                      t();
                  }else if(qus==2){
                      return;
                  }
    }
    
    

    else if (position == 5){ //гаусс
        double checkMatrix[a][b];
        for (int i = 0; i < a; i++){
            for (int j = 0; j < b; j++){
                checkMatrix[i][j] = matrix[i][j];
            }
        }
        
        int swappableCols[a];
        for (int i = 0; i < a; i++){
            swappableCols[i] = i+1;
        }
        
        for (int i = 0; i < a; i++){
            
            
            for (int p = 0; p < a; p++){
                for (int r = 0; r < b; r++){
                    cout << matrix[p][r] << " ";
                }
                cout << endl;
            }
            cout << endl;
            
            
            if (matrix[i][i] == 0){
                int k = i;
                bool done = false;
                while (k < b - 1 && done == false) {
                    if (matrix[i][k] != 0){
                        done = true;
                        for (int p = 0; p < a; p++){
                            double spare = matrix[p][i];
                            matrix[p][i] = matrix[p][k];
                            matrix[p][k] = spare;
                            
                            int temp = swappableCols[i];
                            swappableCols[i] = swappableCols[k];
                            swappableCols[k] = temp;
                            
                            cout << "Вывод замененых столбцов: "<<endl;
                            for (int q = 0; q < a; q++){
                                for (int r = 0; r < b; r++){
                                    cout << matrix[q][r] << " ";
                                }
                                cout << endl;
                            }
                            cout << endl;
                            
                        }
                    }
                    k++;
                }
                if (done == false){
                    cout << "Ошибка! В матрице обнаружена нулевая строка!"<<endl;
                    cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
                              cin>>qus;
                              if (qus==1){
                                  t();
                              }else if(qus==2){
                                  return;
                              }
                }
            }
            
            double startNumber = matrix[i][i];
            if (matrix[i][i] != 0){
                for (int j = 0; j < b; j++){
                    matrix[i][j] = matrix[i][j]/startNumber;
                }
                for (int k = 0; k < a; k++){
                    if (k > i){
                        double kf = matrix[k][i]/matrix[i][i];
                        for (int j = 0; j < b; j++){
                            matrix[k][j] = matrix[k][j] - matrix[i][j]*kf;
                        }
                    }
                }
            } else {
                cout << "Ошибка! В матрице обнаружена нулевая строка!"<<endl;
                cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
                          cin>>qus;
                          if (qus==1){
                              t();
                          }else if(qus==2){
                              return;
                          }
            }
            
        }
        

        
        double x[a];
        
        for (int i = a-1; i >= 0; i--){
            x[i] = matrix[i][b-1];
            int difference = a - i - 1;
            while (difference > 0){
                x[i] -= matrix[i][b-1-difference] * matrix[a-difference][b-1];
                difference -= 1;
            }
        }
        
        for (int i = 0; i < a; i++){
            int temp = swappableCols[i];
            for (int j = i; j < a; j++){
                if (temp > swappableCols[j]){
                    int spare = swappableCols[j];
                    swappableCols[j] = swappableCols[i];
                    swappableCols[i] = spare;

                    double spareX = x[j];
                    x[j] = x[i];
                    x[i] = spareX;
                    break;
                }
            }
        }
        
        for (int i = 0; i < a; i++){
            cout << "x" << swappableCols[i] << " = " <<x[i] << endl;
            
            //проверка
            double sum = 0;
            for (int j = 0; j < a; j++){
                sum += checkMatrix[i][j]*x[j];
            }
            cout << "Погрешность = " << abs(checkMatrix[i][b-1] - sum) << endl << endl;
        }
        cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
                  cin>>qus;
                  if (qus==1){
                      t();
                  }else if(qus==2){
                      return;
                  }
    }
    
    
    else if (position == 6){                       //lu-разложение
        double checkMatrix[a][b];
        
        for (int i = 0; i < a; i++){
            for (int j = 0; j < b; j++){
                checkMatrix[i][j] = matrix[i][j];
            }
        }
        
        double L[a][b], U[a][b];
        
        for (int i = 0; i < a; i++){
            for (int j = 0; j < b; j++){
                L[i][j] = 0;
                U[i][j] = 0;
            }
        }
        
        for (int i = 0; i < a; i++){
            U[0][i] = matrix[0][i];
            if (U[0][0] != 0){
                L[i][0] = matrix[i][0] / U[0][0];
            } else {
                cout << "Ошибка! Обнаружено деление на нулевой элемент в матрице"<<endl;
                cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
                          cin>>qus;
                          if (qus==1){
                              t();
                          }else if(qus==2){
                              return;
                          }
            }
        }
        
        for (int i = 1; i < a; i++){
            for (int j = i; j < a; j++){
                U[i][j] = matrix[i][j];
                L[j][i] = matrix[j][i];
                double sumU = 0;
                double sumL = 0;
                for (int k = 0; k <= i-1; k++){
                    sumU += L[i][k]*U[k][j];
                    sumL += L[j][k]*U[k][i];
                }
                U[i][j] -= sumU;
                L[j][i] -= sumL;
                if (U[i][i] != 0){
                    L[j][i] = L[j][i]/U[i][i];
                } else {
                    cout <<  "Ошибка! Обнаружено деление на нулевой элемент в матрице"<<endl;
                    cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
                              cin>>qus;
                              if (qus==1){
                                  t();
                              }else if(qus==2){
                                  return;
                              }
                }
            }
        }
        
        
        cout << endl << "L =";
        for (int i = 0; i < a; i++){
            for (int j = 0; j < b - 1; j++){
                cout << L[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl << "U =" ;
        for (int i = 0; i < a; i++){
            for (int j = 0; j < b - 1; j++){
                cout << U[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        
        
        double x[a], y[a];

        for (int i = 0; i < a; i++){
            double sum = 0;
            L[i][b - 1] = matrix[i][b - 1];
            for (int j = 0; j < i; j++){
                sum += L[i][j] * x[j];
            }
            if (L[i][i] != 0){
                x[i] = (L[i][b-1]  - sum)/L[i][i];
            } else {
                cout <<  "Ошибка! Обнаружено деление на нулевой элемент в матрице"<<endl;
                cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
                          cin>>qus;
                          if (qus==1){
                              t();
                          }else if(qus==2){
                              return;
                          }
            }
        }

        for (int i = a - 1; i >= 0; i--){
            double sum = 0;
            double right = x[i];
            for (int j = b - 2; j > i; j--){
                sum += U[i][j] * y[j];
            }
            if (U[i][i] != 0){
                y[i] = (right  - sum)/U[i][i];
            } else {
                cout <<  "Ошибка! Обнаружено деление на нулевой элемент в матрице"<<endl;
                cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
                          cin>>qus;
                          if (qus==1){
                              t();
                          }else if(qus==2){
                              return;
                          }
            }
        }


        
        for (int i = 0; i < a; i++){
            cout << "x" << i << " = " <<y[i] << endl;
            
            //проверка
            double sum = 0;
            for (int j = 0; j < a; j++){
                sum += checkMatrix[i][j]*y[j];
            }
            cout << "Погрешность= " << abs(checkMatrix[i][b-1] - sum) << endl << endl;
        }
        
          cout<<"хотите продолжить работу с программой? 1-да 2-нет: ";
                  cin>>qus;
                  if (qus==1){
                      t();
                  }else if(qus==2){
                      return;
                  }
    }
    
    
    
    
}
int main(){
    privet();
    t();
}

  
