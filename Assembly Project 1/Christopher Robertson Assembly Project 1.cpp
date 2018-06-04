/*
Christopher Robertson
ID: 001174618
Assembly Project 1
*/
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int getBase(); //Gets base number system from user
int getTarget(); //Gets target number system from user
string getNum(int); //Gets number in base number system to convert from user
bool isBase(string &, int); //Makes sure the number received from user can be in that base
string calculate(string, int, int); //Converts number from base to target
int alphaToNum(char); //Converts given letter to appropriate number
char numToAlpha(int); //Converts given number to appropriate letter

int main()
{
	bool success = false, //Used for input validation on repeating the program
		repeat = true; //Used for the loop in case the user wants to convert another number
	string num,
		result,
		str = "";
	int base,
		target;
	char input; //Holds the choice to convert another number or not

	do
	{
		base = getBase();
		target = getTarget();
		num = getNum(base);
		if (base == target)
		{ //Don't bother calculating stuff if no conversion is necessary
			result = num;
		}
		else
		{
			result = calculate(num, base, target);
		}
		cout << endl << endl << num << " in base " << base << " is equal to " << result << " in base " << target << ".\n";
		do
		{
			cout << "Would you like to convert another number to another base? (Y/N): ";
			cin >> input;
			input = toupper(input); //Don't need to check for 'y' or 'n' with this
			getline(cin, str); //Grabs any extra characters left on the line after the char cin
			if (!cin) //!cin is set if something that is not a character is put in. Just in case
			{
				cin.clear(); //Clears the flag so we can use cin again without terminating program
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Ignore rest of line, just in case
				input = ' '; //Reset the input, just in case
				str = ""; //Reset str, just in case it was used
				cout << "\nInvalid input. Please try again.\n\n";
				success = false; //Asks if they want to repeat again
			}
			else if (str != "")
			{ //If there was extra stuff behind the first character, just throw it all out and redo
				cout << "\nInvalid input. Please try again.\n\n";
				input = ' ';
				str = "";
				success = false;
			}
			else if (input == 'Y')
			{
				success = true; //Doesn't repeat the question (ie: answered successfully)
				repeat = true; //User wants to convert more
				cout << endl;
			}
			else if (input == 'N')
			{
				success = true;
				repeat = false; //User doesn't want to convert more, terminates program
			}
			else
			{
				input = ' ';
				cout << "\nInvalid input. Please try again.\n\n";
				success = false;
			}
		} while (!success);
	} while (repeat);
	return 0;
}

int getBase()
{
	int input;
	bool success = false;
	string str = "";

	do
	{
		cout << "Enter the base number system: ";
		cin >> input;
		getline(cin, str);
		if (!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			input = 0;
			str = "";
			success = false;
			cout << "\nInvalid input. Please try again.\n\n";
		}
		else if (str != "")
		{
			cout << "\nInvalid input. Please try again.\n\n";
			input = 0;
			str = "";
			success = false;
		}
		else if (input < 2 || input > 16)
		{ //Program only offers between base 2 and base 16
			cout << "\nPlease choose a base number system from Binary (2) to Hex (16).\n\n";
			success = false;
		}
		else
		{ //User's input satisfied all requirements, do not ask for input again
			success = true;
		}
	} while (!success);

	return input;
}

int getTarget()
{
	int input;
	bool success = false;
	string str = "";

	do
	{
		cout << "Enter the target number system: ";
		cin >> input;
		getline(cin, str);
		if (!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			input = 0;
			str = "";
			success = false;
			cout << "\nInvalid input. Please try again.\n\n";
		}
		else if (str != "")
		{
			cout << "\nInvalid input. Please try again.\n\n";
			input = 0;
			str = "";
			success = false;
		}
		else if (input < 2 || input > 16)
		{
			cout << "\nPlease choose a base number system from Binary (2) to Hex (16).\n\n";
			success = false;
		}
		else
		{
			success = true;
		}
	} while (!success);

	return input;
}

string getNum(int base)
{
	bool success = false;
	string input,
		str = "";

	do
	{
		cout << "Enter the value in base: ";
		cin >> input;
		getline(cin, str);
		if (!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			input = "";
			str = "";
			success = false;
			cout << "\nInvalid input. Please try again.\n\n";
		}
		else if (str != "")
		{ //Just in case user accidentally typed space in between two characters of the number
			cout << "\nCharacters after whitespace detected. Please enter number again.\n\n";
			input = "";
			str = "";
			success = false;
		}
		else if (!isBase(input, base))
		{
			cout << "\nInvalid input. Please try again.\n\n";
			input = "";
			str = "";
			success = false;
		}
		else
		{
			success = true;
		}
	} while (!success);

	return input;
}

