import csv
import subprocess

csv_file = "./testing/test_cases.csv"

count = 1

with open(csv_file, newline="") as file:
    reader = csv.reader(file)
    
    for row in reader:
        if(int(row[0]) > 40):
            continue
        if(row[2] == "intrel"):
            continue
        # if(int(row[0]) > 20 and row[2] == "intrel"):
        #     continue

        #print(row[3])
        bash_command = f"hyperfine --max-runs 10 --export-csv result.csv './runme {row[3]}'"
        #print(bash_command)

        try:
            # Running the bash command
            result = subprocess.run(
                bash_command, shell=True, stdout=subprocess.PIPE, text=True, check=False, timeout=30
            )
        except subprocess.TimeoutExpired:
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