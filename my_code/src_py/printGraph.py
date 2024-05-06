'''
Description: 
Author: Bohan Wang
Date: 2024-05-04 15:58:03
LastEditTime: 2024-05-04 16:15:51
LastEditors:  
'''
import matplotlib.pyplot as plt
import numpy as np

def read_coordinates_from_file(filename):
    x_coords = []
    y_coords = []

    try:
        with open(filename, 'r') as file:
            lines = file.readlines()
            if len(lines) < 2:
                print("Error: File does not contain enough data.")
                return None, None

            x_str = lines[0].strip()  # 第一行为横坐标数据
            y_str = lines[1].strip()  # 第二行为纵坐标数据

            x_coords = [int(x) for x in x_str.split(',')]  # 解析横坐标数据
            y_coords = []  # 存储解析后的纵坐标数据
            for line in y_str.split('\n'):  # 按回车分隔纵坐标数据
                if line.strip():  # 忽略空行
                    y_coords.extend([int(y) for y in line.strip().split(',')])  # 解析纵坐标数据

    except FileNotFoundError:
        print(f"Error: File '{filename}' not found.")
        return None, None
    except Exception as e:
        print(f"An error occurred: {e}")
        return None, None

    return x_coords, y_coords

def plot_points(x_coords, y_coords):
    if x_coords is None or y_coords is None:
        return
    
    plt.figure(figsize=(12, 8))
    plt.scatter(x_coords, y_coords, color='blue', marker='o', label='Points', s=20)  # 设置点的大小为20
    plt.title('Scatter Plot of Points')
    plt.xlabel('X Axis')
    plt.ylabel('Y Axis')
    plt.legend()
    plt.grid(True)

    plt.show()

def main():
    filename = 'new.txt'  # 请替换为你的文本文件路径

    # 从文本文件中读取坐标数据
    x_coords, y_coords = read_coordinates_from_file(filename)
    for i in range(20):
        print(x_coords[i])
        print(y_coords[i])
    # 绘制坐标点
    plot_points(x_coords, y_coords)

if __name__ == "__main__":
    main()
