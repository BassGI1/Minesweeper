#include <iostream>
#include "geesespotter_lib.h"

//to test, type "g++ -o main geesespotter.cpp geesespotter_lib.cpp -std=c++11" into the terminal

char *createBoard ( std::size_t xdim, std::size_t ydim ){

    char *board {new char [xdim*ydim] };

    for (int x{0}; x < (xdim*ydim); ++x){

        board [x] = 0;

    }
    return board;
}

void hideBoard ( char *board, std::size_t xdim, std::size_t ydim ){

    for (int x{0}; x < (xdim*ydim); ++x){

        board [x] += 0x20;

    }

}

void cleanBoard ( char *board ){

    delete [] board;
    board = nullptr;

}

void printBoard ( char *board, std::size_t xdim, std::size_t ydim ){

    for (int y{0}; y < ydim; ++y){
        for (int x{0}; x < xdim; ++x){
            if (board [xdim*y + x] >> 5 == 1){
                if (board [xdim*y + x] >= 0x30){
                    std::cout<<" M";
                }
                else{
                    std::cout<<" *";
                }
            }
            else {
                std::cout<<" "<<int(board[xdim*y + x]);
            }
            if (x == xdim - 1){
                std::cout<<std::endl;
            }
        }
    }

}

int mark ( char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc ){

    int loc{yloc*xdim + xloc};

    if ((board [loc] >> 5) == 1){
        if (board [loc] < 0x30){
            board [loc] += 0x10;
            return 0;
        }
        else {
            board [loc] -= 0x10;
            return 0;
        }
    }
    return 2;
}

void computeNeighbors ( char *board, std::size_t xdim, std::size_t ydim ){

    for (int y{0}; y < ydim; ++y){
        for (int x{0}; x < xdim; ++x){
            if (board [xdim*y + x] == 9){
                if (y == 0){
                    if (x == 0){
                        if (board [1] != 9){
                            ++board [1];
                        }
                        if (board [xdim != 9]){
                            ++board [xdim];
                        }
                        if (board [xdim + 1] != 9){
                            ++board [xdim + 1];
                        }
                    }
                    else if (x == xdim - 1){
                        if (board [xdim - 2] != 9){
                            ++board [xdim - 2];
                        }
                        if (board [2*xdim - 2] != 9){
                            ++board [2*xdim - 2];
                        }
                        if (board [2*xdim - 1] != 9){
                            ++board [2*xdim - 1];
                        }
                    }
                    else {
                        if (board [x - 1] != 9){
                            ++board [x - 1];
                        }
                        if (board [x + 1] != 9){
                            ++board [x + 1];
                        }
                        for (int p{0}; p < 3; ++p){
                            if (board [x + xdim - 1 + p] != 9){
                                ++board [x + xdim - 1 + p];
                            }    
                        }
                    }
                }
                else if (y == ydim - 1){
                    if (x == 0){
                        if (board [y*xdim + 1] != 9){
                            ++board [y*xdim + 1];
                        }
                        if (board [(y - 1)*xdim] != 9){
                            ++board [(y - 1)*xdim];
                        }
                        if (board [(y - 1)*xdim + 1] != 9){
                            ++board [(y - 1)*xdim + 1];
                        }
                    }
                    else if (x == xdim - 1){
                        if (board [y*xdim + x - 1] != 9){
                            ++board [y*xdim + x - 1];
                        }
                        if (board [(y - 1)*xdim + x] != 9){
                            ++board [(y - 1)*xdim + x];
                        }
                        if (board [(y - 1)*xdim + x - 1] != 9){
                            ++board [(y - 1)*xdim + x - 1];
                        }
                    }
                    else {
                        if (board [y*xdim + x - 1] != 9){
                            ++board [y*xdim + x - 1];
                        }
                        if (board [y*xdim + x + 1] != 9){
                            ++board [y*xdim + x + 1];
                        }
                        for (int p{0}; p < 3; ++p){
                            if (board [(y - 1)*xdim + x - 1 + p] != 9){
                                ++board [(y - 1)*xdim + x - 1 + p];
                            }
                        }
                    }
                }
                else if ((x == 0) && (y != 0) && (y != ydim - 1)){
                    if (board [(y - 1)*xdim] != 9){
                        ++board [(y - 1)*xdim];
                    }
                    if (board [(y - 1)*xdim + 1] != 9){
                        ++board [(y - 1)*xdim + 1];
                    }
                    if (board [y*xdim + 1] != 9){
                        ++board [y*xdim + 1];
                    }
                    if (board [(y + 1)*xdim] != 9){
                        ++board [(y + 1)*xdim];
                    }
                    if (board [(y + 1)*xdim + 1] != 9){
                        ++board [(y + 1)*xdim + 1];
                    }
                }
                else if ((x == xdim - 1) && (y != 0) && (y != ydim - 1)){
                    if (board [(y - 1)*xdim + x - 1] != 9){
                        ++board [(y - 1)*xdim + x - 1];
                    }
                    if (board [(y - 1)*xdim + x] != 9){
                        ++board [(y - 1)*xdim + x];
                    }
                    if (board [y*xdim + x - 1] != 9){
                        ++board [y*xdim + x - 1];
                    }
                    if (board [(y + 1)*xdim + x - 1] != 9){
                        ++board [(y + 1)*xdim + x - 1];
                    }
                    if (board [(y + 1)*xdim + x] != 9){
                        ++board [(y + 1)*xdim + x];
                    }
                }
                else {
                    for (int p{0}; p < 3; ++p){
                        if (board [(y - 1)*xdim + x - 1 + p] != 9){
                            ++board [(y - 1)*xdim + x - 1 + p];
                        }
                    }
                    if (board [y*xdim + x - 1] != 9){
                        ++board [y*xdim + x - 1];
                    }
                    if (board [y*xdim + x + 1] != 9){
                        ++board [y*xdim + x + 1];
                    }
                    for (int p{0}; p < 3; ++p){
                        if (board [(y + 1)*xdim + x - 1 + p] != 9){
                            ++board [(y + 1)*xdim + x - 1 + p];
                        }
                    }
                }
            }
        }
    }

}

