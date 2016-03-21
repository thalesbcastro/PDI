# Carrega e mostra a imagem
import cv2
img = cv2.imread("biel.png")
crop_img1 = img[0:200, 200:0] # Crop from x, y, w, h -> 100, 200, 300, 400
crop_img2 = img[200:0, 0:200]
# somando as imagens
res = crop_img1 + crop_img2
# NOTE: its img[y: y + h, x: x + w] and *not* img[x: x + w, y: y + h]
cv2.imshow("cropped", res)
cv2.waitKey(0)
