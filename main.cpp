#include "matrix.h"

using namespace std;

void test_header(int num, string name = "") {		// Helper function
  if (name != "") {
    cerr << "Test " << num << ", " << name << ": ";
  } else {
    cerr << "Test " << num << ": ";
  }
}

/*
  Use this function to check whether two values are within 'epsilon'
  from each other. Floats and doubles are inprecise, so using ==
  to check floats is always a bad idea.   
 */
bool almost_equal(float a, float b) {
  float epsilon = 1e-10;
  return (fabs(a - b) < epsilon);
}

/*
  Verify string representation of a matrix.
 */
void test01() {
  test_header(1, "string representation");
  Matrix A(2,2);
  A.set_element(1, 1, 1.0);
  A.set_element(1, 2, 2.0);
  A.set_element(2, 1, 3.0);
  A.set_element(2, 2, 4.0);
  string A_str = "[[1.000000, 2.000000], [3.000000, 4.000000]]";
  if (A.str() != A_str) {
    cerr << "Failed. Got\n" << A.str() << ",\nbut expected\n" << A_str << "" << endl;
  } else {
    cerr << "Passed" << endl;
  }
}


/*
  Verify string representation of a matrix.
 */
void test02() {
  test_header(2, "string representation");
  Matrix A(3,3);
  string A_str = "[[0.000000, 0.000000, 0.000000], [0.000000, 0.000000, 0.000000], [0.000000, 0.000000, 0.000000]]";
  if (A.str() != A_str) {
    cerr << "Failed. Got\n" << A.str() << ",\nbut expected\n" << A_str << "" << endl;
  } else {
    cerr << "Passed" << endl;
  }
}
/*
  Check that the copy constructor works
*/
void test03(const Matrix &A) {
  test_header(3);
  Matrix B(A);

  if (B.same_as(A)) {
    cerr << "Passed" << endl;
  } else {
    cerr << "Failed, the matrix copy is not the same as the original." << endl;
  }
}

void test04(const Matrix &A, const Matrix &B) {
  test_header(4);
  
  if (A.same_as(B)) {
    cerr << "Passed" << endl;
  } else {
    cerr << "Failed: matrices are reported as different." << endl;
  }
}


void test05(const Matrix &A, const Matrix &B) {
  test_header(5);

  if (A.same_as(B)) {
    cerr << "Failed: matrices are reported as same, but they should  not be." << endl;
  } else {
    cerr << "Passed" << endl;
  }
}


void test06(const Matrix &A, const Matrix &B) {
  test_header(6);

  if (A.same_as(B)) {
    cerr << "Failed, m1 and m4 are reported as same, even though they have different dimensions." << endl;
  } else {
    cerr << "Passed" << endl;
  }
}


  
/*
  Verify that addition A+B is correct.
*/
void test08() {
  test_header(8, "addition");

  Matrix A(2, 2);
  A.set_element(1, 1, 1.0);
  A.set_element(1, 2, 2.0);
  A.set_element(2, 1, 3.0);
  A.set_element(2, 2, 4.0);

  Matrix B(2, 2);
  A.add(B);
  if (almost_equal(A.element(1, 1), 1.0)
      && almost_equal(A.element(1, 2),  2.0)
      && almost_equal(A.element(2, 1),  3.0)
      && almost_equal(A.element(2, 2),  4.0)) {
    cerr << "Passed" << endl;;
  } else {
    cerr << "Failed: Adding two matrices failed" << endl;
    return;
  }
}

/*
  Verify that addition A+A correct.
*/
void test09() {
  test_header(9, "addition");

  Matrix A(2, 2);
  A.set_element(1, 1, 1.0);
  A.set_element(1, 2, 2.0);
  A.set_element(2, 1, 3.0);
  A.set_element(2, 2, 4.0);

  A.add(A);
  if (almost_equal(A.element(1,1), 2.0)
      && almost_equal(A.element(1,2), 4.0)
      && almost_equal(A.element(2,1), 6.0)
      && almost_equal(A.element(2,2), 8.0)) {
    cerr << "Passed" << endl;;
  } else {
    cerr << "Failed: Adding two matrices failed" << endl;
    return;
  }
}

/*
  Verify a simple multiplication
*/
void test10() {
  test_header(10, "multiplication");

  Matrix A(2, 2);
  A.set_element(1, 1, 1.0);
  A.set_element(1, 2, 2.0);
  A.set_element(2, 1, 3.0);
  A.set_element(2, 2, 4.0);

  Matrix B(2, 2);		// Only zeros
  A.multiply(B);
  for (int row=1; row <= 2; row++) {
    for (int col=1; col <= 2; col++) {
      if (! almost_equal(A.element(row, col),  0.0)) {
	cerr << "Failed: Multiplication with a zero matrix must yield a zero matrix." << endl;
	return;
      }
    }
  }
  cerr << "Passed" << endl;
}

/*
  Verify another simple multiplication
*/
void test11() {
  test_header(11, "multiplication");

  Matrix A(2, 2);
  A.set_element(1, 1, 1.0);
  A.set_element(1, 2, 2.0);
  A.set_element(2, 1, 3.0);
  A.set_element(2, 2, 4.0);

  Matrix B(2, 2);		// Only zeros
  B.set_element(1, 1, 1.0);
  B.set_element(1, 2, 2.0);
  B.set_element(2, 1, 3.0);
  B.set_element(2, 2, 4.0);

  A.multiply(B);

  float expected[]={7.0, 10.0, 15.0, 22.0};
  for (int row=1; row <= 2; row++) {
    for (int col=1; col <= 2; col++) {
      int idx = (row - 1) * 2 + (col-1);
      if (!almost_equal(A.element(row, col), expected[idx])) {
	cerr << "Failed. Element (" << row << ", " << col << ") is wrong (" << A.element(row, col) << " instead of " << expected[idx] << ")" << endl;
	return;
      }
    }
  }
  cerr << "Passed" << endl;
}


int main() {
  Matrix m1;
  Matrix m1b;

  Matrix m2(string("m2.txt"));

  Matrix m3(2, 3);
  m3.set_element(1, 1, 1.0);
  m3.set_element(2, 2, 1.0);

  test01();
  test02();
  test03(m3);
  test04(m1, m1b);
  test05(m1, m2);
  test06(m1, m3);
  test08();
  test09();
  test10();
  test11();
}
