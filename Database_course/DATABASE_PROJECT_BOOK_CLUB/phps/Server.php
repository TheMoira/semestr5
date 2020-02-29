<?php
 
class Server {
 
  function prn_server () {
     echo 'Tablica $_SERVER
';
     echo "=================
";
     foreach ( $_SERVER as $key => $value )
        print '$_SERVER['.$key.'] = '.$value.'<br>' ;
  }
 
  function prn_post () {
     echo 'Tablica $_POST
';
     echo "===============
";
     foreach ( $_POST as $key => $value )
        print '$_POST['.$key.'] = '.$value.'<br>' ;
  }  
 
  function prn_get () {
     echo 'Tablica $_GET
';
     echo "==============
";
     foreach ( $_GET as $key => $value )
        print '$_GET['.$key.'] = '.$value.'<br>' ;
  }
 
  function prn_cookie () {
     echo 'Tablica $_COOKIE
';
     echo "=================
";
     foreach ( $_COOKIE as $key => $value )
        print '$_COOKIE['.$key.'] = '.$value.'<br>' ;
  }
 
  function prn_session () {
     echo 'Tablica $_SESSION
';
     echo "==================
";
     foreach ( $_SESSION as $key => $value )
        print '$_SESSION['.$key.'] = '.$value.'<br>' ;
  }
}
 
?>