package Armia;
import java.util.ArrayList;

public class Czolg
{
    ArrayList<Rozkaz> rozkazy = new ArrayList<Rozkaz>();
    
    public Czolg(){}

    public void dodajRozkaz(Rozkaz r)
    {
        rozkazy.add(r);
    }

    public String ostatniRozkaz()
    {
        String ostatni = "Ostatni rozkaz do mnie: ";
        return ostatni + rozkazy.get(rozkazy.size() - 1);
    }

    public String toString()
    {
        String out = "";

        for(int i=0; i<rozkazy.size(); i++)
        {
            out += rozkazy.get(i) + "\n";
        }

        return out;
    }
}