//Luis Alvear
//DFSM simulator
//10/17/2022

#include<iostream>
#include<fstream>
#include<string>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	/*Example usage menu*/
	cout << "*COMPILATION USAGE:\nfsm.exe (will compile based on info on FSM.txt by default)\nfsm.exe <filename.txt> (will compile based on info on argv[1] with any file name as a CLI argument)" << endl;
	cout << "\n*NOTE:\nSpecify the size of the language first. Then enter the language, one character at a time.\nEach state has two rows for its function in the file. See example below..." << endl;
	cout << "\n*FILE EXAMPLE:\n0, 1---->Alphabet allowed\n2---->Number of states\n1---->Accepting state\n(0, 0, 0)---->State 0\n(0, 1, 1)---->State 0\n(1, 0, 1)---->State 1\n(1, 1, 0)---->State 1" << endl;

	char choice; //Holds sentinel value

	do {
		
		string line;
		string file;
		string input;

		/*Use FSM.txt if not CLI arguents.
		If thre is a CLI argument use it as filename*/
		if (argc < 2)
		{
			file = ("FSM.txt");
		}
		else if (argc == 2)
		{
			file = argv[1];

		}
		cout << "\nExtracting DFSM information from: " << file << endl;

		ifstream myfile(file);
		string alphabet("");
		string accstates;
		string functions;
		string startstate;
		string transinput;
		string endstate;
		vector <string>transition;
		int nstates;
		int currentline = 0;
		int i = 0;
		int arrcount = 0;
		bool accept = true;
		char state = 48;
		char alphabetarr[10] = { 0 };
		char accstatesarr[10] = { 0 };
		char startstatearr[10] = { 0 };
		char inputarr[10] = { 0 };
		char endstatearr[10] = { 0 };

		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				currentline++;

				/*Gets the alphabet allowed in the DFSM.
				Removes blank spaces and commas,*/
				if (currentline == 1)
				{
					cout << "Alphabet: ";
					alphabet = line;

					alphabet.erase(remove(alphabet.begin(), alphabet.end(), ','), alphabet.end());
					alphabet.erase(remove(alphabet.begin(), alphabet.end(), ' '), alphabet.end());

					for (int i = 0; i < alphabet.size(); i++)
					{
						alphabetarr[i] = alphabet[i];
					}
				}

				/*Gets the number of states in the DFSM*/
				if (currentline == 2)
				{
					cout << "Number of states: ";
					nstates = stoi(line);

				}

				/*Gets accepting states. Removes commas and blank spaces
				Stores them in an array to be checked at the end*/
				if (currentline == 3)
				{
					cout << "Accepting states: ";
					accstates = line;

					accstates.erase(remove(accstates.begin(), accstates.end(), ','), accstates.end());
					accstates.erase(remove(accstates.begin(), accstates.end(), ' '), accstates.end());

					for (int i = 0; i < accstates.size(); i++)
					{
						accstatesarr[i] = accstates[i];
					}
				}
				/*Gets the functions for each state. Removes special characters.*/
				if (currentline >= 4)
				{
					cout << "State function: ";
					functions = line;

					functions.erase(remove(functions.begin(), functions.end(), ','), functions.end());
					functions.erase(remove(functions.begin(), functions.end(), '('), functions.end());
					functions.erase(remove(functions.begin(), functions.end(), ')'), functions.end());
					functions.erase(remove(functions.begin(), functions.end(), ' '), functions.end());
					transition.push_back(functions); //Push the function to a vector

					/*Store the start state in a variable and then add it to an array.
					Same for input and endstate
					Startstate belongs to first position in vector
					transinput belongs to second position in transition vector
					endstate belongs to third position in transition vector*/
					for (i; i < transition.size(); i++)
					{
						//cout << transition[i]<<endl;
						startstate = transition.at(i).substr(0, 1);
						transinput = transition.at(i).substr(1, 1);
						endstate = transition.at(i).substr(2, 2);

						startstatearr[i] += startstate[0];
						inputarr[i] += transinput[0];
						endstatearr[i] += endstate[0];
						arrcount++;//Increment the function array count
					}
				}
				cout << line << endl;
			}
			myfile.close();
		}
		else
		{
			cout << "Couldn't open file";
		}

		/*Declare an initialize a dynamic array that
		will hold the language inputed by the user*/
		int SIZE;
		cout << "\nEnter size of your language: ";
		cin >> SIZE;
		char* language = new char(SIZE);

		for (int i = 0; i < SIZE; i++)
		{
			cout << i + 1 << ". ";
			cin >> language[i];
		}

		bool foundalphabet = true;

		/*Loops trhough the language and the input array from the functions.
		First check if the language from the user is in the DFSM alphabet. Then,
		check if the language is in the input from each state array. If so, if the state is
		the same as the startstate, we set the state to the correspondent
		end state*/
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < arrcount; j++)
			{
				if (alphabet.find(language[i]) != std::string::npos)
				{
					if (language[i] == inputarr[j])
					{
						if (state == startstatearr[j])
						{
							state = endstatearr[j];
							break;
						}
					}
				}
				else
				{
					foundalphabet = false;
					break;
				}	
			}
		}

		/*If the state is the same as any of the accepting states,
		accept the string*/
		bool accepted = false;

		for (int i = 0; i < accstates.size(); i++)
		{
			if (state == accstatesarr[i])
			{
				accepted = true;
				break;
			}
		}

		/*Display result*/
		if (!foundalphabet)
			cout << "Language not in the alphabet (Rejected)\n";
		else if (accepted)
			cout << "Accepted\n";
		else
			cout << "Rejected\n";

		cout << "\nEnter 'a' to enter new DFSM or'q' to quit: ";
		cin >> choice;

	} while (choice != 'q');

	system("PAUSE");
}