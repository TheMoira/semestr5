package Armia;
import java.util.ArrayList;

public class CentrumDowodzenia
{
    ArrayList<Czolg> czolgi = new ArrayList<Czolg>();

    public CentrumDowodzenia(){}

    public void zarejestrujCzolg(Czolg c)
    {
        czolgi.add(c);
    }

    public void wydajRozkaz(String nr, Rozkaz r)
    {
        int number = Integer.parseInt(nr);

        czolgi.get(number-1).dodajRozkaz(r);
    }

    public String toString()
    {
        String out = "";

        out += "Do tej pory centrum dowodzenia wyslalo nastepujace rozkazy:\n";

        for(int i=0; i<czolgi.size(); i++)
        {
            out += "Czolg nr " + (i+1) + " otrzymal rozkazy:\n";
            out += czolgi.get(i) + "\n";
        }

        return out;
    }
}