import java.util.Scanner;

public class lab02
{
 public static void main(String[] args)
 {
  Scanner in = new Scanner(System.in);
      int size1 = in.nextInt();
      int size2 = in.nextInt();



    int [] tab1 = new int[size1];
    int [] tab2 = new int[size2];

    Scanner in2 = new Scanner(System.in);
    for(int i=0; i<size1; i++)
    {
        tab1[i] = in2.nextInt();
    }

Scanner in3 = new Scanner(System.in);

    for(int i=0; i<size2; i++)
    {
        tab2[i] = in3.nextInt();
    }
        
    
    int wynik = ciag(tab1,size1,tab2,size2);

    System.out.println(wynik);

 }

    public static int min(int a, int b)
    {
        return a>b ? b : a;
    }

    public static int ciag(int tab1[], int size1, int tab2[], int size2)
    {
        int count_zero_1 = 0;
        int count_zero_2 = 0;

        for(int i = 0; i<size1; i++)
        {
            if(tab1[i] == 0)
            {
                count_zero_1++;
            }
        }

        //System.out.println("count_zero_1 = " + count_zero_1);

        for(int i=0; i<size2; i++)
        {
            if(tab2[i] == 0)
            {
                count_zero_2++;
            }

        }

       // System.out.println("count_zero_2 = " + count_zero_2);

        int zero_count = min(count_zero_1, count_zero_2);

        //System.out.println("count_zero = " + zero_count);        

        int wynik = 0;

        for(int i=0; i<=zero_count; i++)
        {
            int count1_1 = 0;
            int count1_2 = 0;
            int curr_zero = 0;
    
            for(int j=0; j<size1; j++)
            {

                if(tab1[j] == 0)
                {
                    if(curr_zero <= i)
                    {
                        curr_zero++;
                    }
                }
                else
                {
                    if(curr_zero == i)
                    {
                        count1_1++;
                    }
                    
                }

               // System.out.println("curr_zero = " + curr_zero);
               // System.out.println("i = " + i);
            }

            curr_zero = 0;
            
            for(int j=0; j<size2; j++)
            {
                if(tab2[j] == 0)
                {
                    if(curr_zero <= i)
                    {
                        curr_zero++;
                    }
                }
                else
                {
                    if(curr_zero == i)
                    {
                        count1_2++;
                    }
                    
                }
            }

        
            //System.out.println("count1_1 = " + count1_1);
            //System.out.println("count1_2 = " + count1_2);
            
            int count1 = min(count1_1, count1_2);
            int temp = zero_count + count1;

            //System.out.println("temp = " + temp);


            if(wynik < temp)
            {
                wynik = temp;
            }


    }

        return wynik;

    }

}
