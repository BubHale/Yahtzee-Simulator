/*
Author:Samuel Hale
Creation Date: 4/7/22
Creation Purpose: Emulates a one ended game of yahtzee that provides the user all scoring possibilites given the current 5 dice in front of them
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <numeric>

using namespace std;

int score;//global
vector <int>myDice;//global
vector <int>rollDice;//global
//int const vector that is used for comparison to see what low scoring opportunities are available
const vector <int>category = { 1,2,3,4,5,6 };//global
//int vector that stores potential low scores at its corresponding index based off of the order on yahtzee.io game
vector <int> potentialLowScore(6);//global
//histogram marks the instances of a certain dice face at an index i.e. if there are 3 1's in your pile the histograms first index = 3 for evaluating scoring opportunities
vector <int> histogram(6);//global
//int vector that stores potential high scores at its corresponding index based off of the order on yahtzee.io game 
vector <int> potentialHighScore(7);//global
//boolean vector that checks true at an index if a certain dice face is sensed i.e. if there is 1 in the pile make 0 index true
vector <bool> straightScoringChecker(6);//global
//booelan vector to make sure user doesnt pick a previously selected scoring category more than once
vector <bool> scoringCategoryChecker(13);//global


/*
Purpose: of all high scoring calculating functions below they take the logic of if statements and nest them in a function so I can check all of them in more than one pass through
*/

void CheckOne(vector<int>histogram, int i) {
	if (i == 0 && histogram.at(i) >= 1) {
		straightScoringChecker.at(i) = true;
	}
}

void CheckTwo(vector<int>histogram, int i) {
	if (i == 1 && histogram.at(i) >= 1) {
		straightScoringChecker.at(i) = true;
		}
}

void CheckThree(vector<int>histogram, int i) {
	if (i == 2 && histogram.at(i) >= 1) {
		straightScoringChecker.at(i) = true;
		}
}

void CheckFour(vector<int>histogram, int i) {
	if (i == 3 && histogram.at(i) >= 1) {
		straightScoringChecker.at(i) = true;
		}
}

void CheckFive(vector<int>histogram, int i) {
	if (i == 4 && histogram.at(i) >= 1) {
		straightScoringChecker.at(i) = true;
		}
}

void CheckSix(vector<int>histogram, int i) {
	if (i == 5 && histogram.at(i) >= 1) {
		straightScoringChecker.at(i) = true;
		}
}

void CalculateTwo(int i, bool &twoExist) {
	//Checks for two or more 
	if (histogram.at(i) == 2) {
		twoExist = true;
	}
}

void CalculateThreeOfAKind(vector <int>histogram, vector <int>tempDice, int i, bool &threeExist) {
	//Checks for three of a kind
	if (histogram.at(i) > 2) {
		potentialHighScore.at(0) = accumulate(tempDice.begin(), tempDice.end(), 0);
		if (histogram.at(i) == 3) threeExist = true;
	}
}

void CalculateFourOfAKind(vector <int>histogram, vector <int>tempDice, int i) {
	//Checks for four of a kind
	if (histogram.at(i) > 3) {
		potentialHighScore.at(1) = accumulate(tempDice.begin(), tempDice.end(), 0);
	}
}

void CalculateFullHouse(int i, bool twoExist, bool threeExist) {
	//Checks for full house
	if (twoExist == true && threeExist == true) potentialHighScore.at(2) = 25;
}

void CalculateSmallStraight(int i) {
	//Handles small straight
	if (straightScoringChecker.at(0) == true && straightScoringChecker.at(1) == true && straightScoringChecker.at(2) == true && straightScoringChecker.at(3) == true || straightScoringChecker.at(1) == true && straightScoringChecker.at(2) == true && straightScoringChecker.at(3) == true && straightScoringChecker.at(4) == true || straightScoringChecker.at(2) == true && straightScoringChecker.at(3) == true && straightScoringChecker.at(4) == true && straightScoringChecker.at(5) == true) {
		potentialHighScore.at(3) = 30;
	}
}

