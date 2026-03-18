import os
import cv2
import numpy as np
import random

def add_scanlines(image, line_thickness=2, line_spacing=4, intensity=0.7):
    """Add horizontal scanlines effect"""
    output = image.copy()
    for y in range(0, image.shape[0], line_spacing):
        output[y:y+line_thickness, :] = (output[y:y+line_thickness, :] * intensity).astype(np.uint8)
    return output

def add_color_shift(image, max_shift=5):
    """Random color channel shift"""
    output = image.copy()
    h, w, c = image.shape
    shift = random.randint(-max_shift, max_shift)
    M = np.float32([[1, 0, shift], [0, 1, 0]])
    for i in range(c):
        output[:, :, i] = cv2.warpAffine(output[:, :, i], M, (w, h), borderMode=cv2.BORDER_REFLECT)
    return output

def add_noise(image, amount=0.03):
    """Add random white noise"""
    output = image.copy()
    noise = np.random.randint(0, 256, image.shape, dtype=np.uint8)
    mask = np.random.rand(*image.shape[:2]) < amount
    output[mask] = noise[mask]
    return output

def add_blur(image, max_kernel=5):
    """Random motion-like blur"""
    ksize = random.choice([1, 3, 5])  # odd kernel size
    if ksize > 1:
        return cv2.GaussianBlur(image, (ksize, ksize), 0)
    return image

def adjust_brightness_contrast(image, brightness=0, contrast=0):
    """Adjust brightness and contrast"""
    output = cv2.convertScaleAbs(image, alpha=1 + contrast/100, beta=brightness)
    return output

def add_band_noise(image, num_bands=3):
    """Add horizontal or vertical banding noise"""
    output = image.copy()
    h, w, _ = image.shape
    for _ in range(num_bands):
        y = random.randint(0, h-1)
        band_height = random.randint(1, 3)
        intensity = random.randint(-30, 30)
        output[y:y+band_height, :] = np.clip(output[y:y+band_height, :] + intensity, 0, 255)
    return output

def add_video_artifacts(image):
    """Apply full retro video artifact pipeline"""
    img = image.copy()
    img = add_scanlines(img)
    img = add_color_shift(img)
    img = add_noise(img, amount=0.02)
    img = add_blur(img)
    img = adjust_brightness_contrast(img, brightness=random.randint(-20, 20), contrast=random.randint(-15, 15))
    img = add_band_noise(img)
    return img

# Example Usage:
"""image = cv2.imread("frame_350.jpg")  # Your real no-logo frame
artifact_image = add_video_artifacts(image)

# Show results
cv2.imshow("Retro 1980s Artifact Image", artifact_image)
cv2.waitKey(0)
cv2.destroyAllWindows()"""
def main():
	file_names = os.listdir('debug')
	for file_name in file_names:
		image = cv2.imread('debug//'+file_name)
		artifact_image = add_video_artifacts(image)
		cv2.imwrite('retro_img//'+file_name, artifact_image)
cv2.destroyAllWindows()
if __name__ == "__main__":
	main()