<?php
ini_set('display_errors',1);
ini_set('display_startup_errors',1);
error_reporting(E_ALL);
require 'php-includes/connect.php';
if(isset($_POST['card'])){   
$card=$_POST['card'];
$query = "SELECT * FROM user WHERE card = ? limit 1";
$stmt = $db->prepare($query);
$stmt->execute(array($card));
$rows = $stmt->fetch(PDO::FETCH_ASSOC);
if ($stmt->rowCount()>0) {
    $query ="INSERT INTO history (card) VALUES (?)";
    $stm = $db->prepare($query);
    if ($stm->execute(array($card))) {
        $data = array('cstatus' =>'2'); 
        echo $response = json_encode($data)."\n";
    } 
} else {
    $data = array('cstatus' =>'1'); 
    echo $response = json_encode($data)."\n";
}
}
?>