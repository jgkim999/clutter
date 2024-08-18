<?php
global $sql;
require_once('util.php');

header('Content-Type: application/json; charset=utf-8');
header("HTTP/1.1 200");
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET");
header("Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With");

try {
  $conn = util::mySqlPdo();

  $sql = "SELECT id, firstname, lastname FROM MyGuests LIMIT 10";

  $result = $conn->query($sql);

  $rows = array();
  if ($result->rowCount() > 0)
  {
    while ($row = $result->fetch())
      $rows[] = $row;
    echo json_encode($rows);
  }
  else
  {
    echo "{}";
  }

} catch(PDOException $e) {
    echo $sql . "<br>" . $e->getMessage();
}

$conn = null;
