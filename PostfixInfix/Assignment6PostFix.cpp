/*************************************************************
*	                                                         *
*			 A POSTFIX PROGRAM BY JAMES WASHINGTON		     *
*															 *
*************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "stack.cpp"

using namespace std;

int stringToInt(string);
string intToString(int);
void reverseString(char*);
int getValue(char);
char reverseGetValue(int);
int hexatridecimalToDecimal(string);
char* decimalToHexatridecimal(char[], int);
int getPrecedence(char);
bool isOperand(char);
bool isOperator(char);
void validateInput(string&);
void formatInput(string&);
int getChoice();
int choiceValid(string);
string getExpression(string);
int evaluateOp(int, int, char);
string infixToPostfix(string);
string postfixToInfix(string);
char* evaluateInfix(char[], string);
void menu();
void driver();

int main()
{
	menu();
	driver();
}

/*************************************************************
*	    THIS FUNCTION CONVERTS A STRING TO AN INT		     *
*															 *
*************************************************************/

int stringToInt(string str)
{
	int num = 0;
	int decimal;
	int exponent = 0;

	for (int i = str.length() - 1; i >= 0; i--)
	{
		decimal = 1;

		for (int i = 0; i < exponent; i++)
		{
			decimal *= 10;
		}

		int digit = str[i] - '0';
		num += digit * decimal;
		exponent++;
	}

	return num;
}

/*************************************************************
*	    THIS FUNCTION CONVERTS A INT TO A STRING		     *
*															 *
*************************************************************/

string intToString(int num)
{
	stringstream ss;
	ss << num;
	string str = ss.str();

	return str;
}

/*************************************************************
*			 THIS FUNCTION REVERSES A STRING			     *
*															 *
*************************************************************/

void reverseString(char* str)
{
	int len = strlen(str);
	char temp;

	for (int i = 0; i < len / 2; i++)
	{
		temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
	}
}

/*************************************************************
*	THIS FUNCTION GETS THE DECIMAL FORM OF A BASE 36 DIGIT	 *
*															 *
*************************************************************/

int getValue(char digit)
{
	if (digit >= '0' && digit <= '9')
		return (int)digit - '0';
	else
		return (int)digit - 'A' + 10;
}

/*************************************************************
*	THIS FUNCTION GETS THE BASE 36 FORM OF A DECIMAL DIGIT	 *
*															 *
*************************************************************/

char reverseGetValue(int digit)
{
	if (digit >= 0 && digit <= 9)
		return (char)(digit + '0');
	else
		return (char)(digit - 10 + 'A');
}

/*************************************************************
*	  THIS FUNCTION CONVERTS A BASE 10 NUMBER TO BASE 36     *
*															 *
*************************************************************/

int hexatridecimalToDecimal(string str)
{
	int len = str.length();
	int pow = 1;
	int num = 0;

	for (int i = len - 1; i >= 0; i--)
	{
		int digit = getValue(str[i]);
		num += digit * pow;
		pow *= 36;
	}

	return num;
}

/*************************************************************
*	  THIS FUNCTION CONVERTS A BASE 36 NUMBER TO BASE 10     *
*															 *
*************************************************************/

char* decimalToHexatridecimal(char res[], int inputNum)
{
	int index = 0;

	while (inputNum > 0)
	{
		res[index] = reverseGetValue(inputNum % 36);
		inputNum /= 36;
		index++;
	}
	res[index] = '\0';
	reverseString(res);

	return res;
}

/*************************************************************
*	   THIS FUNCTION GETS THE PRECENDECE OF AN OPERATOR      *
*															 *
*************************************************************/

int getPrecedence(char ch)
{
	if (ch == '*' || ch == '/')
	{
		return 2;
	}
	else if (ch == '+' || ch == '-')
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

/*************************************************************
*	   THIS FUNCTION RETURNS TRUE IF CHAR IS AN OPERAND      *
*															 *
*************************************************************/

bool isOperand(char ch)
{
	string str(1, ch);
	int digit = stringToInt(str);

	return (digit >= 0 && digit <= 9) || (ch >= 'A' && ch <= 'Z');
}

/*************************************************************
*	  THIS FUNCTION RETURNS TRUE IF CHAR IS AN OPERATOR      *
*															 *
*************************************************************/

bool isOperator(char ch)
{
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

/*************************************************************
*	  THIS FUNCTION DELETES SPACE AND CAPITALIZES INPUT      *
*															 *
*************************************************************/

void formatInput(string& input)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == ' ')
		{
			input.erase(i, 1);
			i--;
		}
		
		input[i] = toupper(input[i]);
	}
}

