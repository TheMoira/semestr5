public class Make_board
{
    public static void random(char[][] board, int rows, int cols)
    {
        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<cols; j++)
            {
                int temp = ((int)Math.random())%2;
                if(temp==0)
                {
                    board[i][j] = '.';
                }
                else
                {
                    board[i][j] = 'X';
                }
            }
        }

    }

    public static void boat(char[][] board, int rows, int cols)
    {
        int middle_x = rows/2;
        int middle_y = cols/2;

        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<cols; j++)
            {
                board[i][j] = '.';
            }
        }

        board[middle_x+1][middle_y]='X';
        board[middle_x-1][middle_y]='X';
        board[middle_x][middle_y+1]='X';
        board[middle_x][middle_y-1]='X';
        board[middle_x-1][middle_y-1]='X';


    }

    public static void spaceship(char[][] board, int rows, int cols)
    {
        int middle_x = rows/2;
        int middle_y = cols/2;

        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<cols; j++)
            {
                board[i][j] = '.';
            }
        }
        
        board[middle_x][middle_y-1]='X';
        board[middle_x+1][middle_y]='X';
        board[middle_x-1][middle_y]='X';
        board[middle_x-1][middle_y+1]='X';
        board[middle_x-1][middle_y-1]='X';
        
        
    }

    public static void blinker(char[][] board, int rows, int cols)
    {
        int middle_x = rows/2;
        int middle_y = cols/2;

        for(int i=0; i<rows; i++)
        {
            for(int j=0; j<cols; j++)
            {
                board[i][j] = '.';
            }
        }

        board[middle_x+1][middle_y]='X';
        board[middle_x][middle_y]='X';
        board[middle_x-1][middle_y]='X';

    }
}
