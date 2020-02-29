/**
*klasa dziedziczaca po Point
*@autor Maria Korkuć 
*/
public class Square extends Point
{
    double side;

    /**
    *konstruktor Square
    *ustawia wartości area (oblicza) oraz volume na 0
    *ustawia wartosc name na Square
    *@param n_side dlugosc boku, n_x wspolrzedna x, n_y wspolrzedna y
    */
    Square(double n_side, double n_x, double n_y)
    {
        /**
        *inicjalizacja klasy nadrzędnej Point
        */
        super(n_x,n_y);
        side = n_side;

        area= side * side;
        name = "Square";
    }

    /**
    *tworzy odpowiednie wypisywanie dla klasy Square
    *nadpisuje dziedziczoną metodę po klasie Point
    *@return sformatowane wyswietlanie
    */
    public String toString()
    {
        return "Corner = " + super.toString() + "; side = " + side;
    }


}
