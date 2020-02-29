/**
*klasa bazowa
*@autor Maria Korkuć 
*/
public class Shape
{
    double area;
    double volume;
    String name;

    Shape() 
    {
        area = 0;
        volume = 0;
        name = "";
    }

    /**
    *@return area
    */
    public double area()
    {
        return area;
    }

    /**
    *@return volume
    */
    public double volume()
    {
        return volume;
    }

    /**
    *@return name
    */
    public String getName()
    {
        return name;
    }

}
