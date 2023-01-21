<?php
ini_set('display_errors',1);
ini_set('display_startup_errors',1);
error_reporting(E_ALL);
require 'php-includes/connect.php';
if(isset($_REQUEST['card1'])){ 
$card="13CAD1E";
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
if(isset($_REQUEST['card2'])){ 
    $card="41FCFE45";
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
    if(isset($_REQUEST['card3'])){ 
        $card="5135A45";
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
        if(isset($_REQUEST['card4'])){ 
            $card="B38204B";
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