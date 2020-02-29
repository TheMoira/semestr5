<?php

include 'functions.php';


$email = $_SESSION['user'];
$id_desc = $_POST['details'];


if ( !empty($email) )
{
    if($id_desc)
    {
        $q1 = "SELECT b.id_book from (book_club.book b join book_club.book_item bi on b.id_book = bi.id_book) 
        join book_club.item_description id on bi.id_desc = id.id_desc WHERE id.id_desc = $id_desc";
        $res1 = Result($q1);
        $row = pg_fetch_assoc($res1);
        $id_book = $row['id_book'];

        $q2 = "SELECT u.name, u.surname from book_club.club_user u join book_club.book_item bi on u.id_user = bi.id_owner WHERE bi.id_book = $id_book";
        // echo $q2;
        
        $res2 = Result($q2);
        $row2 = pg_fetch_assoc($res2);
        $owner_name = $row2['name'];
        $owner_surname = $row2['surname'];

        $query = "SELECT 
        b.id_book,
        b.eval,
        b.title, a.name AS a_name, a.surname, 
        e.name, 
        id.is_hardcover, 
        id.is_available,
        id.is_used,
        id.language,
        id.to_exchange,
        id.year,
        id.price
        from (((
        book_club.editorial e join book_club.item_description id on e.id_edit = id.id_edit)
        join book_club.book_item bi on id.id_desc = bi.id_desc)
        join book_club.book b on bi.id_book = b.id_book)
        join book_club.author a on b.id_author = a.id_author
        WHERE id.id_desc = $id_desc";
        
        $qs = "SELECT s.name as ser FROM book_club.book b join book_club.series s on b.id_author = s.id_author WHERE b.id_book = $id_book";
        $r = Result($qs);
        $row3 = pg_fetch_assoc($r);
        $ser = $row3['ser'];


        $query2 = "SELECT 
        g.name AS gen,
        d.description
        from ((
        book_club.description d join book_club.book b on d.id_desc = b.id_desc)
        join book_club.book_genre bg on b.id_book = bg.id_book)
        join book_club.genre g on bg.id_genre = g.id_genre
        WHERE b.id_book = $id_book";

        $res_part1 = Result($query);
        $res_part2 = Result($query2);

        $rows = pg_num_rows($res_part2);

        if(!$rows)
        {
            echo "<p>Błąd</p>";
        }
        else
        {
            $row1=pg_fetch_assoc($res_part1);
            $row2=pg_fetch_assoc($res_part2);

            $hardc = $row1['is_hardcover'] == 't' ? 'Twarda okładka' : 'Miękka okładka';
            $used = $row1['is_used'] == 't' ? 'Używana' : 'Nowa';
            $ex = $row1['to_exchange'] == 't' ? 'Do wymiany' : 'Na sprzedaż';
            $avail = $row1['is_available'] == 't' ? 'Dostępna' : 'Niedostępna';


            echo "<h1>INFORMACJE O KSIĄŻCE '".$row1['title']."'</h1></br>";
            echo "<p>Autor: ".$row1['a_name']." ".$row1['surname']."</p>";
            echo "<p>Wydawnictwo: ".$row1['name']."</p>";
            if($ser) echo "<p>Seria: ".$row1['s_name']."</p>";
            echo "<p>Język: ".$row1['language']."</p>";
            echo "<p>Gatunek: ".$row2['gen']."</p>";
            echo "<p>Ocena: ".$row1['eval']."</p>";
            echo "<p>Informacje fizyczne:</p>";
            echo "<p>$hardc</p>";
            echo "<p>$used</p>";
            echo "<p>$ex</p>";
            echo "<p>$avail</p>";
            if($row1['to_exchange'] == 'true') echo "<p>Cena: ".$row1['price']."</p>";
            echo "<p>Opis: ".$row2['description']."</p>";
            echo "<p>Właściciel: $owner_name, $owner_surname</p>";
            echo "</br></br><a href='../phps/main_page.php' class='button1'>Strona główna</a></br>";
        }
    }
    else
    {
        echo "Problem</br>";
    }
}


?>