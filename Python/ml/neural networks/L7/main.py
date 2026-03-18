import os
import zipfile
import importlib.util
from datetime import datetime
import LSTM_YelpReviewPolarity_tf
import Custom_LSTM_YelpReviewPolarity_tf
def main():
	sample_texts = [
		"This restaurant was amazing! The food was delicious and the service was outstanding.",
		"Terrible experience. The staff was rude and the food was cold.",
		"It was okay. Nothing special but nothing terrible either.",
		"I've been coming here for years and have never been disappointed. Highly recommend!",
		"Wouldn't go back if you paid me. Worst meal I've had in a long time."]
	print("----------LSTM TENSORFLOW recurrent neural network----------")
	# LSTM_YelpReviewPolarity_tf.train()
	LSTM_YelpReviewPolarity_tf.evaluate('LSTM_YelpReviewPolarity_tf_10_epochs.keras')
	LSTM_YelpReviewPolarity_tf.predict('LSTM_YelpReviewPolarity_tf_10_epochs.keras', sample_texts)
	# print("----------Custom LSTM TENSORFLOW recurrent neural network----------")
	# Custom_LSTM_YelpReviewPolarity_tf.train()
	# Custom_LSTM_YelpReviewPolarity_tf.evaluate('Custom_LSTM_YelpReviewPolarity_tf_10_epochs.keras')
	# Custom_LSTM_YelpReviewPolarity_tf.predict('Custom_LSTM_YelpReviewPolarity_tf_10_epochs.keras', sample_texts)
if __name__ == "__main__":
	main()