bool isBase(string & input, int base)
{ //Tests to make sure the input matches the base
	for (int i = 0; i < input.length(); i++)
	{ //Step through the input string
		if (base < 11) //Base that isn't alphanumeric
		{
			if (input[i] < 48 || input[i] > (47 + base)) //Outside of non-alphanumeric base range
			{ //48 through 57 is 0 - 9. > (47 + base) includes 0 and up to the max of that base
				return false; //Like base 3 would be 47 + 3 = 50, ascii 50 is 2, and the highest number--
			}					//--base 3 can go is 2, so it makes sense
		}
		else
		{ //We now know that the base is alphanumeric
			if ((input[i] < 48) || (input[i] > (64 + (base - 10))))
			{ //Check to see if the number is outside the normal bounds (0 - 9, A - F)
				if (input[i] > 96 && input[i] < 103)
				{ //Check to see if it's just a lower case letter, if so, change it to upper case
					input[i] = toupper(input[i]);
				}
				else
				{ //If the input[i] isn't just a lowercase letter, it doesn't match the base number system
					return false;
				}
			}
			else if ((input[i] < 65) && (input[i] > 57))
			{ //If the number is in between ASCII 9 (57) and ASCII A (65) then it is garbage, not number
				return false;
			}
		}
	}
	return true; //Only gets to this point if it passes all the tests above
}

string calculate(string input, int base, int target)
{
	stringstream ss; //Will accept an integer straight into a "string"
	string result = "",
		tempstr = ""; //Here to accept the number, if it is alphanumeric, in its reverse-generated order
	int temp = 0, //Will hold the base 10 number
		length = input.length(),
		power = (length - 1), //Exponent to use
		mod; //For use in the decimal to target base conversion

	if (base < 10)
	{ //If decimal or lower we don't need to pass anything to be converted to alpha
		for (int i = 0; i < length; i++, power--)
		{ //Step through the string one at a time
			temp += (((int)input[i] - 48) * pow(base, power));
		} //ASCII numbers start at 48 and go to 57
	}
	else if (base == 10)
	{ //Don't bother stepping through the string one at a time, use the string to integer function to do it
		temp = stoi(input);
	}
	else
	{ //For alphanumeric systems
		for (int i = 0; i < length; i++, power--)
		{
			if (input[i] > 64 && input[i] < 91)
			{ //We are dealing with alphanumeric numbers, but by definition it can have a number in a place
				temp += (alphaToNum(input[i]) * pow(base, power));
			} //Same process as before, just using the returned converted letter to a number
			else
			{ //If there is a number in the place, we can use the normal method, no alpha to convert
				temp += (((int)input[i] - 48) * pow(base, power));
			}
		}
	}
	//It is now converted to base 10 (decimal)

	if (target == 10)
	{ //Oh look, we've already converted to base 10, how convenient
		ss << temp; //Stream integer into a "string" ss (stringstream, like cout)
		result = ss.str(); //Then slap that stringstream into result using the member function
	}
	else
	{ //Darn, target isn't base 10, more work to do!
		while (temp > 0)
		{ //Standard method to convert decimal to other bases...
			mod = temp % target;
			if (mod > 9)
			{ //If the remainder is greater than 9, we need a letter, so send it over to be converted
				tempstr += numToAlpha(mod); //Slap the converted letter into the string
			}
			else
			{ //Remainder isn't greater than 9, so we can use the direct result (with ASCII displacement)
				tempstr += (mod + 48); //+ 48 because strings store the ASCII value, and 0 is at 48
			}
			temp = (temp / target); //Integer divide to continue the process
		}
		for (int i = (tempstr.length() - 1); i >= 0; i--) //- 1 because string starts at index 0
		{ //Reverse the string, because this process gives the number backwards
			result += tempstr[i];
		}
	}

	return result;
}

int alphaToNum(char alph)
{ //Returns the appropriate number for the given letter
	switch (toupper(alph))
	{
	case 'A':
	{
		return 10;
	}
	case 'B':
	{
		return 11;
	}
	case 'C':
	{
		return 12;
	}
	case 'D':
	{
		return 13;
	}
	case 'E':
	{
		return 14;
	}
	case 'F':
	{
		return 15;
	}
	}
}

char numToAlpha(int num)
{ //Returns appropriate letter for the given number
	switch (num)
	{
	case 10:
	{
		return 'A';
	}
	case 11:
	{
		return 'B';
	}
	case 12:
	{
		return 'C';
	}
	case 13:
	{
		return 'D';
	}
	case 14:
	{
		return 'E';
	}
	case 15:
	{
		return 'F';
	}
	}
}