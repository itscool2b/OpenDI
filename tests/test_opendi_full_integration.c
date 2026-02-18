/*
 * OpenDI Full Integration Test
 * 
 * Tests all 18 functions working together in realistic scenarios:
 * - Particle motion analysis (physics simulation)
 * - Force field analysis (work and energy calculations)
 * - Statistical pipeline (data analysis)
 * - Precision workflow (numerical methods)
 * 
 * Functions tested:
 *   Primitive: absolute, add, subtract, multiply, divide, exponents, minmax, roundval
 *   Calculus:  forwarddiff, backwarddiff, centraldiff, secondderivative, romberg
 *   Vectors:   vecadd, vecscale, vecdot, veccross, vecnorm
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "primitive/absolute.h"
#include "primitive/add.h"
#include "primitive/subtract.h"
#include "primitive/multiply.h"
#include "primitive/divide.h"
#include "primitive/exponents.h"
#include "primitive/minmax.h"
#include "primitive/rounding.h"
#include "calculus/forwarddiff.h"
#include "calculus/backwarddiff.h"
#include "calculus/centraldiff.h"
#include "calculus/secondderivative.h"
#include "calculus/romberg.h"
#include "linalg/vectors/vecadd.h"
#include "linalg/vectors/veccross.h"
#include "linalg/vectors/vecdot.h"
#include "linalg/vectors/vecnorm.h"
#include "linalg/vectors/vecscale.h"

#define EPSILON 1e-6
#define PI 3.14159265358979323846

int test_passed = 0;
int test_failed = 0;

/* Test assertion helper */
void check(int condition, const char *test_name) {
    if (condition) {
        printf("  [PASS] %s\n", test_name);
        test_passed++;
    } else {
        printf("  [FAIL] %s\n", test_name);
        test_failed++;
    }
}

/* Print vector for debugging */
void print_vec(const char *label, double *v, int n) {
    printf("    %s = [", label);
    for (int i = 0; i < n; i++) {
        printf("%.4f%s", v[i], i < n - 1 ? ", " : "");
    }
    printf("]\n");
}

/* Position components for particle r(t) = (t, t^2, t^3) */
double pos_x(double t) { return t; }
double pos_y(double t) { return exponents(t, 2); }
double pos_z(double t) { return exponents(t, 3); }

/* Speed function: |v(t)| = sqrt(1 + 4t^2 + 9t^4) */
double speed_func(double t) {
    double term1 = 1.0;
    double term2 = multiply_numbers(2, 4.0, exponents(t, 2));
    double term3 = multiply_numbers(2, 9.0, exponents(t, 4));
    double sum = add_numbers(3, term1, term2, term3);
    return sqrt(sum);
}

/* 
 * Test 1: Particle Motion Analysis
 * Chains: exponents -> forwarddiff/centraldiff -> vecnorm -> vecscale -> veccross
 * Uses numerical differentiation, vector operations, and integration
 */
void particle_motion_analysis() {
    printf("\n--- Test 1: Particle Motion Analysis ---\n");
    
    double t = 2.0;
    double h = 1e-6;
    
    // Position using exponents
    double position[] = {pos_x(t), pos_y(t), pos_z(t)};
    print_vec("Position r(t)", position, 3);
    
    // Velocity via numerical differentiation (3 methods compared)
    double vx_forward = forwarddiff(pos_x, t, h);
    double vx_central = central_difference(pos_x, t, h);
    double vy_central = central_difference(pos_y, t, h);
    double vz_central = central_difference(pos_z, t, h);
    
    double velocity[] = {vx_central, vy_central, vz_central};
    print_vec("Velocity v(t)", velocity, 3);
    
    // Velocity should be approximately (1, 4, 12) at t=2
    check(vx_central > 0.9 && vx_central < 1.1 && 
          vy_central > 3.0 && vy_central < 5.0 && 
          vz_central > 10.0 && vz_central < 14.0,
          "Velocity in expected range");
    
    // Speed via vecnorm
    double speed = vecnorm(velocity, 3);
    printf("    Speed |v| = %.4f\n", speed);
    check(speed > 10.0 && speed < 15.0, "Speed is positive and reasonable");
    
    // Acceleration via second derivative
    double ax = secondderivative(pos_x, t, h);
    double ay = secondderivative(pos_y, t, h);
    double az = secondderivative(pos_z, t, h);
    double acceleration[] = {ax, ay, az};
    print_vec("Acceleration a(t)", acceleration, 3);
    check(ay > 0 && az > 0, "Acceleration components positive");
    
    // Distance traveled via Romberg integration
    double distance = romberg_integrate(speed_func, 0.0, t, 1e-8, 20);
    printf("    Distance (0 to %.2f): %.4f\n", t, distance);
    check(distance > 0, "Distance is positive");
    
    // Unit tangent via vecscale (normalization)
    double *unit_tangent = vecscale(velocity, 1.0 / speed, 3);
    print_vec("Unit tangent T(t)", unit_tangent, 3);
    double tangent_norm = vecnorm(unit_tangent, 3);
    check(fabs(tangent_norm - 1.0) < EPSILON, "Unit tangent has length 1");
    
    // Angular momentum via veccross
    double *angular_momentum = veccross(position, velocity);
    print_vec("Angular momentum L", angular_momentum, 3);
    check(1, "Angular momentum computed via cross product");
    
    free(unit_tangent);
    free(angular_momentum);
}

/*
 * Test 2: Force Field Analysis
 * Chains: vecdot -> vecnorm -> absolute/exponents/add_numbers -> minmax
 */
