<?php
global $sql;
require_once('util.php');

try {
    $conn = util::mySqlPdo();

    $first_name = util::generateRandomString();
    $last_name = util::generateRandomString();
    $email = util::generateRandomEmail();
    $sql = "INSERT INTO MyGuests (firstname, lastname, email) VALUES ('$first_name', '$last_name', '$email');";

    $conn->exec($sql);
    $last_id = $conn->lastInsertId();

    echo "New record created successfully. Last inserted ID is:" . $last_id;
    
} catch(PDOException $e) {
    echo $sql . "<br>" . $e->getMessage();
}

$conn = null;