void CalculateLargeStraight(int i) {
	//Handles large straight
	if (straightScoringChecker.at(0) == true && straightScoringChecker.at(1) == true && straightScoringChecker.at(2) == true && straightScoringChecker.at(3) == true && straightScoringChecker.at(4) == true || straightScoringChecker.at(1) == true && straightScoringChecker.at(2) == true && straightScoringChecker.at(3) == true && straightScoringChecker.at(4) == true && straightScoringChecker.at(5) == true) {
		potentialHighScore.at(4) = 40;
	}
}

void CalculateChance(vector <int>tempDice, int i) {
	//Handles chance
	potentialHighScore.at(5) = accumulate(tempDice.begin(), tempDice.end(), 0);
}

void CalculateYahtzee(int i) {
	//Handles Yahtzee
	if (histogram.at(i) >= 5) potentialHighScore.at(6) = 50;
}

//Purpose: Print potential scoring opportunity
void PrintPotentialScoring() {
	cout << "Current potential low point opportunities:";
	for (int i = 0; i < potentialLowScore.size(); i++) {
		cout << endl << "Index:" << i+1 << " " << category.at(i) << "'s " << potentialLowScore.at(i) << " points";
	}
	cout << endl;
	cout << "Current potential high point opportunities:";
	for (int i = 0; i < potentialHighScore.size(); i++) {
		if (i == 0) cout << endl << "Index:" << i+7 << " " << "Three of a kind:" << potentialHighScore.at(i) << " points";
		if (i == 1) cout << endl << "Index:" << i+7 << " " <<"Four of a kind:" << potentialHighScore.at(i) << " points";
		if (i == 2) cout << endl << "Index:" << i+7 << " " << "Full House:" << potentialHighScore.at(i) << " points";
		if (i == 3) cout << endl << "Index:" << 'A' << " " << "Small Straight:" << potentialHighScore.at(i) << " points";
		if (i == 4) cout << endl << "Index:" << 'B' << " " << "Large Straight:" << potentialHighScore.at(i) << " points";
		if (i == 5) cout << endl << "Index:" << 'C' << " " << "Chance:" << potentialHighScore.at(i) << " points";
		if (i == 6) cout << endl << "Index:" << 'D' << " " << "YAHTZEE:" << potentialHighScore.at(i) << " points";
	}
	cout << endl;
}

