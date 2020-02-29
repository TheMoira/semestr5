import java.util.ArrayList;

public class Stos<T>
{
    private ArrayList<T> stos = new ArrayList<T>();

    public Stos() {}

    public void push(T value)
    {
        stos.add(value);
    }

    public void pop()
    {
        int size = stos.size();
        stos.remove(size-1);
    }

    public String toString()
    {
        String res = "";

        for(int i=(stos.size()-1); i>=0; i--)
        {
            res += "{" + stos.get(i) + "} ";
        }

        return res;
    }



}