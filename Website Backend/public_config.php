<?php
include ("variables.php");

function encrypt($key,$iv,$data) {
    $method = 'AES-128-CBC';
    $ivsize = openssl_cipher_iv_length($method);
    $en = openssl_encrypt($data,$method,$key,OPENSSL_RAW_DATA,$iv);
    return base64_encode($en);        
}

function checkKeyClan($apiKey) {
    global $worldOffet_b2545, $viewmatrixOffset_b2545, $worldOffet_b2699, $viewmatrixOffset_b2699;
    global $worldOffet_GTAProcess, $viewmatrixOffset_GTAProcess, $worldOffet_b2060, $viewmatrixOffset_b2060;
    global $worldOffet_b2372, $viewmatrixOffset_b2372, $worldOffet_b2612, $viewmatrixOffset_b2612;
    global $worldOffet_b2189, $viewmatrixOffset_b2189, $worldOffet_b2802, $viewmatrixOffset_b2802;
    global $worldOffet_b2944, $viewmatrixOffset_b2944;
    global $worldOffet_b3095, $viewmatrixOffset_b3095;

    $conn = new mysqli('localhost', '', '', '');
    if ($conn->connect_error) {
        die("Bağlantı başarısız: " . $conn->connect_error);
    }

    $stmt = $conn->prepare("SELECT clan FROM api_keys WHERE api_key = ?");
    $stmt->bind_param("s", $apiKey);
    $stmt->execute();
    $stmt->bind_result($clan);
    $stmt->fetch();
    $stmt->close();
    $conn->close();
    
    $guncelEpoch = time();
    $encryptedResponse = encrypt($guncelEpoch,"aaaaaaaaaaaaaaaa",json_encode([
        'worldOffet_b2545' => $worldOffet_b2545, 'viewmatrixOffset_b2545' => $viewmatrixOffset_b2545, 
        'worldOffet_b2699' => $worldOffet_b2699, 'viewmatrixOffset_b2699' => $viewmatrixOffset_b2699, 
        'worldOffet_GTAProcess' => $worldOffet_GTAProcess, 'viewmatrixOffset_GTAProcess' => $viewmatrixOffset_GTAProcess, 
        'worldOffet_b2060' => $worldOffet_b2060, 'viewmatrixOffset_b2060' => $viewmatrixOffset_b2060, 
        'worldOffet_b2372' => $worldOffet_b2372, 'viewmatrixOffset_b2372' => $viewmatrixOffset_b2372, 
        'worldOffet_b2612' => $worldOffet_b2612, 'viewmatrixOffset_b2612' => $viewmatrixOffset_b2612, 
        'worldOffet_b2189' => $worldOffet_b2189, 'viewmatrixOffset_b2189' => $viewmatrixOffset_b2189, 
        'worldOffet_b2802' => $worldOffet_b2802, 'viewmatrixOffset_b2802' => $viewmatrixOffset_b2802, 
        'worldOffet_b2944' => $worldOffet_b2944, 'viewmatrixOffset_b2944' => $viewmatrixOffset_b2944,
        'worldOffet_b3095' => $worldOffet_b3095, 'viewmatrixOffset_b3095' => $viewmatrixOffset_b3095
        ]));
    if ($clan) {
        if ($clan == "public") {
            echo  $encryptedResponse . "&" . base64_encode($guncelEpoch);
        } else {
            echo encrypt($guncelEpoch,"aaaaaaaaaaaaaaaa","Malesef") . "&". base64_encode($guncelEpoch);
        }
    } else {
        echo encrypt($guncelEpoch,"aaaaaaaaaaaaaaaa","Malesef") . "&". base64_encode($guncelEpoch);
    }
}

if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    if (isset($_GET['key'])) {
        $apiKey = $_GET['key'];
        checkKeyClan($apiKey);
    } else {
        echo "API key parametresi eksik.";
    }
}
?>