int reveal ( char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc ){

    int loc{xdim*yloc + xloc};

    if (board [loc] >= 0x30){
        return 1;
    }
    else if (board [loc] < 0x20){
        return 2;
    }
    else if (board [loc] == 0x29){
        board [loc] -= 0x20;
        return 9;
    }

    else if ((board [loc] == 0x20)){
        board [loc] = 0;
        if (yloc == 0){
            if (xloc == 0){
                if ((board [1] < 0x29) && (board [1] >= 0x20)){
                    board [1] -= 0x20;
                }
                if ((board [xdim] < 0x29) && (board [xdim] >= 0x20)){
                    board [xdim] -= 0x20;
                }
                if ((board [xdim + 1] < 0x29) && (board [xdim + 1] >= 0x20)){
                    board [xdim + 1] -= 0x20;
                }
            }
            else if (xloc == xdim - 1){
                if ((board [xloc - 1] < 0x29) && (board [xloc - 1] >= 0x20)){
                    board [xloc - 1] -= 0x20;
                }
                if ((board [xloc + xdim - 1] < 0x29) && (board [xloc + xdim - 1] >= 0x20)){
                    board [xloc + xdim - 1] -= 0x20;
                }
                if ((board [xloc + xdim] < 0x29) && (board [xloc + xdim] >= 0x20)){
                    board [xloc + xdim] -= 0x20;
                }
            }
            else {
                if ((board [xloc - 1] < 0x29) && (board [xloc - 1] >= 0x20)){
                    board [xloc - 1] -= 0x20;
                }
                if ((board [xloc + 1] < 0x29) && (board [xloc + 1] >= 0x20)){
                    board [xloc + 1] -= 0x20;
                }
                for (int p{0}; p < 3; ++p){
                    if ((board [xloc + xdim - 1 + p] < 0x29) && (board [xloc + xdim - 1 + p] >= 0x20)){
                        board [xloc + xdim - 1 + p] -= 0x20;
                    }
                }
            }
        }
        else if (yloc == ydim - 1){
            if (xloc == 0){
                if ((board [(yloc - 1)*xdim] < 0x29) && (board [(yloc - 1)*xdim] >= 0x20)){
                    board [(yloc - 1)*xdim] -= 0x20;
                }
                if ((board [(yloc - 1)*xdim + 1] < 0x29) && (board [(yloc - 1)*xdim + 1] >= 0x20)){
                    board [(yloc - 1)*xdim + 1] -= 0x20;
                }
                if ((board [yloc*xdim + 1] < 0x29) && (board [yloc*xdim + 1] >= 0x20)){
                    board [yloc*xdim + 1] -= 0x20;
                }
            }
            else if (xloc == xdim - 1){
                if ((board [(yloc - 1)*xdim + xloc] < 0x29) && (board [(yloc - 1)*xdim + xloc] >= 0x20)){
                    board [(yloc - 1)*xdim + xloc] -= 0x20;
                }
                if ((board [(yloc - 1)*xdim + xloc - 1] < 0x29) && (board [(yloc - 1)*xdim + xloc - 1] >= 0x20)){
                    board [(yloc - 1)*xdim + xloc - 1] -= 0x20;
                }
                if ((board [yloc*xdim + xloc - 1] < 0x29) && (board [yloc*xdim + xloc - 1] >= 0x20)){
                    board [yloc*xdim + xloc - 1] -= 0x20;
                }
            }
            else {
                if ((board [yloc*xdim + xloc - 1] < 0x29) && (board [yloc*xdim + xloc - 1] >= 0x20)){
                    board [yloc*xdim + xloc - 1] -= 0x20;
                }
                if ((board [yloc*xdim + xloc + 1] < 0x29) && (board [yloc*xdim + xloc + 1] >= 0x20)){
                    board [yloc*xdim + xloc + 1] -= 0x20;
                }
                for (int p{0}; p < 3; ++p){
                    if ((board [(yloc - 1)*xdim + xloc - 1 + p] < 0x29) && (board [(yloc - 1)*xdim + xloc - 1 + p] >= 0x20)){
                    board [(yloc - 1)*xdim + xloc - 1 + p] -= 0x20;
                    }
                }
            }
        }
        else if ((xloc == 0) && (yloc != 0) && (yloc != ydim - 1)){
            if ((board [(yloc - 1)*xdim] < 0x29) && (board [(yloc - 1)*xdim] >= 0x20)){
                board [(yloc - 1)*xdim] -= 0x20;
            }
            if ((board [(yloc - 1)*xdim + 1] < 0x29) && (board [(yloc - 1)*xdim + 1] >= 0x20)){
                board [(yloc - 1)*xdim + 1] -= 0x20;
            }
            if ((board [yloc*xdim + 1] < 0x29) && (board [yloc*xdim + 1] >= 0x20)){
                board [yloc*xdim + 1] -= 0x20;
            }
            if ((board [(yloc + 1)*xdim] < 0x29) && (board [(yloc + 1)*xdim] >= 0x20)){
                board [(yloc + 1)*xdim] -= 0x20;
            }
            if ((board [(yloc + 1)*xdim + 1] < 0x29) && (board [(yloc + 1)*xdim + 1] >= 0x20)){
                board [(yloc + 1)*xdim + 1] -= 0x20;
            }
        }
        else if ((xloc == xdim - 1) && (yloc != 0) && (yloc != ydim - 1)){
            if ((board [(yloc - 1)*xdim + xloc] < 0x29) && (board [(yloc - 1)*xdim + xloc] >= 0x20)){
                board [(yloc - 1)*xdim + xloc] -= 0x20;
            }
            if ((board [(yloc - 1)*xdim + xloc - 1] < 0x29) && (board [(yloc - 1)*xdim + xloc - 1] >= 0x20)){
                board [(yloc - 1)*xdim + xloc - 1] -= 0x20;
            }
            if ((board [yloc*xdim + xloc - 1] < 0x29) && (board [yloc*xdim + xloc - 1] >= 0x20)){
                board [yloc*xdim + xloc - 1] -= 0x20;
            }
            if ((board [(yloc + 1)*xdim + xloc - 1] < 0x29) && (board [(yloc + 1)*xdim + xloc - 1] >= 0x20)){
                board [(yloc + 1)*xdim + xloc - 1] -= 0x20;
            }
            if ((board [(yloc + 1)*xdim + xloc] < 0x29) && (board [(yloc + 1)*xdim + xloc] >= 0x20)){
                board [(yloc + 1)*xdim + xloc] -= 0x20;
            }
        }
        else {
            for (int p{0}; p < 3; ++p){
                if ((board [(yloc - 1)*xdim + xloc - 1 + p] < 0x29) && (board [(yloc - 1)*xdim + xloc - 1 + p] >= 0x20)){
                    board [(yloc - 1)*xdim + xloc - 1 + p] -= 0x20;
                }
                if ((board [(yloc + 1)*xdim + xloc - 1 + p] < 0x29) && (board [(yloc + 1)*xdim + xloc - 1 + p] >= 0x20)){
                    board [(yloc + 1)*xdim + xloc - 1 + p] -= 0x20;
                }
            }
            if ((board [yloc*xdim + xloc - 1] < 0x29) && (board [yloc*xdim + xloc - 1] >= 0x20)){
                board [yloc*xdim + xloc - 1] -= 0x20;
            }
            if ((board [yloc*xdim + xloc + 1] < 0x29) && (board [yloc*xdim + xloc + 1] >= 0x20)){
                board [yloc*xdim + xloc + 1] -= 0x20;
            }
        }
        return 0;
    }
    else {
        board [loc] -= 0x20;
        return 0;
    }

}

bool isGameWon ( char *board, std::size_t xdim, std::size_t ydim ){

    for (int x{0}; x < xdim*ydim; ++x){

        if ((board [x] > 0x8) && (board [x] <= 0x38) && (board [x] != 0x29)){
            return false;
        }

    }
    return true;
}