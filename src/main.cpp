#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <limits>

struct Position
{
    int row;
    int col;
};

struct GameState
{
    std::vector<std::string> map;
    Position playerPosition;
    int score = 0;
    bool running = true;
    bool won = false;
};

std::vector<std::string> createStartingMap()
{
    return {
        "##########",
        "#P   C   #",
        "#  ##    #",
        "#    C   #",
        "#   ###  #",
        "#     G  #",
        "##########"
    };
}

void displayGame(const GameState& game)
{
    std::cout << std::endl;
    std::cout << "========== Simple 2D Grid Game ==========" << std::endl;
    std::cout << "Score: " << game.score << std::endl;
    std::cout << std::endl;

    for (const std::string& row : game.map)
    {
        std::cout << row << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Move using W, A, S, D. Press Q to quit." << std::endl;
}

char getPlayerMove()
{
    char move;

    std::cout << "Enter move: ";
    std::cin >> move;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    move = static_cast<char>(std::toupper(static_cast<unsigned char>(move)));

    return move;
}

bool isValidMoveCommand(char move)
{
    return move == 'W' || move == 'A' || move == 'S' || move == 'D' || move == 'Q';
}

Position calculateNewPosition(Position currentPosition, char move)
{
    Position newPosition = currentPosition;

    if (move == 'W')
    {
        newPosition.row--;
    }
    else if (move == 'S')
    {
        newPosition.row++;
    }
    else if (move == 'A')
    {
        newPosition.col--;
    }
    else if (move == 'D')
    {
        newPosition.col++;
    }

    return newPosition;
}

void processMove(GameState& game, char move)
{
    if (move == 'Q')
    {
        game.running = false;
        return;
    }

    if (!isValidMoveCommand(move))
    {
        std::cout << "Invalid command. Use W, A, S, D, or Q." << std::endl;
        return;
    }

    Position newPosition = calculateNewPosition(game.playerPosition, move);

    char targetCell = game.map[newPosition.row][newPosition.col];

    if (targetCell == '#')
    {
        std::cout << "You cannot move through walls." << std::endl;
        return;
    }

    if (targetCell == 'C')
    {
        game.score += 10;
        std::cout << "You collected a coin! Score +10." << std::endl;
    }

    if (targetCell == 'G')
    {
        game.won = true;
        game.running = false;
    }

    game.map[game.playerPosition.row][game.playerPosition.col] = ' ';
    game.playerPosition = newPosition;
    game.map[game.playerPosition.row][game.playerPosition.col] = 'P';
}

GameState createGame()
{
    GameState game;

    game.map = createStartingMap();
    game.playerPosition = { 1, 1 };
    game.score = 0;
    game.running = true;
    game.won = false;

    return game;
}

void runGame()
{
    GameState game = createGame();

    while (game.running)
    {
        displayGame(game);

        char move = getPlayerMove();

        processMove(game, move);
    }

    displayGame(game);

    if (game.won)
    {
        std::cout << "Congratulations! You reached the goal." << std::endl;
        std::cout << "Final score: " << game.score << std::endl;
    }
    else
    {
        std::cout << "Game ended." << std::endl;
        std::cout << "Final score: " << game.score << std::endl;
    }
}

int main()
{
    runGame();

    return 0;
}
