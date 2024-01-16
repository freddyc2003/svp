import csv
import subprocess

csv_file = "./test-gen.csv"

count = 1

timeout = 0

with open(csv_file, newline="") as file:
    reader = csv.reader(file)
    
    for row in reader:
        bash_command = f"hyperfine -N -u millisecond --max-runs 10 --export-csv result.csv './runme {row[3]}'"

        try:
            # Running the bash command
            result = subprocess.run(
                bash_command, shell=True, stdout=subprocess.PIPE, text=True, check=False, timeout=60
            )
        except subprocess.TimeoutExpired:
            timeout += 1
            with open("timeout.csv", "a", newline="") as hyperfine_results:
                csv_writer = csv.writer(hyperfine_results)

                csv_writer.writerow([row[1], row[2], row[3], row[4]])
            continue

        with open('result.csv', 'r') as result_file:
            result_reader = csv.reader(result_file)

            next(result_reader)

            for result_row in result_reader:
                new_row = [row[0], row[1], row[2], result_row[1], result_row[2]]

            print(new_row)

            with open("hyperfine_results.csv", "a", newline="") as hyperfine_results:
                csv_writer = csv.writer(hyperfine_results)

                csv_writer.writerow(new_row)
    
        print(f"{count}")

        count += 1

print(f"Timeout = {timeout}")
