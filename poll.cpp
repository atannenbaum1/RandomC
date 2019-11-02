//// here i will work on building the second function

//IMPORT REQUIRED LIBRARIES
#include <iostream>
#include <cctype>
#include <string>
using namespace std;

//SET UP A FUNCTION TO CHANGE STATE CODE TO UPPERCASE FROM SUBSTRING MADE IN HASPROPERSYNTAX
string upper_case(string& str) {
	for (size_t i = 0; i < str.size(); i++) {
		str[i] = toupper(str[i]);
	}
	return str;
}

//USE FUNCTION PROVIDED IN SPEC
bool isValidUppercaseStateCode(string stateCode)
{
	upper_case(stateCode);
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
		"LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
		"OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos  &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}

bool hasProperSyntax(string polldata) {

	//CHECK IF POLLDATA IS EMPTY STRING, RETURN TRUE
	if (polldata == "")
		return true;

	//CREATE STATECODE SUBSTRING TO CHECK IF STATECODE IS VALID
	string state = polldata.substr(0, 2);

	//IF POLLDATA ONLY CONTAINS STATECODE, RETURN TRUE
	if (polldata.size() == 2 && isValidUppercaseStateCode(state))
		return true;

	//SET UP FIRST WHILE LOOP TO CHECK STATEFORCASTS LONGER THAN 2
	int i = 0;
	while (i != polldata.size()) {

		//A VALID STATEFORECAST CANNOT INCLUDE A SPACE
		if (polldata[i] == ' ')
			return false;

		//IF THE STATEFORECAST HAS A VALID STATECODE UPDATE THE INDEX
		if (isValidUppercaseStateCode(state))
			i += 2;
		else
			return false;

		//SET UP NESTED WHILE LOOP TO RUN THROUGH STATEFORECASTS WITH MULTIPLE PARTY RESULTS
		//	THIS WILL ONLY RUN IF THERE IS NOT A COMMA PRESENT OR IF THE END OF THE POLLDATA STRING HAS NOT BEEN REACHED
		while (i != polldata.size() && polldata[i] != ',') {

			//THE INDEX FOLLOWING THE STATE CODE MUST BE A DIGIT
			if (isdigit(polldata[i]))
				i++;
			else
				return false;

			//THE NEXT PLACE HAS AN OPTIONAL DIGIT
			if (isdigit(polldata[i]))
				i++;

			//IF THE LOOP HAS NOT ENDED AND THERE IS A NON LETTER AT THE END, IT IS NOT PROPER SYNTAX
			if (isalpha(polldata[i]))
				i++;
			else
				return false;

		}

		//SET UP VARIABL TO IDENTIFY FINAL INDEX
		int end_index = polldata.size() - 1;
		
		//CHECK IF ENDING IN COMMA, INVALID IF SO
		if (polldata[end_index] == ',')
			return false;
		
		//UPDATE THE INDEX IF THERE IS A COMMA SEPARATING STATE FORECASTS, IF THERE IS NO COMMA, BREAK THE LOOP AND IT IS PROPER SYNTAX AT THIS POINT
		if (polldata[i] == ',')
			i++;
		else
			break;
	}
	return true;
}

//SECOND FUNCTION TO DETERMINE TOTAL NUMBER OF PREDICTED VOTES FOR A PARTY
int tallySeats(string pollData, char party, int& seatTally) {

	//RETURN 1 IF THE PARTY IS NOT PROPER PARTY CODE AND IF THE POLL STRING DOESN'T HAVE PROPER SYNTAX
	if (!hasProperSyntax(pollData) && !isalpha(party))
		return 1;

	//RETURN 1 IF THE POLL DATA STRING DOESN'T HAVE PROPER SYNTAX
	if (!hasProperSyntax(pollData))
		return 1;

	//RETURN 2 IF THE PARTY CODE IS NOT PROPER
	if (!isalpha(party))
		return 2;

	//SET INITIAL VALUE FOR SETTALLY
	seatTally = 0;

	//CHANGE ALL LETTERS TO UPPERCASE FOR THE PARTY AND STRING TO MAKE COMPARISONS EASIER
	upper_case(pollData);
	party = toupper(party);

	//FOR LOOP TO FIND DIGITS BEFORE PARTY CHARACTER
	for (size_t i = 0; i != pollData.size(); i++) {

		// IF THERE ARE TWO DIGITS PRESENT
		if (pollData[i] == party && isdigit(pollData[i - 2]))
			seatTally += atoi(&pollData.at(i - 2)); //CONVERT THESE CHARACTERS TO DIGITS AND UPDATE SEATTALLY

		// iF THERE IS ONLY 1 DIGIT PRESENT
		else if (pollData[i] == party && isdigit(pollData[i - 1]))
			seatTally += atoi(&pollData.at(i - 1)); //CONVERT THESE CHARACTERS TO DIGITS AND UPDATE SEATTALLY
	}
	return 0;
}

// Ill work more on the main function now
int main() {
	int seat_num; //integer for settally 
	//string pollData = "ca50d40r25d32t";
	if (hasProperSyntax("ct, ,"))
		cout << "True" << endl;
	else
		cout << "False" << endl;

	seat_num = -888;
	if (tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'd', seat_num) == 0 && seat_num == 22)
		cout << "yes 1" << endl;

	seat_num = -888;
	if(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", '@', seat_num) == 2 && seat_num == -888)
		cout << "yes 2" << endl;

	seat_num = -888;
	if(tallySeats("CT5D,NY9R17D1I,VT, ne3r00D", '@', seat_num) == 1 && seat_num == -888) 
		cout << "yes 3" << endl;

	seat_num = -888;
	if(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'l', seat_num) == 0 && seat_num == 0) 
		cout << "yes 4" << endl;

	seat_num = -888;
	if(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'r', seat_num) == 0  && seat_num == 12) 
		cout << "yes 5" << endl;

	seat_num = -888;
	if(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'i', seat_num) == 0 && seat_num == 1) 
		cout << "yes 6" << endl;

	seat_num = -888;
	if(tallySeats("ca,ny,ks,NJ4d", 'd', seat_num) == 0 && seat_num == 4) 
		cout << "yes 7" << endl;

	seat_num = -888;
	if(tallySeats("ct4r,ca, ,ks4r", 'r', seat_num) == 1 && seat_num == -888) 
		cout << "yes 8" << endl;

	seat_num = -888;
	if(tallySeats("vt", 'd', seat_num) == 0 && seat_num == 0) 
		cout << "yes 9" << endl;

	seat_num = -888;
	if(tallySeats("ca,ny,co,cz", 'd', seat_num) == 0 && seat_num == 0) 
		cout << "yes 10" << endl;

	seat_num = -888;
	if(tallySeats("ct, ,", ' ', seat_num) == 1 && seat_num == -888) 
		cout << "yes 11" << endl;

	seat_num = -888;
	if (tallySeats("", 'd', seat_num) == 0 && seat_num == 0)
		cout << "yes 12" << endl;
}

