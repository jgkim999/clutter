<?php
require_once('config.php');

class util
{
    /**
     * @throws \Random\RandomException
     */
    public static function generateRandomString(int $length = 10): string
    {
        $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
        $charactersLength = strlen($characters);
        $randomString = '';

        for ($i = 0; $i < $length; $i++)
        {
            $randomString .= $characters[random_int(0, $charactersLength - 1)];
        }
        return $randomString;
    }

    /**
     * @throws \Random\RandomException
     */
    public static function generateRandomEmail(int $length = 8): string
    {
        $characters = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
        $charactersLength = strlen($characters);
        $randomString = '';

        for ($i = 0; $i < $length; $i++)
        {
            $randomString .= $characters[random_int(0, $charactersLength - 1)];
        }
        return $randomString . '@example.com';
    }

    public static function mySqlPdo(): PDO
    {
        $dsn = sprintf("mysql:host=%s;dbname=%s;charset=utf8mb4", DBHOST, DBNAME);
        $conn = new PDO($dsn, DBUSER, DBPASS);
        $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        return $conn;
    }
}
