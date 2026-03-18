import os
import random
import shutil
from pathlib import Path
import argparse
def split_dataset(dataset_path, train_path, val_path, test_path, train_ratio=0.7, val_ratio=0.15, test_ratio=0.15):
    if not abs(train_ratio + val_ratio + test_ratio - 1.0) < 1e-10:
        raise ValueError("Train, validation, and test ratios must sum to 1.0")
    random.seed(42)    
    os.makedirs(train_path, exist_ok=True)
    os.makedirs(val_path, exist_ok=True)
    os.makedirs(test_path, exist_ok=True)
    class_folders = [f for f in os.listdir(dataset_path) 
                    if os.path.isdir(os.path.join(dataset_path, f))]
    for class_name in class_folders:
        print('{:<{}}'.format(class_name,37),end="",sep='',flush=True)
        os.makedirs(os.path.join(train_path, class_name), exist_ok=True)
        os.makedirs(os.path.join(val_path, class_name), exist_ok=True)
        os.makedirs(os.path.join(test_path, class_name), exist_ok=True)
        class_path = os.path.join(dataset_path, class_name)
        image_files = [f for f in os.listdir(class_path) 
                      if os.path.isfile(os.path.join(class_path, f)) and 
                      f.lower().endswith(('.png', '.jpg', '.jpeg', '.bmp', '.gif'))]
        random.shuffle(image_files)
        total_images = len(image_files)
        train_end = int(total_images * train_ratio)
        val_end = train_end + int(total_images * val_ratio)
        train_files = image_files[:train_end]
        val_files = image_files[train_end:val_end]
        test_files = image_files[val_end:]
        for file_name in train_files:
            shutil.copy2(
                os.path.join(class_path, file_name),
                os.path.join(train_path, class_name, file_name))        
        for file_name in val_files:
            shutil.copy2(
                os.path.join(class_path, file_name),
                os.path.join(val_path, class_name, file_name))        
        for file_name in test_files:
            shutil.copy2(
                os.path.join(class_path, file_name),
                os.path.join(test_path, class_name, file_name))
        print(" train: ",len(train_files),"; validation: ",len(val_files),"; test: ",len(test_files))
    print("\nDataset splitting complete!")
    print("Train data: ",f"{train_ratio*100:.2f}%")
    print("Validation data: ",f"{val_ratio*100:.2f}%")
    print("Test data: ",f"{test_ratio*100:.2f}%")