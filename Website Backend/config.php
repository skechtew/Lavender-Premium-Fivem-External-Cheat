<?php
function getApiKeyDetails($apiKey) {
    $conn = new mysqli('localhost', '', '', '');
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }
    $stmt = $conn->prepare("SELECT expire_at, hwid, ban, clan FROM api_keys WHERE api_key = ?");
    $stmt->bind_param("s", $apiKey);
    $stmt->execute();
    $stmt->bind_result($expireAt, $hwid, $ban, $clan);
    $stmt->fetch();
    $stmt->close();
    $conn->close();

    if ($expireAt) {
        return [
            'valid' => $expireAt > time(), 
            'expire_at' => $expireAt,
            'hwid' => $hwid,
            'ban' => $ban,
            'clan' => $clan
        ];
    } else {
        return [
            'valid' => false, 
            'expire_at' => null,
            'hwid' => null,
            'ban' => null,
            'clan' => null
        ];
    }
}

function createApiKey($apiKey, $clan, $expiryDays) {
    $conn = new mysqli('localhost', '', '', '');
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $stmt = $conn->prepare("SELECT COUNT(*) FROM api_keys WHERE api_key = ?");
    $stmt->bind_param("s", $apiKey);
    $stmt->execute();
    $stmt->bind_result($count);
    $stmt->fetch();
    $stmt->close();

    if ($count > 0) {
        $conn->close();
        return ['status' => 'exists'];
    }

    $expireAt = time() + ($expiryDays * 86400);
    $stmt = $conn->prepare("INSERT INTO api_keys (api_key, expire_at, hwid, ban, clan) VALUES (?, ?, '', false, ?)");
    $stmt->bind_param("sis", $apiKey, $expireAt, $clan);
    $success = $stmt->execute();
    $stmt->close();
    $conn->close();
    return ['status' => $success ? 'created' : 'error'];
}

function deleteApiKey($apiKey) {
    $conn = new mysqli('localhost', '', '', '');
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }
    $stmt = $conn->prepare("DELETE FROM api_keys WHERE api_key = ?");
    $stmt->bind_param("s", $apiKey);
    $success = $stmt->execute();
    $stmt->close();
    $conn->close();
    return $success;
}

function resetHwid($apiKey) {
    $conn = new mysqli('localhost', '', '', '');
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $stmt = $conn->prepare("UPDATE api_keys SET hwid = '' WHERE api_key = ?");
    $stmt->bind_param("s", $apiKey);
    $success = $stmt->execute();
    $stmt->close();
    $conn->close();

    return $success;
}

function banHwid($hwid) {
    $conn = new mysqli('localhost', '', '', '');
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $stmt = $conn->prepare("SELECT ban FROM api_keys WHERE hwid = ?");
    $stmt->bind_param("s", $hwid);
    $stmt->execute();
    $stmt->bind_result($ban);
    $stmt->fetch();
    $stmt->close();

    if ($ban) {
        $conn->close();
        return ['status' => 'already_banned'];
    }

    $stmt = $conn->prepare("UPDATE api_keys SET ban = TRUE WHERE hwid = ?");
    $stmt->bind_param("s", $hwid);
    $success = $stmt->execute();
    $stmt->close();
    $conn->close();
    return ['status' => $success ? 'banned' : 'error'];
}

function unbanHwid($hwid) {
    $conn = new mysqli('localhost', '', '', '');
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $stmt = $conn->prepare("SELECT ban FROM api_keys WHERE hwid = ?");
    $stmt->bind_param("s", $hwid);
    $stmt->execute();
    $stmt->bind_result($ban);
    $stmt->fetch();
    $stmt->close();

    if (!$ban) {
        $conn->close();
        return ['status' => 'not_banned'];
    }

    $stmt = $conn->prepare("UPDATE api_keys SET ban = FALSE WHERE hwid = ?");
    $stmt->bind_param("s", $hwid);
    $success = $stmt->execute();
    $stmt->close();
    $conn->close();
    return ['status' => $success ? 'unbanned' : 'error'];
}

function updateKey($apiKey, $extraDays, $removeDays) {
    $conn = new mysqli('localhost', '', '', '');
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $apiKeyDetails = getApiKeyDetails($apiKey);
    if (!$apiKeyDetails['valid']) {
        return ['status' => 'invalid_key'];
    }

    $expireAt = $apiKeyDetails['expire_at'];
    if ($extraDays) {
        $expireAt += $extraDays * 86400;
    }
    if ($removeDays) {
        $expireAt -= $removeDays * 86400;
    }

    $stmt = $conn->prepare("UPDATE api_keys SET expire_at = ? WHERE api_key = ?");
    $stmt->bind_param("is", $expireAt, $apiKey);
    $success = $stmt->execute();
    $stmt->close();
    $conn->close();

    return ['status' => $success ? 'updated' : 'error'];
}

