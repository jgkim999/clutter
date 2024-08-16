<?php
global $sql;
require_once('util.php');

try {
    $conn = util::mySqlPdo();

    // prepare sql and bind parameters
    $stmt = $conn->prepare("INSERT INTO MyGuests (firstname, lastname, email) VALUES (:firstname, :lastname, :email)");
    $stmt->bindParam(':firstname', $firstname);
    $stmt->bindParam(':lastname', $lastname);
    $stmt->bindParam(':email', $email);

    // insert a row
    $firstname = util::generateRandomString();
    $lastname = util::generateRandomString();
    $email = util::generateRandomEmail();
    $stmt->execute();

    // insert another row
    $firstname = util::generateRandomString();
    $lastname = util::generateRandomString();
    $email = util::generateRandomEmail();
    $stmt->execute();

    // insert another row
    $firstname = util::generateRandomString();
    $lastname = util::generateRandomString();
    $email = util::generateRandomEmail();
    $stmt->execute();

    $last_id = $conn->lastInsertId();
    echo "New record created successfully. Last inserted ID is:" . $last_id;
    
} catch(PDOException $e) {
    echo $sql . "<br>" . $e->getMessage();
}

$conn = null;
