
public class lab3string
{
    public static int dlugosc(String s)
    {
        return s.length();
    }

    public static int ile_razy_literka_wystepuje(String s, char a)
    {
        int wynik = 0;

        for(int i=0; i<s.length(); i++)
        {
            if(s.charAt(i) == a)
            {
                wynik++;
            }
        }

        return wynik;
    }

    public static boolean czy_takie_same(String s1, String s2)
    {
        return s1.equals(s2);
    }

    public static String wspak(String s)
    {
        String odp = new String();

        for(int i=s.length() - 1; i >= 0; i--)
        {
            odp += s.charAt(i);
        }

        return odp;

    }

    public static boolean czy_plaindrom(String s)
    {
        String palindrom = wspak(s);

        return s.equals(palindrom);
    }

    public static boolean czy_abecadlowe(String s)
    {
        for(int i=1; i < s.length(); i++)
        {
            if(s.charAt(i) < s.charAt(i-1))
            {
                return false;
            }   
        }
        
        return true;
    }

    public static String rot13(String s)
    {
        String rot = new String();

        for(int i=0; i<s.length(); i++)
        {
            int ascii = (int)s.charAt(i);

            if((ascii > 64 && ascii < 91) || (ascii > 96 && ascii < 123))
            {
                int begining = Character.isLowerCase(s.charAt(i)) ? 97 : 65;
                char curr = (char) (((int)(s.charAt(i)) - begining + 13)%26 + begining);

                rot += curr;
            }
            else
            {
                rot += s.charAt(i);
            }   
        }

        return rot;

    }
}
