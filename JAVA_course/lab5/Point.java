/**
*klasa dziedziczaca po Shape
*@autor Maria Korkuć 
*/
public class Point extends Shape
{
    double x;
    double y;

    /**
    *konstruktor Point
    *ustawia wartości area oraz volume na 0
    *ustawia wartosc name na Point
    *@param n_x wspolrzedna x, n_y wspolrzedna y
    */
    Point(double n_x, double n_y)
    {
        x = n_x;
        y = n_y;

        area=0.0;
        volume = 0.0;
        name = "Point";
    }

    /**
    *tworzy odpowiednie wypisywanie dla klasy Point
    *@return sformatowane wyswietlanie
    */
    public String toString()
    {
        return "[" + x + ", " + y + "]";
    }


}
