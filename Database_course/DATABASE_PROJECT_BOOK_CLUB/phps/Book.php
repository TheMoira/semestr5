<?php
 
class Book {
 
    public $title;
    public $author;    //name,surname
    public $series = "null";
    public $eval;
    public $lang;
    public $editorial;
    public $year;
    public $is_used = false;
    public $is_available = true;
    public $is_hardcover = false;
    public $to_sell = true;
    public $to_exchange = false;
    public $price = 0;
    public $description = "brak opisu";
    public $genre;

   function __construct () {
    session_start() ;
 }
       
   function _set_values () 
   {
        $this->title = $_POST['title'] ;
        // echo "title: $this->title \n";
        $author_data = explode(' ',$_POST['author']);
        $this->author['name'] = $author_data[0];

        if(count($author_data) == 2)
        {
            $this->author['surname'] = $author_data[1];
        }
        else
        {
            $this->author['surname'] = $author_data[0];
        }

        $this->eval = $_POST['eval'] ;
        // echo "eval: $this->eval \n";
        $this->lang = $_POST['language'] ;
        $this->editorial = $_POST['editorial'] ;
        // echo "edit: $this->editorial \n";
        $this->year = $_POST['year'] ;
        // echo "ywar: $this->year \n";
        if(!empty($_POST['series']))
        {
            $this->series = $_POST['series'];
        }

        if(!empty($_POST['description']))
        {
            $this->description = $_POST['description'];
        }

        if(isset($_POST['used']))
        {
            $this->is_used = true;
        }

        if(isset($_POST['hardcover']))
        {
            $this->is_hardcover = true;
        }


        if($_POST['trans'] == 'sell')
        {
            if(empty($_POST['price']))
            {
                $this->to_sell = false;
                $this->to_exchange = true;
            }
            else
            {
                $this->price = $_POST['price'];
            }
        }
        else
        {
            $this->to_sell = false;
            $this->to_exchange = true;
        }

        $this->genre = $_POST['genre'];
        // echo "BOOK END \n";
    }          
 

}
?>