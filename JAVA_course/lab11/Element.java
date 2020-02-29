public class Element<T>
{
    private T value;
    public Element<T> next;

    public Element() 
    {
        next = null;
    }

    public void set(T val)
    {
        value = val;
    }

    public void add(T val)
    {
        if(next == null)
        {
            next = new Element<T>();
            next.set(val);
        }
        else
        {
            next.add(val);
        }
    }

    public T get()
    {
        return value;
    }

    public String toString()
    {
        if(next == null)
        {
            return "{" + value + "}";
        }
        else
        {
            return "{" + value + "} " + next.toString();
        }
    }

    public void del()
    {
        if(next.next == null)
        {
            next = null;
        }
        else
        {
            next.del();
        }
    }

}