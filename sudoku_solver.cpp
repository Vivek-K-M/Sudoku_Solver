#include<bits/stdc++.h>
#define N 9
using namespace std;


class sudoku
{
	int grid[N][N];

public:
	void input();
	bool row_check(int,int);
	bool column_check(int,int);
	bool box_check(int,int,int);
	void print_sudoku();
	bool empty_place(int&,int&);
	bool is_valid_place(int,int,int);
	bool sudoku_solver();
};

/*

SAMPE INPUT AND OUTPUT:

INPUT ->

0 5 0 0 8 3 0 1 7 
0 0 0 1 0 0 4 0 0
3 0 4 0 0 5 6 0 8
0 0 0 0 3 0 0 0 9
0 9 0 8 2 4 5 0 0
0 0 6 0 0 0 0 7 0
0 0 9 0 0 0 0 5 0
0 0 7 2 9 0 0 8 6
1 0 3 6 0 7 2 0 4

OUTPUT ->

6 5 2  | 4 8 3  | 9 1 7 
9 7 8  | 1 6 2  | 4 3 5 
3 1 4  | 9 7 5  | 6 2 8 
------------------------
8 2 5  | 7 3 6  | 1 4 9 
7 9 1  | 8 2 4  | 5 6 3 
4 3 6  | 5 1 9  | 8 7 2 
------------------------
2 6 9  | 3 4 8  | 7 5 1 
5 4 7  | 2 9 1  | 3 8 6 
1 8 3  | 6 5 7  | 2 9 4 

*/

void sudoku::print_sudoku()        //print the sudoku as answer.
{
    for (int i=0 ; i<N ; i++)
    {
        for (int j=0 ; j<N ; j++)
        {
            if(j==3 or j==6)
                cout << " | ";
            cout << grid[i][j] <<" ";
        }
        if(i==2 || i==5)
        {
            cout << endl;
            for(int k=0; k<N-1; k++)
                cout << "---";
        }
      cout << endl;
   }
}

void sudoku::input()
{
	cout<<" Enter the sudoku grid with empty places marked as 0 "<<endl;

	for(int i=0 ; i<N ; i++)
		for(int j=0 ; j<N ; j++)
			cin>>grid[i][j];
}

bool sudoku::row_check(int row, int val) {      //check if the number is present in the row.
    for(int j=0 ; j<N ; j++)
        if(grid[row][j]==val) return true;

    return false;
}

bool sudoku::column_check(int col, int val) {    //check if the number is present in the column.
    for(int i=0 ; i<N ; i++)
        if(grid[i][col]==val) return true;

    return false;
}

bool sudoku::box_check(int startRow, int startCol, int val) {     //check if the number is present in the 3x3 box or not.
    for(int i=0 ; i<3 ; i++)
        for(int j=0 ; j<3 ; j++)
            if(grid[i+startRow][j+startCol]==val) return true;

    return false;
}

bool sudoku::empty_place(int &i, int &j)        //find the empty location and update the row and column.
{
    for(i=0 ; i<N ; i++)
        for(j=0 ; j<N ; j++)
            if(grid[i][j]==0) return true;   //0 is an empty place.
    
    return false;
}

bool sudoku::is_valid_place(int row, int col, int val)    //perform all three checks to check if it is a valid cell to insert the number in this place.
{     
    return !row_check(row,val) and !column_check(col,val) and !box_check(row-row%3, col-col%3, val); 
}

bool sudoku::sudoku_solver()   //solve the sudoku using backtracking.
{
    int row,col;
    if(!empty_place(row,col)) return true;   //all places are filled so return true.
    for(int i=1 ; i<=9 ; i++)
    {
        if(is_valid_place(row,col,i))
        {
            grid[row][col] = i;          //insert the number.
            if(sudoku_solver())          //recursively check for other cells.
                return true;
            grid[row][col] = 0;          //return to previous state or undo the change for backtracking.
        }
    }
    return false;
}

int main()
{
	sudoku obj;        					//create a sudoku object.
	obj.input();                        //accept the sudoku grid from the user.
    if(obj.sudoku_solver())				//solve the sudoku.
    	obj.print_sudoku();

    else cout<<"No answer exists!!!";

    return 0;
}