/*************************************************************
*			THIS FUNCTION CHECKS IF INPUT IS VALID		     *
*															 *
*************************************************************/

void validateInput(string& input)
{
	bool valid = false;
	int count = 0;
	int operators = 0;
	int operands = 0;

	while (!valid)
	{
		if (count == 0)
		{
			for (int i = 0; i < input.length(); i++)
			{
				if (isOperator(input[i]))
				{
					operators++;
				}
				else if (isOperand(input[i]))
				{
					operands++;
				}
			}
		}

		if (operators > 0 && operands != operators + 1)
		{
			cout << "Input invalid, please try again >> ";
			getline(cin, input);
			cout << endl;

			formatInput(input);

			operators = 0;
			operands = 0;
			count = 0;
		}
		else if (isOperator(input[0]))
		{
			cout << "Input invalid, please try again >> ";
			getline(cin, input);
			cout << endl;

			formatInput(input);

			operators = 0;
			operands = 0;
			count = 0;
		}
		else if (!isOperand(input[count]) && !isOperator(input[count]) && input[count] != '(' && input[count] != ')')
		{
			cout << "Input invalid, please try again >> ";
			getline(cin, input);
			cout << endl;

			formatInput(input);

			operators = 0;
			operands = 0;
			count = 0;
		}
		else
		{
			count++;

			if (count >= input.length())
			{
				valid = true;
			}
		}
	}
}

/*************************************************************
*		 THIS FUNCTION CHECKS IF MENU CHOICE IS VALID        *
*															 *
*************************************************************/

int choiceValid(string choice)
{
	bool valid = false;
	int num;

	while (!valid)
	{
		num = stringToInt(choice);

		if (num > 0 && num <= 3)
		{
			valid = true;
		}
		else
		{
			cout << "Input invalid, please try again >> ";
			getline(cin, choice);
			cout << endl;
		}
	}

	return num;
}

/*************************************************************
*		  THIS FUNCTION GETS THE USER'S MENU CHOICE		     *
*															 *
*************************************************************/

int getChoice()
{
	string choice;

	cout << "Please enter your choice from the menu above >> ";
	getline(cin, choice);
	cout << endl;

	return choiceValid(choice);
}

/*************************************************************
*		  THIS FUNCTION GETS THE USER'S EXPRESSION		     *
*															 *
*************************************************************/

string getExpression(string type)
{
	string exp;

	cout << "Please enter a " << type << " expression >> ";
	getline(cin, exp);
	cout << endl;

	formatInput(exp);
	validateInput(exp);

	return exp;
}

/*************************************************************
*	   THIS FUNCTION PERFORMS THE OPERATION ON OPERANDS	     *
*															 *
*************************************************************/

int evaluateOp(int a, int b, char operate) 
{
	switch (operate) 
	{
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': return a / b;
	}
}

/*************************************************************
*		   THIS FUNCTION CONVERTS INFIX TO POSTFIX	         *
*															 *
*************************************************************/

string infixToPostfix(string input)
{
	Stack<char> stack;
	int len = input.length();
	string result;
	int digit;

	for (int i = 0; i < len; i++)
	{
		string str(input[i], 1);
		digit = stringToInt(str);
		
		if ((digit >= 0 && digit <= 9) || (input[i] >= 'A' && input[i] <= 'Z'))
		{
			result += input[i];
		}
		else if (input[i] == '(')
		{
			stack.push('(');
		}
		else if (input[i] == ')')
		{
			while (!stack.isEmpty() && stack.top() != '(')
			{
				char ch = stack.top();
				stack.pop();
				result += ch;
			}
			if (stack.top() == '(')
			{
				char ch = stack.top();
				stack.pop();
			}
		}
		else 
		{
			while (!stack.isEmpty() && getPrecedence(input[i]) <= getPrecedence(stack.top()))
			{
				char ch = stack.top();
				stack.pop();
				result += ch;
			}
			stack.push(input[i]);
		}

	}

	while (!stack.isEmpty())
	{
		char ch = stack.top();
		stack.pop();
		result += ch;
	}

	return result;

}

/*************************************************************
*		   THIS FUNCTION CONVERTS POSTFIX TO INFIX	         *
*															 *
*************************************************************/

