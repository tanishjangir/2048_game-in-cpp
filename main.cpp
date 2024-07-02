#include "cppgraphics.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

void initialisingwithzero(vector<vector<int>> &grid)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            grid[i][j] = 0;
        }
    }
}

bool is_full(const vector<vector<int>> &grid)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {

            if (grid[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

// Function to map numbers to colors
void getColor(int number) {
    if (number == 2) cg::set_fill_color(238.0 / 255.0, 228.0 / 255.0, 218.0 / 255.0);
    else if (number == 4) cg::set_fill_color(237.0 / 255.0, 224.0 / 255.0, 200.0 / 255.0);
    else if (number == 8) cg::set_fill_color(242.0 / 255.0, 177.0 / 255.0, 121.0 / 255.0);
    else if (number == 16) cg::set_fill_color(245.0 / 255.0, 149.0 / 255.0, 99.0 / 255.0);
    else if (number == 32) cg::set_fill_color(246.0 / 255.0, 124.0 / 255.0, 95.0 / 255.0);
    else if (number == 64) cg::set_fill_color(246.0 / 255.0, 94.0 / 255.0, 59.0 / 255.0);
    else if (number == 128) cg::set_fill_color(237.0 / 255.0, 207.0 / 255.0, 114.0 / 255.0);
    else if (number == 256) cg::set_fill_color(237.0 / 255.0, 204.0 / 255.0, 97.0 / 255.0);
    else if (number == 512) cg::set_fill_color(237.0 / 255.0, 200.0 / 255.0, 80.0 / 255.0);
    else if (number == 1024) cg::set_fill_color(237.0 / 255.0, 197.0 / 255.0, 63.0 / 255.0);
    else if (number == 2048) cg::set_fill_color(237.0 / 255.0, 194.0 / 255.0, 46.0 / 255.0);
    else cg::set_fill_color(205.0 / 255.0, 193.0 / 255.0, 180.0 / 255.0); // Default color for empty cells
}

bool has_possible_moves(const vector<vector<int>> &grid) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (grid[i][j] == 0) return true;
            if (i < 3 && grid[i][j] == grid[i + 1][j]) return true;
            if (j < 3 && grid[i][j] == grid[i][j + 1]) return true;
        }
    }
    return false;
}

bool check_win(const vector<vector<int>> &grid) {
    for (auto row : grid) {
        for ( auto cell : row) {
            if (cell == 2048) {
                return true;
            }
        }
    }
    return false;
}

void draw(const vector<vector<int>> &grid, int score) {
    cg::clear();
    cg::set_background_color(cg::Brown);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            getColor(grid[i][j]);
            cg::rectangle(100 + i * 150, 100 + j * 150, 150, 150);

            if (grid[i][j] != 0) {
                cg::set_color(cg::Black);
                cg::text_centered(to_string(grid[i][j]), 175 + i * 150, 175 + j * 150, 50);
            }
        }
    }

    // Draw the score
    cg::set_color(cg::White);
    cg::text("Score: " + to_string(score), 600, 50, 30);

    if (check_win(grid)) {
        cg::set_color(cg::White);
        cg::text_centered("You Won!", 400, 400, 100);
        cg::wait_until_closed();
    }

    // Draw "Game Over" if the player loses
    if (!has_possible_moves(grid)) {
        cg::set_color(cg::White);
        cg::text_centered("Game Over!", 400, 400, 100);
        cg::wait_until_closed();
    }
}


void newnumber(vector<vector<int>> &grid)
{
    while (true)
    {
        int x = cg::random_int(3);
        int y = cg::random_int(3);
        if (grid[x][y] == 0)
        {
            grid[x][y] = 2;
            return;
        }
    }
}



void squash(vector<vector<int>> &grid, int key,int &score) {
    if (key == cg::KeyDown) {
        for (int i = 0; i < 4; i++) {
            for (int j = 3; j > 0; j--) {
                int src = j - 1;
                while (src >= 0 && grid[i][src] == 0) {
                    src--;
                }
                if (src < 0) {
                    break;
                }
                if (grid[i][src] == grid[i][j]) {
                    grid[i][j] = 2 * grid[i][j];
                    score += grid[i][j]; // Update the score
                    grid[i][src] = 0;
                } else if (grid[i][j] == 0) {
                    swap(grid[i][j], grid[i][src]);
                    ++j; // Corrected the increment
                }
            }
        }
    }
    else if (key == cg::KeyUp) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int src = j + 1;
                while (src < 4 && grid[i][src] == 0) {
                    src++;
                }
                if (src >= 4) { // Corrected the condition
                    break;
                }
                if (grid[i][src] == grid[i][j]) {
                    grid[i][j] = 2 * grid[i][j];
                    score += grid[i][j]; // Update the score
                    grid[i][src] = 0;
                } else if (grid[i][j] == 0) {
                    swap(grid[i][j], grid[i][src]);
                    --j; // Corrected the decrement
                }
            }
        }
    } 
    else if (key == cg::KeyRight) {
        for (int i = 0; i < 4; i++) {
            for (int j = 3; j > 0; j--) {
                int src = j - 1;
                while (src >= 0 && grid[src][i] == 0) {
                    src--;
                }
                if (src < 0) {
                    break;
                }
                if (grid[src][i] == grid[j][i]) {
                    grid[j][i] = 2 * grid[j][i];
                    score += grid[i][j]; // Update the score
                    grid[src][i] = 0;
                } else if (grid[j][i] == 0) {
                    swap(grid[j][i], grid[src][i]);
                    ++j; // Corrected the increment
                }
            }
        }
    } 
    else if (key == cg::KeyLeft) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int src = j + 1;
                while (src < 4 && grid[src][i] == 0) {
                    src++;
                }
                if (src >= 4) { // Corrected the condition
                    break;
                }
                if (grid[src][i] == grid[j][i]) {
                    grid[j][i] = 2 * grid[j][i];
                    score += grid[i][j]; // Update the score
                    grid[src][i] = 0;
                } else if (grid[j][i] == 0) {
                    swap(grid[j][i], grid[src][i]);
                    --j; // Corrected the decrement
                }
            }
        }
    }
}

int main()
{
    
    cg::create_window("2048 Game", 800, 800);

    vector<vector<int>> grid(4, vector<int>(4));
    initialisingwithzero(grid);

    int score = 0;
    newnumber(grid);
    newnumber(grid);

    while (cg::refresh()) {
        draw(grid, score);
        int key = cg::wait_until_keypressed();
        if (key == cg::WindowClosed) {
            break;
        }
        squash(grid, key, score);
        if (!is_full(grid)) {
            newnumber(grid);
        }
    }

    draw(grid, score);

    cg::wait_until_closed();
    return 0;
}
