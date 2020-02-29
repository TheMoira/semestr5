
public class Stos<T>
{
    Element<T> head; 
    boolean start;

    public Stos() 
    {
        head = new Element<T>();
        start = false;
    }

    public void push(T value)
    {
        if(start)
        {
            head.add(value);
        }
        else
        {
            head.set(value);    
            start = true;
        }
    }

    public void pop()
    {
        if(head.next == null)
        {
            head = null;
        }
        else
        {
            head.del();
        }
    }

    public String toString()
    {
        if(head == null)
        {
            return "stos pusty";
        }

        String [] odp = head.toString().split(" ");
        String res = "";

        for(int i=odp.length-1; i>=0; i--)
        {
            res += odp[i] + " ";
        }

        return res;
    }



}