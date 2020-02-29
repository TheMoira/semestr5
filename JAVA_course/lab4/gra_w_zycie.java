public class gra_w_zycie
{
    static public void play(int rows, int cols, int steps, int preset)
    {
        char[][] board = new char[rows][cols];

        switch(preset)
        {
            case 0:
                Make_board.random(board, rows, cols);
                break;

            case 1:
                Make_board.boat(board, rows, cols);
                break;

            case 2:
                Make_board.blinker(board, rows, cols);
                break;

            case 3:
                Make_board.spaceship(board, rows, cols);
                break;

            default:
                Make_board.random(board, rows, cols);
                break;
            
        }
        
        
        print_game(board, rows, cols, steps);

    }

    static void print_game(char[][] board, int rows, int cols, int steps)
    {
        int dt = 1;

        while(dt<steps)
        {
            System.out.print("-");
            System.out.print(dt);
            System.out.print("-");
            System.out.println();

            Game.next_step(board, rows, cols);
            
            for(int row = 0; row<rows; row++)
            {
                System.out.println(board[row]);
            }
            
            System.out.println();
            dt++;
        }
    }

    
}
