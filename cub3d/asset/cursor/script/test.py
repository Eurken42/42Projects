import os
from PIL import Image

# Charger l'image
img = Image.open("test_cursor.png")
# Boucle pour créer les images rotatées
for i in range(360):
    rotated = img.rotate(-i)
    filename = "{}_cursor.png".format(i)
    rotated.save(filename)

