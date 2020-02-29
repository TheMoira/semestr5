public class Game
{
    public static void next_step(char[][] board, int rows, int cols)
    {
        char[][] copy = new char[rows][cols];
        
        for(int row = 0; row<rows; row++)
        {
            for(int col=0; col<cols; col++)
            {
                copy[row][col] = board[row][col];
            }        
        }

        for(int row = 0; row < rows; row++)
        {
            for(int col = 0; col<cols; col++)
            {
                int zywi = alive_count(board,rows, cols, row,col);

                
                if(board[row][col] == 'X')
                {
                    if(!(zywi==3 || zywi==2))
                    {
                        copy[row][col] = '.';
                    }
                }
                else
                {
                    if(zywi == 3)
                    {
                        copy[row][col] = 'X';
                    }
                }
            }
        }

        for(int row = 0; row<rows; row++)
        {
            for(int col=0; col<cols; col++)
            {
                board[row][col] = copy[row][col];
            }        
        }
        
    }

    
     //konkretna kolumna i wiersz  
    static int alive_count(char[][] board, int rows, int cols, int row, int col)
    {
        int zywi = 0;

        if((row > 0 && row < rows-1) && (col > 0 && col < cols-1))
        {
            for(int i=-1; i<=1; i++)
            {
                for(int j=-1; j<=1; j++)
                {
                    if(board[row+i][col+j] == 'X' && i!= row && j!= col) zywi++;
                }
            }
        }
        else if(row == 0 && col == 0)
        {
            for(int i=0; i<=1; i++)
            {
                for(int j=0; j<=1; j++)
                {
                    if(board[row+i][col+j] == 'X' && i!= row && j!= col) zywi++;
                }
            }
        }
        else if(row==rows-1 && col==cols-1)
        {
            for(int i=-1; i<=0; i++)
            {
                for(int j=-1; j<=0; j++)
                {
                    if(board[row+i][col+j] == 'X' && i!= row && j!= col) zywi++;
                }
            }
        }
        else if(row==rows-1 && col==0)
        {
            for(int i=-1; i<=0; i++)
            {
                for(int j=0; j<=1; j++)
                {
                    if(board[row+i][col+j] == 'X' && i!= row && j!= col) zywi++;
                }
            }
        }
        else if(row==0 && col==cols-1)
        {
            for(int i=0; i<=1; i++)
            {
                for(int j=-1; j<=0; j++)
                {
                    if(board[row+i][col+j] == 'X' && i!= row && j!= col) zywi++;
                }
            }
        }
        else if(row<rows-1 && row>0 && col==0)
        {
            for(int i=-1; i<=1; i++)
            {
                for(int j=0; j<=1; j++)
                {
                    if(board[row+i][col+j] == 'X' && i!= row && j!= col) zywi++;
                }
            }
        }
        else if(row<rows-1 && row>0 && col==cols-1)
        {
            for(int i=-1; i<=1; i++)
            {
                for(int j=-1; j<=0; j++)
                {
                    if(board[row+i][col+j] == 'X' && i!= row && j!= col) zywi++;
                }
            }
        }
        else if(col<cols-1 && col>0 && row==0)
        {
            for(int i=0; i<=1; i++)
            {
                for(int j=0; j<=1; j++)
                {
                    if(board[row+i][col+j] == 'X' && i!= row && j!= col) zywi++;
                }
            }
        }
        else if(col<cols-1 && col>0 && row==0)
        {
            for(int i=0; i<=1; i++)
            {
                for(int j=-1; j<=0; j++)
                {
                    if(board[row+i][col+j] == 'X' && i!= row && j!= col) zywi++;
                }
            }
        }


        return zywi;
    }


}
