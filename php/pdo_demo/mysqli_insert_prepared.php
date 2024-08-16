<?php
require_once('config.php');
require_once('util.php');

// Create connection
$conn = new mysqli(DBHOST, DBUSER, DBPASS, DBNAME);

//$conn->set_charset("utf8");

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$stmt = $conn->prepare("INSERT INTO MyGuests (firstname, lastname, email) VALUES (?, ?, ?)");
$stmt->bind_param("sss", $firstname, $lastname, $email);

$firstname = util::generateRandomString();
$lastname = util::generateRandomString();
$email = util::generateRandomEmail();
$stmt->execute();

$firstname = util::generateRandomString();
$lastname = util::generateRandomString();
$email = util::generateRandomEmail();
$stmt->execute();

$firstname = util::generateRandomString();
$lastname = util::generateRandomString();
$email = util::generateRandomEmail();
$stmt->execute();

echo "New record inserted";

$stmt->close();
$conn->close();
