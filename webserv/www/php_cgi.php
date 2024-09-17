<?php
	if ($_SERVER['REQUEST_METHOD'] == 'POST') {
		header("Location: " . $_SERVER['PHP_SELF']);
		$input = fgets(STDIN);

		parse_str($input, $output);
		if (isset($output['fname']) && isset($output['lname'])) {
			$fname = $output['fname'];
			$lname = $output['lname'];

			$file = './www/user_data.txt';
			$current = file_get_contents($file);

			// Append new data to the file
			$current .= "First Name: $fname, Last Name: $lname\n";

			// Write contents back to the file
			file_put_contents($file, $current);
			echo '<!DOCTYPE html><html>';
			echo '<head><link rel="icon" type="image/x-icon" href="images/favicon.ico"><link rel="stylesheet" type="text/css" href="css/pat.css"></head>';
			echo '<body><div class="pat"><h1>Success!</h1><p>First Name: ' . $fname . ', Last Name: ' . $lname . '</p></div>';
			echo '<button onclick="window.location.href=\'index.html\';">Go Back</button>';
			echo '</body></html>';
			exit();
		}
	} elseif ($_SERVER['REQUEST_METHOD'] == 'GET') {
		$file = './www/user_data.txt';

		// If the file exists, display its contents
		if (file_exists($file)) {
			$contents = file_get_contents($file);
			echo '<!DOCTYPE html><html>';
			echo '<head><link rel="icon" type="image/x-icon" href="images/favicon.ico"><link rel="stylesheet" type="text/css" href="css/user.css"></head>';
			echo '<body><h1>User Data:</h1><p><div class="data">';
			echo nl2br($contents);
			echo '</div><br><button onclick="window.history.go(-1); return false;">Go Back</button><br><img class="barbie" src="images/BarbieOnWheels.png">';
			echo "</p></body></html>";
		}
	} elseif ($_SERVER['REQUEST_METHOD'] == 'DELETE') {
		$file = './www/user_data.txt';
		if (file_exists($file)) {
			$lines = file($file);
			array_pop($lines); // remove the last line
			file_put_contents($file, $lines);

			// Redirect back to the script + ratio
			echo '<!DOCTYPE html><html><head><link rel="icon" type="image/x-icon" href="images/favicon.ico"></head>';
			echo '<body><h1>Success!</h1><p>Last User deleted</p>';
			echo '<button onclick="window.location.href=\'index.html\';">Go Back</button></html>';
			exit();
		}
	}
?>