//Purpose: Get user to pick which scoring opportunity they want
//Input: none
//Output: selects whatever score the user wants to pick in a round, sets it to true so they can't pick it again and updates their score 
void PickPotentialScore() {
	//VARIABLE DECLARATION
	char userInput;

	//Prints scoring opportunities to give users a catalog to choose from
	PrintPotentialScoring();

	cout << "Enter the index of the potential score you want to add to your score:";

	//Gets users input and validates it
	cin >> userInput;
	while (toupper(userInput) != '1' && toupper(userInput) != '2' && toupper(userInput) != '3' && toupper(userInput) != '4' && toupper(userInput) != '5' && toupper(userInput) != '6' && toupper(userInput) != '7' && toupper(userInput) != '8' && toupper(userInput) != '9' && toupper(userInput) != 'A' && toupper(userInput) != 'B' && toupper(userInput) != 'C' && toupper(userInput) != 'D') {
		cout << "Acceptable entries are: Indexes 1-9, 'A', 'B', 'C', or 'D' You entered:" << userInput << " Please try again:";
		cin >> userInput;
		cout << endl;
	}
	cout << endl;

	//Switch case handles which index the users choose for score
	//Handles booleans so that the user can only choose each category once
	//Validates user input if they try to choose a category again
	switch(toupper(userInput)) {
	case '1':
		if (scoringCategoryChecker.at(0) == false) {
			scoringCategoryChecker.at(0) = true;
			score = score + potentialLowScore.at(0);
		}
		else {
			cout << "You have already chosen ones please try again!\n";
			PickPotentialScore();
		}
		break;
	case '2':
		if (scoringCategoryChecker.at(1) == false) {
			scoringCategoryChecker.at(1) = true;
			score = score + potentialLowScore.at(1);
		}
		else {
			cout << "You have already chosen twos please try again!\n";
			PickPotentialScore();
		}
		break;
	case '3':
		if (scoringCategoryChecker.at(2) == false) {
			scoringCategoryChecker.at(2) = true;
			score = score + potentialLowScore.at(2);
		}
		else {
			cout << "You have already chosen threes please try again!\n";
			PickPotentialScore();
		}
		break;
	case '4':
		if (scoringCategoryChecker.at(3) == false) {
			scoringCategoryChecker.at(3) = true;
			score = score + potentialLowScore.at(3);
		}
		else {
			cout << "You have already chosen fours please try again!\n";
			PickPotentialScore();
		}
		break;
	case '5':
		if (scoringCategoryChecker.at(4) == false) {
			scoringCategoryChecker.at(4) = true;
			score = score + potentialLowScore.at(4);
		}
		else {
			cout << "You have already chosen fives please try again!\n";
			PickPotentialScore();
		}
		break;
	case '6':
		if (scoringCategoryChecker.at(5) == false) {
			scoringCategoryChecker.at(5) = true;
			score = score + potentialLowScore.at(5);
		}
		else {
			cout << "You have already chosen sixes please try again!\n";
			PickPotentialScore();
		}
		break;
	case '7':
		if (scoringCategoryChecker.at(6) == false) {
			scoringCategoryChecker.at(6) = true;
			score = score + potentialHighScore.at(0);
		}
		else {
			cout << "You have already chosen three of a kind please try again!\n";
			PickPotentialScore();
		}
		break;
	case '8':
		if (scoringCategoryChecker.at(7) == false) {
			scoringCategoryChecker.at(7) = true;
			score = score + potentialHighScore.at(1);
		}
		else {
			cout << "You have already chosen four of a kind please try again!\n";
			PickPotentialScore();
		}
		break;
	case '9':
		if (scoringCategoryChecker.at(8) == false) {
			scoringCategoryChecker.at(8) = true;
			score = score + potentialHighScore.at(2);
		}
		else {
			cout << "You have already chosen full hoouse please try again!\n";
			PickPotentialScore();
		}
		break;
	case 'A':
		if (scoringCategoryChecker.at(9) == false) {
			scoringCategoryChecker.at(9) = true;
			score = score + potentialHighScore.at(3);
		}
		else {
			cout << "You have already chosen small straight please try again!\n";
			PickPotentialScore();
		}
		break;
	case 'B':
		if (scoringCategoryChecker.at(10) == false) {
			scoringCategoryChecker.at(10) = true;
			score = score + potentialHighScore.at(4);
		}
		else {
			cout << "You have already chosen large straight please try again!\n";
			PickPotentialScore();
		}
		break;
	case 'C':
		if (scoringCategoryChecker.at(11) == false) {
			scoringCategoryChecker.at(11) = true;
			score = score + potentialHighScore.at(5);
		}
		else {
			cout << "You have already chosen chance please try again!\n";
			PickPotentialScore();
		}
		break;
	case 'D':
		if (scoringCategoryChecker.at(12) == false) {
			scoringCategoryChecker.at(12) = true;
			score = score + potentialHighScore.at(6);
		}
		break;
	}

	//After user picks score this will pick dictate end of round so update vectors appropriately
	histogram = { 0,0,0,0,0,0 };
	potentialHighScore = { 0,0,0,0,0,0,0 };
	potentialLowScore = { 0,0,0,0,0,0 };
	myDice.clear();
	rollDice.clear();
}

