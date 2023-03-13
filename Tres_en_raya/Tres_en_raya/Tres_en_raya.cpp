#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <ctime>
#include <thread>
// #include <pthread.h>
#include <random>

class out_of_bounderies
{
public:
    const char* what() const throw()
    {
        return "Out of bounderies! Try again";
    }
};

int empty_spaces = 9;
char matrix[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '} };

void print_matrix(void);
void welcome_message(void);
int get_player_row(void);
int get_player_column(void);
void player_input(void);
char check();
void ai_input(void);

int main(void)
{
    welcome_message();
    print_matrix();
    player_input();

    return 0;
}

int get_player_row(void)
{
    int player_row;
    while (true)
    {
        try
        {
            std::cout << "Enter the row: ";
            std::cin >> player_row;
            if (std::cin.fail())
            {
                throw std::runtime_error("Invalid Input");
            }
            if (player_row < 0 || player_row > 2)
            {
                throw out_of_bounderies();
            }
            break;
        }
        catch (const std::exception& runtime_error)
        {
            std::cerr << "Error: " << runtime_error.what() << std::endl
                << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                '\n');
        }
        catch (const out_of_bounderies& error)
        {
            std::cerr << "Error: " << error.what() << std::endl
                << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                '\n');
        }
    }
    return player_row;
}

int get_player_column()
{
    int player_column;
    while (true)
    {
        try
        {
            std::cout << "Enter the column: ";
            std::cin >> player_column;
            if (std::cin.fail())
            {
                throw std::runtime_error("Invalid Input");
            }
            if (player_column < 0 || player_column > 2)
            {
                throw out_of_bounderies();
            }
            break;
        }
        catch (const std::exception& runtime_error)
        {
            std::cerr << "Error: " << runtime_error.what() << std::endl
                << std::endl;
            std::cin.clear();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                '\n');
        }
        catch (const out_of_bounderies& error)
        {
            std::cerr << "Error: " << error.what() << std::endl
                << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                '\n');
        }
    }
    return player_column;
}

char check()
{
    for (int i = 0; i < 3; i++)
    {
        if (matrix[i][0] == 'X' && matrix[i][1] == 'X' && matrix[i][2] == 'X')
            return 'X';
        if (matrix[i][0] == 'O' && matrix[i][1] == 'O' && matrix[i][2] == 'O')
            return 'O';
    }

    // check columns
    for (int j = 0; j < 3; j++)
    {
        if (matrix[0][j] == 'X' && matrix[1][j] == 'X' && matrix[2][j] == 'X')
            return 'X';
        if (matrix[0][j] == 'O' && matrix[1][j] == 'O' && matrix[2][j] == 'O')
            return 'O';
    }

    // check diagonals
    if (matrix[0][0] == 'X' && matrix[1][1] == 'X' && matrix[2][2] == 'X')
        return 'X';
    if (matrix[0][0] == 'O' && matrix[1][1] == 'O' && matrix[2][2] == 'O')
        return 'O';

    if (matrix[0][2] == 'X' && matrix[1][1] == 'X' && matrix[2][0] == 'X')
        return 'X';
    if (matrix[0][2] == 'O' && matrix[1][1] == 'O' && matrix[2][0] == 'O')
        return 'O';

    return ' ';
}

void ai_input()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2);
    while (true)
    {
        int ai_row = dis(gen);
        int ai_column = dis(gen);
        if (matrix[ai_row][ai_column] == ' ')
        {
            matrix[ai_row][ai_column] = 'O';
            empty_spaces--;
            break;
        }
    }
}

void player_input()
{

    while (empty_spaces > 0)
    {
        int player_row = get_player_row();
        int player_column = get_player_column();
        if (matrix[player_row][player_column] == 'X' || matrix[player_row][player_column] == 'O')
        {
            std::cout << "Place already taken!\n\n";
            player_input();
        }
        else
        {
            matrix[player_row][player_column] = 'X';
            empty_spaces--;
        }
        check();
        if (empty_spaces > 0)
        {
            ai_input();
        }
        check();
        print_matrix();
        if (check() == 'X')
        {
            std::cout << "The player wins!\n\n";
            break;
        }
        if (check() == 'O')
        {
            std::cout << "The AI wins!\n\n";
            break;
        }
        std::cout << empty_spaces << std::endl;
    }
}

void print_matrix(void)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            std::cout << " " << matrix[i][j];
            if (j != 2)
                std::cout << " |";
        }
        if (i != 2)
        {
            std::cout << std::endl;
            std::cout << "---|---|---";
            std::cout << std::endl;
        }
    }
    std::cout << std::endl
        << std::endl;
}

void welcome_message(void)
{
    std::string message =
        "Welcome to the Tic-Tac-Toe game!\nYour goal is to put 3 consecutive X to win! Good Luck.\n\n";
    for (char c : message)
    {
        std::cout << c;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}
