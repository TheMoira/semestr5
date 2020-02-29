<?php

include 'functions.php';


function add_book($book, $email)
{
    $db = connect();

    $temp = 0;
    $exists = false;

    $id_user = get_new_index('club_user', $email, $exists);
    // echo "user: $id_user </br>";
    $id_genre = genre_id($book->genre);

    $id_book = get_new_index('book', $book->title, $exists);
    // echo "book: $id_book exists = $exists</br>";

    if($exists)
    {
        //sprawdzamy czy to na pewno ta sama ksiazka (czy zgadza sie autor)
        $check_query = "SELECT surname FROM book_club.author a 
        JOIN book_club.book b on a.id_author = b.id_author 
        WHERE title = '".$book->title."' AND surname = '".$book->author['surname']."'";

        $check_result = pg_query($db, $check_query) or die("problem with author_check query");
        $rows = pg_num_rows($check_result);

        if($rows == 0)
        {
            $id_book = get_new_index('book', $book->author['surname']."/".$book->title, $exists);
            $exists = false;
        }

    }


    if(!$exists)
    {
        $exists = false;
        $id_author = get_new_index('author', $book->author['surname'], $exists);
        // echo "author: $id_author </br>";
        if(!$exists)
        {
            //dodaj autora
            insert_author($id_author, $book->author['name'], $book->author['surname']);
        }

        $id_series = -1;
        if($book->series != "null")
        {
            $id_series = get_new_index('series', $book->series, $exists);
            // echo "series: $id_series </br>";
            if(!$exists)
            {
                //dodaj serie
                insert_series($id_series, $id_author, $book->series);
            }
        }

        $id_description = get_new_index('description', $book->description, $exists);
        //dodaj description
        // echo "description: $id_description </br>";
        insert_desc($id_description, $book->description);

        //dodaj book
        insert_book($id_book, $id_author, $id_description, $id_series, $book->title, $book->eval, $id_genre);
        
    }

    $id_book_item = get_new_index('book_item', $temp, $exists);
    //dodaj item_book
    insert_book_item($id_book_item, $id_book, $id_user, $id_description);
    // echo "book_item: $id_book_item </br>";

    $id_edit = get_new_index('editorial', $book->editorial, $exists);
    // echo "edit: $id_edit </br>";
    if(!$exists)
    {
        //dodaj editorial
        insert_editorial($id_edit, $book->editorial);
    }
    
    $id_item_description = get_new_index('item_description', $temp, $exists);
    //dodaj item description
    insert_item_desc($id_item_description, $id_edit, $id_book_item, $book->is_available,
    $book->is_used, $book->is_hardcover, $book->lang, $book->to_exchange, $book->price, $book->year);
    // echo "item_desc: $id_item_description </br>";

    //update book_count
    $temp_query = "SELECT book_count FROM book_club.club_user WHERE id_user = ".$id_user;
    $res1 = pg_query($db, $temp_query);
    if(! $res1)
    {
        echo "Problem with book_count query</br>";
        exit;
    }
    else
    {
        echo $res1;
        $count = (int)pg_fetch_result($res1,0,0) + 1;
        $query_user = "UPDATE book_club.club_user
        SET book_count = ".$count." WHERE id_user = ".$id_user;
        $result = pg_query($db, $query_user);
    }

}


function insert_author($id, $name, $surname)
{
    $db = connect();

    $query = "INSERT INTO book_club.author (id_author, name, surname) 
    VALUES (".$id.", '".$name."', '".$surname."')";

    $result = pg_query($db, $query) or die("Failed to add author");
}


function insert_series($id_series, $id_author, $name)
{
    $db = connect();

    $query = "INSERT INTO book_club.series (id_series, id_author, name) 
    VALUES (".$id_series.", ".$id_author.", '".$name."')";

    $result = pg_query($db, $query) or die("Failed to add serie");
}

function insert_desc($id_desc, $desc)
{
    $db = connect();

    $query = "INSERT INTO book_club.description (id_desc, description) 
    VALUES (".$id_desc.", '".$desc."')";

    $result = pg_query($db, $query) or die("Failed to add description");
}

function insert_book($id_book, $id_author, $id_desc, $id_series, $title, $eval, $id_genre)
{
    $db = connect();

    $query = "INSERT INTO book_club.book (id_book, id_author, id_desc, id_series, title, eval) 
    VALUES (".$id_book.", ".$id_author.", ".$id_desc.", ".$id_series.", '".$title."', ".$eval.")";

    echo $query."</br>";
    $query2 = "INSERT INTO book_club.book_genre (id_genre, id_book) 
    VALUES (".$id_genre.",".$id_book.")";

    $result = pg_query($db, $query) or die("Failed to add book");
    $result2 = pg_query($db, $query2) or die("Failed to add book_genre");
}

function insert_book_item($id_book_item, $id_book, $id_user, $id_desc)
{
    $db = connect();

    $query = "INSERT INTO book_club.book_item (id_book_item, id_book, id_owner, id_desc) 
    VALUES (".$id_book_item.", ".$id_book.", ".$id_user.", ".$id_desc.")";

    $result = pg_query($db, $query) or die("Failed to add book_item");
}

function insert_editorial($id_edit, $name)
{
    $db = connect();

    $query = "INSERT INTO book_club.editorial (id_edit, name) 
    VALUES (".$id_edit.", '".$name."')";

    $result = pg_query($db, $query) or die("Failed to add editorial");
}

function insert_item_desc($id_item_description, $id_edit, $id_book_item, $is_available,
$is_used, $is_hardcover, $lang, $to_exchange, $price, $year)
{
    $db = connect();

    $query = "INSERT INTO 
    book_club.item_description (id_desc, id_edit, id_book_item, is_available,
    is_used, is_hardcover, language, to_exchange, year, price) 
    VALUES (".$id_item_description.", ".$id_edit.", ".$id_book_item.", ".to_bool($is_available).", ".to_bool($is_used).", ".to_bool($is_hardcover).", '".$lang."', ".to_bool($to_exchange).", '".$year."', ".$price.")";


    $result = pg_query($db, $query) or die("Failed to add item_description");
}



?>