//Purpose: Calculate potential scoring opportunity
void PotentialScoringLogic() {
	//VARIABLE DECLARATION
	//Reinitializes booleans to false so their is no error in calculating score opportunities
	straightScoringChecker = { false,false,false,false,false,false };
	//bool variable that checks for the occurence of 2 in the histogram used to sense the occurrence of a full house
	bool twoExist = false;
	//bool variable that checks for the occurence of 3 in the histogram used to sense the occurrence of a full house
	bool threeExist = false;
	histogram = { 0,0,0,0,0,0 };
	potentialHighScore = { 0,0,0,0,0,0,0 };
	potentialLowScore = { 0,0,0,0,0,0 };
	
	//Concatenates both vectors and sorts them which will be used to assess scoring opportunitites
	vector <int>tempDice(myDice);
	tempDice.insert(tempDice.end(), rollDice.begin(), rollDice.end());
	sort(tempDice.begin(), tempDice.end());
	
	//Handles lows
	//Outer loop for looping through categories
	for (int i = 0; i < category.size(); i++) {
		//Inner loop for looping through tempDice and comparing it to current low category also increments histogram
		for (int j = 0; j < tempDice.size(); j++) {
			if (tempDice.at(j) == category.at(i)) {
				potentialLowScore.at(i) = potentialLowScore.at(i) + category.at(i);
				histogram.at(i)++;
			}
		}
	}

	//Handles highs
	//Loops through histogram and checks to see if certain things are true if they are a score will be added to a high scoring vector
	for (int i = 0; i < histogram.size(); i++) {
		
		//Checks conditions needed to measure small and large straight
		CheckOne(histogram, i);
		CheckTwo(histogram, i);
		CheckThree(histogram, i);
		CheckFour(histogram, i);
		CheckFive(histogram, i);
		CheckSix(histogram, i);
		
		//Calculates different high scoring opportunities
		CalculateTwo(i, twoExist);
		CalculateThreeOfAKind(histogram, tempDice, i, threeExist);
		CalculateFourOfAKind(histogram, tempDice, i);
		CalculateFullHouse(i, twoExist, threeExist);
		CalculateSmallStraight(i);
		CalculateLargeStraight(i);
		CalculateChance(tempDice, i);
		CalculateYahtzee(i);

	}
	//Clears tempDice so no errors occur when this function is called again
	tempDice.clear();
}

//Purpose: Prints first roll message
void RollMessage() {
	cout << "Press R to roll dice\n";
}

//Purpose: Prints Dice
//Input: General vector
//Output: Prints vector in a sorted format with indexes to help user with input
void PrintDice(vector <int>ary) {
	//Iterates through passed in dice pile and prints it following a format
	for (int i = 0; i < ary.size(); i++) {
		cout << endl << "Index:" << i + 1 << " " << ary.at(i);
	}
	cout << endl;
}

/*
Purpose: Handle transfers from myDice -> rollDice
Input: Index, userInput, pileInput
*/
void MyDiceToRollDice(int &index, char &userInput, char &pileInput) {
	stringstream str;
	//Handle myDice -> rollPile dice transfer
	if (toupper(pileInput) == 'B' && myDice.size() > 0) {
		//Makes sure user is inputting a correct index prior to dice transfer
		while (index - 1 > myDice.size() - 1 || index - 1 < 0) {
			//Prints dice indexes available and prompts 
			PrintDice(myDice);
			cout << "That is not a valid roll pile index please try again:";

			//Gets user input translates it to integer for comparison
			cin >> userInput;
			str << userInput;
			str >> index;
			cout << endl;

			//Had input issues that I suspected were the result of stringstream so we reinitialize after stream pulls from input
			userInput = 'D';
		}
		//Handles dice transfer
		rollDice.push_back(myDice.at(index - 1));
		myDice.erase(myDice.begin() + (index - 1));

	}

	//Handles case if user specified myDice -> rollDice by myDice was empty
	else if (toupper(pileInput) == 'B' && myDice.size() == 0) {
		cout << "You can't transfer from that pile since it is empty; the specified index will be transferred from roll dice instead." << endl;
		pileInput = 'A';

		//Handles rollPile -> myDice dice transfer
		if (toupper(pileInput) == 'A' && rollDice.size() > 0) {
			//Makes sure user is inputting a correct index prior to dice transfer
			while (index - 1 > rollDice.size() - 1 || index - 1 < 0) {
				//Prints dice indexes available and prompts 
				PrintDice(rollDice);
				cout << "That is not a valid roll pile index please try again:";

				//Gets user input translates it to integer for comparison
				cin >> userInput;
				str << userInput;
				str >> index;
				cout << endl;

				//Had input issues that I suspected were the result of stringstream so we reinitialize after stream pulls from input
				userInput = 'D';
			}
			//Handles the dice transfer
			myDice.push_back(rollDice.at(index - 1));
			rollDice.erase(rollDice.begin() + (index - 1));

		}
	}
}

