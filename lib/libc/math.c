/*
 * Copyright (C) 2020 Jordan DALCQ & contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <math.h>
#include <stddef.h>
#include "kernel/log.h"
#define precision 100

double
pow(double base, double power)
{
    /*
     * Ok, I'm also too lazy to make floating point numbers 
     */
    uint64_t iterator;
    double return_value = 1;


    for (iterator = 0; iterator < power; iterator++)
    {
        return_value *= base;
    }

    return return_value;
}

double
factorial(double number)
{
    double i;
    double return_value = 1;

    for (i = 1; i < number; i++)
    {
        return_value *= i;
    }

    return return_value;
}

double
exp(double x)
{
    size_t k;
    double return_value = 0;

    for (k = 0; k < precision; k++)
    {
        return_value += (pow(x, k) / factorial(k));
    }

    return return_value;
}

int
abs(int j)
{
    if (j < 0)
    {
        return j * -1;
    }

    else
    {
        return j;
    }
}
