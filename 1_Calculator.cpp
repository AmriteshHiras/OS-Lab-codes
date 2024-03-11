#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int calc(int choice, int a, int b){
    switch(choice){
        case 1:{
            cout << "Sum of " << a << ", " << b << " is: " << a + b << "\n";
            break;
        }
        case 2:{
            cout << "Difference of " << a << ", " << b << " is: " << a - b << "\n";
            break;
        }
        case 3:{
            cout << "Product of " << a << ", " << b << " is: " << a * b << "\n";
            break;
        }
        case 4:{
            cout << "Division of " << a << ", " << b << " is: " << a / b << "\n";
            break;
        }
        case 5:{
            cout << "HCf of " << a << ", " << b << " is: " << __gcd(a, b) << "\n";
            break;
        }
        case 6:{
            cout << "LCM of " << a << ", " << b << " is: " << (a * b)/__gcd(a, b) << "\n";
            break;
        }
        case 7:{
            cout << "ThankYou!\n";
            break;
        }
        default:{
            cout << "Invalid input!\n";
            break;
        }
    }
}

int main(){
    int choice, a, b;
    cout << "Type the number provided before the command you would like to execute:-\n";
    cout << "1. Add two numbers\n2. Difference of two numbers\n3. Product of two numbers\n";
    cout << "4. Division of two numbers\n5. Highest common factor of two numbers\n";
    cout << "6. Least common multiple of two numbers\n7. Exit\n";
    while(choice != 7){
        cout << "Enter choice: ";
        cin >> choice;
        if (choice != 7){
            cout << "Enter first number: ";
            cin >> a;
            cout << "Enter second number: ";
            cin >> b;
            calc(choice, a, b);
        }
        else{
            calc(choice, 0, 0);
        }
    }
}