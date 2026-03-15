#include "pch.h"
#include "../../include/polynomial.h"

TEST(PolynomialTest, test_default_constructor_creates_empty_polynomial) {
	Polynomials p;
	EXPECT_TRUE(p.isEmpty());
}
TEST(PolynomialTest, test_Default_constructor_Size_is_zero) {
	Polynomials p;
	EXPECT_EQ(p.size(), 0);
}
TEST(PolynomialTest, test_Copy_constructor_Size_matches) {
	Polynomials p1;
	p1.parseFromString("2x + 3y");
	Polynomials p2(p1);
	EXPECT_EQ(p2.size(), p1.size());
}
TEST(PolynomialTest, test_Copy_constructor_Coefficients_match) {
	Polynomials p1;
	p1.parseFromString("2x + 3y");
	Polynomials p2(p1);
	auto monoms1 = p1.getMonoms();
	auto monoms2 = p2.getMonoms();
	EXPECT_NEAR(monoms1[0].koefficient, monoms2[0].koefficient, 1e-10);
}
TEST(PolynomialTest, test_Copy_constructor_Degree_match) {
	Polynomials p1;
	p1.parseFromString("2x + 3y");
	Polynomials p2(p1);
	auto monoms1 = p1.getMonoms();
	auto monoms2 = p2.getMonoms();
	EXPECT_EQ(monoms1[0].degree, monoms2[0].degree);
}
TEST(PolynomialTest, test_Assignment_operator_Content_matches) {
	Polynomials p1;
	p1.parseFromString("x^2 + y^2");
	Polynomials p2;
	p2 = p1;
	auto monoms1 = p1.getMonoms();
	auto monoms2 = p2.getMonoms();
	EXPECT_NEAR(monoms1[0].koefficient, monoms2[0].koefficient, 1e-10);
}
TEST(PolynomialTest, test_Parse_simple_polinomial_Size) {
	Polynomials p;
	p.parseFromString("2x + 3y - 4z");
	EXPECT_EQ(p.size(), 3);
}
TEST(PolynomialTest, test_Parse_simple_polynomial_DegreeX) {
	Polynomials p;
	p.parseFromString("2x + 3y - 4z");
	auto monoms = p.getMonoms();
	EXPECT_EQ(monoms[0].degree, 100);
}
TEST(PolynomialTest, test_Parse_simple_polynomial_CoeffX) {
	Polynomials p;
	p.parseFromString("2x + 3y - 4z");
	auto monoms = p.getMonoms();
	EXPECT_NEAR(monoms[0].koefficient, 2.0, 1e-10);
}
TEST(PolynomialTest, test_Parse_decimal_coefficient_3_75) {
	Polynomials p;
	p.parseFromString("3.75x");
	auto monoms = p.getMonoms();
	EXPECT_NEAR(monoms[0].koefficient, 3.75, 1e-10);
}
TEST(PolynomialTest, test_Parse_coefficient_without_integer_0_5) {
	Polynomials p;
	p.parseFromString(".5x");
	auto monoms = p.getMonoms();
	EXPECT_NEAR(monoms[0].koefficient, 0.5, 1e-10);
}
TEST(PolynomialTest, test_Parse_missing_coefficient_X) {
	Polynomials p;
	p.parseFromString("x");
	auto monoms = p.getMonoms();
	EXPECT_NEAR(monoms[0].koefficient, 1.0, 1e-10);
}
TEST(PolynomialTest, test_Parse_missing_coefficient_Y) {
	Polynomials p;
	p.parseFromString("y");
	auto monoms = p.getMonoms();
	EXPECT_NEAR(monoms[0].koefficient, 1.0, 1e-10);
}
TEST(PolynomialTest, test_Parse_missing_coefficient_Z) {
	Polynomials p;
	p.parseFromString("z");
	auto monoms = p.getMonoms();
	EXPECT_NEAR(monoms[0].koefficient, 1.0, 1e-10);
}
TEST(PolynomialTest, test_Parse_empty_string_Returns_False) {
	Polynomials p;
	EXPECT_FALSE(p.parseFromString(""));
}
TEST(PolynomialTest, test_Parse_zero_Is_empty) {
	Polynomials p;
	p.parseFromString("0");
	EXPECT_TRUE(p.isEmpty());
}
TEST(PolynomialTest, test_addition_Result_size) {
	Polynomials p1, p2;
	p1.parseFromString("2x + 3y");
	p2.parseFromString("x - y");
	Polynomials result = p1 + p2;
	EXPECT_EQ(result.size(), 2);
}
TEST(PolynomialTest, test_addition_coefficient_X) {
	Polynomials p1, p2;
	p1.parseFromString("2x + 3y");
	p2.parseFromString("x - y");
	Polynomials result = p1 + p2;
	auto monoms = result.getMonoms();
	EXPECT_NEAR(monoms[0].koefficient, 3.0, 1e-10);
}
TEST(PolynomialTest, test_addition_coefficient_Y) {
	Polynomials p1, p2;
	p1.parseFromString("2x + 3y");
	p2.parseFromString("x - y");
	Polynomials result = p1 + p2;
	auto monoms = result.getMonoms();
	ASSERT_EQ(monoms.size(), 2);
	bool foundY = false;
	for (const auto& m : monoms) {
		if (m.degree == 10) {
			EXPECT_NEAR(m.koefficient, 2.0, 1e-10);
			foundY = true;
			break;
		}
	}
	EXPECT_TRUE(foundY);
}
TEST(PolynomialTest, test_addition_cancellation_empty) {
	Polynomials p1, p2;
	p1.parseFromString("2x + 3y");
	p2.parseFromString("-2x - 3y");
	Polynomials result = p1 + p2;
	EXPECT_TRUE(result.isEmpty());
}
TEST(PolynomialTest, test_addition_with_empty_Size_same) {
	Polynomials p1, empty;
	p1.parseFromString("2x + 3y");
	Polynomials result = p1 + empty;
	EXPECT_EQ(result.size(), p1.size());
}
TEST(PolynomialTest, test_subtraction_Result_size) {
	Polynomials p1, p2;
	p1.parseFromString("5x - 3y");
	p2.parseFromString("2x + y");
	Polynomials result = p1 - p2;
	EXPECT_EQ(result.size(), 2);
}
TEST(PolynomialTest, test_subtraction_Coefficient_x) {
	Polynomials p1, p2;
	p1.parseFromString("5x - 3y");
	p2.parseFromString("2x + y");
	Polynomials result = p1 - p2;
	auto monoms = result.getMonoms();
	EXPECT_NEAR(monoms[0].koefficient, 3.0, 1e-10);
}
TEST(PolynomialTest, test_subtraction_Coefficient_y) {
	Polynomials p1, p2;
	p1.parseFromString("5x - 3y");
	p2.parseFromString("2x + y");
	Polynomials result = p1 - p2;
	auto monoms = result.getMonoms();
	EXPECT_NEAR(monoms[1].koefficient, -4.0, 1e-10);
}
TEST(PolynomialTest, test_subtraction_Cancellation_empty) {
	Polynomials p1, p2;
	p1.parseFromString("2x + 3y");
	p2.parseFromString("2x + 3y");
	Polynomials result = p1 - p2;
	EXPECT_TRUE(result.isEmpty());
}
TEST(PolynomialTest, test_Multiply_by_positive_constant_Size) {
	Polynomials p;
	p.parseFromString("2x - 3y + 4");
	Polynomials result = p * 2.5;
	EXPECT_EQ(result.size(), 3);
}
TEST(PolynomialTest, test_Multiply_by_positive_constant_CoeffX) {
	Polynomials p;
	p.parseFromString("2x - 3y + 4");
	Polynomials result = p * 2.5;
	auto monoms = result.getMonoms();
	EXPECT_NEAR(monoms[0].koefficient, 5.0, 1e-10);
}
TEST(PolynomialTest, test_Multiply_by_positive_constant_CoeffY) {
	Polynomials p;
	p.parseFromString("2x - 3y + 4");
	Polynomials result = p * 2.5;
	auto monoms = result.getMonoms();
	EXPECT_NEAR(monoms[1].koefficient, -7.5, 1e-10);
}
TEST(PolynomialTest, test_Multiply_by_positive_constant_Constant) {
	Polynomials p;
	p.parseFromString("2x - 3y + 4");
	Polynomials result = p * 2.5;
	auto monoms = result.getMonoms();
	EXPECT_NEAR(monoms[2].koefficient, 10.0, 1e-10);
}
TEST(PolynomialTest, test_Multiply_by_negative_constant_CoeffX) {
	Polynomials p;
	p.parseFromString("2x - 3y");
	Polynomials result = p * (-2.0);
	auto monoms = result.getMonoms();
	EXPECT_NEAR(monoms[0].koefficient, -4.0, 1e-10);
}
TEST(PolynomialTest, test_Multiply_by_zero_Empty) {
	Polynomials p;
	p.parseFromString("2x + 3y");
	Polynomials result = p * 0.0;
	EXPECT_TRUE(result.isEmpty());
}
TEST(PolynomialTest, test_Multiply_by_simple_Size) {
	Polynomials p1, p2;
	p1.parseFromString("x + y");
	p2.parseFromString("x - y");
	Polynomials result = p1 * p2;
	EXPECT_EQ(result.size(), 2);
}
TEST(PolynomialTest, test_Multiply_by_simple_Coeff_x2) {
	Polynomials p1, p2;
	p1.parseFromString("x + y");
	p2.parseFromString("x - y");
	Polynomials result = p1 * p2;
	auto monoms = result.getMonoms();
	EXPECT_NEAR(monoms[0].koefficient, 1.0, 1e-10);
}
TEST(PolynomialTest, test_Multiply_by_simple_Coeff_y2) {
	Polynomials p1, p2;
	p1.parseFromString("x + y");
	p2.parseFromString("x - y");
	Polynomials result = p1 * p2;
	auto monoms = result.getMonoms();
	EXPECT_NEAR(monoms[1].koefficient, -1.0, 1e-10);
}
TEST(PolynomialTest, test_Multiply_different_vars_DegreeXZ) {
	Polynomials p1, p2;
	p1.parseFromString("2x + 3y");
	p2.parseFromString("4z");
	Polynomials result = p1 * p2;
	auto monoms = result.getMonoms();
	EXPECT_EQ(monoms[0].degree, 101);
}
TEST(PolynomialTest, test_Multiply_different_vars_DegreeYZ) {
	Polynomials p1, p2;
	p1.parseFromString("2x + 3y");
	p2.parseFromString("4z");
	Polynomials result = p1 * p2;
	auto monoms = result.getMonoms();
	EXPECT_EQ(monoms[1].degree, 11);
}
TEST(PolynomialTest, test_Multiply_different_vars_CoeffXZ) {
	Polynomials p1, p2;
	p1.parseFromString("2x + 3y");
	p2.parseFromString("4z");
	Polynomials result = p1 * p2;
	auto monoms = result.getMonoms();
	EXPECT_NEAR(monoms[0].koefficient, 8.0, 1e-10);
}
TEST(PolynomialTest, test_Multiply_different_vars_CoeffYZ) {
	Polynomials p1, p2;
	p1.parseFromString("2x + 3y");
	p2.parseFromString("4z");
	Polynomials result = p1 * p2;
	auto monoms = result.getMonoms();
	EXPECT_NEAR(monoms[1].koefficient, 12.0, 1e-10);
}
TEST(PolynomialTest, test_Multiply_with_zero_Empty) {
	Polynomials p, zero;
	p.parseFromString("2x + 3y");
	Polynomials result = p * zero;
	EXPECT_TRUE(result.isEmpty());
}
TEST(PolynomialTest, test_Degree_exceed_x_throws) {
	Polynomials p1, p2;
	p1.parseFromString("x^9");
	p2.parseFromString("x^2");
	EXPECT_THROW(p1 * p2, std::runtime_error);
}
TEST(PolynomialTest, test_Combine_like_terms_Size) {
	Polynomials p;
	p.parseFromString("2x + 3x - x");
	EXPECT_EQ(p.size(), 1);
}
TEST(PolynomialTest, test_Combine_like_terms_Coefficient) {
	Polynomials p;
	p.parseFromString("2x + 3x - x");
	auto monoms = p.getMonoms();
	EXPECT_NEAR(monoms[0].koefficient, 4.0, 1e-10);
}
TEST(PolynomialTest, test_Complex_combining_Size) {
	Polynomials p;
	p.parseFromString("2x^2y + 3xy^2 - x^2y + 2xy^2 + 5");
	EXPECT_EQ(p.size(), 3);
}
TEST(PolynomialTest, test_Complex_combining_Coeff_X2Y) {
	Polynomials p;
	p.parseFromString("2x^2y + 3xy^2 - x^2y + 2xy^2 + 5");
	auto monoms = p.getMonoms();
	EXPECT_NEAR(monoms[0].koefficient, 1.0, 1e-10);
}
TEST(PolynomialTest, test_Complex_combining_Coeff_XY2) {
	Polynomials p;
	p.parseFromString("2x^2y + 3xy^2 - x^2y + 2xy^2 + 5");
	auto monoms = p.getMonoms();
	EXPECT_NEAR(monoms[1].koefficient, 5.0, 1e-10);
}
TEST(PolynomialTest, test_Remove_zeros_addition_X_Disappears) {
	Polynomials p1, p2;
	p1.parseFromString("2x + 3y");
	p2.parseFromString("-2x + y");
	Polynomials result = p1 + p2;
	auto monoms = result.getMonoms();
	bool foundX = false;
	for (const auto& m : monoms) {
		if (m.degree == 100) foundX = true;
	}
	EXPECT_FALSE(foundX);
}
TEST(PolynomialTest, test_Remove_zeros_subtraction_Y_Disappears) {
	Polynomials p1, p2;
	p1.parseFromString("2x + 3y");
	p2.parseFromString("2x + 3y");
	Polynomials result = p1 - p2;
	EXPECT_TRUE(result.isEmpty());
}
TEST(PolynomialTest, test_Complete_cancellation_Empty) {
	Polynomials p;
	p.parseFromString("x + y - x - y");
	EXPECT_TRUE(p.isEmpty());
}
TEST(PolynomialTest, test_Sort_descending_first_Is_X3) {
	Polynomials p;
	p.parseFromString("z + x^2y + 5 + x^3");
	auto monoms = p.getMonoms();
	EXPECT_EQ(monoms[0].degree, 300);
}
TEST(PolynomialTest, test_Sort_descending_second_Is_X2Y) {
	Polynomials p;
	p.parseFromString("z + x^2y + 5 + x^3");
	auto monoms = p.getMonoms();
	EXPECT_EQ(monoms[1].degree, 210);
}
TEST(PolynomialTest, test_Sort_descending_second_last_Is_Z) {
	Polynomials p;
	p.parseFromString("z + x^2y + 5 + x^3");
	auto monoms = p.getMonoms();
	EXPECT_EQ(monoms[monoms.size() - 2].degree, 1);
}
TEST(PolynomialTest, test_Sort_descending_last_Is_constant) {
	Polynomials p;
	p.parseFromString("z + x^2y + 5 + x^3");
	auto monoms = p.getMonoms();
	EXPECT_EQ(monoms[monoms.size() - 1].degree, 0);
}
TEST(PolynomialTest, test_max_degree_999) {
	Polynomials p;
	p.parseFromString("x^9y^9z^9");
	auto monoms = p.getMonoms();
	EXPECT_EQ(monoms[0].degree, 999);
}
TEST(PolynomialTest, test_zero_degree_constant) {
	Polynomials p;
	p.parseFromString("x^0y^0z^0 + 5");
	auto monoms = p.getMonoms();
	bool foundConstant = false;
	for (const auto& m : monoms) {
		if (m.degree == 0) foundConstant = true;
	}
	EXPECT_TRUE(foundConstant);
}
TEST(PolynomialTest, test_combined_add_then_subtract_size) {
	Polynomials A, B;
	A.parseFromString("2x + 3y");
	B.parseFromString("x - y");
	Polynomials result = (A + B) - B;
	EXPECT_EQ(result.size(), A.size());
}
TEST(PolynomialTest, test_combined_add_then_subtract_CoeffX) {
	Polynomials A, B;
	A.parseFromString("2x + 3y");
	B.parseFromString("x - y");
	Polynomials result = (A + B) - B;
	auto monomsResult = result.getMonoms();
	auto monomsA = A.getMonoms();
	EXPECT_NEAR(monomsResult[0].koefficient, monomsA[0].koefficient, 1e-10);
}
TEST(PolynomialTest, test_combined_multiply_by_constant_Size) {
	Polynomials A;
	A.parseFromString("2x + 3y");
	Polynomials result = (A * 2.0) * 0.5;
	EXPECT_EQ(result.size(), A.size());
}
TEST(PolynomialTest, test_combined_multiply_by_constant_Coeff) {
	Polynomials A;
	A.parseFromString("2x + 3y");
	Polynomials result = (A * 2.0) * 0.5;
	auto monomsResult = result.getMonoms();
	auto monomsA = A.getMonoms();
	EXPECT_NEAR(monomsResult[0].koefficient, monomsA[0].koefficient, 1e-10);
}
TEST(PolynomialTest, test_invalid_input_returns_empty) {
	Polynomials p;
	p.parseFromString("invalid input");
	EXPECT_TRUE(p.isEmpty());
}
TEST(PolynomialTest, test_whitespace_input_returns_false) {
	Polynomials p;
	EXPECT_FALSE(p.parseFromString("   "));
}
TEST(PolynomialTest, test_size_five_monoms) {
	Polynomials p;
	p.parseFromString("x + y + z + xy + xyz");
	EXPECT_EQ(p.size(), 5);
}
TEST(PolynomialTest, test_size_after_combining_reduced) {
	Polynomials p;
	p.parseFromString("x + x + x + x");
	EXPECT_EQ(p.size(), 1);
}
TEST(PolynomialTest, test_size_after_clear_zero) {
	Polynomials p;
	p.parseFromString("x + y + z");
	p = Polynomials();
	EXPECT_EQ(p.size(), 0);
}