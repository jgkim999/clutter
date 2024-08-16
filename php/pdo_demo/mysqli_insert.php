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

$sql = sprintf("INSERT INTO MyGuests (firstname, lastname, email) VALUES ('%s', '%s', '%s');",
    util::generateRandomString(),
    util::generateRandomString(),
    util::generateRandomEmail());

if ($conn->query($sql) === TRUE) {
    $last_id = $conn->insert_id;
    echo "New record created successfully. Last inserted ID is:" . $last_id;
} else {
    echo "Error:" . $sql . "<br>" . $conn->error;
}

$conn->close();
