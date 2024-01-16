import csv
import subprocess

csv_file = "./test-gen-accuracy.csv"

count = 0

passed = 0
failed = 0

total = 6596

with open(csv_file, newline="") as file:
    reader = csv.reader(file)

    for row in reader:
        bash_command = f"./runme {row[3]}"

        try:
            result = subprocess.run(
                bash_command,
                shell=True,
                stdout=subprocess.PIPE,
                text=True,
                check=False,
                timeout=60,
            )
        except subprocess.TimeoutExpired:
            total -= 1
            print("HANGS")
            print("--------------")
            continue

        output = result.stdout

        count += 1

        accuracy = abs(float(output) - float(row[4]))

        if accuracy < 0.0001:
            print(f"{count}/{total}: PASS")
            print("--------------")
            passed += 1
        else:
            failed += 1
            print("FAIL")
            print("--------------")

        
        row = [row[0], row[1], row[2], row[3], row[4], float(output), accuracy]

        with open("accuracy-results.csv", "a", newline="") as csv_file:
            csv_writer = csv.writer(csv_file)
            csv_writer.writerow(row)

print(f"Pass percentage: {round((passed/count)*100, 2)}%")
