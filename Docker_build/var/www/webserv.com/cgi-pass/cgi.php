#!/usr/bin/php
<?php
    if ($_SERVER['REQUEST_METHOD'] === 'GET') {
        $name = $_GET['name'] ?? 'World';
        $server = $_SERVER['SERVER_SOFTWARE'];
        header('Content-Type: text/html; charset=utf-8');
        header('Content-length: 10;');
        echo "<h1>Hello, $name!</h1>";
    }


    // $_POST for application/x-www-form-urlencoded ou multipart/form-data //
    //php://input for other content
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        $postData = file_get_contents('php://input');
        header('Content-Type: text/html; charset=utf-8');
        header('Content-length: ' . mb_strlen($postData, 'UTF-8'));
        echo "<p>You posted: $postData</p>";
    }
?>
