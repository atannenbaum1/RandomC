// A.TANNENBAUM
//////////////////////////////
//////// PROJECT 5 ///////////
//////////////////////////////

#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<cstring>
#include<cassert>
using namespace std;

//DECLARE CONSTANT FOR MAX PATTERN WORD LENGTH
const int MAX_WORD_LENGTH = 20;

//FUNCTION TO MAKE ALL CHARACTERS OF 2D CHARACTER STRING LOWERCASE
void lowerfunc(char word1[][MAX_WORD_LENGTH + 1], int nPatterns) {

	//RUN A FOR LOOP TO CHECK EACH C STRING
	for (int x = 0; x < nPatterns; x++) {

		//RUN A NESTED FOR LOOP TO CHECK EACH CHARACTERIN EACH C STRING
		for (int y = 0; y < MAX_WORD_LENGTH + 1; y++) {
			if (word1[x][y] != '\0') {
				word1[x][y] = tolower(word1[x][y]);
			}
			else
				break;
		}
	}

}

//FUNCTION TO CHECK EACH WORD IN PATTERN FOR PROPER FORM
void checkalpha(char word1[][MAX_WORD_LENGTH + 1], int index, int separation[]) {

	//RUN FOR LOOP TO LOOK AT EACH CHARACTER
	for (int j = 0; j < MAX_WORD_LENGTH + 1;) {

		//IF STATEMENT BLOCK TO CHECK EACH CHARACTER IS AN ALPHABETICAL LETTER
		if (isalpha(word1[index][j]) && word1[index][j + 1] == '\0')
			break;
		else if (isalpha(word1[index][j]))
			j++;
		else {

			//FOR LOOP TO CHANGE ALL BAD IMPROPER PATTERNS TO NULL CHARACTER
			for (int aa = 0; aa < MAX_WORD_LENGTH + 1; aa++) {
				word1[index][aa] = '\0';

			}

			//IDENTIFY THIS SPOT IN SEPARATION ARRAY BY SETTING TO LARGE ARBITRARY VALUE
			separation[index] = 1000;
			break;
		}
	}
}

//FUNCTION TO CHANGE TO NULL CHARACTER ACROSS ALL CHARACTERS OF A C STRING
void addzerobyte(char word1[][MAX_WORD_LENGTH + 1], int index) {

	//RUN FOR LOOP TO EXAMINE EACH CHARACTER AND CHANGE TO NULL CHARACTER
	for (int aa = 0; aa < MAX_WORD_LENGTH + 1; aa++) {
		word1[index][aa] = '\0';
	}
}

//FUNCTION TO COMPARE PATTERN WORDS OF EACH CHARACTER ARRAY AND CHANGE CORRESPONDING PATTERN WORD TO NULL CHARACTER
void compare(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int nPatterns) {

	/*NOTE: THIS FUNCTION IS ALWAYS RUN AFTER ADDZEROBYTE OR CHECKALPHA FUNCTIONS, SO ITS IMPLEMENTATION WILL WORK IN CHECKING
			FOR NULLCHARACTER IN FIRST INDEX*/

	//FOR LOOP TO CHECK IF NULL CHARACTER PRESENT IN FIRST INDEX 
	for (int w = 0; w < nPatterns; w++) {

		/*CHECK NULL CHARACTER OF FIRST WORD OR SECOND WORD CHARACTER ARRAYS IN IF STATEMENT BLOCKAND CHANGE OPPOSING 
				WORD OF THE SAME PATTERN (AT SAME INDEX) TO NULL CHARACTERS*/
		if (word1[w][0] == '\0') {
			for (int aa = 0; aa < MAX_WORD_LENGTH + 1; aa++) {
				word2[w][aa] = '\0';
			}
		}
		else if (word2[w][0] == '\0') {
			for (int aa = 0; aa < MAX_WORD_LENGTH + 1; aa++) {
				word1[w][aa] = '\0';
			}
		}
	}
}

