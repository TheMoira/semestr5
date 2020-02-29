<?php


session_start() ;
echo "<link rel='stylesheet' href = '../CSS/style.css'>";

function connect()
{
    $dbconn = pg_connect("host=localhost dbname=u7korkuc user=u7korkuc password=7korkuc") or die('Could not connect: ' . pg_last_error());
    return $dbconn;
}

function Result($query)
{
    $db = connect();
    $result = pg_query($db, $query) or die (pg_last_error($db));
    return $result;
}

function get_id_type($field)
{
    $id_type = "";

    switch($field)
    {
        case 'book':
            $id_type = "id_book";
        break;
        case 'author':
            $id_type = "id_author";
        break;
        case 'club_user':
            $id_type = "id_user";
        break;
        case 'editorial':
            $id_type = "id_edit";
        break;
        case 'series':
            $id_type = "id_series";
        break;
        case 'description':
            $id_type = "id_desc";
        break;
        case 'book_item':
            $id_type = "id_book_item";
        break;
        case 'item_description':
            $id_type = "id_desc";
        break;
        case 'transaction':
            $id_type = "id_trans";
        break;
        default:
            $id_type = "wrong";
        break;
    }

    return $id_type;
}

function get_value_type($field)
{
    $val_type = "";

    switch($field)
    {
        case 'book':
            $val_type = "title";
        break;
        case 'author':
            $val_type = "surname";
        break;
        case 'club_user':
            $val_type = "email";
        break;
        case 'editorial':
            $val_type = "name";
        break;
        case 'series':
            $val_type = "name";
        break;
        default:
            $val_type = "wrong";
        break;
    }

    return $val_type;
}

function can_already_exist($field)
{
    $up = array('book','author','club_user','editorial','series');
    return in_array($field, $up);
}

//ex. 'club_user', $email
function get_new_index($field, $value, &$exists)  //zwraca nowy index do dodania do bazy, w zaleznosci od rodzaju dodanego pola
{
    $new_id = -1;
    $need_new = false;

    $db = connect();

    $updatable = can_already_exist($field);

    $id_type = get_id_type($field);

    if($updatable)
    {
        $value_type = get_value_type($field);
        $query = "SELECT ".$id_type." FROM book_club.".$field." WHERE ".$value_type." = '".$value."';";
        // echo $query."</br>";
        $result = pg_query($db, $query);
        if(! $result)
        {
            echo "Problem with query</br>";
            $exists = true;
            exit;
        }

        $rows = pg_num_rows($result);

        if($rows == 0)  //jesli nie ma jeszcze takiego autora/ksiazki/serii itd
        {
            $need_new = true;
        }
        else if($rows == 1) //jesli jest to znajdujemy odpowiednie id
        {
            $res = pg_fetch_row($result);
            // echo $query." -- ".$res[0]."</br>";
            $new_id = (int)$res[0];
            $exists = true;
        }   
        else
        {
            $exists = true;
            echo "weird</br>";
        }

    }
    else
    {
        $need_new = true;
    }
    
    if($need_new)
    {
        $exists = false;

        $new_id_query = "SELECT MAX(".$id_type.") FROM book_club.".$field;
        $id_result = pg_query($db,$new_id_query);

        if(!$id_result)
        {
            echo "<h1>oops</h1></br>";
        }
        else
        {
            $rows = pg_num_rows($id_result);
            if($rows == 0)
            {
                //dodajemy index 0
                $new_id = 0;
            }
            else
            {
                $max = (int)pg_fetch_result($id_result,0,0) + 1;
                $new_id = $max;
            }
        }

    }


    return $new_id;
}

function db_add_user($name, $surname, $email, $password)
{

    $exists = false;
    $id_new = get_new_index('club_user', $email, $exists);
    echo $id_new."</br>";
    if($id_new == -1 || !$id_new)
    {
        echo "Problemo</br>";
        exit;
    }

    $db = connect();
    $query = "INSERT INTO book_club.club_user (id_user, name, surname, book_count, email, password) 
    VALUES ($id_new, '".$name."', '".$surname."', 0, '".$email."', '".$password."')";

    $result = pg_query($db, $query) or die(pg_last_error($db));

}


function genre_id($genre)
{
    $id = -1;

    switch($genre)
    {
        case 'fantasy':
            $id = 0;
        break;
        case 'scifi':
            $id = 1;
        break;
        case 'report':
            $id = 2;
        break;
        case 'romance':
            $id = 3;
        break;
        case 'novel':
            $id = 4;
        break;
        case 'crime':
            $id = 5;
        break;
        case 'drama':
            $id = 6;
        break;
        case 'horror':
            $id = 7;
        break;
        case 'classic':
            $id = 8;
        break;
        case 'textbook':
            $id = 9;
        break;
        default:
            $id = 10;
        break;
    }

    return $id;
}


function to_bool($some_bool)
{
    return $some_bool == 1 ? 'true' : 'false';
}

?>