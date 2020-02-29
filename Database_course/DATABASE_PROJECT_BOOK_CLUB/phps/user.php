<?php
 
function __autoload($class_name) {
    include $class_name . '.php' ;
}
 
$user = new Register_new ;
 
if ( $user->_is_logged() ) { 
   $user->_read_user();
   echo $user->_write();
   echo "<p><a href='main_page.php'>Powrot do programu glownego</a></p>";
}
 
?>