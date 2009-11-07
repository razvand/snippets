<?php
	$ip = $_SERVER['REMOTE_ADDR']
	echo "IP address is $ip<br />"

	$fp = fopen('log.txt', 'a+') or die("Can't open file log.txt");

	$result = fwrite($fileHandle, "IP: $ip Name: Gogu de la gaze");

	if ($result) {
		echo "Data written successfully.<br />";
	} else {
		echo "Data write failed.<br />";
	}

	fclose($fileHandle);
?>