function getAllApiKeys() {
    $conn = new mysqli('localhost', '', '', '');
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $stmt = $conn->prepare("SELECT api_key, expire_at, hwid, ban, clan FROM api_keys");
    if (!$stmt->execute()) {
        return ['status' => 'error', 'message' => 'Failed to execute query'];
    }
    $result = $stmt->get_result();
    $keys = [];
    while ($row = $result->fetch_assoc()) {
        $keys[] = $row;
    }
    $stmt->close();
    $conn->close();
    return ['status' => 'success', 'keys' => $keys];
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $action = $_POST['action'];
    $apiKey = isset($_POST['key']) ? $_POST['key'] : null;

    if ($action === 'check') {
        $apiKeyDetails = getApiKeyDetails($apiKey);
        if ($apiKeyDetails['valid']) {
            echo json_encode(['status' => 'valid', 'expire_at' => date('Y-m-d', $apiKeyDetails['expire_at']), 'hwid' => $apiKeyDetails['hwid'], 'ban' => $apiKeyDetails['ban'], 'clan' => $apiKeyDetails['clan']]);
        } else {
            echo json_encode(['status' => 'invalid', 'expire_at' => $apiKeyDetails['expire_at'] ? date('Y-m-d', $apiKeyDetails['expire_at']) : null, 'hwid' => $apiKeyDetails['hwid'], 'ban' => $apiKeyDetails['ban'], 'clan' => $apiKeyDetails['clan']]);
        }
    } elseif ($action === 'create') {
        $expiryDays = $_POST['expiry_days'];
        $clan = $_POST['clan'];
        $result = createApiKey($apiKey, $clan, $expiryDays);
        echo json_encode(['status' => $result['status']]);
    } elseif ($action === 'delete') {
        $success = deleteApiKey($apiKey);
        echo json_encode(['status' => $success ? 'deleted' : 'error']);
    } elseif ($action === 'reset_hwid') {
        $success = resetHwid($apiKey);
        echo json_encode(['status' => $success ? 'reset' : 'error']);
    } elseif ($action === 'ban_hwid') {
        $hwid = $_POST['hwid'];
        $result = banHwid($hwid);
        echo json_encode(['status' => $result['status']]);
    } elseif ($action === 'unban_hwid') {
        $hwid = $_POST['hwid'];
        $result = unbanHwid($hwid);
        echo json_encode(['status' => $result['status']]);
    } elseif ($action === 'update') {
        $extraDays = isset($_POST['extra_days']) ? $_POST['extra_days'] : 0;
        $removeDays = isset($_POST['remove_days']) ? $_POST['remove_days'] : 0;
        $result = updateKey($apiKey, $extraDays, $removeDays);
        echo json_encode(['status' => $result['status']]);
    } elseif ($action === 'get_keys') {
        $result = getAllApiKeys();
        if ($result['status'] === 'success') {
            echo json_encode(['keys' => $result['keys']]);
        } else {
            echo json_encode(['status' => 'error', 'message' => $result['message']]);
        }
    }
}

function encrypt($key,$iv,$data) {
    $method = 'AES-128-CBC';
    $ivsize = openssl_cipher_iv_length($method);
    $en = openssl_encrypt($data,$method,$key,OPENSSL_RAW_DATA,$iv);
    return base64_encode($en);        
}

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    if (isset($_GET['api_key'])) {
        $apiKey = $_GET['api_key'];
        $apiKeyDetails = getApiKeyDetails($apiKey);

        header('Access-Control-Allow-Origin: *');
        header('Content-type: application/json');
        if (!$apiKeyDetails['expire_at']) {
            echo encrypt("yaladediyalama","aaaaaaaaaaaaaaaa","Key yok");
        } elseif (!$apiKeyDetails['valid']) {
            echo encrypt("yaladediyalama","aaaaaaaaaaaaaaaa","Key zaman yok");
        } else {
            echo encrypt("yaladediyalama","aaaaaaaaaaaaaaaa",json_encode([
                'expireEpoch' => $apiKeyDetails['expire_at'],
                'hwid' => $apiKeyDetails['hwid'],
                'ban' => $apiKeyDetails['ban'],
                'clan' => $apiKeyDetails['clan']
            ]));
        }
    } else {
        echo json_encode(['message' => 'API key parametresi eksik.']);
    }
}
?>
