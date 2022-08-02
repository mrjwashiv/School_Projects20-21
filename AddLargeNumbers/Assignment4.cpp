/*************************************************************
*	                                                         *
*		  A LARGE NUMBER PROGRAM BY JAMES WASHINGTON		 *
*															 *
*************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

int MAX_DIGITS = 14;
int MAX_NUMS = 11;

void outputHeader();
int stringToInt(string);
string intToString(int);
void reverseString(string&);
string numIsValid(string);
void numOfNumValid(string&);
void ifSameSize(string[], int, bool&);
int getMax(string[], int, int&);
void formatNums(string[], int);
int* getNumStart(string[], int);
string* getNumOfNums(int&);
void getNumbers(string[], int);
string addNumbers(string[], int);
string* multiplyNumbers(string[], int, string&, int&);
void deformatNumbers(string[], int);
void addCommas(string[], int);
void addCommasAns(string&);
void isFormatted(string[], int, string&);
void outputAdd(string[], int, string, bool);
void outputMult(string[], int, string[], int, string);

int main()
{
	outputHeader();

	int size;
	string addAns;
	string multAns;
	int msize;
	string* nums = getNumOfNums(size);
	getNumbers(nums, size);

	addAns = addNumbers(nums, size);
	string* work = multiplyNumbers(nums, size, multAns, msize);

	outputAdd(nums, size, addAns, false);
	outputMult(nums, size, work, msize, multAns);
}

/*************************************************************
*	    THIS FUNCTION OUTPUTS HEADER FOR THE PROGRAM	     *
*															 *
*************************************************************/

void outputHeader()
{
	cout << "/*************************************************************\ " << endl;
	cout << "*                                                             * " << endl;
	cout << "*                      LARGE NUMBERS                          * " << endl;
	cout << "*                                                             * " << endl;
	cout << "\*************************************************************/ " << endl << endl;

	cout << "WELCOME USER!" << endl << endl;
	cout << "# TO GET STARTED ENTER HOW MANY NUMBERS YOU WANT." << endl;
	cout << "# NEXT ENTER THE NUMBERS AND THE CALULATIONS WILL BE MADE." << endl;
	cout << "ENJOY THE PROGRAM!!!" << endl << endl;
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
*	    THIS FUNCTION CONVERTS A STRING TO AN INT		     *
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

void reverseString(string& str)
{
	char temp;

	for (int i = 0; i < str.length() / 2; i++)
	{
		temp = str[i];
		str[i] = str[(str.length() - 1) - i];
		str[(str.length() - 1) - i] = temp;
	}
}

/*************************************************************
*	    THIS FUNCTION VERIFIES THE NUMBERS INPUTTED		     *
*															 *
*************************************************************/

string numIsValid(string num)
{
	int digit;
	string dig;
	bool valid = false;
	bool digitValid;

	while (!valid)
	{
		if (num.length() > 1)
		{
			int count = 0;

			while (num[count] == '0' && count < num.length() - 1)
			{
				count++;
			}

			num.erase(0, count);
		}

		digitValid = true;

		if (num.size() > MAX_DIGITS || num == "")
		{
			cout << "Invalid input, try again >> ";
			getline(cin, num);
			cout << endl;
			valid = false;
			digitValid = false;
		}
		else
		{
			int count = 0;

			while (digitValid && count < num.size())
			{
				dig = num[count];
				digit = stringToInt(dig);

				if (digit < 0 || digit > 9)
				{
					cout << "Invalid input, try again >> ";
					getline(cin, num);
					cout << endl;
					digitValid = false;
					valid = false;
				}

				count++;
			}
		}

		valid = digitValid;
	}

	return num;
}

/*************************************************************
*	THIS FUNCTION VARIFIES THE AMOUNT OF NUMBERS INPUTTED	 *
*															 *
*************************************************************/

void numOfNumValid(string& input)
{
	bool valid = false;
	int num;

	while (!valid)
	{
		num = stringToInt(input);

		if (num < 2 || num > MAX_NUMS)
		{
			cout << "Invalid input, try again >> ";
			getline(cin, input);
			cout << endl;
			valid = false;
		}
		else
		{
			valid = true;
		}
	}
}

/*************************************************************
*			THIS FUNCTION CHECKS IF ALL THE NUMBERS          *
*					  ARE THE SAME SIZE						 *
*************************************************************/

void ifSameSize(string numbers[], int size, bool& sameSize)
{
	int count = 0;
	
	while (sameSize && count < size - 1)
	{
		sameSize = (numbers[count].length() == numbers[count + 1].length());
		count++;
	}
}

/*************************************************************
*			THIS FUNCTION GETS THE INDEX AND LENGTH 	     *
*					OF THE BIGGEST NUMBER					 *
*************************************************************/

int getMax(string numbers[], int size, int& max)
{
	int index = 0;
	max = numbers[0].length();

	for (int i = 0; i < size; i++)
	{
		if (numbers[i].length() > max)
		{
			max = numbers[i].length();
			index = i;
		}
	}

	return index;
}

/*************************************************************
*		 THIS FUNCTION ADDS SPACES BEFORE EACH NUMBER		 *
*					  SO THEIR ALIGNED						 *
*************************************************************/

void formatNums(string numbers[], int size)
{
	bool sameSize = true;

	ifSameSize(numbers, size, sameSize);

	if (!sameSize)
	{
		int max;
		int index = getMax(numbers, size, max);

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < max + 1; j++)
			{
				if (numbers[i].length() != numbers[index].length())
				{
					numbers[i] = " " + numbers[i];
				}
			}
		}
	}
}

