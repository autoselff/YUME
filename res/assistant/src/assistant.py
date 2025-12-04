import os

current_dir = os.path.dirname(os.path.abspath(__file__))
proj_dir = os.path.abspath(os.path.join(current_dir, '../../../../../'))

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
    print("The YUME Assistant is a built-in helper whose task is to make many tedious things easier and faster.")

    print(f'[assistant] current direction - {current_dir}')
    print(f'[assistant] project direction - {proj_dir}')

    if not os.path.exists(proj_dir):
        print(f"Directory {proj_dir} does not exist.")
    else:
        print("Scanning dir: ", proj_dir)
        print(f"Counting complete. Grand total: {count_project_lines(proj_dir)} lines.")
