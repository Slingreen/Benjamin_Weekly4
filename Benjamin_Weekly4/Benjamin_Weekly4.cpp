/**********************************************************************************************************
 *      Weekly assignment 4
 *
 *      Some tasks about different things
 *
 *
 *  @file    Benjamin_Weekly4.CPP
 *  @author  Benjamin A.E. Darici
 */

#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

//  Different functions used throughout the code
//  Task 1 and related functions
void Task1();
char letterUp(char c);

//  Task 2 and related functions
void Task2();
void movement(const char c, int(&pos)[2]);

//  Task 3 and related functions
void Task3();

//  Task 4 and related functions
void Task4();
std::vector<int> roll(const int r);
void hold(std::vector<int> &hold, std::vector<int> dice);
int sixes(std::vector<int> held);
bool pair(std::vector<int> held);

//  Other functions used throughout the code
int getNumber(const char* c, const int min, const int max);
void writeMenu();
char Read_Command(const char* c);

//  A struct used and a related function used in task 3
struct person {
    int phn = 0;
    std::string name = "";

    person();
};
person::person()
{
    std::cout << "Name:  ";
    std::getline(std::cin, name);
    phn = getNumber("Phone number", 1000000, 99999999);
}

//  A main code with a switch to let the user choose which task to use, a sort of main menu
int main()
{
    char command;

    writeMenu();
    command = Read_Command("Command");

    while (command != 'Q')
    {
        std::cin.ignore(32767, '\n');
        switch (command)
        {
        case '1': Task1(); break;
        case '2': Task2(); break;
        case '3': Task3(); break;
        case '4': Task4(); break;
        default: writeMenu(); break;
        }
        command = Read_Command("Command");
    }
}
/*   ________________________________
    /                                "-_
   /      .  |  .                       \
  /      : \ | / :                       \
 /        '-___-'                         \
/_________________________________________ \
     _______| |________________________--""-L
    /       F J                              \
   /       F   J                              L
  /      :'     ':                            F
 /        '-___-'                            /
/_________________________________________--"

 Wormhole 'bout to take you to new functions
*/

//  Turning lower case letters to upper case letters
void Task1()
{
    char letter{ ' ' };
    std::cout << "Write a lower case letter: ";
    std::cin >> letter;
    letter = letterUp(letter);
    std::cout << "Capital letter of input: " << letter << std::endl;
}

char letterUp(char c)
{
    if ('a' <= c && c <= 'z')
    {
        c -= ('a' - 'A');
    }
    return c;
}

//  A game board with some simple mechanics
void Task2()
{
    std::vector<std::vector<char>> grid(10, std::vector<char>(10, ' '));
    grid[5][6] = 'G';
    grid[8][1] = '/';
    grid[2][8] = '\\';

    bool exit = false;

    char key = ' ';
    int pos[2]{ 0,0 };

    while (exit == false)
    {
        for (int i = 0; i < grid.size(); i++) {
            std::cout << std::endl << "-------------------------------------------" << std::endl;
            for (int j = 0; j < grid.size(); j++) {
                if (i == pos[0] && j == pos[1]) {
                    std::cout << " | *";
                }
                else
                {
                    std::cout << " | " << grid[i][j];
                }
            }
            std::cout << " | ";
        }
        std::cout << std::endl << "-------------------------------------------" << std::endl;

        key = _getch();
        system("CLS");
        movement(key, pos);
        if (grid[pos[0]][pos[1]] == 'G')
        {
            exit = true;
        }

        if (grid[pos[0]][pos[1]] == '\\')
        {
            pos[0] = 8;
            pos[1] = 1;
        }
        else if (grid[pos[0]][pos[1]] == '/')
        {
            pos[0] = 2;
            pos[1] = 8;
        }
    }
    std::cout << "You reached the end!" << std::endl;
}

//  Movement options in task 2
void movement(const char c, int(&pos)[2])
{
    if (letterUp(c) == 'W')
    {
        if (pos[0] != 0) {
            pos[0] -= 1;
        }
    }
    else if (letterUp(c) == 'A')
    {
        if (pos[1] != 0) {
            pos[1] -= 1;
        }
    }
    else if (letterUp(c) == 'S')
    {
        if (pos[0] != 9) {
            pos[0] += 1;
        }
    }
    else if (letterUp(c) == 'D')
    {
        if (pos[1] != 9) {
            pos[1] += 1;
        }
    }
}

