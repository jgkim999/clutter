<?php
global $sql;
require_once('util.php');

try {
    $conn = util::mySqlPdo();

    $conn->beginTransaction();

    for ($i = 0; $i < 3; $i++)
    {
        $first_name = util::generateRandomString();
        $last_name = util::generateRandomString();
        $email = util::generateRandomEmail();
        $conn->exec("INSERT INTO MyGuests (firstname, lastname, email) VALUES ('$first_name', '$last_name', '$email');");
    }

    $conn->commit();

    $last_id = $conn->lastInsertId();

    echo "New record created successfully. Last inserted ID is:" . $last_id;
    
} catch(PDOException $e) {
    echo $sql . "<br>" . $e->getMessage();
}

$conn = null;
