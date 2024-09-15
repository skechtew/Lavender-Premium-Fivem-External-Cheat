<?php

function connectDB() {
    $conn = new mysqli('localhost', '', '', '');
    if ($conn->connect_error) {
        die("Bağlantı hatası: " . $conn->connect_error);
    }
    return $conn;
}


function checkAndUpdateHwid($apiKey, $newHwid) {
    $conn = connectDB();


    $stmt = $conn->prepare("SELECT expire_at, hwid, ban FROM api_keys WHERE api_key = ?");
    $stmt->bind_param("s", $apiKey);
    $stmt->execute();
    $stmt->bind_result($expireAt, $hwid, $ban);
    $stmt->fetch();
    $stmt->close();


    if ($expireAt) {

        return [
                'status' => 'exists',
                'expire_at' => date('Y-m-d', $expireAt),
                'hwid' => $hwid,
                'ban' => $ban
            ];
    } else {

        $conn->close();
        return ['status' => 'invalid_key'];
    }
}


if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $apiKey = isset($_GET['key']) ? $_GET['key'] : null;
    $hwid = isset($_GET['hwid']) ? $_GET['hwid'] : null;

    if ($apiKey && $hwid) {
        $result = checkAndUpdateHwid($apiKey, $hwid);
        header('Content-Type: application/json');
        echo json_encode($result);
    } else {
        header('Content-Type: application/json');
        echo json_encode(['status' => 'missing_parameters']);
    }
}
?>