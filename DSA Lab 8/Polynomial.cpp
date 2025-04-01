#include "Polynomial.h"
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;


Term::Term(double coeff, int exp) : coefficient(coeff), expree(exp), next(nullptr) {}

Polynomial::Polynomial() : head(nullptr) {}

Polynomial::~Polynomial()
{
    while (head) 
    {
        Term* temp = head;
        head = head->next;
        delete temp;
    }
}

void Polynomial::readFromFile(const string& filename) 
{
    ifstream file(filename);
    if (!file) 
    {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line)) 
    {
        istringstream iss(line);
        double coeff;
        char x, pow;
        int exp;
        while (iss >> coeff >> x >> pow >> exp) 
        {
            addTerm(coeff, exp);
        }
    }
}

void Polynomial::addTerm(double coeff, int exp) 
{
    if (coeff == 0)
    {
        return;
    }
    Term* newTerm = new Term(coeff, exp);
    if (!head || head->expree > exp) 
    {
        newTerm->next = head;
        head = newTerm;
        return;
    }
    Term* current = head;
    while (current->next && current->next->expree < exp) 
    {
        current = current->next;
    }
    if (current->expree == exp) 
    {
        current->coefficient += coeff;
        if (current->coefficient == 0) 
        {
            Term* toDelete = current;
            head = current->next;
            delete toDelete;
        }
    }
    else 
    {
        newTerm->next = current->next;
        current->next = newTerm;
    }
}

Polynomial Polynomial::add(const Polynomial& other) const 
{
    Polynomial result;
    Term* current = head;
    Term* otherCurrent = other.head;
    while (current || otherCurrent) 
    {
        if (!current)
        {
            result.addTerm(otherCurrent->coefficient, otherCurrent->expree);
            otherCurrent = otherCurrent->next;
        }
        else if (!otherCurrent) 
        {
            result.addTerm(current->coefficient, current->expree);
            current = current->next;
        }
        else if (current->expree < otherCurrent->expree) 
        {
            result.addTerm(current->coefficient, current->expree);
            current = current->next;
        }
        else if (current->expree > otherCurrent->expree) 
        {
            result.addTerm(otherCurrent->coefficient, otherCurrent->expree);
            otherCurrent = otherCurrent->next;
        }
        else 
        {
            result.addTerm(current->coefficient + otherCurrent->coefficient, current->expree);
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
    }
    return result;
}

Polynomial Polynomial::multiply(const Polynomial& other) const 
{
    Polynomial result;
    for (Term* current = head; current; current = current->next) 
    {
        for (Term* otherCurrent = other.head; otherCurrent; otherCurrent = otherCurrent->next) 
        {
            result.addTerm(current->coefficient * otherCurrent->coefficient, current->expree + otherCurrent->expree);
        }
    }
    return result;
}

double Polynomial::evaluate(double x) const 
{
    double result = 0.0;
    for (Term* current = head; current; current = current->next) 
    {
        result += current->coefficient * pow(x, current->expree);
    }
    return result;
}

void Polynomial::print() const 
{
    Term* current = head;
    while (current) 
    {
        cout << current->coefficient << "x^" << current->expree;
        if (current->next)
        {
            cout << " + ";
        }
        current = current->next;
    }
    cout << endl;
}