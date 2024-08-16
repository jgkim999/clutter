<?php
require_once('config.php');

// Create connection
$conn = new mysqli(DBHOST, DBUSER, DBPASS, DBNAME);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

echo $conn->host_info . "\n";

echo "Connected successfully";
