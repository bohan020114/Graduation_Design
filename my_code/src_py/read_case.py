'''
Description: print mtx(in x,y)
Author: Bohan Wang
Date: 2024-05-04 13:37:53
LastEditTime: 2024-05-05 17:05:34
LastEditors:  
'''

def parse_line(line):
    # Split the line by whitespace
    parts = line.strip().split()
    if len(parts) != 2:
        return None, None, None, None, None

    metadata, value_str = parts[0], parts[1]
    metadata = metadata.strip('()').split(',')
    if len(metadata) != 4:
        return None, None, None, None, None

    try:
        # Extract values from metadata
        j = int(metadata[0].split(':')[1])
        jcol = int(metadata[1].split(':')[1])
        i = int(metadata[2].split(':')[1])
        irow = int(metadata[3].split(':')[1])
        value = float(value_str)
        return irow, jcol, j, i, value
    except (ValueError, IndexError):
        return None, None, None, None, None

def process_file(input_file):
    irow_values = []
    jcol_values = []
    j_values = []
    i_values = []
    values = []

    with open(input_file, 'r') as file:
        for line in file:
            irow, jcol, j, i, value = parse_line(line)
            set = 250
            if irow is not None and i < set and j < set:
                j_values.append(j)
                i_values.append(i)
                values.append(value)
            if irow is not None and irow < set and jcol < set:
                irow_values.append(irow)
                jcol_values.append(jcol)
                values.append(value)

    return irow_values, jcol_values, j_values, i_values, values


def write_to_file(filename, irow_values, jcol_values, j_values):
    with open(filename, 'w') as file:
        # Write irow values as the first line
        file.write(','.join(map(str, irow_values)) + '\n')

        # Write jcol values as the second line
        file.write(','.join(map(str, jcol_values)) + '\n')

        # Write j values as the third line
        # file.write(' '.join(map(str, j_values)) + '\n')

def main(input_file):
    irow_values, jcol_values, j_values, i_values, values = process_file(input_file)

    # 写入 old.txt
    write_to_file('old.txt', irow_values, jcol_values, values)

    # 写入 new.txt
    write_to_file('new.txt', i_values, j_values, values)

if __name__ == "__main__":
    input_file = '/home/parallels/Documents/design/banchmark-matrix0222/case1_1.txt'  # 请替换为实际的输入文件名
    main(input_file)
