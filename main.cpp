#include <ncurses.h>
#include <thread>
#include <chrono>
#include <vector>

void drawDiagonalLine(int x1, int y1, int x2, int y2);
bool showPerson = true;

int main() {
    initscr();
    noecho();
    curs_set(FALSE);
    
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    
    int x1 = maxX / 4;
    int y1 = 0;
    int x2 = maxX - maxX / 4;
    int y2 = 0;
    int x3 = maxX - maxX / 8;
    int y3 = maxY - maxY / 2;
    int x4 = maxX / 8;
    int y4 = maxY - maxY / 2;
    
    int px1 = maxX / 2;
    int py1 = maxY / 6;
    int px2 = maxX - maxX / 3;
    int py2 = maxY / 6;
    int px3 = maxX - maxX / 6;
    int py3 = maxY - maxY / 2;
    int px4 = maxX / 4;
    int py4 = maxY - maxY / 2;

    //Person
    std::vector<std::vector<char> > person;
    person.push_back(std::vector<char>());
    person[0].push_back(' ');
    person[0].push_back('O');
    person[0].push_back(' ');

    person.push_back(std::vector<char>());
    person[1].push_back('/');
    person[1].push_back('|');
    person[1].push_back('\\');
    
    person.push_back(std::vector<char>());
    person[2].push_back(' ');
    person[2].push_back('|');
    person[2].push_back(' ');

    person.push_back(std::vector<char>());
    person[3].push_back('/');
    person[3].push_back(' ');
    person[3].push_back('\\');
    
    
    //Tree
    std::vector<std::vector<char> > tree;
    tree.push_back(std::vector<char>());
    tree[0].push_back(' ');
    tree[0].push_back(' ');
    tree[0].push_back('_');
    tree[0].push_back(' ');
    tree[0].push_back(' ');

    tree.push_back(std::vector<char>());
    tree[1].push_back(' ');
    tree[1].push_back('/');
    tree[1].push_back('|');
    tree[1].push_back('\\');
    tree[1].push_back(' ');
    
    tree.push_back(std::vector<char>());
    tree[2].push_back(' ');
    tree[2].push_back('/');
    tree[2].push_back('|');
    tree[2].push_back('\\');
    tree[2].push_back(' ');

    tree.push_back(std::vector<char>());
    tree[3].push_back(' ');
    tree[3].push_back('/');
    tree[3].push_back('|');
    tree[3].push_back('\\');
    tree[3].push_back(' ');
    
    tree.push_back(std::vector<char>());
    tree[4].push_back('-');
    tree[4].push_back('-');
    tree[4].push_back('-');
    tree[4].push_back('-');
    tree[4].push_back('-');
    
    tree.push_back(std::vector<char>());
    tree[5].push_back(' ');
    tree[5].push_back('-');
    tree[5].push_back('-');
    tree[5].push_back('-');
    tree[5].push_back(' ');
    
    tree.push_back(std::vector<char>());
    tree[6].push_back(' ');
    tree[6].push_back('-');
    tree[6].push_back('-');
    tree[6].push_back('-');
    tree[6].push_back(' ');

    int personX = maxX / 2;
    int personY = maxY / 2;
    
    int treeX = maxX / 3;
    int treeY = maxY / 4;

    while (1) {
        clear();

        box(stdscr, ACS_VLINE, ACS_HLINE);
        
        mvaddch(py1, px1, ACS_ULCORNER);
        mvaddch(py2, px2, ACS_URCORNER);
        mvaddch(py3, px2, ACS_LRCORNER);
        mvaddch(py4, px1, ACS_LLCORNER);
        mvhline(py1, px1 + 1, ACS_HLINE, px2 - px1 - 1);
        mvhline(py3, px1 + 1, ACS_HLINE, px2 - px1 - 1);
        mvvline(py1 + 1, px1, ACS_VLINE, py4 - py1 - 1);
        mvvline(py2 + 1, px2, ACS_VLINE, py3 - py2 - 1);

        mvaddch(y1, x1, ACS_ULCORNER);
        mvaddch(y2, x2, ACS_URCORNER);
        mvaddch(y3, x2, ACS_LRCORNER);
        mvaddch(y4, x1, ACS_LLCORNER);
        mvhline(y1, x1 + 1, ACS_HLINE, x2 - x1 - 1);
        mvhline(y3, x1 + 1, ACS_HLINE, x2 - x1 - 1);
        mvvline(y1 + 1, x1, ACS_VLINE, y4 - y1 - 1);
        mvvline(y2 + 1, x2, ACS_VLINE, y3 - y2 - 1);
        
        double slope = static_cast<double>(y3 - y4) / (x2 - x1);
        
        drawDiagonalLine(x1, y4, -1, maxY);
        drawDiagonalLine(x2, y3, maxX + 1, maxY);
        
        for (int i = 0; i < tree.size(); i++) {
            for (int j = 0; j < tree[i].size(); j++) {
                mvaddch(treeY + i, treeX + j - 1, tree[i][j]);
            }
        }
        
        if (showPerson) {
            for (int i = 0; i < person.size(); i++) {
                for (int j = 0; j < person[i].size(); j++) {
                    mvaddch(personY + i, personX + j - 1, person[i][j]);
                }
            }
        }

        refresh();

        int userInput = getch();

        switch (userInput) {
            case 'd':
                personX++;
                break;
            case 'a':
                personX--;
                break;
            case 'w':
                if (y3 - 3 < personY)
                    personY--;
                else if (personX > px1 && personX < px2 && showPerson) {
                    showPerson = false;
                    personY--;
                }
                break;
            case 's':
                if (personY < maxY - 5){
                    if (y3 - 5 < personY){
                        showPerson = true;
                    }
                    personY++;
                }
                break;
            case 'q':
                endwin();
                return 0;
            default:
                break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}

void drawDiagonalLine(int x1, int y1, int x2, int y2) {
    char slash = '/';
    
    if (x2 > x1)
        slash = '\\';
    
    int dx = x2 - x1;
    int dy = y2 - y1;

    int sx = (dx > 0) ? 1 : -1;
    int sy = (dy > 0) ? 1 : -1;

    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;

    int err = dx - dy;

    int x = x1;
    int y = y1;

    while (1) {
        mvaddch(y, x, slash);
        
        if (x == x2 && y == y2) break;
        
        int e2 = 2 * err;
        
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}
