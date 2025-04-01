#include "Polynomial.h"
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;

int main() 
{
    Polynomial p1, p2;
    string filename;
    cout << "Enter the name of the polynomial file => ";
    cin >> filename;
    p1.readFromFile(filename);
    cout << "Polynomial 1: ";
    p1.print();
    int choice;
    do 
    {
        cout << "1. ADD polynomial\n";
        cout << "2. MULTIPLY polynomial\n";
        cout << "3. EVALUATE polynomial\n";
        cout << "4. QUIT\n";
        cout << "Enter choice # => ";
        cin >> choice;
        switch (choice) 
        {
        case 1:
        {
            cout << "Enter the file containing the polynomial to add => ";
            cin >> filename;
            p2.readFromFile(filename);
            Polynomial sum = p1.add(p2);
            cout << "Sum: ";
            sum.print();
            break;
        }
        case 2: 
        {
            cout << "Enter the file containing the polynomial to multiply => ";
            cin >> filename;
            p2.readFromFile(filename);
            Polynomial product = p1.multiply(p2);
            cout << "Product: ";
            product.print();
            break;
        }
        case 3: 
        {
            double x;
            cout << "Enter the value of x to evaluate the polynomial => ";
            cin >> x;
            double result = p1.evaluate(x);
            cout << "Evaluation at x = " << x << ": " << result << endl;
            break;
        }
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } 
    while (choice != 4);

    return 0;
}