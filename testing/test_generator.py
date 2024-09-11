import csv
from fpylll import IntegerMatrix, SVP, FPLLL
from random import randint, seed
from itertools import product

seed(1234)
FPLLL.set_random_seed(1234)

# bits = [8, 16, 32, 64]
bits = [8, 16, 32]

types = [
    "uniform",
    "intrel",
    # "ntrulike",
    # "ntrulike2",
]

dims_x_counts = [
    (1, 100),
    (2, 100),
    (3, 100),
    (4, 100),
    (5, 100),
    (6, 100),
    (7, 100),
    (8, 100),
    (9, 100),
    (10, 100),
    (11, 10),
    (12, 10),
    (13, 10),
    (14, 10),
    (15, 10),
    (16, 10),
    (17, 10),
    (18, 10),
    (19, 10),
    (20, 10),
]

total_count = len(bits) * len(types) * sum(x[1] for x in dims_x_counts)
current_count = 0

for b, (d, c), t in product(bits, dims_x_counts, types):
    for i in range(c):
        if d == 1:
            n = randint(-(2**b), 2**b)
            mat_str = f"[{n}]"
            norm = n
        else:
            mat = IntegerMatrix(d, d + 1 if t == "intrel" else d)
            mat.randomize(t, bits=b)
            mat.resize(d, d)

            mat_str = " ".join([f"[{' '.join(str(m) + '.0' for m in l)}]" for l in mat])

            # print(mat_str)

            try:
                SVP.shortest_vector(mat)
            except:
                continue

            norm = mat[0].norm()

        norm_str = str(abs(norm))
        current_count += 1
        print(
            f"{current_count}/{total_count}\t({round(current_count/total_count, 2)})\t|\tbits: {b}\tdim: {d}\tcount: {i+1}/{c}\t{t}"
        )

        row = [d, b, t, mat_str, norm_str]

        with open("test.csv", "a", newline="") as csv_file:
            # Create a CSV writer
            csv_writer = csv.writer(csv_file)

            # Append the new data as a new row
            csv_writer.writerow(row)