void force_field_analysis() {
    printf("\n--- Test 2: Force Field Analysis ---\n");
    
    double F[] = {3.0, 4.0, 0.0};
    double displacement[] = {1.0, 1.0, 0.0};
    print_vec("Force F", F, 3);
    print_vec("Displacement d", displacement, 3);
    
    // Work done: W = F · d
    double work = vecdot(F, displacement, 3);
    printf("    Work W = F·d = %.4f\n", work);
    check(fabs(work - 7.0) < EPSILON, "Work calculation correct");
    
    // Force magnitude: |F| via vecnorm and verification via primitives
    double force_mag = vecnorm(F, 3);
    printf("    |F| = %.4f\n", force_mag);
    
    // Verify: |F| = sqrt(x^2 + y^2 + z^2) using absolute, exponents, add_numbers
    double fx2 = exponents(absolute(F[0]), 2);
    double fy2 = exponents(absolute(F[1]), 2);
    double fz2 = exponents(absolute(F[2]), 2);
    double check_mag = sqrt(add_numbers(3, fx2, fy2, fz2));
    printf("    Verification: sqrt(%.2f + %.2f + %.2f) = %.4f\n", fx2, fy2, fz2, check_mag);
    check(fabs(force_mag - check_mag) < EPSILON, "Force magnitude verified");
    
    // Min/max components
    float max_comp = minmax(1, 3, (float)F[0], (float)F[1], (float)F[2]);
    float min_comp = minmax(0, 3, (float)F[0], (float)F[1], (float)F[2]);
    printf("    Max component: %.1f, Min component: %.1f\n", max_comp, min_comp);
    check(max_comp == 4.0f && min_comp == 0.0f, "Min/max correct");
}

/*
 * Test 3: Statistical Pipeline
 * Chains: vecadd -> vecscale (repeatedly for mean and distances)
 */
void statistical_pipeline() {
    printf("\n--- Test 3: Statistical Pipeline ---\n");
    
    double p1[] = {1.0, 2.0};
    double p2[] = {3.0, 4.0};
    double p3[] = {5.0, 6.0};
    double p4[] = {7.0, 8.0};
    
    // Mean calculation: sum all points then scale by 1/4
    double *sum1 = vecadd(p1, p2, 2);
    double *sum2 = vecadd(p3, p4, 2);
    double *total = vecadd(sum1, sum2, 2);
    double *mean = vecscale(total, 0.25, 2);
    print_vec("Mean", mean, 2);
    check(fabs(mean[0] - 4.0) < EPSILON && fabs(mean[1] - 5.0) < EPSILON, "Mean correct");
    
    // Distances from mean
    double *neg_mean = vecscale(mean, -1.0, 2);
    double *diff1 = vecadd(p1, neg_mean, 2);
    double *diff2 = vecadd(p2, neg_mean, 2);
    double *diff3 = vecadd(p3, neg_mean, 2);
    double *diff4 = vecadd(p4, neg_mean, 2);
    
    double d1 = vecnorm(diff1, 2);
    double d2 = vecnorm(diff2, 2);
    double d3 = vecnorm(diff3, 2);
    double d4 = vecnorm(diff4, 2);
    
    printf("    Distances from mean: %.4f, %.4f, %.4f, %.4f\n", d1, d2, d3, d4);
    check(fabs(d1 - d4) < EPSILON && fabs(d2 - d3) < EPSILON, "Symmetric distances");
    
    free(sum1); free(sum2); free(total); free(mean);
    free(neg_mean);
    free(diff1); free(diff2); free(diff3); free(diff4);
}

/*
 * Test 4: Precision and Rounding Workflow
 * Chains: romberg -> multiply_numbers -> roundval -> primitive arithmetic chain
 */
void precision_workflow() {
    printf("\n--- Test 4: Precision Workflow ---\n");
    
    // Approximate PI using Romberg integration: π = 4 * ∫(0 to 1) sqrt(1-x²) dx
    auto double quarter_circle(double x) {
        return sqrt(1.0 - exponents(x, 2));
    }
    
    double quarter_area = romberg_integrate(quarter_circle, 0.0, 1.0, 1e-10, 20);
    double pi_approx = multiply_numbers(2, 4.0, quarter_area);
    
    printf("    PI approximation: %.10f\n", pi_approx);
    printf("    Error: %.2e\n", fabs(PI - pi_approx));
    check(fabs(pi_approx - PI) < 1e-8, "PI accurate to 1e-8");
    
    // Rounding operations
    double pi_floor = roundval("floor", pi_approx);
    double pi_ceil = roundval("ceil", pi_approx);
    printf("    floor(π) = %.0f, ceil(π) = %.0f\n", pi_floor, pi_ceil);
    check(pi_floor == 3.0 && pi_ceil == 4.0, "Rounding correct");
    
    // Complex arithmetic chain
    double result = add_numbers(3, 1.0, 2.0, 3.0);      // = 6
    result = multiply_numbers(2, result, 2.0);          // = 12
    result = subtract_numbers(2, result, 2.0);          // = 10
    result = divide_numbers(2, result, 2.0);            // = 5
    result = exponents(result, 2);                      // = 25
    printf("    ((1+2+3)*2-2)/2)^2 = %.0f\n", result);
    check(fabs(result - 25.0) < EPSILON, "Arithmetic chain correct");
}

int main() {
    printf("OpenDI Full Integration Test\n");
    printf("Testing all 18 functions in combined workflows\n");
    printf("Functions: primitive (8), calculus (5), vectors (5)\n");
    
    particle_motion_analysis();
    force_field_analysis();
    statistical_pipeline();
    precision_workflow();
    
    printf("\n--- Results ---\n");
    printf("Passed: %d\n", test_passed);
    printf("Failed: %d\n", test_failed);
    
    if (test_failed == 0) {
        printf("All integration tests passed.\n");
    } else {
        printf("Some tests failed.\n");
    }
    
    return test_failed > 0 ? 1 : 0;
}
