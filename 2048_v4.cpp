#include <iostream>
#include <stdlib.h>     
#include <stdio.h>     
//#include <ncurses.h>     
using namespace std;

class game2048 {
    private:
    int size;
    int *matrix;
    int score;
    int row, column;
    public:
    void ReDraw2() {
        int column2;
        
        cout << "SCORE:" << score << endl; 
        //
        cout << "+-" ;
        for (column2=0;column2<size;column2++)  cout << "--+" ;
        cout << endl ;
        //
        for (column=0;column<size;column++) {
            cout << "+-" ;
            for (column2=0;column2<size;column2++)  cout << "---+" ;
            cout << endl ;
        //

            cout << '|' ;
            for (row=0;row<size;row++) {
                cout.width(3);
                if (matrix[row*size+column]!= 0)
                     cout << matrix[row*size+column];
                else cout << "   ";
                //cout << "|";
            }
            cout << " |" << endl ;
        }    
        //
        cout << "+-" ;
        for (column=0;column<size;column++)  cout << "---+" ;
        cout << endl ;        //
        cout << "press \'A\' for left shift, \'D\' for rigth shift," ; 
        cout << " \'W\' for up shift, \'X\' for down shift" << endl; 
        
    };
        void ReDraw() {
        //ищем максимальное значение, что бы узнать его ширину в знаках
        int maximum=0;            
        int width; 
        for (column=0;column<size;column++) 
            for (row=0;row<size;row++) 
                if (matrix[row*size+column] > maximum) maximum = matrix[row*size+column];
        //   
        for (width =0; maximum>0; width++) maximum = maximum / 10;
        //
        width++;
        //
        cout << "SCORE:" << score << " Width:" << width << endl; 
        for (column=0;column<size;column++) {
            cout << '|' ;
            for (row=0;row<size;row++) {
                cout.width(width);
                cout << matrix[row*size+column];
            }
            cout << " |" << endl ;
        }    
        
       cout << "press \'A\' for left shift, \'D\' for rigth shift," ; 
       cout << " \'W\' for up shift, \'X\' for down shift" << endl; 
        
    };
    

    int Next(void) {
        int fr=0;
        int random;
        
        for (column=0;column<size;column++) {
            for (row=0;row<size;row++) {
                if (matrix[row+column*size]==0) fr++;
            }
        };    
                
        if (fr<1) return 1;
        
        int ret=0;

        while (ret==0) {
            random = rand() % (size*size);
            if (matrix[random]==0) {
                matrix[random] = 2;
                ret=1;
            }    
        }
        return 0;
    } ;   

    void Left() {
        cout  << "Left shift" << endl;
        for (row=0;row<size;row++) {
            //first squize
            for (column=1;column<size;column++) {
                int position=column;
                while (position>0) { 
                    if (matrix[row + size*(position-1)]==0) { //Если число слева равно 0 то сдвигаем влево
                        matrix[row + size*(position-1)] = matrix[row + size*position];
                        matrix[row + size*position]=0;
                        position--;
                    } else break;
                }//while    
            }    
            //union tile
            for (column=1;column<size;column++) {
                if (matrix[row + size*(column-1)] == matrix[row + size*column]) { //если равны, но складываем
                    matrix[row + size*(column-1)] =  matrix[row + size*column] * 2;
                    matrix[row + size*column]=0;
                    score = score + matrix[row + size*(column-1)];
                    
                }    
            }
            //final squize
            for (column=1;column<size;column++) {
                int position=column;
                while (position>0) { 
                    if (matrix[row + size*(position-1)]==0) { //Если число слева равно 0 то сдвигаем влево
                        matrix[row + size*(position-1)] = matrix[row + size*position];
                        matrix[row + size*position]=0;
                        position--;
                    } else break;
                }//while    
            }    
            
        }//for row
    }//left

    
    void Rigth() {
        cout  << "Rigth shift" << endl;
        for (row=0;row<size;row++) {
            //first squize
            for (column=size-2;column>=0;column--) {
                int position=column;
                while (position<(size-1)) { 
                    if (matrix[row + size*(position+1)]==0) { //Если число справа равно 0 то сдвигаем вправо
                        matrix[row + size*(position+1)] = matrix[row + size*position];
                        matrix[row + size*position]=0;
                        position++;
                    } else break;
                }//while    
            }    
            //union tile
            for (column=size-2;column>=0;column--) {
                if (matrix[row + size*(column+1)] == matrix[row + size*column]) { //если равны, но складываем
                    matrix[row + size*(column+1)] =  matrix[row + size*column] * 2;
                    matrix[row + size*column]=0;
                    score = score + matrix[row + size*(column+1)];
                    
                }    
            }
            //final squize
            for (column=size-2;column>=0;column--) {
                int position=column;
                while (position<(size-1)) { 
                    if (matrix[row + size*(position+1)]==0) { //Если число справа равно 0 то сдвигаем вправо
                        matrix[row + size*(position+1)] = matrix[row + size*position];
                        matrix[row + size*position]=0;
                        position++;
                    } else break;
                }//while    
            }               

        }//for row
    }//rigth


