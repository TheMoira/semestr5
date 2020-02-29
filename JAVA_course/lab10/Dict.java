import java.util.Scanner;
import java.util.ArrayList;
import java.io.*;
import java.io.FileNotFoundException;
// import java.io.FileWriter;  
// import java.io.IOException; 


public class Dict
{
    private String file;


    public Dict()
    {
        file = "dict.txt";
    }

    public void add(String pol, String ang)
    {
        String temp = "";
        String [] curr_line;
        try{
            FileReader f = new FileReader(file);

            BufferedReader buff = new BufferedReader(f);

            temp = buff.readLine();

            while(temp != null)
            {

                curr_line = temp.split(",");

                if(curr_line.length == 2)
                {
                    if(curr_line[0].equals(pol) || curr_line[1].equals(ang))
                    {
                        throw(new Exception());
                    }
                }

                temp = buff.readLine();
            }

            buff.close();
        }
        catch(IOException e)
        {
            System.out.println("Nie ma takiego pliku");
        }
        catch(Exception a)
        {
            System.out.println("Juz jest takie haslo w slowniku!");
        }

        try
        {
            FileWriter buff = new FileWriter(file,true);
            // BufferedWriter buff = new BufferedWriter(f);
            buff.write("\n" + pol + "," + ang);
            buff.close();
        }
        catch(IOException e)
        {
            System.out.println("Nie ma takiego pliku");
        }
    }

    public void del(String word)
    {
        String [] curr_line;
        String old = "";
        String temp = "";

        try{
            FileReader f = new FileReader(file);

            BufferedReader buff = new BufferedReader(f);

            temp = buff.readLine();

            while(temp != null)
            {

                curr_line = temp.split(",");

                if(curr_line.length == 2)
                {
                    if(!(curr_line[0].equals(word) || curr_line[1].equals(word)))
                    {
                        old += curr_line[0] + "," + curr_line[1] + "\n";
                    }
                }

                temp = buff.readLine();
            }

            buff.close();
        }
        catch(IOException e)
        {
            System.out.println("Nie ma takiego pliku");
        }

        try
        {
            FileWriter f2 = new FileWriter(file);
            BufferedWriter buff2 = new BufferedWriter(f2);

            buff2.write(old);
            buff2.close();

        }
        catch(IOException e1)
        {
            System.out.println("Nie ma takiego pliku");
        }


    }

    public String find(String word)
    {
        String odp = "Nie ma takiego slowa w slowniku";
            
        try
        {
            Scanner in = new Scanner(new File(file)); 
            String [] line;
        

            while(in.hasNextLine())
            {
                line = in.nextLine().split(",");

                if(line.length == 2)
                {
                    if(line[0].equals(word))
                    {
                        odp = line[1];
                    }
                    else if(line[1].equals(word))
                    {
                        odp = line[0];
                    }
                }
            }

        }
        catch(IOException e)
        {
            System.out.println("Nie ma takiego pliku");
        }


        return odp;
    }


}