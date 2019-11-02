//IMPORT PROPER LIBRARIES
#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
using namespace std;


////////////////////////////////////////
//////////// FUNCTION 1 ////////////////
////////////////////////////////////////

int appendToAll(string a[], int n, string value) {

	//CREATE IF STATEMENT TO RETURN -1 IF INTEGER IS A NEGATIVE NUMBER
	if (n < 0) {
		return -1;
	}

	//FOR LOOP TO APPEND THE STRING VALUE ONTO EACH INDEX OF THE STRING ARRAY
	for (int k = 0; k < n; k++) {
		a[k] += value;
	}

	//RETURN N TO THE PROGRAM
	return n;
}




////////////////////////////////////////
//////////// FUNCTION 2 ////////////////
////////////////////////////////////////

int lookup(const string a[], int n, string target) {

	//CREATE IF STATEMENT TO RETURN -1 IF INTEGER IS A NEGATIVE NUMBER
	if (n < 0) {
		return -1;
	}

	//INDEX INITIALIZED
	int k = 0;

	//WHILE LOOP TO SEARCH THROUGH INDICES
	while (k < n) {

		//IF STATEMENT TO RETURN K TO PROGRAM IF MATCH IS FOUND
		if (a[k] == target) {
			return k;
		}
		else
			k++; //UPDATE INDEX IF MATCH IS NOT FOUND
	}

	//IF WHILE LOOP FINISHES AND FINDS NO MATCH, RETURN -1
	return -1;

}




////////////////////////////////////////
//////////// FUNCTION 3 ////////////////
////////////////////////////////////////

int positionOfMax(const string a[], int n) {

	//CREATE IF STATEMENT TO RETURN -1 IF INTEGER IS A NEGATIVE NUMBER
	if (n <= 0) {
		return -1;
	}

	//DECLARE STRING TO COMPARE TO
	string largest;
	int k = 0;

	//WHILE LOOP TO FIND STRING >= ANY OTHER STRING IN ARRAY
	while (k < n) {

		if (largest <= a[k]) {
			largest = a[k];
			k++;
		}
		else
			k++;
	}

	//FOR LOOP TO OUTPUT WHAT INDEX THE STRING IS LOCATED AT IN THE ARRAY
	for (size_t i = 0; i != n; i++) {
		if (largest == a[i])
			return i;
	}

	//IF NOTHING INTERESTING, RETURN -1
	return -1;
}




////////////////////////////////////////
//////////// FUNCTION 4 ////////////////
////////////////////////////////////////

int rotateLeft(string a[], int n, int pos) {

	//CREATE IF STATEMENT TO RETURN -1 IF INTEGER IS A NEGATIVE NUMBER
	if (n <= 0) {
		return -1;
	}

	//CREATE STRING VARIABLE 
	string move_str = a[pos];

	//OUTER FOR LOOP FOR LOOKING THROUGH STRING TO COMPARE TO
	for (int k = 0; k < n; k++) {

		//IF STATEMENT TO FIND WHERE MOVE_STR IS IN STRING
		if (a[k] == move_str) {

			//FOR LOOP TO MOVE ALL ELEMENTS TO LEFT INDEX AFTER THIS ELEMENT WAS FOUND
			for (int i = k + 1; i < n; i++) {
				a[i - 1] = a[i];
			}

			//FOR LOOP TO ADD ELEMENT AT POSITION INPUTTED OT END OF STRING
			for (int j = 0; j < n; j++) {
				if (j == n - 1) {
					a[j] = move_str;
				}

			}

			//RETURN THE POSITION FOUND IF ONE WAS FOUND
			return k;
		}

	}

	//IF NOTHING WAS FOUND, RETURN -1
	return -1;
}




////////////////////////////////////////
//////////// FUNCTION 5 ////////////////
////////////////////////////////////////

int countRuns(const string a[], int n) {

	//CREATE IF STATEMENT TO RETURN -1 IF INTEGER IS A NEGATIVE NUMBER
	if (n < 0) {
		return -1;
	}
	else if (n == 0) {
		return 0;
	}

	//SET UP INT COUNT 
	int i = 1;

	//GIVEN A NON EMPTY STRING, 1 CAN BE THE LOWEST NUMBER
	int sequence = 1;

	//WHILE LOOP TO COMPARE DIFFERENT INDICES OF STRING UP TO INDEX N - 1
	while (i < n) {

		if (a[i] != a[i - 1]) {
			sequence++;
			i++;
		}
		else
			i++;

	}

	//RETURN VALUE OF SEQUENCE TO PROGRAM
	return sequence;
}




////////////////////////////////////////
//////////// FUNCTION 6 ////////////////
////////////////////////////////////////

int flip(string a[], int n) {

	//CREATE IF STATEMENT TO RETURN -1 IF INTEGER IS A NEGATIVE NUMBER
	if (n < 0) {
		return -1;
	}

	//SET UP TEMPORARY STRING TO CREATE NEW FLIPPED ARRAY
	string temp;

	//FOR LOOP TO MAKE FLIPPED ARRAY
	for (int i = 0; i < n / 2; i++) {
		temp = a[n - i - 1];
		a[n - i - 1] = a[i];
		a[i] = temp;
	}

	//RETURN VALUE FOR N
	return n;
}




////////////////////////////////////////
//////////// FUNCTION 7 ////////////////
////////////////////////////////////////

