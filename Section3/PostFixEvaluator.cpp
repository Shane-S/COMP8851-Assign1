#include <sstream>
#include <stack>
#include <iterator>
#include <vector>
#include <iostream>
#include "PostFixEvaluator.h"

using namespace std;

double postfixEvaluator(string&& expression) {
	using namespace std;

	vector<string> tokenized;
	stack<double> numbers;

	// Tokenise the expression
	istringstream iss(expression);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter(tokenized));

	// Process each token, pushing numbers onto the stack performing operations as each operator is encountered
	for (auto& str : tokenized) {
		double num;
		istringstream doubleIss(str);
		if (doubleIss >> num) {
			numbers.push(num);
		}
		else {
			istringstream charIss(str);
			char op;
			charIss >> op;

			double num1 = numbers.top();
			numbers.pop();
			double num2 = numbers.top();
			numbers.pop();

			switch (op) {
			case '+':
				numbers.push(num1 + num2);
				break;
			case '-':
				numbers.push(num1 - num2);
				break;
			case '*':
				numbers.push(num1 * num2);
				break;
			case '/':
				numbers.push(num1 / num2);
				break;
			default:
				cout << "What have you done..." << endl;
				cin.get();
				exit(EXIT_FAILURE);
				break;
			}
		}
	}

	return numbers.top();
}