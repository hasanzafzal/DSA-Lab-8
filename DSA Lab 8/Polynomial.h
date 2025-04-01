#pragma once
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;

class Term 
{
public:
    double coefficient;
    int expree;
    Term* next;
    Term(double coeff, int exp);
};

class Polynomial 
{
private:
    Term* head;
public:
    Polynomial();
    ~Polynomial();
    void readFromFile(const std::string& filename);
    void addTerm(double coeff, int exp);
    Polynomial add(const Polynomial& other) const;
    Polynomial multiply(const Polynomial& other) const;
    double evaluate(double x) const;
    void print() const;
};

#endif