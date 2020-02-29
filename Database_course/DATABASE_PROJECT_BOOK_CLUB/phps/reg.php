<?php
 
function __autoload($class_name) {
    include $class_name . '.php' ;
}
 
$reg = new Register_new ;
$reg->_read();
$reg->db_register_user();
$reg->_write();
echo $reg->_save();
echo "<p><a href='main_page.php'>Powrot do programu glownego</a></p>";
             
?>