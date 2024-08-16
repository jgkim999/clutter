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

$first_name = util::generateRandomString();
$last_name = util::generateRandomString();
$email = util::generateRandomEmail();
$sql = "INSERT INTO MyGuests (firstname, lastname, email) VALUES ('$first_name', '$last_name', '$email');";

$first_name = util::generateRandomString();
$last_name = util::generateRandomString();
$email = util::generateRandomEmail();
$sql .= "INSERT INTO MyGuests (firstname, lastname, email) VALUES ('$first_name', '$last_name', '$email');";

$first_name = util::generateRandomString();
$last_name = util::generateRandomString();
$email = util::generateRandomEmail();
$sql .= "INSERT INTO MyGuests (firstname, lastname, email) VALUES ('$first_name', '$last_name', '$email');";

if ($conn->multi_query($sql) === TRUE) {
    $last_id = $conn->insert_id;
    echo "New record created successfully. Last inserted ID is:" . $last_id;
} else {
    echo "Error:" . $sql . "<br>" . $conn->error;
} 

$conn->close();
