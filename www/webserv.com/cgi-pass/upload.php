<?php
$target_dir = "upload/";
$target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
  echo "Le fichier ". htmlspecialchars(basename($_FILES["fileToUpload"]["name"])). " a été uploadé.";
} else {
  echo "Erreur lors de l'upload du fichier.";
}
?>