//  Struct array of people with phone numbers and names
void Task3()
{
    char command;
    std::vector<person*> people;

    std::cout << "The following Options are available: \n"
        << "\t N    Makes a new person\n"
        << "\t W    Writes all people\n"
        << "\t Q    Return to main menu\n";

    command = Read_Command("Choice");

    while (command != 'Q')
    {
        std::cin.ignore(32767, '\n');
        switch (command)
        {
        case 'N':
            if (people.size() < 10) {
                people.push_back(new person);
            }
            else
            {
                std::cout << "Error, there already exists 10 people" << std::endl;
            }
            break;

        case 'W':
            for (int i = 0; i < people.size(); i++)
            {
                std::cout << "Name:  " << people[i]->name << "\tPhone number:  " << people[i]->phn << std::endl;
            };
            std::cout << std::endl;
            break;

        default:
            std::cout << "The following commands are available: \n"
                << "\t N    Makes a new person\n"
                << "\t W    Writes all people\n"
                << "\t Q    Return to main menu\n";
            break;
        }
        command = Read_Command("Choice");
    }

}

//  Rolling dice
void Task4()
{
    char halt{ ' ' };
    std::vector<int> held;
    std::vector<int> dice;

    std::cout << std::endl;
    do
    {
        std::cout << std::endl << "roll" << std::endl;
        dice = roll(5 - held.size());
        hold(held, dice);
            
    } while (held.size() < 5);

    for (int i{ 0 }; i < held.size(); i++) {
        std::cout << held[i] << "\t";
    }

    std::cout
        << "There are "
        << sixes(held)
        << " sixes rolled, and there is "
        << (pair(held) ? "a" : "no")
        << " pair."
        << std::endl;
}

//  Function that rolls 5 die for task 4
std::vector<int> roll(const int r) {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock
    std::vector<int> roll;
    for (int i{ 0 }; i < r; i++) {
        roll.push_back(std::rand() % 6 + 1);
    }
    return roll;
}

//  Function that holds dice for task 4
void hold(std::vector<int>& hold, std::vector<int> dice)
{
    int n = 0;
    char input[200] = "";
    bool wrong = false;
    do
    {
        for (int j = 0; j < dice.size(); j++)
        {
            std::cout << dice[j] << " ";
        }
        std::cout << std::endl << "Dice to hold (H to halt): ";
        do {
            wrong = false;
            std::cout << " (" << 1 << " - " << dice.size() << "):  ";
            std::cin.getline(input, 200);
            if (letterUp(input[0]) == 'H') {
                return;
            }
            n = atoi(input);
            if (n == 0 && input[0] != '0')
            {
                wrong = true;   std::cout << "\nNot a number\n\n";
            }
        } while (wrong || n < 0 || n > dice.size());
        hold.push_back(dice[n - 1]);
        dice[n - 1] = dice[dice.size() - 1];
        dice.pop_back();
        std::cout << std::endl;
    } while (dice.size() > 0);
}

//  Function that counts sixes for task 4
int sixes(std::vector<int> held) 
{
    int s{ 0 };
    for (int i = 0; i < held.size(); i++)
    {
        if (held[i] == 6) 
        {
            s++;
        }
    }
    return s;
}

//  Function that checks for a pair among the die for task 4
bool pair(std::vector<int> held) 
{
    for (int i = 0; i < held.size(); i++)
    {
        for (int j = 0; j < held.size(); j++)
        {
            if (held[i]==held[j])
            {
                return true;
            }
        }
    }
    return false;
}

//  A function that returns numbers within a min and max value
int getNumber(const char* c, const int min, const int max) {
    char input[200] = "";
    int  number = 0;
    bool wrong = false;

    do {
        wrong = false;
        std::cout << c << " (" << min << " - " << max << "):  ";
        std::cin.getline(input, 200);
        number = atoi(input);
        if (number == 0 && input[0] != '0')
        {
            wrong = true;   std::cout << "\nNot a number\n\n";
        }
    } while (wrong || number < min || number > max);

    return number;
}

// A tiny function just to read input commands
char Read_Command(const char* c)
{
    char command;
    std::cout << c << ":  ";
    std::cin >> command;
    return(toupper(command));
}

// A tiny function to write out the choices the switch provides in the main function
void writeMenu()
{
    std::cout << "The following commands are available: \n"
        << "\t 1    Runs task 1\n"
        << "\t 2    Runs task 2\n"
        << "\t 3    Runs task 3\n"
        << "\t 4    Runs task 4\n"
        << "\t Q    Quits program\n";
}