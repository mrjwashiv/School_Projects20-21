// Assignment5Polynomials.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

int MAX_POLYNOMIALS = 14;

struct aTerm
{
    int coefficient;
    int exponent;
    aTerm* next;
};
typedef aTerm* polynomial;

int stringToInt(string);
string intToString(int);
void numOfPolyValid(string&); 
string polyIsValid(string);
void addTerm(polynomial, int, int);
int getSize(polynomial);
int getNumofPoly();
string getInput(int);
int getCoefficient(string);
int getExponent(string);
polynomial parseInput(string);
polynomial* initializeArray(int);
string deparseList(polynomial);
int getMinExponent(polynomial, polynomial);
polynomial addPoly(polynomial, polynomial);
polynomial deleteTerm(polynomial, int);
void combineLikeTerms(polynomial);
polynomial multiplyPoly(polynomial, polynomial);
void outputResults(polynomial*, polynomial, polynomial, int);
void outputPoly(polynomial);

int main()
{
    polynomial addResult = new aTerm;
    addResult->next = NULL;
    polynomial multResult = new aTerm;
    multResult->next = NULL;

    int size = getNumofPoly();
    polynomial* polys = initializeArray(size);

    for (int i = 0; i < size; i++)
    {
        if (i == 0)
        {
            addResult = addPoly(polys[i], polys[i + 1]);
            multResult = multiplyPoly(polys[i], polys[i + 1]);
            i = i + 1;
        }
        else
        {
            addResult = addPoly(addResult, polys[i]);
            multResult = multiplyPoly(multResult, polys[i]);
        }
    }

    outputResults(polys, addResult, multResult, size);
}

void outputPoly(polynomial poly)
{
    while (poly->next != NULL)
    {
        cout << poly->coefficient << endl;
        cout << poly->exponent << endl << endl;
        poly = poly->next;
    }
    if (poly != NULL)
    {
        cout << poly->coefficient << endl;
        cout << poly->exponent << endl;
    }
}

int stringToInt(string str)
{
    int num = 0;
    int decimal;
    int exponent = 0;

    for (int i = str.length() - 1; i >= 0; i--)
    {
        if (str[i] != '-')
        {
            decimal = 1;

            for (int j = 0; j < exponent; j++)
            {
                decimal *= 10;
            }

            int digit = str[i] - '0';
            num += digit * decimal;
            exponent++;
        }
    }

    if (str[0] == '-')
    {
        num -= (2 * num);
    }

    return num;
}

string intToString(int num)
{
    stringstream ss;
    ss << num;
    string str = ss.str();

    return str;
}

