<?php
require_once('config.php');
require_once('util.php');

// Create connection
$conn = mysqli_connect(DBHOST, DBUSER, DBPASS, DBNAME);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . mysqli_connect_error());
}

echo $conn->host_info . "\n";

echo "Connected successfully";
