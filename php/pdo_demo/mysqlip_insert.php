<?php
require_once('config.php');
require_once('util.php');

// Create connection
$conn = mysqli_connect(DBHOST, DBUSER, DBPASS, DBNAME);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . mysqli_connect_error());
}

$first_name = util::generateRandomString();
$last_name = util::generateRandomString();
$email = util::generateRandomEmail();
$sql = "INSERT INTO MyGuests (firstname, lastname, email) VALUES ('$first_name', '$last_name', '$email');";

if (mysqli_query($conn, $sql)) {
    $last_id = mysqli_insert_id($conn);
    echo "New record created successfully. Last inserted ID is:" . $last_id;
} else {
    echo "Error:" . $sql . "<br>" . mysqli_error($conn);
}

mysqli_close($conn);