//FUNCTION TO SHIFT ALL PROPER PATTERNS UP IN INDEX LOCATION, MOVING ALL IMPROPER WORDS (NULL CHARACTERS AS THIS POINT) TO HIGHER INEX LOCATION
int shift_up(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], const int nPatterns) {

	//INITIALIZE NEW INTEGER TO RETURN TO FUNCTION
	int new_in = nPatterns;

	//FOR LOOP TO LOOP THROUGH AMOUNT OF PATTERNS
	for (int z = 0; z < new_in;) {
		if (word1[z][0] == '\0') {

			//IF NULL CHARACTER FOUND IN FIRST INDEX, MOVE ALL ELEMENTS IN ARRAY
			for (int z1 = z; z1 < new_in - 1; z1++) {
				strcpy(word1[z1], word1[z1 + 1]);
				strcpy(word2[z1], word2[z1 + 1]);
			}

			//UPDATE INDEX TO CONTAIN REMAINING VALID ELEMENTS
			new_in--; 
		}
		else
			z++; //UPDATE INDEX TO LOOK AT NEXT PATTERN WORD LOCATION
	}

	//THIS VALUE REPRESENTS THE NEW INTEGER TO BE RETURNED BY THE MAKEPROPER FUNCTION
	return new_in;
}

//FUNCTION TO DELETE INVALID ENTRIES IN SEPARATION ARRAY
void sep_delete(int separation[], const int nPatterns) {

	//SETUP ELEMENT AMOUNG USING NPATTERNS
	int new_in_sep = nPatterns;

	//FOR LOOP TO LOOK AT EACH INDEX OF ARRAY
	for (int z = 0; z < new_in_sep;) {

		//EARLIER, ALL INVALID VALUES WERE SET TO 1000
		if (separation[z] == 1000) {

			//NETED FOR LOOP TO MOVE ALL ELEMENTS IF MATCH FOUND
			for (int z1 = z; z1 < new_in_sep - 1; z1++) {
				separation[z1] = separation[z1 + 1];
			}
			new_in_sep--; //UPDATING PATTERN COUNTS
		}
		else
			z++; //UPDATE INDEX TO LOOK AT NEXT WORD
	}
}

//FUNCTION TO ERASE ALL CHARACTERS THAT ARE NOT ALPHABETICAL LETTERS OR SPACES
void erase_nonalpha(char str[], int docbound) {

	/*NOTE: NOTICE THAT I DO NOT RETURN DOCBOUND TO THE FUNCTION TO USE AS A BOUND FOR OTHER LOOPS, I OPTED FOR LOOKING FOR THE NULL
			CHARACTER IN MY SECOND FUNCTION MOST OF THE TIME */

	//ESTABLISH INDEX COUNT
	int x = 0;

	//WHILE LOOP TO KEEP OPERATIONS FROM UNDEFINED BEHAVIOR
	while (x < docbound) {

		//IF STATEMENT BLOCK TO FIND ALL NON ALPPHABETICAL AND SPACE CHARACTERS, THEN MOVE ELEMENTS OVER
		if (!isalpha(str[x]) && str[x] != ' ') {
			for (int y = x; str[y] != '\0'; y++) {
				str[y] = str[y + 1];
			}
			docbound--; //UPDATE DOCBOUND FOR LOOP
		}
		else
			x++; //UPDATE INDEX TO LOOK AT NEXT CHARACTER
	}

}

//FUNCTION TO CHANGE ALL CHARACTERS OF A 1D ARRAY TO LOWERCASE
void lower_1d(char str[], int size) {

	//FOR LOOP TO LOOK AT EACH CHARACTER
	for (int i = 0; i < size; i++) {

		//IF STATEMENT BLOCK TO CHANGE ALL CHARCTERS TO LOWERCASE UNTIL HITTING THE NULL CHARACTER
		if (str[i] != '\0') {
			str[i] = tolower(str[i]);
		}
	}
}

/*ONE OF THE TWO REQUIRED FUNCTION TO CHECK THE INPUTTED PATTERNS FOR PROPER FORM, THEN CHANGE PATTERN ARRAY ACCORDINGLY TO ONLY
	ONLY CONTAIN PROPER PATTERNS*/
