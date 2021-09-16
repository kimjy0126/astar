#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>

#include "node.h"
#include "coord.h"

using namespace std;

extern Coord Node::start;
extern Coord Node::end;

void print_usage(const char* argv0)
{
    cout << "usage: " << argv0 << " <map file>\n";
}

void read_file(const char* filename, int& row, int& col, char**& map)
{
    ifstream fin(filename);
    stringstream ss;

    string tmp;
    getline(fin, tmp);
    ss.str(tmp);
    while (ss >> row >> col) {}

    map = new char*[row];
    for (int i = 0; i < row; i++) {
        map[i] = new char[col];

        getline(fin, tmp);
        ss.clear();
        ss.str(tmp);

        for (int j = 0; j < col; j++) {
            ss >> map[i][j];
        }
    }

    fin.close();
}

void print_map(char** map, int row, int col)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (map[i][j] == 'X') {
                cout << "\e[44m";
            } else if (map[i][j] == 'V') {
                cout << "\e[41m";
            } else if (map[i][j] == 'O') {
                cout << "\e[49m";
            } else if (map[i][j] == 'C') {
                cout << "\e[43m";
            } else if (map[i][j] == 'P') {
                cout << "\e[42m";
            }

            if (Coord(i, j) == Node::start) {
                cout << "S\e[0m";
            } else if (Coord(i, j) == Node::end) {
                cout << "E\e[0m";
            } else {
                cout << " \e[0m";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

int main(int argc, const char** argv)
{
    if (argc != 2) {
        print_usage(argv[0]);
        return 1;
    }

    int row, col;
    char** map;
    read_file(argv[1], row, col, map);

    Coord start, end;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (map[i][j] == 'S') {
                start = Coord(i, j);
            } else if (map[i][j] == 'E') {
                end = Coord(i, j);
            }
        }
    }

    Node::start = start;
    Node::end = end;
    priority_queue<Node*, vector<Node*>, compare_node> pq;
    Node* start_node = new Node(Node::start, 0);
    pq.push(start_node);

    Node* target_node;
    while (!pq.empty()) {
        target_node = pq.top();
        pq.pop();
        map[target_node->pos.row][target_node->pos.col] = 'V';

        cout << "target_node: (" << target_node->pos.row << ", " << target_node->pos.col << ")\t"
             << "f: " << target_node->f << ", g: " << target_node->g << ", h: " << target_node->h << "\n";
        print_map(map, row, col);

        if (target_node->pos == Node::end) {
            cout << "!!! FOUND PATH !!!" << "\n";
            break;
        }

        int dir_row[] = {0, 1, 0, -1};
        int dir_col[] = {1, 0, -1, 0};

        for (int i = 0; i < 4; i++) {
            int newpos_row = target_node->pos.row + dir_row[i];
            int newpos_col = target_node->pos.col + dir_col[i];

            if (newpos_row >= 0 && newpos_row < row && newpos_col >= 0 && newpos_col < col &&
                map[newpos_row][newpos_col] != 'X' &&
                map[newpos_row][newpos_col] != 'V' &&
                map[newpos_row][newpos_col] != 'C') {
                Node* new_node = new Node(Coord(newpos_row, newpos_col), target_node->g + 1, target_node);
                pq.push(new_node);
                map[newpos_row][newpos_col] = 'C';
            }
        }
    }

    while (target_node != NULL) {
        map[target_node->pos.row][target_node->pos.col] = 'P';
        target_node = target_node->prev_node;
    }

    print_map(map, row, col);

    return 0;
}
