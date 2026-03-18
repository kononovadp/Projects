import os
import zipfile
import importlib.util
from datetime import datetime
import СNN_bi_LSTM_LJSpeech_tf
import Custom_СNN_bi_LSTM_LJSpeech_tf
def main():
	print("----------СNN-bi-LSTM TENSORFLOW----------")
	# СNN_bi_LSTM_LJSpeech_tf.train()
	СNN_bi_LSTM_LJSpeech_tf.eval_and_pred('СNN_bi_LSTM_LJSpeech_tf_10_epochs.keras')
	# print("----------Custom СNN-bi-LSTM TENSORFLOW----------")
	# Custom_СNN_bi_LSTM_LJSpeech_tf.train()
	# Custom_СNN_bi_LSTM_LJSpeech_tf.evaluate('Custom_СNN_bi_LSTM_LJSpeech_tf_10_epochs.keras')
	# Custom_СNN_bi_LSTM_LJSpeech_tf.speech_to_text('Custom_СNN_bi_LSTM_LJSpeech_tf_10_epochs.keras')
if __name__ == "__main__":
	main()