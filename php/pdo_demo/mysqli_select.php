<?php
header('Content-Type: application/json; charset=utf-8');

require_once('config.php');
require_once('util.php');

// Create connection
$conn = new mysqli(DBHOST, DBUSER, DBPASS, DBNAME);

//$conn->set_charset("utf8");

// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT id, firstname, lastname FROM MyGuests LIMIT 10";
$result = $conn->query($sql);

header("HTTP/1.1 200");
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET");
header("Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With");

$rows = array();
if ($result->num_rows > 0) {
  // output data of each row
  while($row = $result->fetch_assoc()) {
    //echo "id: " . $row["id"]. " - Name: " . $row["firstname"]. " " . $row["lastname"]. "<br>";
    $rows[] = $row;
  }
  echo json_encode($rows);
} else {
  echo "{}";
}
$conn->close();