int differ(const string a1[], int n1, const string a2[], int n2) {

	//CREATE IF STATEMENT TO RETURN -1 IF INTEGER IS A NEGATIVE NUMBER
	if (n1 < 0 || n2 < 0) {
		return -1;
	}

	//CREATE INT TO HOLD INDEX WHERE STRINGS ARE NOT EQUAL
	int index_notequal = 0;

	//SPLIT UP INTO 3 IF STATEMENTS DEPENDING ON WHETHER N1 OR N2 IS THE LESSER VALUE

	//IF STATEMENT TO COMPARE STRINGS AND RETURN INDEX WHERE THEY ARE NOT EQUAL IF N1<N2
	if (n1 < n2) {
		for (int k = 0; k < n1; k++) {
			if (a1[k] != a2[k]) {
				index_notequal = k;
				return index_notequal;
			}
		}
		return n1;
	}

	//IF STATEMENT TO COMPARE STRINGS AND RETURN INDEX WHERE THEY ARE NOT EQUAL IF N2<N1
	if (n2 < n1) {
		for (int k = 0; k < n2; k++) {
			if (a1[k] != a2[k]) {
				index_notequal = k;
				return index_notequal;
			}
		}
		return n2;
	}

	//IF STATEMENT TO COMPARE STRINGS AND RETURN INDEX WHERE THEY ARE NOT EQUAL IF N1=N2, 
	//IN THIS CASE CHOOSING N1 OR N2 AS BOUNDS DOESN'T MATTER, ARBITRARILY CHOSE N1
	if (n1 == n2) {
		for (int k = 0; k < n1; k++) {
			if (a1[k] != a2[k]) {
				index_notequal = k;
				return index_notequal;
			}
		}
		return n1;
	}

	//RETURN THAT THEY ARE EQUAL NOWHERE IF THEY AREN'T EQUAL ANYWHERE
	return index_notequal;

}




////////////////////////////////////////
//////////// FUNCTION 8 ////////////////
////////////////////////////////////////

int subsequence(const string a1[], int n1, const string a2[], int n2) {

	//CREATE IF STATEMENT TO RETURN -1 IF INTEGER IS A NEGATIVE NUMBER
	if (n1 <= 0 || n2 < 0) {
		return -1;
	}
	else if (n2 == 0) {
		return 0;
	}
	else if (n2 > n1)
		return -1;

	//FOR WHILE LOOP START WITH -1 AS DEFAULT
	int index_match = -1;

	//CREATE INDEX
	int j = 0;

	//WHILE LOOP TO CHECK FOR A MATCH IN INDEX WITH STRING A1 VERSUS A2
	while (index_match == -1) {
		if (a1[j] == a2[0])
			index_match = j;
		else if ((a1[j] != a2[0]) && (j == n1 - 1))
			return -1;
		else
			j++;
	}

	//IF MATCH WAS FOUND, CHECK TO SEE IF THE ENTIRE SEQUENCE OF A2 IS IN A1 WITH FOR LOOP BELOW
	int k;
	for (k = 0; k < n2;) {
		if ((a1[k + index_match] == a2[k]) && (k == n2 - 1))
			return index_match;

		if (a1[k + index_match] == a2[k])
			k++;

		if (a1[k + index_match] != a2[k])
			return -1;
	}

	//SHOULD NOT REACH THIS POINT, BUT IN CASE, RETURN -1
	return index_match;
}




////////////////////////////////////////
//////////// FUNCTION 9 ////////////////
////////////////////////////////////////

int lookupAny(const string a1[], int n1, const string a2[], int n2) {

	//CREATE IF STATEMENT TO RETURN -1 IF INTEGER IS A NEGATIVE NUMBER
	if (n1 <= 0 || n2 <= 0) {
		return -1;
	}

	//CREATE INT TO HOLD INDEX WHERE STRINGS ARE NOT EQUAL
	int index_equal = -1;

	//SET UP A FOR LOOP TO INDEX THORUGH EACH INDEX OF THE SECOND STRING AND COMPARE TO EVERY INDEX OF THE FIRST STRING
	for (int k = 0; k < n1; k++) {
		for (int i = 0; i < n2; i++) {
			if (a2[i] == a1[k]) {
				index_equal = k; //IF MATCH IS FOUND THEN SET INTEGER INDEX_EQUAL TO THIS INDEX AN RETURN THE INDEX
				return index_equal;
			}
		}
	}

	//THIS WILL RETURN -1 IF THERE WAS NOTHING EQUAL TO BE FOUND
	return index_equal;

}




////////////////////////////////////////
//////////// FUNCTION 10 ////////////////
////////////////////////////////////////

int divide(string a[], int n, string divider) {

	//CREATE IF STATEMENT TO RETURN -1 IF INTEGER IS A NEGATIVE NUMBER
	if (n < 0) {
		return -1;
	}

	//CREATE TEMPORARY STRING TO STORE VALUES SO THEY ARE NOT LOST
	string temp1 = "";

	//START ITERATION WITH J AND UPDATE J ONLY WHEN THE VALUE IS LESS THAN THE DIVIDER
	int j = 0;

	//FOR LOOP TO RUN THROUGH ALL ELEMENTS OF THE STRING
	for (int k = 0; k < n; k++) {
		if (a[k] < divider) {
			temp1 = a[j]; //SET THIS VALUE EQUAL TO TEMP1 IN ORDER TO SAVE IT
			a[j] = a[k];
			a[k] = temp1;
			j++;
		}
	}

	//RETURN THE FINAL INDEX J WHERE THE CONDITION WAS TRUE
	return j;


}


int main() {


	string d[9] = { "xavier", "betty", "john", "john", "ed", "ed", "ed", "john", "john" };
	int p = countRuns(d, 9);  //  returns 5
	cout << p << endl;
	int a = countRuns(d, 6);  //  returns 4 ; the runs from "john" and "ed" are equal but ed came first
	cout << a << endl;
	int b = countRuns(d, 1);  //  returns 1 ; only one element with one run
	cout << b << endl;
	int c = countRuns(d, 0);  //  returns -1; count 0 elements of a run, so this would be an error
	cout << c << endl;


}