void numOfPolyValid(string& input)
{
    bool valid = false;
    int num;

    while (!valid)
    {
        num = stringToInt(input);

        if (num < 2 || num > MAX_POLYNOMIALS)
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

//void polyIsValid(string& poly)
//{
    /*bool valid = false;
    int count = 0;
    int len = poly.length();
    bool bNumValid;
    bool cNumValid;
    bool aNumValid;


    while (!valid)
    {
        while (count < len)
        {
            if (poly[count] == ' ')
            {
                poly.erase(count);
                count++;
            }
        }

        count = 0;

        while (count < len)
        {
            string befCh(1, poly[count - 1]);
            string curCh(1, poly[count]);
            string aftCh(1, poly[count + 1]);

            bNumValid = isValidNum(befCh);
            cNumValid = isValidNum(curCh);
            aNumValid = isValidNum(aftCh);

            if ((curCh == "+" || curCh == "-") && ((!bNumValid && befCh != "^") || !aNumValid))
            {
                cout << "Invalid input, try again >> ";
                getline(cin, poly);
                cout << endl;
                valid = false;
            }
            else if (curCh == "x" && ((!bNumValid || (aftCh != "^" && (aftCh != "-" || aftCh != "+")))))
            {
                cout << "Invalid input, try again >> ";
                getline(cin, poly);
                cout << endl;
                valid = false;
            }
            else if (curCh == "^" && (befCh != "x" || (aftCh != "-" && !aNumValid)))
            {
                cout << "Invalid input, try again >> ";
                getline(cin, poly);
                cout << endl;
                valid = false;
            }
            else if (!cNumValid && ((!bNumValid || (befCh != "-" && befCh != "+" && befCh != "^") || (!aNumValid || (aftCh != "-" && aftCh != "+")))))
            {
                cout << "Invalid input, try again >> ";
                getline(cin, poly);
                cout << endl;
                valid = false;
            }
            else if (!cNumValid && curCh != "-" && curCh != "+" && curCh != "x")
            {
                cout << "Invalid input, try again >> ";
                getline(cin, poly);
                cout << endl;
                valid = false;
            }
            else
            {
                valid = true;
            }
        }
    }
}*/


void addTerm(polynomial poly, int coeff, int exp)
{
    while (poly->next != NULL)
    {
        poly = poly->next;
    }

    polynomial newTerm = new aTerm;
    poly->next = newTerm;
    newTerm->coefficient = coeff;
    newTerm->exponent = exp;
    newTerm->next = NULL;
}

int getSize(polynomial poly)
{
    int count = 0;

    while (poly != NULL)
    {
        count++;
        poly = poly->next;
    }

    return count;
}

int getNumofPoly()
{
    string size;

    cout << "Number of Polynomials >> ";
    getline(cin, size);
    cout << endl;

    numOfPolyValid(size);

    return stringToInt(size);
}

string getInput(int index)
{
    string input;

    cout << "Enter a polynomial " << index << " >> ";
    getline(cin, input);
    cout << endl;

    return input;
}

int getCoefficient(string term)
{
    if (term[0] == '+')
    {
        term.erase(0, 1);
    }

    int len = term.length();

    if (len == 1 && term[0] != 'x')
    {
        return stringToInt(term);
    }
    else if (term[0] == 'x')
    {
        return 1;
    }
    else if (term == "-x")
    {
        return -1;
    }
    else
    {
        string coeff;

        for (int i = 0; i < len; i++)
        {
            if (term[i] == 'x')
            {
                coeff = term.substr(0, i);
            }
        }

        if (coeff == "")
        {
            coeff = term;
        }

        return stringToInt(coeff);
    }
}

int getExponent(string term)
{
    int len = term.length();

    if (len == 1 && term[0] != 'x')
    {
        return 0;
    }
    else if (term[len - 1] == 'x')
    {
        return 1;
    }
    else
    {
        string exp;

        for (int i = 0; i < len; i++)
        {
            if (term[i] == '^')
            {
                exp = term.substr(i + 1);
            }
        }

        return stringToInt(exp);
    }
}

polynomial parseInput(string input)
{
    int len = input.length();
    int count = 0;
    int beg = 0;    
    int coeff;
    int exp;
    string term;
    polynomial head = new aTerm;
    head->next = NULL;
    bool start = true;


    while (count < len)
    {
        if (((input[count] == '+' || input[count] == '-') && input[count - 1] != '^') || count == len - 1)
        {
            term = input.substr(beg, (count - beg));

            if (count == len - 1)
            {
                term += input[len - 1];
            }

            coeff = getCoefficient(term);
            exp = getExponent(term);

            if (start)
            {
                head->coefficient = coeff;
                head->exponent = exp;
                start = false;
            }
            else
            {
                addTerm(head, coeff, exp);
            }

            beg = count;
        }

        count++;
    }

    return head;
}

polynomial* initializeArray(int size)
{
    polynomial* polys = new polynomial[size];
    string input;

    for (int i = 0; i < size; i++)
    {
        input = getInput(i + 1);
        polys[i] = parseInput(input);
    }

    return polys;
}

string deparseList(polynomial poly)
{
    string result = "";
    bool start = true;

    if (poly == NULL)
    {
        return "0";
    }
    else
    {
        string coeff;
        string exp;

        while (poly != NULL)
        {
            coeff = intToString(poly->coefficient);
            exp = intToString(poly->exponent);
           
            if (!start)
            {
                result += " ";
            }

            if (coeff[0] == '-')
            {
                if (!start)
                {
                    result += "- ";
                }
                else
                {
                    result += "-";
                }

                if (exp == "0")
                {
                    result += coeff.substr(1);
                }
                else if (exp == "1")
                {
                    result += coeff.substr(1) + "x";
                }
                else 
                {
                    result += coeff.substr(1) + "x^" + exp;
                }
            }
            else
            {
                if (!start)
                {
                    result += "+ ";
                }

                if (exp == "0")
                {
                    result += coeff + " ";
                }
                else if (exp == "1")
                {
                    result += coeff + "x";
                }
                else
                {
                    result += coeff + "x^" + exp;
                }
            }

            if (start)
            {
                start = false;
            }

            poly = poly->next;
        }

        return result;
    }
}

int getMinExponent(polynomial poly1, polynomial poly2)
{
    int minExp;

    while (poly1->next != NULL)
    {
        poly1 = poly1->next;
    }

    while (poly2->next != NULL)
    {
        poly2 = poly2->next;
    }

    minExp = poly1->exponent;

    if (poly1->exponent > poly2->exponent)
    {
        minExp = poly2->exponent;
    }

    return minExp;
}

polynomial addPoly(polynomial poly1, polynomial poly2)
{
    polynomial result = new aTerm;
    result->next = NULL;
    polynomial head1 = poly1;
    polynomial head2 = poly2;
    int sum = 0;
    bool start = true;

    int maxExp = poly1->exponent;
    int minExp = getMinExponent(poly1, poly2);

    if (poly1->exponent < poly2->exponent)
    {
        maxExp = poly2->exponent;
    }

    for (int i = maxExp; i >= minExp; i--)
    {
        poly1 = head1;
        poly2 = head2;

        while (poly1->next != NULL && poly1->exponent > i)
        {
            poly1 = poly1->next;
        }

        while (poly2->next != NULL && poly2->exponent > i)
        {
            poly2 = poly2->next;
        }


        if (poly1 != NULL && poly1->exponent == i)
        {
            sum += poly1->coefficient;
        }

        if (poly2 != NULL && poly2->exponent == i)
        {
            sum += poly2->coefficient;
        }

        if (sum != 0 && start)
        {
            result->coefficient = sum;
            result->exponent = i;
            start = false;
        }
        else if (sum != 0)
        {
            addTerm(result, sum, i);
        }

        sum = 0;
    }

    return result;
}

polynomial deleteTerm(polynomial poly, int pos)
{
    polynomial temp = poly;

    if (pos == 0)
    {
        poly = poly->next;
        temp = NULL;
        delete temp;
        return poly;
    }
    else
    {
        for (int i = 0; temp->next != NULL && i < pos - 1; i++)
        {
            temp = temp->next;
        }

        if (temp == NULL || temp->next == NULL)
        {
            return poly;
        }

        if (temp->next->next == NULL)
        {
            delete temp->next;
            temp->next = NULL;
        }
        else
        {
            polynomial next = temp->next->next;
            delete temp->next;
            temp->next = next;
        }
        return poly;
    }    
}

void combineLikeTerms(polynomial poly)
{
    polynomial ptr1;
    polynomial ptr2;
    polynomial dup;
    ptr1 = poly;

    while (ptr1 != NULL && ptr1->next != NULL)
    {
        ptr2 = ptr1;

        while (ptr2->next != NULL)
        {
            if (ptr1->exponent == ptr2->next->exponent)
            {
                ptr1->coefficient = ptr1->coefficient + ptr2->next->coefficient;
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;

                delete (dup);
            }
            else
            {
                ptr2 = ptr2->next;
            }
        }

        ptr1 = ptr1->next;
    }
}

polynomial multiplyPoly(polynomial head1, polynomial head2)
{
    polynomial result = new aTerm;
    result->next = NULL;
    bool start = true;

    polynomial poly1 = head1;
    polynomial poly2 = head2;

    int coeff;
    int exp;

    while (poly1 != NULL)
    {
        while (poly2 != NULL)
        {
            coeff = poly1->coefficient * poly2->coefficient;
            exp = poly1->exponent + poly2->exponent;

            if (start)
            {
                result->coefficient = coeff;
                result->exponent = exp;
                start = false;
            }
            else
            {
                addTerm(result, coeff, exp);
            }

            poly2 = poly2->next;
        }

        poly2 = head2;

        poly1 = poly1->next;
    }

    combineLikeTerms(result);
    return result;
}

void outputResults(polynomial* polys, polynomial addResult, polynomial multResult, int size)
{
    string poly;
    string aResult = deparseList(addResult);
    string mResult = deparseList(multResult);

    for (int i = 0; i < size; i++)
    {
        poly = deparseList(polys[i]);

        if (i == 0)
        {
            cout << "Sum = (" << poly << ")";
        }
        else
        {
            cout << " + (" << poly << ")";
        }
    }

    cout << endl;
    cout << right << setw(6) << "= " << aResult << endl << endl;

    for (int i = 0; i < size; i++)
    {
        poly = deparseList(polys[i]);

        if (i == 0)
        {
            cout << "Product = (" << poly << ")";
        }
        else
        {
            cout << " * (" << poly << ")";
        }
    }

    cout << endl;
    cout << right << setw(10) << "= " << mResult;
}