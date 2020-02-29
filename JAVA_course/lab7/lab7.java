import java.util.Scanner;

public class lab7
{
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int instances = in.nextInt();

        int [][] tab = new int[instances][n];

        for(int i=0; i<instances; i++)
        {
            Scanner in2 = new Scanner(System.in);
            for(int j=0; j<n; j++)
            {
                tab[i][j] = in2.nextInt();
            }
        }

        String odp = test.check_results(tab,instances,n);
        System.out.println(odp);



    }
}