import csv
import multiprocessing
import os
import subprocess
from concurrent.futures import ProcessPoolExecutor
from functools import partial
import matplotlib
import pandas as pd

matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np


def readFile(output_dir):
    stats_file = os.path.join(output_dir, 'stats.txt')
    if not os.path.exists(stats_file):
        print(f"Stats file {stats_file} not found!")
        return None

    try:
        with open(stats_file, 'r') as f:
            stats_text = f.read()
    except IOError as e:
        print(f"Error reading stats file: {e}")
        return None

    # List of parameters to read from the stats file
    params = [
        "simSeconds",
        "simFreq",
        "simInsts",
        "simOps",
        "system.l2.overallMissRate::cpu.inst",
        "system.l2.overallMissRate::cpu.data",
        "system.l2.overallMissRate::total"
    ]

    results = parse_simulation_statistics(stats_text, params)
    return list(results.values())  # returning as list for use in run_test


def parse_simulation_statistics(input_text, params):
    results = {}
    for param in params:
        pattern = rf"^{param}\s+(\S+)"
        match = re.search(pattern, input_text, re.MULTILINE)
        if match:
            results[param] = match.group(1)
        else:
            results[param] = None
    return results


def run_policy(policy, benchmark):
    output_dir = f"m5out/{benchmark}_{policy}"
    os.makedirs(output_dir, exist_ok=True)
    cmd = [
        "./build/X86/gem5.opt", "configs/deprecated/example/se.py",
        "-c", benchmark,
        "--caches", "--l2cache", "--l2_size=4kB", "--mem-type=DDR4_2400_16x4",
        "--cacheline_size", "32", "--l2_repl", policy,
        "--outdir", output_dir
    ]
    subprocess.run(cmd)
    return readFile(output_dir)  # return list of cache parameters


def run_test(testBench):
    executor2 = multiprocessing.Pool()
    res = executor2.map(partial(run_policy, benchmark=testBench), policy_list)

    res_transpose = [[res[i][j] for i in range(policy_number)] for j in range(parametr_number)]

    for i in range(1, parametr_number):
        plt.subplot(2, parametr_number // 2, i)
        plt.plot(res_transpose[0], res_transpose[i])
        plt.title(parametr_list[i])

    plt.subplots_adjust(wspace=0.5, hspace=0.5)
    plt.suptitle(testBench)
    plt.savefig(testBench + ".jpg")

    res_list = []
    for r in res:
        t = [testBench]
        t.extend(r)
        res_list.append(t)

    return res_list


testBench_list = ["ben1", "ben2", "ben3", "ben4",
                  "ben5", "ben6", "ben7", "ben8",
                  "ben9", "ben0"]

policy_list = ["LRU", "FIFO", "OPT", "LIFO" , "RandomRP"]

parametr_list = [
        "simSeconds",
        "simFreq",
        "simInsts",
        "simOps",
        "system.l2.overallMissRate::cpu.inst",
        "system.l2.overallMissRate::cpu.data",
        "system.l2.overallMissRate::total"
    ]

policy_number = 4  # Update to the correct number of policies
test_number = 10
parametr_number = 6

filename = "simulate_result.csv"


def main():
    executor = ProcessPoolExecutor()
    results = executor.map(run_test, testBench_list)
    fields = ["test_bench"]
    fields.extend(parametr_list)
    with open(filename, 'w') as csvfile:
        csvwriter = csv.writer(csvfile)
        csvwriter.writerow(fields)
        for result in results:
            csvwriter.writerows(result)


if __name__ == '__main__':
    main()