/*
Purpose: Handle transfers from rollDice -> myDice
Input: Index, userInput, pileInput, stringstream str
*/
void RollDiceToMyDice(int &index, char &userInput, char &pileInput) {
	stringstream str;
	//Handles rollPile -> myDice dice transfer
	if (toupper(pileInput) == 'A' && rollDice.size() > 0) {
		//Makes sure user is inputting a correct index prior to dice transfer
		while (index - 1 > rollDice.size() - 1 || index - 1 < 0) {
			//Prints dice indexes available and prompts 
			PrintDice(rollDice);
			cout << "That is not a valid roll pile index please try again:";

			//Gets user input translates it to integer for comparison
			cin >> userInput;
			str << userInput;
			str >> index;
			cout << endl;

			//Had input issues that I suspected were the result of stringstream so we reinitialize after stream pulls from input
			userInput = 'D';
		}
		//Handles the dice transfer
		myDice.push_back(rollDice.at(index - 1));
		rollDice.erase(rollDice.begin() + (index - 1));

	}

	//Handles case if user specified rollPile -> myDice but rollDice was empty
	else if(toupper(pileInput) == 'A' && rollDice.size() == 0) {
		cout << "You can't transfer from that pile since it is empty; the specified index will be transferred from your dice instead." << endl;
		pileInput = 'B';

		//Handle myDice -> rollPile dice transfer
		if (toupper(pileInput) == 'B' && myDice.size() > 0) {
			//Makes sure user is inputting a correct index prior to dice transfer
			while (index - 1 > myDice.size() - 1 || index - 1 < 0) {
				//Prints dice indexes available and prompts 
				PrintDice(myDice);
				cout << "That is not a valid roll pile index please try again:";

				//Gets user input translates it to integer for comparison
				cin >> userInput;
				str << userInput;
				str >> index;
				cout << endl;

				//Had input issues that I suspected were the result of stringstream so we reinitialize after stream pulls from input
				userInput = 'D';
			}
			//Handles dice transfer
			rollDice.push_back(myDice.at(index - 1));
			myDice.erase(myDice.begin() + (index - 1));
			pileInput = 'A';
		}
	}
}

