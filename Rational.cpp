/**
 * Copyright [2023] <Junhyoung Lee>
 * Implementation of Scanner for fractional number calculator
 * CSE 374, 23wi, muh after HP
 */

#include <cmath>
#include "Rational.h"

int gg(int a, int b);

namespace Rational374 {

    Rational::Rational() {
        Rational(0, 1);
    }

    Rational::Rational(int n) {
        Rational(n, 1);
    }

    Rational::Rational(int n, int d) {
        int cc = n * d;

        if (cc >= 0) {
            cc = 1;
        } else {
            cc = -1;
        }

        int dd = gg(abs(n), abs(d));
        if (dd != 0) {
            numer_ = cc * n / abs(dd);
            denom_ = cc * d / abs(dd);
        } else {
            numer_ = n;
            denom_ = d;
        }
    }

    int Rational::n() const {
	  if (denom_ > 0) {
	    return numer_ / gg(numer_, denom_);
	    return numer_;
	  } else if (denom_ == 0) {
	    return numer_;
	  } else {
	    return -1 * (numer_ / gg(numer_, denom_));
	    }
    }


    int Rational::d() const {
	  if (denom_ > 0) {
	    return denom_ / gg(numer_, denom_);
	    return denom_;
	  } else if (denom_ == 0) {
	    return denom_;
	  } else {
	    return -1 * (denom_ / gg(numer_, denom_));
	    }
    }



    Rational Rational::plus(Rational other) const {
        int num_1, den_1;
        num_1 = numer_ * other.denom_ + denom_ * other.numer_;
        den_1 = denom_ * other.denom_;
    return Rational(num_1, den_1);
    }

    Rational Rational::minus(Rational other) const {
        int num_1, den_1;
        num_1 = numer_ * other.denom_ - denom_ * other.numer_;
        den_1 = denom_ * other.denom_;
    return Rational(num_1, den_1);
    }

    Rational Rational::times(Rational other) const {
        int num_1, den_1;
        num_1 = numer_ * other.numer_;
        den_1 = denom_ * other.denom_;
    return Rational(num_1, den_1);
    }

    Rational Rational::div(Rational other) const {
        int num_1, den_1;
        num_1 = numer_ * other.denom_;
        den_1 = denom_ * other.numer_;
    return Rational(num_1, den_1);
    }

}

int gg(int a, int b) {
    if (b != 0) {
        return gg((int)abs(b), (int)abs(a) % (int)abs(b));
    } else {
        return a;
    }
}