    void Up() {
        cout  << "Up shift"<< endl;
        for (column=0;column<size;column++) {
            //first squize
            for (row=1;row<size;row++) {
                int position=row;
                while (position>0) { 
                    if (matrix[column*size + (position-1)]==0) { //Если число слева равно 0 то сдвигаем влево
                        matrix[column*size + (position-1)] = matrix[column*size + position];
                        matrix[column*size +  position]=0;
                        position--;
                    } else break;
                }//while    
            }    
            //union tile
            for (row=1;row<size;row++) {
                if (matrix[row - 1 + size*column] == matrix[row + size*column]) { //если равны, но складываем
                    matrix[row - 1 + size*column] =  matrix[row + size*column] * 2;
                    matrix[row + size*column]=0;
                    score = score + matrix[row-1 + size*column];
                }    
            }
            //final squize
            for (row=1;row<size;row++) {
                int position=row;
                while (position>0) { 
                    if (matrix[column*size + (position-1)]==0) { //Если число слева равно 0 то сдвигаем влево
                        matrix[column*size + (position-1)] = matrix[column*size + position];
                        matrix[column*size +  position]=0;
                        position--;
                    } else break;
                }//while    
            }    

            
        }//for column
    }//up
    
    void Down() {
        cout  << "Down " << endl;
        for (column=0;column<size;column++) {
            //first squize
            for (row=size-2;row>=0;row--) {
                int position=row;
                while (position<(size-1)) { 
                    //cout<< "Col=" << column << " Row=" << row << " Pos=" << position << endl;
                    if (matrix[column*size + (position+1)]==0) { //Если число слева равно 0 то сдвигаем влево
                        matrix[column*size + (position+1)] = matrix[column*size + position];
                        matrix[column*size +  position]=0;
                        position++;
                    } else break;
                }//while    
            }    
            //union tile
            for (row=size-2;row>=0;row--) {
                if (matrix[row + 1 + size*column] == matrix[row + size*column]) { //если равны, но складываем
                    matrix[row + 1 + size*column] =  matrix[row + size*column] * 2;
                    matrix[row + size*column]=0;
                    score = score + matrix[row+ 1 + size*column];
                }    
            }
            //final squize
            for (row=size-2;row>=0;row--) {
                int position=row;
                while (position<(size-1)) { 
                    //cout<< "Col=" << column << " Row=" << row << " Pos=" << position << endl;
                    if (matrix[column*size + (position+1)]==0) { //Если число слева равно 0 то сдвигаем влево
                        matrix[column*size + (position+1)] = matrix[column*size + position];
                        matrix[column*size +  position]=0;
                        position++;
                    } else break;
                }//while    
            }    
        }//for column
    } //down
    
    game2048 (int len) {
        size = len;
        score = 0;
        matrix = new int [size*size];
        for (column=0;column<size;column++) {
            for (row=0;row<size;row++) {
                matrix[row+column*len]=0;
            }
        };    
        
    };
    
};

int main()
{  int i;
   cout << "2048 (c) 2015" << endl; 
   game2048 game(4);
   char key;
   int gameover=0;
    game.Next();
    game.Next();
    game.ReDraw();
   while (gameover==0) {
        cin >> key;
        //key=getch();
        switch (key) {
            case 'A'|'a':   
                            game.Left();
                            gameover=game.Next();
                            break;
            case 'D'|'d':
                            game.Rigth();
                            gameover=game.Next();
                            break;
            case 'W'|'w':
                            game.Up();
                            gameover=game.Next();
                            break;
            case 'X'|'x':
                            game.Down();
                            gameover=game.Next();
                            break;
            case 'Q'|'q':
                           cout << endl << "BYE-BYE!!!" << endl; 
                           return 0;

        }
        game.ReDraw();
   }        
   cout << endl << "GAME OVER!!!" << endl; 
   return -1;
}

