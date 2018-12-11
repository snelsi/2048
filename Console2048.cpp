// This is the realisation of Console "2048" Game using Ñ++
#include "Console2048.h"

#define N 4			// FIELD SIZE

using namespace std;

unsigned score;		// Current score
unsigned highscore;	// Highest score

bool proceed;		// Should game continue
bool first2048;		// Does user got 2048


// Set Console text color
void setColor(int color) 
{
	SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((15 << 4) | color) );
}

// Cell setColor set (depending on cell value)
void setCellColor(int a) {
	switch (a) {
	case 2:    setColor(4);  break;
	case 4:    setColor(3);  break;
	case 8:    setColor(5);	 break;
	case 16:   setColor(2);  break;
	case 32:   setColor(6);  break;
	case 64:   setColor(1);  break;
	case 128:  setColor(7);  break;
	case 256:  setColor(8);  break;
	case 512:  setColor(9);  break;
	case 1024: setColor(10); break;
	case 2048: setColor(11); break;
	default:   setColor(4);  break;
	}
}


// Print field on the screen
// ---------
// | 2 |   |
// ---------
// |   | 2 |
// ---------
void printField(int **arr) {
	system("cls");

	cout << "\n     Score:  ";
	setColor(5); 
	cout << setw(5) << score; 
	setColor(0);

	cout << "\tHighscore:  ";
	setColor(3);
	cout << highscore << "\n\n";
	setColor(0);

	for (int i = 0; i < N; i++)
	{
		// ----------------
		cout << " ";
		for (int j = 0; j < N; j++) cout << "-------";
		cout << "-\n ";

		// |    |     |     |
		for (int j = 0; j < N; j++)
			cout << "|      ";
		cout << "|\n ";

		// |  2  |     |  2  |
		for (int j = 0; j < N; j++)
		{
			cout << "|";
			if (arr[i][j] != 0)
			{
				setCellColor(arr[i][j]);
				cout << setw(5) << arr[i][j] << " ";
				setColor(0);
			}
			else
			{
				cout << "      ";
			}
		}
		// |    |     |     |
		cout << "|\n ";
		for (int j = 0; j < N; j++)
			cout << "|      ";
		cout << "|\n";
	}
	// ------------------
	cout << " ";
	for (int j = 0; j < N; j++)
		cout << "-------";
	cout << "-\n";
}


// Add new number when move
void randfill(int **arr) {
	srand(time(NULL));
	int x;
	int y;
	for (int i = 0; i < 1000; i++)
	{
		x = rand() % N;
		y = rand() % N;
		if (arr[x][y] == 0)
		{
			arr[x][y] = (rand() % 11 >= 9) ? 4 : 2;
			score += arr[x][y];
			return;
		}
	}
}


// User got to 2048
void winMenu() {
	first2048 = false;
	cout << "\nCongratulations! You won!\nKeep playing?\n";
	char r;
	bool ind = 1;
	do {
		cin >> r;
		switch (r)
		{
		case 'y': case 'Y': case 'Ä': case 'ä': proceed = 1; ind = 0; break;	// Continue match
		case 'n': case 'N': case 'Í': case 'í': proceed = 0; ind = 0; break;	// End match
		default: cout << "Enter answer in y/n form: ";
		}
	} while (ind);
}


// Is there any moves left
bool check(int **arr) {
	// Empty cell
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (arr[i][j] == 0)
			{
				return 1;
			}
		}
	}
	// Identical neighboring cells
	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N - 1; j++)
		{
			if (arr[i][j] == arr[i + 1][j] || arr[i][j] == arr[i][j + 1])
			{
				return 1;
			}
		}
		if (arr[i][N - 1] == arr[i + 1][N - 1] || arr[N - 1][i] == arr[N - 1][i + 1])
		{
			return 1;
		}
	}
	// No moves left
	return 0;
}


// Shift cells up
bool movefuncUP(int **arr) {
	bool ind = 1;
	int l;
	for (int j = 0; j < N; j++)
	{
		l = 1;
		for (int i = 1; i < N; i++)
		{
			if (arr[i][j] != 0 && i >= l)
			{
				if (arr[i - 1][j] == 0)
				{
					arr[i - 1][j] = arr[i][j];
					arr[i][j] = 0;
					i -= 2;
					ind = 0;
				}
				else
				{
					if (arr[i - 1][j] == arr[i][j])
					{
						arr[i - 1][j] += arr[i][j];
						if (first2048 && arr[i - 1][j] == 2048)
						{
							winMenu();
						}
						score += arr[i - 1][j];
						arr[i][j] = 0;
						l = i + 1;
						ind = 0;
					}
				}
			}
		}
	}
	return ind;
}