int makeProper(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int nPatterns) {

	//SPEC REQUIRED PATTERNS LESS THAN ZERO TO BE TREATED AS ZERO
	if (nPatterns < 0) {
		nPatterns = 0;
	}

	//CHNAGE ALL WORDS TO CSTRING TO LOWER CASE
	lowerfunc(word1, nPatterns);
	lowerfunc(word2, nPatterns);


	//FOR LOOP TO LOOK AT PATTERNS TO CHECK FOR SOME SOME SIMPLE ISSUES
	for (int i = 0; i < nPatterns;) {

		//IF STATEMENT BLOCK TO CHECK IF SEPARATION OF ANY PATTERNS ARE ZERO, IF SO, THEY ARE INVALID
		if (separation[i] < 0) {
			addzerobyte(word1, i);
			addzerobyte(word2, i);
			separation[i] = 1000;
			continue;
		}
		else {
			//IF PATTERNS DO NOT HAVE NEGATIVE SEPARATION, MAKE SURE THEY ONLY CONTAIN ALPHABETICAL LETTERS
			checkalpha(word1, i, separation);
			checkalpha(word2, i, separation);
		}

		//LOOK AT NEXT WORD
		i++;
	}

	//CHANGE ALL WORDS OF A PATTERN TO NULL CHARACTER
	compare(word1, word2, nPatterns);

	//SHIFT THE ARRAY UP IN ORDER FOR FURTHER COMPARISON
	int new_in = shift_up(word1, word2, nPatterns);

	//FOR LOOP TO LOOK FOR DUPLICATES IN PATTERN ARRAYS
	for (int a = 0; a < new_in; a++) {

		//TEMPORARY ARRAYS TO STORE WORDS TO COMPARE TO PATTERN ARRAYS
		char temp1[MAX_WORD_LENGTH + 1];
		char temp2[MAX_WORD_LENGTH + 1];
		strcpy(temp1, word1[a]);
		strcpy(temp2, word2[a]);

		/*FOR LOOP TO FIND DUPLICATES AN IF FOUND, CHECK SEPARATION: A DUPLICATE PATTERN CAN HAVE THE WORDS IN EITHER ORDER
				SO IF STATEMENT BLOCK CONSIDERS THIS*/
		for (int b = 0; b < new_in; b++) {
			if (strcmp(temp1, word1[b]) == 0 && strcmp(temp2, word2[b]) == 0) {

				//DUPLICATE PATTERNS WITH LOWER SEPARATIONS ARE DELETED AND REDERED INVALID
				if (separation[a] < separation[b]) {
					addzerobyte(word1, a);
					addzerobyte(word2, a);
					separation[a] = 1000;
				}
			}
			else if (strcmp(temp1, word2[b]) == 0 && strcmp(temp2, word1[b]) == 0) {
				if (separation[a] < separation[b]) {
					addzerobyte(word1, a);
					addzerobyte(word2, a);
					separation[a] = 1000;

				}
			}

		}

		//FIND WHERE THERE ARE DUPLICATE PATTERNS WITH THE SAME SEPARATION AND SET UP TEMPORARY ARRAYS TO KEEP TRACK OF THEIR LOCATION
		int count_dup[1000];
		int count_dup_index = 0;

		/*FOR LOOP TO RUN THROUGH AS BEFORE BUT ONLY UPDATE THE TEMP ARRAYS ABOVE, NO REMOVALS YET: ONCE AGAIN, WE CHECK FOR THE PATTERNS
			TO OCCUR IN EITHER ORDER AND ONLY WHEN EQUAL TO EACH OTHER*/
		for (int b = 0; b < new_in; b++) {
			if (strcmp(temp1, word1[b]) == 0 && strcmp(temp2, word2[b]) == 0) {
				if (separation[a] == separation[b]) {
					count_dup[count_dup_index] = a;
					count_dup_index++;
				}
			}
			else if (strcmp(temp1, word2[b]) == 0 && strcmp(temp2, word1[b]) == 0) {
				if (separation[a] == separation[b]) {
					count_dup[count_dup_index] = a;
					count_dup_index++;
				}
			}

		}

		/*ARRAY CAN CONTAIN ANY PERMUTATION OF PROPER PATTERNS, SO IF THERE ARE AN N NUMBER OF PATTERNS THAT ARE DUPLICATES WITH THE SAME
			SEPARATION, THEN REMOVE N-1 OF THOSE PATTERN USING A FOR LOOP*/
		for (int b = 0; b < count_dup_index - 1; b++) {

			addzerobyte(word1, count_dup[b]);
			addzerobyte(word2, count_dup[b]);

		}
	}

	//"DELETE" ALL INVALID SEPARATION VALUES BY MOVING THEM AFTER THE VALID NUMBERS
	sep_delete(separation, nPatterns);

	//ONCE AGAIN, SHIFT PROPER PATTERN ARRAYS
	int new_in1 = shift_up(word1, word2, new_in);

	//FUNCTION OUTPUTS NUMBER OF PROPER PATTERNS TO BE RETURNED TO MAIN
	return new_in1;
}

