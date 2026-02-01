#include <iostream>
using namespace std;

// ---------- Original Board ---------- //
int original[9][9] = {
    {5,3,0,0,7,0,0,0,0},
    {6,0,0,1,9,5,0,0,0},
    {0,9,8,0,0,0,0,6,0},
    {8,0,0,0,6,0,0,0,3},
    {4,0,0,8,0,3,0,0,1},
    {7,0,0,0,2,0,0,0,6},
    {0,6,0,0,0,0,2,8,0},
    {0,0,0,4,1,9,0,0,5},
    {0,0,0,0,8,0,0,7,9}
};

int board[9][9];
bool fixedCell[9][9];

// ---------- Stack for Undo ---------- //
struct Move { int r,c,prev; Move* next; };
Move* top = NULL;
int moves=0, mistakes=0;

// ---------- Stack Operations ---------- //
void push(int r,int c,int prev){
    top=new Move{r,c,prev,top};
    }
bool pop(int &r,int &c,int &prev){ 
    if(!top) return false; 
    Move* t=top; 
    r=t->r;
    c=t->c;
    prev=t->prev; 
    top=top->next; 
    delete t; 
    return true; 
}

// ---------- Initialize Game ---------- //
void init(){ moves=mistakes=0; top=NULL;
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++){
            board[i][j]=original[i][j];
            fixedCell[i][j]=(original[i][j]!=0);
        }
}

// ---------- Display Sudoku Board ---------- //
void display(){
    cout << "\n🎮    S U D O K U  G A M E    🎮\n";
    cout << "\n Moves✔️: " << moves << "   Mistakes⚠️: " << mistakes << "\n\n";
    cout << "    1 2 3   4 5 6   7 8 9\n";
    cout << "  ┏━━━━━━━┳━━━━━━━┳\n";

    for(int i=0;i<9;i++){
        cout << i+1 << " ┃ ";
        for(int j=0;j<9;j++){
            if(board[i][j]==0) cout << ". ";
            else cout << board[i][j] << " ";
            if((j+1)%3==0) cout << "┃ ";
        }
        cout << "\n";
        if((i+1)%3==0 && i!=8) cout << "  ┣━━━━━━━╋━━━━━━━╋\n";
        else if(i==8) cout << "  ┗━━━━━━━┻━━━━━━━┻\n";
    }
}

// ---------- Check Valid Move ---------- //
bool isValid(int r,int c,int n){
    for(int i=0;i<9;i++)
        if(board[r][i]==n || board[i][c]==n) 
        return false;
    int sr=r-r%3, sc=c-c%3;
    for(int i=0;i<3;i++) for(int j=0;j<3;j++)
        if(board[sr+i][sc+j]==n) return false;
    return true;
}

// ---------- Hint ---------- //
void hint(int r,int c){
    if(board[r][c]!=0){ 
        cout << "Cell already filled!\n"; 
        return; 
        
    }
    for(int n=1;n<=9;n++)
        if(isValid(r,c,n)){ 
            cout << "💡 Hint: Try " << n << endl; 
            return; 
            
        }
    cout << "💡 No valid number exists!\n";
}

// ---------- Check Solved ---------- //
bool solved(){
    for(int i=0;i<9;i++) for(int j=0;j<9;j++) if(board[i][j]==0) return false;
    return true;
}

// ---------- Main ---------- //
int main(){
    init();
    int choice;

    while(true){
        display();
        if(solved()){ cout << "\n🎉 CONGRATULATIONS! YOU SOLVED THE SUDOKU! 🎉\n"; break; }

        cout << "\n1️⃣ Enter Number✏️";
        cout << "\n2️⃣ Undo Last Move↩️";
        cout << "\n3️⃣ Get Hint  💡";
        cout << "\n4️⃣ Reset Game  ♻️";
        cout << "\n5️⃣ Exit🚪\nChoice: ";
        cin >> choice;

        if(choice==1){
            int r,c,n; 
            cout << "Row Col Number: "; cin >> r >> c >> n; 
            r--; c--;
            if(r<0||r>8||c<0||c>8||n<1||n>9) 
            cout << "❌ Input out of range!\n";
            else if(fixedCell[r][c]) 
            cout << "🔒 Cannot change original cell!\n";
            else if(isValid(r,c,n)) { 
                push(r,c,board[r][c]); 
                board[r][c]=n; 
                moves++; 
                
            }
            else { cout << "❌ Invalid move!\n"; 
            mistakes++; 
            }
        }
        else if(choice==2){ 
            int r,c,p; 
            if(pop(r,c,p)) 
            board[r][c]=p; 
            else cout << "❌ Nothing to undo!\n"; 
        }
        else if(choice==3){ 
            int r,c; 
            cout << "Row Col: "; 
            cin >> r >> c; 
            hint(r-1,c-1); 
        }
        else if(choice==4){ 
            init(); 
            cout << "♻️ Game reset!\n"; 
        }
        else if(choice==5) break;
        else cout << "❌ Invalid choice!\n";
    }
}