// Shift cells down
bool movefuncDOWN(int **arr) {
	bool ind = 1;
	int l;
	for (int j = 0; j < N; j++)
	{
		l = N - 2;
		for (int i = N - 2; i >= 0; i--)
		{
			if (arr[i][j] != 0 && i <= l)
			{
				if (arr[i + 1][j] == 0)
				{
					arr[i + 1][j] = arr[i][j];
					arr[i][j] = 0;
					i += 2;
					ind = 0;
				}
				else
				{
					if (arr[i + 1][j] == arr[i][j])
					{
						arr[i + 1][j] *= 2;
						if (first2048 && arr[i + 1][j] == 2048)
						{
							winMenu();
						}
						score += arr[i + 1][j];
						arr[i][j] = 0;
						l = i - 1;
						ind = 0;
					}
				}
			}
		}
	}
	return ind;
}

// Shift cells left
bool movefuncLEFT(int **arr) {
	bool ind = 1;
	int l;
	for (int i = 0; i < N; i++)
	{
		l = 1;
		for (int j = 1; j < N; j++)
		{
			if (arr[i][j] != 0 && j >= l)
			{
				if (arr[i][j - 1] == 0)
				{
					arr[i][j - 1] = arr[i][j];
					arr[i][j] = 0;
					j -= 2;
					ind = 0;
				}
				else
				{
					if (arr[i][j - 1] == arr[i][j])
					{
						arr[i][j - 1] += arr[i][j];
						if (first2048 && arr[i][j - 1] == 2048)
						{
							winMenu();
						}
						score += arr[i][j - 1];
						arr[i][j] = 0;
						l = j + 1;
						ind = 0;
					}
				}
			}
		}
	}
	return ind;
}


// Shift cells right
bool movefuncRIGHT(int **arr) {
	bool ind = 1;
	int l;
	for (int i = 0; i < N; i++)
	{
		l = N - 2;
		for (int j = N - 2; j >= 0; j--)
		{
			if (arr[i][j] != 0 && j <= l)
			{
				if (arr[i][j + 1] == 0)
				{
					arr[i][j + 1] = arr[i][j];
					arr[i][j] = 0;
					j += 2;
					ind = 0;
				}
				else
				{
					if (arr[i][j + 1] == arr[i][j])
					{
						arr[i][j + 1] += arr[i][j];
						if (first2048 && arr[i][j + 1] == 2048)
						{
							winMenu();
						}
						score += arr[i][j + 1];
						arr[i][j] = 0;
						l = j - 1;
						ind = 0;
					}
				}
			}
		}
	}
	return ind;
}


// Start new match
void match(int **arr) {
	bool ind;
	proceed = true;
	first2048 = true;

	// Reseting field
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			arr[i][j] = 0;
		}
	}
	score = 0;
	// Initial fill
	randfill(arr);
	randfill(arr);

	printField(arr);
	do
	{
		// Get user move
		do
		{
			ind = 1;
			char move = _getch();
			switch (move)
			{
			// Ind = 0 if at least 1 cell was moved
			case 72: case 'w': case 'ö':  ind = movefuncUP(arr);     break;
			case 80: case 's': case 'û':  ind = movefuncDOWN(arr);   break;
			case 75: case 'a': case 'ô':  ind = movefuncLEFT(arr);   break;
			case 77: case 'd': case 'â':  ind = movefuncRIGHT(arr);  break;
			}
			cin.clear();
		} while (ind);
		// Add new elem to field
		randfill(arr);
		// Print field
		printField(arr);
		// Check for ability to make move
	} while (proceed && check(arr));

	cout << "End of the game!" << endl;
	if (!first2048) cout << "You won! Good job!\n" << endl;

	cout << endl << "Final score: " << score << endl;
	cout << "Impressive!";

	// Save Highscore
	if (score > highscore)
	{
		cout << "New Highscore! :o\n";
		highscore = score;
		ofstream Highscore("highscore.txt");
		Highscore << highscore;
		Highscore.close();
	}
	while (getchar() != '\n');
}


// Question to user: exit or new game
bool exitFunction() {
	char v;
	// Try to get an answer 10 times
	for (int i = 0; i < 10; i++)
	{
		cout << "Play again? (y/n) : ";
		cin >> v;
		while (getchar() != '\n');
		switch (v)
		{
		case 'y': case 'Y': return 1;	// New game
		case 'n': case 'N': return 0;	// Exit
		default: cout << "*** Enter answer in y/n format! ***\n";
		}
	}
	// If no answer after 10 times, exit
	return 0;
}


// New game
void playgame() {
	// Reading highscore from file
	ifstream Highsore("highscore.txt");
	if (Highsore)
	{
		Highsore >> highscore;
	}
	else
	{
		highscore = 0;
	}
	Highsore.close();

	// Creating field
	int **arr = new int*[N];
	for (int i = 0; i < N; i++)
	{
		arr[i] = new int[N];
	}

	do {
		// Launch game 
		match(arr);
	} while (exitFunction());

	// Clear memory
	for (int i = 0; i < N; i++)
		delete[] arr[i];
	delete[] arr;
}