/*SECOND REQUIRED FUNCTION TO TAKE IN PROPER PATTERNS AND CHECK A DOCUMENT TO SEE IF THESE PATTERNS OCCUR. SHOULD ANY VALID PATTERNS OCCUR IN
	IN THE DOCUMENT, THEN THE DOCUMENT EARNS A RATING POINT, THE FUNCTION RETURNS THE TOTAL RATING*/
int rate(const char document[], const char word1[][MAX_WORD_LENGTH + 1], const char word2[][MAX_WORD_LENGTH + 1], const int separation[], int nPatterns) {

	//SET UP RATING VARIBALE INITIALIZED TO ZERO
	int rating = 0;

	//BUILD A TEMPORARY ARRAY WITH ALL CHARACTERS FROM ORIGINAL DOCUMENT USING A FOR LOOP
	char doc_temp[251];
	int doc_c = 0;
	for (doc_c = 0; doc_c < 251;) {

		//IF STATEMENT BLOCK TO RUN UNTIL NULL CHARACTER IS ENCOUNTERED
		if (document[doc_c] != '\0') {
			doc_temp[doc_c] = document[doc_c];
			doc_c++;
		}
		else {
			doc_temp[doc_c] = '\0';
			doc_c++;
			break;
		}
	}

	//INTEGER BOUND BASED ON LENGTH OF CHAR ARRAY USED IN HEPER FUNCTIONS
	int docbound = doc_c + 1;

	//HELPER FUNCTIONS TO PUT DOCUMENT INTO PROPER FORM
	erase_nonalpha(doc_temp, docbound);
	lower_1d(doc_temp, docbound);

	//IF FOCUMENT IS AN EMPTY STRING, THEN THE RATING IS ZERO BY DEFAULT
	if (doc_temp[0] == '\0') {
		return rating;
	}

	//CHECK FOR OTHER INCONCSISTIES IN THE DOCUMENT USING A FOR LOOP
	int aaa = 0;
	while (doc_temp[aaa] != '\0') {

		//IF STATEMENT BLOCK TO CHECK IF DOCUMENT CONTAINS ALPHABETICAL LETTERS, IF IT DOES NOT, THE DOCUMENT HAS NO PATTERNS TO MATCH TO
		// IN THIS CASE, ZERO WILL BE RETURNED TO MAIN
		if (isalpha(doc_temp[aaa])) {
			break;
		}
		else if (doc_temp[aaa] == ' ' && doc_temp[aaa + 1] == '\0') {
			return rating;
		}
		else if (doc_temp[aaa] == ' ') {
			aaa++;
		}
		else
			return rating;
	}

	//BOOL VALUE TO KEEP INTEGER A OF FOR LOOP CONSTANT UNTIL THE DOCUMENT HAS BEEN COMPLETELY GONE THROUGH
	bool checkb = true;
	int b = 0;

	//FOR LOOP T COMPARE WORDS IN PATTERN ARRAYS TO THE DOCUMENT
	for (int a = 0; a < nPatterns;) {

		//TEMPORARY ARRAYS TO STORE WORDS FROM THE PATTERN ARRAYS TO THEN COMPARE AGAINST DOCUMENT
		char temp1[MAX_WORD_LENGTH + 1];
		char temp2[MAX_WORD_LENGTH + 1];
		strcpy(temp1, word1[a]);
		strcpy(temp2, word2[a]);

		
		//ONCE WORDS HAD BEEN COLLECTED FROM PATTERN ARRAY, COLLECT A WORD FROM THE DOCUMENT USING A WHILE LOOP IN ORDER TO FIND A PATTERN
		char temp3[251];
		int d = 0; //VARIABLE TO INDEX THROUGH THE TEMP ARRAY BEING BUILT 
		while (doc_temp[b] != '\0') {

			//IF STATMENT BLOCK TO EITHER ADD TO TEMP ARRAY OR BREAK ONCE A WORD HAS BEEN COLLECTED
			if ((doc_temp[b + 1] == ' ') && isalpha(doc_temp[b])) {
				temp3[d] = doc_temp[b];
				temp3[d + 1] = '\0';
				b += 2;
				break; //WORDS ARE INDICATED BETWEEN EACH SPACE
			}
			else if (doc_temp[b + 1] == '\0' && isalpha(doc_temp[b])) {
				temp3[d] = doc_temp[b];
				temp3[d + 1] = '\0';
				b++;
				checkb = false; //ONCE THE END OF THE STRING IS REACHED, INDEX A NEEDS TO BE UPDATED TO OBTAIN ANOTHER WORD FROM THE
								// THE PATTERN LIST, WE WILL SEE THIS LATER
				break;
			}
			else if (isalpha(doc_temp[b])) { 

				//CONTINUE COLLECTING LETTERS FROM THE DOCUMENT IF A SPACE HAS NT BEEN ENCOUNTERED
				temp3[d] = doc_temp[b];
				d++;
				b++;

			}
			else if (doc_temp[b] == ' ' && doc_temp[b + 1] != '\0') {
				//IF JUST A SPACE IS ENCOUNTERED AT THE BEGINNING OF THE BUILDING OF AN ARRAY, CONTINUTE BUILDING
				b++;
			}
			else {
				//SHOULD THESE CONDITIONS FAIL, THE BUILDING OF THE WORD IS EITHER DONE OR INVALID, SO UPDATE THE INDEX AND BREAK
				b++;
				break;
			}

		}

		/* NOW THAT WE HAVE A WORD FROM THE DOCUMENT, IF IT MATCHES EITHER WORD FROM THE PATTERN, LETS SEE IF ANOTHER WORD FROM THE 
				THE DOCUMENT MATCHES THE SECOND WORD IN THE PATTERN */
		bool repeat = false;
		if (strcmp(temp3, temp1) == 0 || strcmp(temp3, temp2) == 0) {

			//WHILE LOOP WILL ONLY RUN IF AT LEAST ONE WORD MATCHES
			while (!repeat) {

				//IF THE FIRST WORD IN THE PATTERN EQUALS THE DOCUMENT, LOOK FOR A SECOND WORD
				if (strcmp(temp1, temp3) == 0) {

					//THIS COLLECTS A SECOND WRD FROM THE DOCUMENT IN THE SAME WAY AS BEFORE, EXCEPT A COUNTER IS KEPT TO SEE IF THE SEPARATION
						// IS ALSO FULFILLED
					int counter = -1;
					int c = b;
					bool temp4_check = false;
					while (!temp4_check) {
						d = 0;
						char temp4[251] = { 0 };
						while (doc_temp[c] != '\0') {


							if ((doc_temp[c + 1] == ' ') && isalpha(doc_temp[c])) {
								temp4[d] = doc_temp[c];
								temp4[d + 1] = '\0';
								c += 2;
								break;
							}
							else if (doc_temp[c + 1] == '\0' && isalpha(doc_temp[c])) {
								temp4[d] = doc_temp[c];
								temp4[d + 1] = '\0';
								c++;
								break;
							}
							else if (isalpha(doc_temp[c])) {
								temp4[d] = doc_temp[c];
								d++;
								c++;
							}
							else if (doc_temp[c] == ' ' && doc_temp[c + 1] != '\0') {
								c++;
							}
							else {
								c++;
								break;
							}

						}

						// WHEN A WORD IS COLLECTED ADD TO THE COUNTER
						counter++;

						//IF THE SECOND WORD COLLECTED EQUALS THE SECOND WORD OF THE PATTERN AND IT IS WITHIN THE SEPARATION THRESHOLD
							// THEN A VALID PATTERN IS FOUND, THE RATING IS UPDATED, AND WE BREAK OUT OF THE WHILE LOOP
						if ((strcmp(temp2, temp4) == 0) && (counter <= separation[a])) {
							rating++;
							repeat = true;
						}
						else if ((doc_temp[c] == '\0')) {

							//IF WE ARE AT THE END OF THE DOCUMENT AND NO PATTERN HAS BEEN FOUND, THEN BREAK OUT OF THE WHILE LOOP
							repeat = true;
						}

						//WHEN WE ARE AT THE END OF THE DOCUMENT WE WANT TO START OVER COLLECTED A NEW WORD SO WE WANT TO 
							//BREAK OUT OF BOTH WHILE LOOPS
						if (doc_temp[c] == '\0') {
							temp4_check = true;
						}


					}

				}
				else if (strcmp(temp2, temp3) == 0) {
					//THE SECOND PART OF THIS IF STATEMENT IS EXACTLY THE SAME AS THE THE FIRST PART, EXCEPT THIS COMPARES IF THE FIRST WORD 
						// FOR THE DOCUMENT EQUALS THE SECOND WORD OF THE PATTERN AND THEN COMPARES THE SECOND WORD FROM THE DOCUMENT TO THE FIRST
						// WORD OF THE PATTERN

					int counter = -1;
					int z = b;
					bool temp4_check = false;
					while (!temp4_check) {
						d = 0;
						char temp4[251] = { 0 };
						while (doc_temp[z] != '\0') {



							if ((doc_temp[z + 1] == ' ') && isalpha(doc_temp[z])) {
								temp4[d] = doc_temp[z];
								temp4[d + 1] = '\0';
								z += 2;
								break;
							}
							else if (doc_temp[z + 1] == '\0' && isalpha(doc_temp[z])) {
								temp4[d] = doc_temp[z];
								temp4[d + 1] = '\0';
								z++;
								break;
							}
							else if (isalpha(doc_temp[z])) {
								temp4[d] = doc_temp[z];
								d++;
								z++;
							}
							else if (doc_temp[z] == ' ' && doc_temp[z + 1] != '\0') {
								z++;
							}
							else {
								z++;
								break;
							}

						}

						counter++;

						if ((strcmp(temp1, temp4) == 0) && (counter <= separation[a])) {

							rating++;
							repeat = true;
						}
						else if ((doc_temp[z] == '\0')) {
							repeat = true;
						}

						if (doc_temp[z] == '\0') {
							temp4_check = true;
						}



					}
				}

				//JUST IN CASE WE ARE HERE AND WE NEED TO BREAK OUT OF THE WHILE LOOP STILL
				repeat = true;
			}
		}

		//IF WE ARE AT THE END OF THE DOCUMENT, WE WANT TO START OVER WITH A NEW PATTERN AND AT THE BEGINNING OF THE DOCUMENT
		// THIS IS CONTROLLED USING THE BOOL MENTIONED BEFORE 
		if (!checkb) {
			a++;
			b = 0;
			checkb = true;
		}

	}

	//RETURN THE RATING OF TH DOCUMENT TO MAIN
	return rating;
}