string postfixToInfix(string input)
{
	Stack<string> stack;

	for (int i = 0; input[i] != '\0'; i++)
	{
		if (isOperand(input[i]))
		{
			string op(1, input[i]);
			stack.push(op);
		}
		else
		{
			string op1 = stack.top();
			stack.pop();
			string op2 = stack.top();
			stack.pop();
			stack.push(("(" + op2 + input[i] + op1 + ")"));
		}
	}

	return stack.top();
}

/*************************************************************
*		   THIS FUNCTION EVALUATES INFIX EXPRESSION	         *
*															 *
*************************************************************/

char* evaluateInfix(char res[], string input) 
{
	Stack<int> values;
	Stack<char> ops;
	int digit;

	for (int i = 0; i < input.length(); i++)
	{
		string str(1, input[i]);
		digit = stringToInt(str);

		if (input[i] == '(')
		{
			ops.push(input[i]);
		}
		else if ((digit >= 0 && digit <= 9) || (input[i] >= 'A' && input[i] <= 'Z')) 
		{
			string num = "";
			num += input[i];

			int val;

			string str(input[i + 1], 1);
			digit = stringToInt(str);

			while (i < input.length() - 1 && ((digit >= 0 && digit <= 9) || (input[i + 1] >= 'A' && input[i + 1] <= 'Z')))
			{
				num += input[i];
				i++;

				string str(input[i], 1);
				digit = stringToInt(str);
			}
			val = hexatridecimalToDecimal(num);
			values.push(val);
		}
		else if (input[i] == ')')
		{
			while (!ops.isEmpty() && ops.top() != '(')
			{
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(evaluateOp(val1, val2, op));
			}

			if (!ops.isEmpty())
			{
				ops.pop();
			}
		}
		else
		{
			while (!ops.isEmpty() && getPrecedence(ops.top()) >= getPrecedence(input[i]))
			{
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(evaluateOp(val1, val2, op));
			}

			ops.push(input[i]);
		}
	}

	while (!ops.isEmpty())
	{
		int val2 = values.top();
		values.pop();

		int val1 = values.top();
		values.pop();

		char op = ops.top();
		ops.pop();

		values.push(evaluateOp(val1, val2, op));
	}

	decimalToHexatridecimal(res, values.top());
	return res;
}

/*************************************************************
*	    THIS FUNCTION OUTPUTS HEADER FOR THE PROGRAM	     *
*															 *
*************************************************************/

void menu()
{
	cout << "/************************************************************** " << endl;
	cout << "*                                                             * " << endl;
	cout << "*                     INFIX / POSTFIX                         * " << endl;
	cout << "*                                                             * " << endl;
	cout << "**************************************************************/ " << endl << endl;

	cout << "WELCOME USER!" << endl << endl;
	cout << "# TO GET STARTED, ENTER YOUR CHOICE FROM THE MENU BELOW." << endl;
	cout << "# NEXT ENTER YOUR EXPRESSION AND THE CALCULATIONS WILL BE MADE." << endl;
	cout << "ENJOY THE PROGRAM!!!" << endl << endl;

	cout << "MENU:" << endl << endl;
	cout << " 1. CONVERT INFIX TO POSTFIX" << endl;
	cout << " 2. EVALUATE POSTFIX EXPRESSION" << endl;
	cout << " 3. CONVERT INFIX TO POSTFIX AND EVALUATE IT" << endl << endl;
}

/*************************************************************
*		 THIS FUNCTION IS THE DRIVER FOR THE PROGRAM	     *
*															 *
*************************************************************/

void driver()
{
	int choice = getChoice();
	string exp;
	string newExp;
	string result;
	char res[100];

	if (choice == 1)
	{
		exp = getExpression("infix");
		newExp = infixToPostfix(exp);

		cout << "Infix   >> " << exp << endl;
		cout << "Postfix >> " << newExp << endl;
	}
	else if (choice == 2)
	{
		exp = getExpression("postfix");
		newExp = postfixToInfix(exp);

		result = evaluateInfix(res, newExp);

		cout << exp << " = " << result << endl;
	}
	else
	{
		exp = getExpression("infix");
		newExp = infixToPostfix(exp);

		result = evaluateInfix(res, exp);

		cout << "Infix   >> " << exp << endl;
		cout << "Postfix >> " << newExp << endl << endl;

		cout << newExp << " = " << result << endl;
	}
}