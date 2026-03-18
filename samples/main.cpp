#include "../include/polynomial.h"
#include <iostream>
#include <limits>
void printMenu() {
  std::cout << "\n----- Calculator polynomov -----" << std::endl;
  std::cout << "1. Sum of the polynomials (A + B)" << std::endl;
  std::cout << "2. Subtraction of the polynomials (A - B)" << std::endl;
  std::cout << "3. Multiplying a polynomial by a constant" << std::endl;
  std::cout << "4. Multiplying of the polynomials (A * B)" << std::endl;
  std::cout << "5. Enter new polynomials" << std::endl;
  std::cout << "0. EXIT" << std::endl;
  std::cout << "Select action" << std::endl;
}
int main() {
  Polynomials A, B;
  bool polynomials_initialized = false;
  std::cout << "Welcome to calculator polynomials from 3 variables (x,y,z)!"
            << std::endl;
  std::cout << "Maximum degree of each variable: 9" << std::endl;
  while (true) {
    if (!polynomials_initialized) {
      std::cout << "Enter first polynomial A: " << std::endl;
      std::cin >> A;
      std::cout << "Enter second polynomial B: " << std::endl;
      std::cin >> B;
      std::cout << std::endl;
      std::cout << "Polynomial A: " << A << std::endl;
      std::cout << "Polynomial B: " << B << std::endl;
      polynomials_initialized = true;
    }
    printMenu();
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (choice == 0) {
      std::cout << "Bye!\n";
      break;
    }
    try {
      switch (choice) {
      case 1: {
        Polynomials C = A + B;
        std::cout << "A + B = " << C << std::endl;
        break;
      }
      case 2: {
        Polynomials C = A - B;
        std::cout << "A - B = " << C << std::endl;
        break;
      }
      case 3: {
        double constant;
        std::cout << "Enter constant: ";
        std::cin >> constant;
        std::cout << "A * " << constant << " = " << (A * constant) << std::endl;
        std::cout << "B * " << constant << " = " << (B * constant) << std::endl;
        break;
      }
      case 4: {
        Polynomials C = A * B;
        std::cout << "A * B = " << C << std::endl;
        break;
      }
      case 5: {
        polynomials_initialized = false;
        break;
      }
      default:
        std::cout << "Wrong choice. Try again!\n";
      }
    } catch (const std::exception &e) {
      std::cout << "Error: " << e.what() << std::endl;
    }
  }
  return 0;
}