/*************************************************************
*		 THIS FUNCTION FINDS WHERE THE NUMBERS START		 *
*						FOR EACH NUMBER	  					 *
*************************************************************/

int* getNumStart(string numbers[], int size)
{
	int numStart;
	int* numStartArr = new int[size];

	for (int i = 0; i < size; i++)
	{
		numStart = 0;
		string strChar(1, numbers[i][0]);

		while (strChar == " ")
		{
			numStart++;
			strChar = numbers[i][numStart];
		}

		numStartArr[i] = numStart;
	}

	return numStartArr;
}

/*************************************************************
*		 THIS FUNCTION GETS THE AMOUNT OF NUMBERS			 *
*															 *
*************************************************************/

string* getNumOfNums(int& numOfNums)
{
	string input;

	cout << "How many numbers >> ";
	getline(cin, input);
	cout << endl;

	numOfNumValid(input);

	numOfNums = stringToInt(input);
	string* numbers = new string[numOfNums];

	return numbers;
}

/*************************************************************
*			 THIS FUNCTION GETS ALL THE NUMBERS		         *
*															 *
*************************************************************/

void getNumbers(string numbers[], int size)
{
	string input;
	int index = 0;

	for (int i = 0; i < size; i++)
	{
		cout << "Enter number " << i + 1 << " >> ";
		getline(cin, input);
		cout << endl;

		numbers[i] = numIsValid(input);
	}

	formatNums(numbers, size);
}

/*************************************************************
*	    THIS FUNCTION ADDS THE NUMBERS DIGIT BY DIGIT	     *
*															 *
*************************************************************/

string addNumbers(string numbers[], int size)
{
	int sum = 0;
	int carry = 0;
	string add;
	string result;
	int max = numbers[0].length();

	for (int i = max - 1; i >= 0; i--)
	{

		sum = 0;
		sum += carry;
		carry = 0;

		for (int j = 0; j < size; j++)
		{
			string strChar(1, numbers[j][i]);

			if (strChar != " ")
			{
				sum += stringToInt(strChar);
			}
		}

		add = intToString(sum);

		if (max == 1)
		{
			result += add;
		}
		else if (i == 0)
		{
			reverseString(add);
			result += add;
		}
		else
		{
			result += add[add.size() - 1];
		}

		carry = stringToInt(add.substr(0, add.size() - 1));
	}

	if (max != 1)
	{
		reverseString(result);
	}

	return result;
}

/*************************************************************
*	     THIS FUNCTION MULTIPLIES THE FIRST AND LAST 	     *
*					NUMBER DIGIT BY DIGIT					 *
*************************************************************/

string* multiplyNumbers(string numbers[], int size, string& ans, int& msize)
{
	string* multWork;
	int* numStart;
	int product;
	int carry = 0;
	string multiplier;
	string multiplicand;
	string multiply;
	string result;
	int count = 0;
	bool swap = false;

	numStart = getNumStart(numbers, size);

	if ((numbers[size - 1].length() - numStart[size - 1]) > (numbers[0].length() - numStart[0]))
	{
		string temp1 = numbers[0];
		numbers[0] = numbers[size - 1];
		numbers[size - 1] = temp1;

		int temp2 = numStart[0];
		numStart[0] = numStart[size - 1];
		numStart[size - 1] = temp2;
		swap = true;
	}

	multWork = new string[numbers[size - 1].length() - numStart[size - 1]];
	msize = numbers[size - 1].length() - numStart[size - 1];

	for (int i = numStart[size - 1]; i < numbers[size - 1].length(); i++)
	{
		multiplier = numbers[size - 1][i];
		result = "";

		for (int j = numbers[0].length() - 1; j >= numStart[0]; j--)
		{
			if (numbers[0][j] != ' ')
			{
				product = 0;
				product += carry;
				carry = 0;
				multiplicand = numbers[0][j];

				if (i < numbers[size - 1].length() - 1 && j == numbers[0].length() - 1)
				{
					for (int k = 0; k < numbers[size - 1].length() - i - 1; k++)
					{
						result += "0";
					}
				}

				product += stringToInt(multiplier) * stringToInt(multiplicand); //cout << product << " " << multiplier << " " << j << " " << multiplicand << endl;
				multiply = intToString(product);

				if (multiply.length() == 1 || j == numStart[0])
				{
					result = multiply + result;
				}
				else
				{
					carry = stringToInt(multiply.substr(0, multiply.size() - 1));
					result = multiply[multiply.size() - 1] + result;
				}
			}
		}

		multWork[count] = result;
		count++;
	}

	formatNums(multWork, msize);
	ans = addNumbers(multWork, msize);

	return multWork;
}

