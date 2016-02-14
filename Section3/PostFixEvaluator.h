#pragma once
#include <string>

/**
 * @brief	Evaluates a postfix (reverse Polish notation) expression (inefficiently). Precondition: input is not stupid.
 *
 * @author	Shane
 * @date	1/25/2016
 *
 * @param [in]	expression	The expression to evaluate.
 *
 * @return	The result of the expression.
 */
double postfixEvaluator(std::string&& expression);