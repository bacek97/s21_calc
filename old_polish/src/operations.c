//
// Created by Gladis Ariane on 4/2/22.
//

#include "operations.h"

double eval_add(double a, double b) {
    return a + b;
}

double eval_sub(double a, double b) {
    return a - b;
}

double eval_mul(double a, double b) {
    return a * b;
}

double eval_div(double a, double b) {
    return a / b;
}

double eval_mod(double a, double b) {
    return fmod(a, b);
}

double eval_pow(double a, double b) {
    return pow(a, b);
}

double eval_neg(double a, UNUSED double b) {
    return -a;
}

double eval_sin(double x, UNUSED  double u) {
    return sin(x);
}

double eval_cos(double x, UNUSED  double u) {
    return cos(x);
}

double eval_tan(double x, UNUSED  double u) {
    return tan(x);
}

double eval_sqr(double x, UNUSED double u) {
    return sqrt(x);
}

double eval_ctg(double x, UNUSED double u) {
    return 1 / tan(x);
}

double eval_log(double x, UNUSED double u) {
    return log(x);
}
