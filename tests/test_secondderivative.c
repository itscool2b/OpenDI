#include <stdio.h>
#include <math.h>
#include "calculus/secondderivative.h"

// Test function: f(x) = x^2, f''(x) = 2
double test_func1(double x) {
    return x * x;
}

// Test function: f(x) = x^3, f''(x) = 6x
double test_func2(double x) {
    return x * x * x;
}

// Test function: f(x) = sin(x), f''(x) = -sin(x)
double test_func3(double x) {
    return sin(x);
}

// Test function: f(x) = e^x, f''(x) = e^x
double test_func4(double x) {
    return exp(x);
}

// Test function: f(x) = 3x + 2, f''(x) = 0 (linear)
double test_func5(double x) {
    return 3 * x + 2;
}

int main() {
    printf("=== Testing second_derivative ===\n");
    
    double h = 0.001;
    
    // Test f(x) = x^2 at x = 3, expected f''(3) = 2
    double result1 = secondderivative(test_func1, 3.0, h);
    printf("f(x)=x^2 at x=3: f''(3) ≈ %.4f (expected: ~2.00, error: %.4f)\n", 
           result1, fabs(result1 - 2.0));
    
    // Test f(x) = x^3 at x = 2, expected f''(2) = 12
    double result2 = secondderivative(test_func2, 2.0, h);
    printf("f(x)=x^3 at x=2: f''(2) ≈ %.4f (expected: ~12.00, error: %.4f)\n", 
           result2, fabs(result2 - 12.0));
    
    // Test f(x) = sin(x) at x = 0, expected f''(0) = -sin(0) = 0
    double result3 = secondderivative(test_func3, 0.0, h);
    printf("f(x)=sin(x) at x=0: f''(0) ≈ %.4f (expected: ~0.00, error: %.4f)\n", 
           result3, fabs(result3 - 0.0));
    
    // Test f(x) = sin(x) at x = pi/2, expected f''(pi/2) = -sin(pi/2) = -1
    double result4 = secondderivative(test_func3, M_PI/2, h);
    printf("f(x)=sin(x) at x=π/2: f''(π/2) ≈ %.4f (expected: ~-1.00, error: %.4f)\n", 
           result4, fabs(result4 - (-1.0)));
    
    // Test f(x) = e^x at x = 1, expected f''(1) = e
    double result5 = secondderivative(test_func4, 1.0, h);
    printf("f(x)=e^x at x=1: f''(1) ≈ %.4f (expected: ~%.4f, error: %.4f)\n", 
           result5, exp(1), fabs(result5 - exp(1)));
    
    // Test f(x) = 3x + 2 at x = 5, expected f''(5) = 0
    double result6 = secondderivative(test_func5, 5.0, h);
    printf("f(x)=3x+2 at x=5: f''(5) ≈ %.4f (expected: ~0.00, error: %.4f)\n", 
           result6, fabs(result6 - 0.0));
    
    // Test h = 0 edge case
    double result7 = secondderivative(test_func1, 3.0, 0.0);
    printf("h=0 edge case: result = %f (expected: NAN)\n", result7);
    
    return 0;
}
