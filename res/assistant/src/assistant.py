import AILib as AL
import AIDataReader as AIdr

import os

proj_dir = r'C:\Users\mydat\Documents\YUME' # HERE YOU CAN PAST A PATH TO YOUR PROJECT DIRECTORY

def count_project_lines(path):
    INCLUDED_FORMATS = ('.txt', '.cpp', '.h', '.py')
    EXCLUDED_DIRS = {'deps', 'glfw', 'glm'}

    lines_counter = 0
    files_line_counts = {}

    try:
        for root, dirs, files in os.walk(path):
            dirs[:] = [d for d in dirs if d not in EXCLUDED_DIRS]

            for file_name in files:
                if file_name.endswith(INCLUDED_FORMATS):
                    file_path = os.path.join(root, file_name)
                    try:
                        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                            lines = f.readlines()
                            line_count = len(lines)
                            lines_counter += line_count
                            print(f"{file_path}: {line_count} lines")
                            files_line_counts[file_path] = line_count
                    except IOError as e:
                        print(f"Could not read file {file_path}: {e}")
                    except Exception as e:
                        print(f"An unexpected error occurred with file {file_path}: {e}")
    except Exception as e:
        print(f"An error occurred while walking through directory {path}: {e}")
    return lines_counter


if __name__ == "__main__":

    print("The Assistant is a built-in helper whose task is to make many tedious things easier and faster.")
    print("It is also responsible for AILib support, although this is still in the development stage.")

    B = 6
    D = 0.01
    A = 0

    xtrain: list = []
    answers: list = []

    reader = AIdr.AIDataReader('data/aidata.txt')

    AL.GEN_2VAL_LISTS_ANSWERS(200, xtrain, answers)
    print(xtrain)
    print(answers)

    neuron_w = [-2, 0.1]
    n1 = AL.Neuron([1, 0], neuron_w, False, True)
    mode = AL.Mode(False, 0, A, n1.nreturn)

    print("AIlib is the YUME AI system, made from scratch without any external libraries.")
    print("AIlib does not collect or send your data, and it is currently under development.")
    print("AIlib does not affect engine efficiency, but in the future, it will only improve it.")

    for i in range(0, len(xtrain)):
        n1 = AL.Neuron(xtrain[i], neuron_w, bool(answers[i]), not bool(answers[i]))
        n1.TRAIN_NEURON(A, B, D, mode)
        neuron_w = n1.w

    print("scanning dir: ", proj_dir)
    print(f"Counting complete. Grand total: {count_project_lines(proj_dir)} lines.")
    print()