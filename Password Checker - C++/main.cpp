#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class passWordCheck {

private:
	string password;
	string secondPassword;
	int passwordLength;
	int charCount[5] = { 0 };

public:

	passWordCheck() {
		this -> password = "";
		this -> secondPassword = "";
		this -> passwordLength = 0;
	}

	void setPassword(string s) {
		this->password = s;
	}

	void setSecondayPassword(string s) {
		this->secondPassword = s;
	}

	void setPasswordLength(int num) {
		this->passwordLength = num;
	}

	void setCharCount(int num, int i) {
		this->charCount[i] = num;
	}

	string getPassword() {
		return this->password;
	}

	string getSecondaryPassword() {
		return this->secondPassword;
	}

	int getPasswordLength() {
		return this->passwordLength;
	}

	void displayRules(ofstream& outFile) {
		cout << "Please create a password that follows these rules: \n";
		outFile << "Please create a password that follows these rules: \n";
		cout << "1) The password length: 8-32 characters \n";
		outFile << "1) The password length: 8-32 characters \n";
		cout << "2) At least one numerical, i.e., 0, 1, 2,.. \n";
		outFile << "2) At least one numerical, i.e., 0, 1, 2,.. \n";
		cout << "3) At least one upper case letter, i.e., A, B, C, ... \n";
		outFile << "3) At least one upper case letter, i.e., A, B, C, ... \n";
		cout << "4) At least one lower case letter, i.e., a, b, c, ... \n";
		outFile << "4) At least one lower case letter, i.e., a, b, c, ... \n";
		cout << "5) At least one of the special characters, but it must be within the set:{ # $ * ( ) % & ^}. A total of eight (8) special characters. No other special characters are allowed. \n \n";
		outFile << "5) At least one of the special characters, but it must be within the set:{ # $ * ( ) % & ^}. A total of eight (8) special characters. No other special characters are allowed. \n \n";
	}

	void askPasswd(ofstream& outFile) {
		for (int reset = 0; reset < 5; reset++) {
			setCharCount(0, reset);
		}

		string test;
		displayRules(outFile);
		cout << "Pleae enter your password now: ";
		outFile << "\nPlease enter your password now: ";
		cin >> test;
		setPassword(test);
		outFile << getPassword() + "\n";
		setPasswordLength(strlen(getPassword().c_str()));
		while (getPasswordLength() < 8 || getPasswordLength() > 32) {
			cout << getPassword() + "\n";
			displayFail(outFile);
			askPasswd(outFile);
		}
	}


	void displaySucess(ofstream& outFile) {
		cout << "\nYour password will be updated in a few minutes";
		outFile << "\nYour password will be updated in a few minutes";
	}

	void displayFail(ofstream& outFile) {
		cout << "\nYour password failed one or more password rules \n";
		outFile << "\nYour password failed one or more password rules \n";
	}

	void displayMatchFail(ofstream& outFile) {
		cout << "\nThe password you just entered does not match what you previously entered.\nPlease start over and enter a new password.\n";
		outFile << "\nThe password you just entered does not match what you previously entered.\nPlease start over and enter a new password.\n";
	}

	void checkCharType(char ch, int& c) {
		/*
		charCount[0] store the count of illegal special characters
		charCount[1] store the count of numeric
		charCount[2] store the count of lower case characters
		charCount[3] store the count of upper case characters
		charCount[4] store the count of legal special characters set:{ # $ * ( ) % & ^}
		*/
		if ((int)ch >= 48 && (int)ch <= 57) {
			charCount[1]++;
		}
		else if ((int)ch >= 97 && (int)ch <= 122) {
			charCount[2]++;
		}
		else if ((int)ch >= 65 && (int)ch <= 90) {
			charCount[3]++;
		}
		else if ((int)ch >= 35 && (int)ch <= 41 && (int)ch != 39 || (int)ch == 94) {
			charCount[4]++;
		}
		else {
			charCount[0]++;
		}

	}

	int checkRules() {
		//checks charCount array and sees if it is valid. [0] = 0 and [1]-[4] are greather than 0
		//return 1 if valid and 0 if not
		if (charCount[0] != 0) {
			return 0;
		}
		else {
			for (int i = 1; i <= 4; i++) {
				if (charCount[i] == 0)
					return 0;
			}
			return 1;
		}

	}

	int matching(string s1, string s2) {
		//checks to see ife the two strings are matching 
		if (s1 == s2)
			return 1;
		return 0;
	}
};



int main(int argc, char** argv) {
	int validYesNo = 0;
	int matchYesNo = 0;
	int count = 3;
	int test = 0;
	string secondaryPass = "";
	ofstream outFile;
	outFile.open(argv[1]);
	passWordCheck PassCheck;
	while (matchYesNo == 0) {
		while (validYesNo == 0) {
			PassCheck.askPasswd(outFile);
			for (int i = 0; i < PassCheck.getPasswordLength(); i++) {
				PassCheck.checkCharType(PassCheck.getPassword()[i], test);
			}
			validYesNo = PassCheck.checkRules();
			if (validYesNo != 1) {
				PassCheck.displayFail(outFile);
			}
		}
		cout << "Please re-type your password: ";
		outFile << "Please re-type your password: ";
		cin >> secondaryPass;
		PassCheck.setSecondayPassword(secondaryPass);
		outFile << secondaryPass + "\n";
		matchYesNo = PassCheck.matching(PassCheck.getPassword(), PassCheck.getSecondaryPassword());
		if (matchYesNo == 0) {
			PassCheck.displayMatchFail(outFile);
			validYesNo = 0;
		}
	}
	PassCheck.displaySucess(outFile);
	outFile.close();
}
