public class test
{
    public static String check_results(int[][] tab, int inst, int n)
    {
        int size = n/2;

        int [] tab1 = new int[size];
        int [] tab2 = new int[size];


            //tablica sprawdzan dla kazdej cyfry:
            //czy uda sie z prawdzic z 1,2,3,4,... itd
        boolean [] check = new boolean[n+1];
            
        //spr dla kazdej liczby
        for(int k=1; k<=n; k++)
        {
            wypelnij(check,n+1,false);
            check[k] = true;
            check[0] = true;

            for(int i=0; i<inst; i++)
            {
                for(int j=0; j<size; j++)
                {
                    tab1[j] = tab[i][j];
                    tab2[j] = tab[i][j+3];
                }
                
                if(zawiera(tab1,k,size))
                {
                    for(int j=0;j<size;j++)
                    {
                        check[tab2[j]] = true; 
                    }
                }
                else
                {
                    for(int j=0;j<size;j++)
                    {
                        check[tab1[j]] = true; 
                    }
                }

            }

            if(!sprawdz(check,n+1))
            {
                return "NIE";
            }

            ///nie sprawdza samej siebie

        }

        return "TAK";
    }

    public static void wypelnij(boolean[] tab, int n,boolean val)
    {
        for(int i=0; i<n;i++)
        {
            tab[i] = val;
        }
    }

    public static boolean sprawdz(boolean [] check, int n)
    {
        for(int i=0; i<n; i++)
        {
            if(check[i] == false)
            {
                return false;
            }
        }

        return true;
    }

    public static boolean zawiera(int [] tab1, int k, int size)
    {
        for(int i=0; i<size; i++)
        {
            if(tab1[i] == k)
            {
                return true;
            }
        }

        return false;
    }
}