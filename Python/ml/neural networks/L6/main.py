import os
import zipfile
import importlib.util
from datetime import datetime
import CNN_Xception_tensorflow
def ConvertTimeDelta(duration):
	days, seconds = duration.days, duration.seconds
	hours = days * 24 + seconds // 3600
	minutes = (seconds % 3600) // 60
	seconds = (seconds % 60)
	return str(hours), str(minutes), str(seconds)
def main():
	print("----------Xception TENSORFLOW convolutional neural network----------")
	CNN_Xception_tensorflow.train()
	CNN_Xception_tensorflow.evaluate('Xception_Logo-2K_tensorflow_12_epochs.keras')
	CNN_Xception_tensorflow.detect_logos_in_video('video3.mp4', 'Xception_Logo-2K_tensorflow_12_epochs.keras')
if __name__ == "__main__":
	main()