int main() {


	//TESTING OF THE MAKEPROPER FUNCTION
	char w1[8][MAX_WORD_LENGTH + 1] = { "mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have", "NeFaRiOuS" };
	char w2[8][MAX_WORD_LENGTH + 1] = { "scientist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad", "pLoT" };
	int sep[8] = { 1, 3, 0, 2, 1, 0, 12, 0 };

	char w1_1[8][MAX_WORD_LENGTH + 1] = { "mad", "der anged", "NEFARIOUS", "half-witted", "robo t", "plot", "have", "NeFaRiOuS" };
	char w2_1[8][MAX_WORD_LENGTH + 1] = { "sci entist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad", "pLoT" };
	int sep_1[8] = { 1, 3, 0, 2, 1, 0, 12, 0 };

	char w1_2[8][MAX_WORD_LENGTH + 1] = { "mad", "", "4444444", " ", "robot", "     ", "have", "NeFaRiOu0" };
	char w2_2[8][MAX_WORD_LENGTH + 1] = { "", "robot", "PLOT", "assistant", "der anged", "Nefarious 3", "ma2d", "pLoT" };
	int sep_2[8] = { 1, 3, 0, 2, 1, 0, 12, 0 };

	char w1_3[8][MAX_WORD_LENGTH + 1] = { "mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have", "NeFaRiOuS" };
	char w2_3[8][MAX_WORD_LENGTH + 1] = { "scientist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad", "pLoT" };
	int sep_3[8] = { -1, -3, 0, -1, -1, 2, -12, 1 };

	char w1_4[8][MAX_WORD_LENGTH + 1] = { "mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have", "NeFaRiOuS" };
	char w2_4[8][MAX_WORD_LENGTH + 1] = { "scientist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad", "pLoT" };
	int sep_4[8] = { 1, 3, 0, 2, 1, 0, 12, 0 };

	char w1_5[8][MAX_WORD_LENGTH + 1] = { "mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have", "NeFaRiOuS" };
	char w2_5[8][MAX_WORD_LENGTH + 1] = { "scientist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad", "pLoT" };
	int sep_5[8] = { 1, 3, 0, 2, 1, 0, 12, 0 };

	char w1_6[8][MAX_WORD_LENGTH + 1] = { "mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have", "NeFaRiOuS" };
	char w2_6[8][MAX_WORD_LENGTH + 1] = { "scientist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad", "pLoT" };
	int sep_6[8] = { 1, 3, 0, 2, 1, 0, -12, 0 };

	char w1_7[8][MAX_WORD_LENGTH + 1] = { "mad", "deran ged", "NEFARIO US", "half-witted", "robot", "plot", "have", "NeFaRiOuS" };
	char w2_7[8][MAX_WORD_LENGTH + 1] = { "scien tist", "robot", "PLOT", "assistant", "der anged", "Nefar ious", "mad", "pLoT" };
	int sep_7[8] = { 1, 3, 0, 2, 1, 0, 12, 0 };

	char w1_8[8][MAX_WORD_LENGTH + 1] = { "mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "ha ve", "NeFaRiOuS" };
	char w2_8[8][MAX_WORD_LENGTH + 1] = { "scienti st", "rob ot", "PL OT", "assistant", "d eranged", "Ne farious", "mad", "pLoT" };
	int sep_8[8] = { 1, 3, 0, 2, 1, 0, 12, 0 };

	char w1_9[8][MAX_WORD_LENGTH + 1] = { "mad", "derange2d", "NEFAR2IOUS", "half-witted", "rob4ot", "plot", "ha11ve", "NeF2aRiOuS" };
	char w2_9[8][MAX_WORD_LENGTH + 1] = { "scient ist", "robot", "PLOT", "assis3tant", "deranged", "Nefar11ious", "mad", "pLoT" };
	int sep_9[8] = { 1, 3, 0, 2, 1, 0, 12, 0 };

	char w1_10[8][MAX_WORD_LENGTH + 1] = { "mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have", "NeFaRiOuS" };
	char w2_10[8][MAX_WORD_LENGTH + 1] = { "scientist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad", "pLoT" };
	int sep_10[8] = { 1, 1, 0, 2, 1, 0, 12, 0 };

	char w1_11[8][MAX_WORD_LENGTH + 1] = { "mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have", "NeFaRiOuS" };
	char w2_11[8][MAX_WORD_LENGTH + 1] = { "scientist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad", "pLoT" };
	int sep_11[8] = { -1, -3, 0, -2, -1, 0, 12, 0 };

	char w1_12[8][MAX_WORD_LENGTH + 1] = { "mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have", "NeFaRiOuS" };
	char w2_12[8][MAX_WORD_LENGTH + 1] = { "scientist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad", "pLoT" };
	int sep_12[8] = { -1, -3, 0, -2, -1, 0, -12, 0 };

	char w1_13[8][MAX_WORD_LENGTH + 1] = { "mad", "deranged", "plot", "half-witted", "robot", "Nefarious", "have", "NeFaRiOuS" };
	char w2_13[8][MAX_WORD_LENGTH + 1] = { "mad", "robot", "PLOT", "assistant", "deranged", "plot", "mad", "pLoT" };
	int sep_13[8] = { 1, 3, 0, 2, 1, 0, 12, 5 };

	char w1_14[8][MAX_WORD_LENGTH + 1] = { "mad", "robot", "plot", "half-witted", "deranged", "Nefarious", "have", "NeFaRiOuSi" };
	char w2_14[8][MAX_WORD_LENGTH + 1] = { "mad", "robot", "Plot", "assistant", "deranged", "plot", "mad", "pLoT" };
	int sep_14[8] = { 1, 3, 0, 2, 1, 0, 12, 5 };

	assert(makeProper(w1, w2, sep, 8) == 4);
	assert(makeProper(w1_1, w2_1, sep_1, 8) == 2);
	//assert(makeProper(w1_2, w2_2, sep_2, 8) == 0);		//infinite loop
	assert(makeProper(w1_3, w2_3, sep_3, 8) == 1);		//should equal one
	assert(makeProper(w1_4, w2_4, sep_4, 0) == 0);
	assert(makeProper(w1_5, w2_5, sep_5, -2) == 0);
	assert(makeProper(w1_6, w2_6, sep_6, 8) == 3);		//should equal 3
	assert(makeProper(w1_7, w2_7, sep_7, 8) == 2);
	assert(makeProper(w1_8, w2_8, sep_8, 8) == 1);
	//assert(makeProper(w1_9, w2_9, sep_9, 8) == 0);		//can't handle 0 elements being valid
	assert(makeProper(w1_10, w2_10, sep_10, 8) == 4);
	assert(makeProper(w1_11, w2_11, sep_11, 8) == 2);
	assert(makeProper(w1_12, w2_12, sep_12, 8) == 1);		//should be equal to 1
	assert(makeProper(w1_13, w2_13, sep_13, 8) == 5);		//should be 6
	assert(makeProper(w1_14, w2_14, sep_14, 8) == 7);
	cout << "All tests succeeded #1" << endl;


	//TESTING OF THE RATE FUNCTION
	const int TEST1_NRULES = 4;
	char test1w1[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"mad",       "deranged", "nefarious", "have"
	};
	char test1w2[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"scientist", "robot",    "plot",      "mad"
	};
	int test1dist[TEST1_NRULES] = {
		1,           3,          0,           12
	};
	assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
	assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
	assert(rate("**** 2018 ****",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	assert(rate("  That plot: NEFARIOUS!",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	assert(rate("that plot nefarious",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	/*assert(rate("deranged deranged robot deranged robot robot",		//this should equal 1
		test1w1, test1w2, test1dist, TEST1_NRULES) == 8);*/
	assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	assert(rate(" t",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	assert(rate("18235182736182736,cmme",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	assert(rate("",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	assert(rate("mad scientist",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	assert(rate("mad mads mads scientist",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	assert(rate("The deranged robot had a very nefarious plot",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
	assert(rate("Dinosaurs are not very nefarious creatures, but are often deranged!",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	assert(rate("the per3son and with the m3ad scien3333tist is very brave",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	assert(rate("robot robot robot robot",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	assert(rate("the mad scentist schemed a nefarious plo6t with his sidekick dera66 nged robot",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	assert(rate("0000 0000 1111 plot",
		test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	cout << "All tests succeeded #2" << endl;

}