/*
Purpose: Handles every roll after the first of the round
Function: Handles reroll functionality by prompting getting input, sensing input if reroll it rerolls using dice pile
if its not reroll character it goes to check for an index and puts that index in users pile and deletes it from rollpile
Input: numRoll variable to keep track of how many times user has rolled in a round
*/
void RerollLogic(int &numRoll) {
	//VARIABLE DECLARATION
	char userInput;
	char pileInput;
	//Loop handles the 3 rolls system
	while (numRoll < 3) {

		//Prints the potential scores user can pick
		PotentialScoringLogic();
		PrintPotentialScoring();

		cout << "Enter the index of the dice you want to keep or push back to roll pile; Enter R to reroll or Enter C to pick score:";

		//Get users input and validate it
		cin >> userInput;
		while (toupper(userInput) != 'R' && toupper(userInput) != 'C' && toupper(userInput) != '1' && toupper(userInput) != '2' && toupper(userInput) != '3' && toupper(userInput) != '4' && toupper(userInput) != '5') {
			cout << "Acceptable entries are: 'R', 'C', or Indexes 1-5. You entered:" << userInput << " Please try again:";
			cin >> userInput;
			cout << endl;
		}
		cout << endl;

		//rerolls Roll Dice pile depending on its current size
		if (toupper(userInput) == 'R') {
			for (int i = 0; i < rollDice.size(); i++) {
				rollDice.at(i) = rand() % 6 + 1;
			}
			numRoll++;

			//Sort Dice Piles if they have 2 or more elements
			if (myDice.size() > 1) sort(myDice.begin(), myDice.end());
			if (rollDice.size() > 1) sort(rollDice.begin(), rollDice.end()); 


			//Print Dice Piles
			cout << "Your dice:";
			PrintDice(myDice);
			cout << "Roll dice:";
			PrintDice(rollDice);

			//Once user has used their 3rd roll they have to pick the score they want
			if (numRoll == 3) {
				PotentialScoringLogic();
				PickPotentialScore();
			}
		}

		//Handles user wanting to continue and pick their score
		else if (toupper(userInput) == 'C') {
			PickPotentialScore();
			numRoll = 3;
		}

		//Handles the user wanting to add a dice to his pile 
		else {
			//converts userinput to integer
			int index;
			stringstream str;
			str << userInput;
			str >> index;
			userInput = 'D';

			cout << "Enter 'A' if your transferring an index from roll pile to your pile; Enter 'B' if you're transferring an index from your pile to the roll pile:";

			//Gets users input and validates it
			cin >> pileInput;
			cout << endl;
			while (toupper(pileInput) != 'A' && toupper(pileInput) != 'B') {
				cout << "Only acceptable entries are 'A'(rollpile->yourpile) or 'B'(yourpile->rollpile) please try again:";
				cin >> pileInput;
				cout << endl;
			}

			//Functions to handle dice transfers due to needed if statement execution
			RollDiceToMyDice(index, userInput, pileInput);
			MyDiceToRollDice(index, userInput, pileInput);

			//Sort Dice Piles so long as they have 2 or more elements
			if (myDice.size() > 1) sort(myDice.begin(), myDice.end());
			if (rollDice.size() > 1) sort(rollDice.begin(), rollDice.end());
			

			//Print Dice Piles
			cout << "Your dice:";
			PrintDice(myDice);
			cout << "Roll dice:";
			PrintDice(rollDice);
			
		}
	}
}

/*
Purpose: Handle first round logic
Function: Sets up seed random for true random picks, initialized rollDice sorts and prints it
Input: userInput and numRoll to track rolls and handle users inputted choice
*/
void FirstRollLogic(char userInput, int &numRoll) {
	srand(time(NULL));

	//initialize dice to roll dice
	if (toupper(userInput) == 'R') {
		for (int i = 0; i < 5; i++) {
			rollDice.push_back(rand() % 6 + 1);
		}

		//increment numRoll to see how many rolls user has before round ends
		numRoll++;

		//Sort Dice Pile
		sort(rollDice.begin(), rollDice.end());

		//Print Dice Pile
		cout << "Roll dice:";
		PrintDice(rollDice);
		
	}
}

//Purpose: Runs the game and exits when game is over
int main() {
	//VARIABLE DECLARATION
	char userInput;
	int numRoll;
	//for loop handles rounds
	for (int i = 0; i < 13; i++) {
			numRoll = 0;
			cout << "Round:" << i + 1 << endl;
			cout << "Your current score is:" << score << endl;
			RollMessage();

			//Get users input and validate it
			cin >> userInput;
			while (toupper(userInput) != 'R') {
				cout << "Only acceptable entry is 'R'; you entered:" << userInput << " please try again:";
				cin >> userInput;
				cout << endl;
			}
			//Different logic for first roll and second/third roll
			FirstRollLogic(userInput, numRoll);
			RerollLogic(numRoll);
	}

	cout << "Your score to end the game is:" << score << endl;
	
	system("pause");
	return 0;
}