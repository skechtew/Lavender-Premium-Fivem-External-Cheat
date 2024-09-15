<?php
function banApiKey($apiKey, $ban) {
    $conn = new mysqli('localhost', '', '', '');
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }


    $stmt = $conn->prepare("SELECT COUNT(*) FROM api_keys WHERE hwid = ?");
    $stmt->bind_param("s", $apiKey);
    $stmt->execute();
    $stmt->bind_result($count);
    $stmt->fetch();
    $stmt->close();

    if ($count == 0) {
        $conn->close();
        return ['status' => 'key_not_found'];
    }

 
    $stmt = $conn->prepare("UPDATE api_keys SET ban = ? WHERE hwid = ?");
    $stmt->bind_param("is", $ban, $apiKey);
    $success = $stmt->execute();
    $stmt->close();

    if ($success) {

        $stmt = $conn->prepare("SELECT api_key, expire_at, hwid, ban FROM api_keys WHERE hwid = ?");
        $stmt->bind_param("s", $apiKey);
        $stmt->execute();
        $stmt->bind_result($apiKey, $expireAt, $hwid, $ban);
        $stmt->fetch();
        $stmt->close();
        $conn->close();

        return [
            'status' => 'success',
            'api_key' => $apiKey,
            'expire_at' => date('Y-m-d H:i:s', $expireAt),
            'hwid' => $hwid,
            'ban' => $ban
        ];
    } else {
        $conn->close();
        return ['status' => 'error'];
    }
}

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    if (isset($_GET['hwid']) && isset($_GET['ban'])) {
        $apiKey = $_GET['hwid'];
        $ban = (int)$_GET['ban'];
        $result = banApiKey($apiKey, $ban);
        echo json_encode($result);
    } else {
        echo json_encode(['status' => 'error', 'message' => 'API key or ban parameter is missing']);
    }
}
?>