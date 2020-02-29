import java.io.*;
import java.io.FileNotFoundException;

public class lab10
{
    public static void main(String[] args)
    {
        String action = args[0];
        
        Dict dict = new Dict();

        if(action.equals("add"))
        {   
            if(args.length == 3)
            {
                dict.add(args[1],args[2]);
            }
            else
            {
                System.out.println("Zla ilosc argumentow");
            }
        }
        else if(action.equals("del"))
        {
            dict.del(args[1]);
        }
        else
        {
            //wypisz odpowiednik slowa
            System.out.println(dict.find(args[0]));
        }

    }
}