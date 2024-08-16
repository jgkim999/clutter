<?php
require_once('util.php');

try {
    $conn = util::mySqlPdo();

    echo "Connected successfully";
    $conn = null;
} catch(PDOException $e) {
    echo "Connection failed: " . $e->getMessage();
}
