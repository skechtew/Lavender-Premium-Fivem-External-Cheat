<?php
$servername = "localhost";
$username = ""; 
$password = ""; 
$dbname = ""; 


$conn = new mysqli($servername, $username, $password, $dbname);


if ($conn->connect_error) {
    die("Bağlantı hatası: " . $conn->connect_error);
}
function encrypt($key,$iv,$data) {
    $method = 'AES-128-CBC';
    $ivsize = openssl_cipher_iv_length($method);
    $en = openssl_encrypt($data,$method,$key,OPENSSL_RAW_DATA,$iv);
    return base64_encode($en);        
}

if (isset($_GET['lastversion'])) {
    $lastversion = $_GET['lastversion'];

   
    $sql = "SELECT * FROM lastversion WHERE version = ?";
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("s", $lastversion);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows > 0) {
        
        echo encrypt("yaladediyalama","aaaaaaaaaaaaaaaa","ID var");
    } else {
       
        $sql = "INSERT INTO lastversion (version) VALUES (?)";
        $stmt = $conn->prepare($sql);
        $stmt->bind_param("s", $lastversion);

        if ($stmt->execute()) {
            echo encrypt("yaladediyalama","aaaaaaaaaaaaaaaa","ID eklendi");
        } else {
            echo "Hata: " . $stmt->error;
        }
    }

    $stmt->close();
} else {
    echo "lastversion parametresi belirtilmemiş.";
}

$conn->close();
?>
