/*                      Ahmet Hilmi Berber                    */
/*                          171044027                         */
/*                         CSE241 HW01                        */
/*         You can look up my tests at the link below         */
/*  https://github.com/ahmetberber/CSE241FALL2019-HW01-TESTS  */

#include<iostream>

using namespace std;

int main(){
       int L, i, j, k, q, m , n, heart, heartFlag = 0, centerLine = 1; 
       do{
              cin >> L;
       }while(L < 0 || L > 45); /* If input is less than 0 or bigger than 45, user should enter positive integer and this integer must be less than 45 because of the overflow */
       int fibonacci[L]; 
       if(L == 0){ /* If input is 0, that means there is 1 row right there and there is no heart of pyramid */
              heartFlag = 1;
       }
       else if(L % 2 == 0){
              centerLine = (L + 2) / 2 + 1;/* If number of rows are odd, then the heart of pyramid must be under the middle row */
       }
       else{
              centerLine = (L + 1) / 2 + 1;/* If number of rows are even, then the heart of pyramid calculated by given formula */
       }
       fibonacci[0] = 1, fibonacci[1] = 1; /* I have to use the hard coded values because if we want to provide a fibonacci series, we have to initialize the first two numbers at least */ 
       for(i = 0; i < L + 1; i++){
              if(i > 1){/* I created the new fibonacci number for next row */
                     fibonacci[i] = fibonacci[i-1] + fibonacci[i-2];
              }
              for(j = 0; j <= i; j++){/* Here this loop, I calculated the every element in the row at the beginning of each column */
                     q = 0;/* This variable holds the sum of previous two elements in the column */
                     m = 0;/* This variable holds the n's value because n's value have to keep for next number */
                     n = fibonacci[j]; /* This variable holds the next fibonacci element in the column */
                     for(k = 0; k < i - j; k++){
                            q = m + n;
                            m = n;
                            n = q;
                     }
                     q = n;/* and we got the value which we want to print */
                     if(i == centerLine - 1 && j == i / 2){/* The heart of pyramid have to be middle number of the given row */
                            heart = q;
                     }
                     cout << q << " ";
              }
              cout << endl;
       }
       cout << "Biggest number: " << fibonacci[L] << endl;
       if(heartFlag != 1){/* If user did not enter 0 */
              if(centerLine % 2 == 0){/* If length of the center line is even, this means there are 2 numbers at the center */
                     cout << "Heart of the pyramid: " << heart << " " << heart << endl;
              }
              else{/* If length of the center line is odd, this means there are 1 number at the center */
                     cout << "Heart of the pyramid: " << heart << endl;
              }
       }
       else{/* If user entered 0 */
              cout << "Heart of the pyramid: " << endl;
       }
       return 0;
}