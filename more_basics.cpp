/*
function overloading is same as that of old version of c++
*/
// Function with int parameter
int add(int a, int b) {
    return a + b;
}

// Function with double parameter
double add(double a, double b) {
    return a + b;
}
int function_overloading() {
    cout << "Sum of integers: " << add(5, 3) << endl; // Calls int version
    cout << "Sum of doubles: " << add(5.5, 3.2) << endl; // Calls double version
    return 0;

}