/*************************************************************
*	  THIS FUNCTION DELETES THE SPACE BEFORE EACH NUMBER     *
*															 *
*************************************************************/

void deformatNumbers(string numbers[], int size)
{
	int count;

	for (int i = 0; i < size; i++)
	{
		count = 0;

		while (numbers[i][count] == ' ')
		{
			numbers[i].erase(0, 1);
		}
	}
}

/*************************************************************
*	      THIS FUNCTION ADDS COMMAS TO EACH NUMBER		     *
*															 *
*************************************************************/

void addCommas(string numbers[], int size)
{
	int pos;

	for (int i = 0; i < size; i++)
	{
		if (numbers[i].length() > 3)
		{
			pos = numbers[i].length() - 3;

			while (pos > 0)
			{
				numbers[i].insert(pos, ",");
				pos -= 3;
			}
		}
	}
}

/*************************************************************
*			THIS FUNCTION ADDS COMMAS TO THE ANSWER		     *
*															 *
*************************************************************/

void addCommasAns(string& ans)
{
	int pos = ans.length() - 3;

	while (pos > 0)
	{
		ans.insert(pos, ",");
		pos -= 3;
	}
}

/*************************************************************
*			THIS FUNCTION CHECKS IF NUMBERS NEED 			 *
*			    COMMAS AND/OR SPACES DELETED				 *
*************************************************************/

void isFormatted(string numbers[], int size, string& ans)
{
	bool hasCommas = false;
	bool moreThanThree = false;
	bool isDeformatted = true;
	bool ansHasCommas = false;
	bool ansMoreThanThree = (ans.length() > 3);

	for (int i = 0; i < size; i++)
	{
		if (numbers[i][0] == ' ')
		{
			isDeformatted = false;
		}
	}

	for (int i = 0; i < size; i++)
	{
		if (numbers[i].length() > 3)
		{
			moreThanThree = true;
			for (int j = 0; j < numbers[i].length(); j++)
			{
				if (numbers[i][j] == ',')
				{
					hasCommas = true;
				}
			}
		}
	}

	for (int i = 0; i < ans.length(); i++)
	{
		if (ans[i] == ',')
		{
			ansHasCommas = true;
		}
	}

	if (!isDeformatted)
	{
		deformatNumbers(numbers, size);
	}

	if (moreThanThree && !hasCommas)
	{
		addCommas(numbers, size);
	}

	if (ansMoreThanThree && !ansHasCommas)
	{
		addCommasAns(ans);
	}
}

/*************************************************************
*			 THIS FUNCTION OUTPUTS THE ADDITION			     *
*															 *
*************************************************************/

void outputAdd(string numbers[], int size, string ans, bool isMultiply)
{
	if (!isMultiply)
	{
		cout << "The sum of: " << endl << endl;
	}

	isFormatted(numbers, size, ans);

	int maxLen = ans.length() + 3;

	for (int i = 0; i < size; i++)
	{
		if (i == size - 1)
		{
			cout << "+) " << right << setw(maxLen - 3) << numbers[i] << endl;
		}
		else
		{
			cout << right << setw(maxLen) << numbers[i] << endl;
		}
	}

	for (int i = 0; i < maxLen; i++)
	{
		cout << "-";
	}

	cout << endl << right << setw(maxLen) << ans << endl << endl << endl;
}

/*************************************************************
*		  THIS FUNCTION OUTPUTS THE MULTIPLICATION			 *
*															 *
*************************************************************/

void outputMult(string numbers[], int size, string multWork[], int msize, string ans)
{	
	isFormatted(numbers, size, ans);

	int multiplicandLen = numbers[0].length();
	int multiplierLen = numbers[size - 1].length();
	int maxLen = ans.length() + 3;
	
	cout << "The product of:" << endl << endl;

	cout << right << setw(maxLen) << numbers[0] << endl;
	cout << "*) " << right << setw(maxLen - 3) << numbers[size - 1] << endl;

	for (int i = 0; i < maxLen; i++)
	{
		cout << "-";
	}

	cout << endl;

	outputAdd(multWork, msize, ans, true);
}