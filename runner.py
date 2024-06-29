import csv
import os
import subprocess
import matplotlib
import re

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
    return results

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
    output_dir = f"./m5out"
    os.makedirs(output_dir, exist_ok=True)
    cmd = [
        "./build/X86/gem5.opt", "configs/deprecated/example/se.py",
        "-c", benchmark,
        "--caches", "--l2cache", "--l2_size=4kB", "--mem-type=DDR4_2400_16x4",
        "--cacheline_size", "128", "--l2_repl", policy,
    ]

    try:
        subprocess.run(cmd, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Simulation for {benchmark} with policy {policy} failed: {e}")
        return None

    return readFile(output_dir)

def run_test(testBench):
    results = []

    for policy in policy_list:
        res = run_policy(policy, testBench)
        if res:
            t = [testBench, policy]
            t.extend(res.values())
            results.append(t)

    if results:
        res_transpose = [[r[i] for r in results] for i in range(len(results[0]))]
        for i in range(2, len(parameter_list) + 2):
            plt.subplot(2, (len(parameter_list) + 1) // 2, i - 1)
            plt.plot(policy_list, res_transpose[i], marker='o')
            plt.title(parameter_list[i - 2])

        plt.subplots_adjust(wspace=0.5, hspace=0.5)
        plt.suptitle(testBench)
        plt.savefig(testBench + ".jpg")
        plt.clf()  # Clear the current figure for the next plot

    return results

testBench_list =["ben2"]
# ["ben0", "ben1", "ben2", "ben3", "ben4", "ben5", "ben6", "ben7", "ben8", "ben9"]
policy_list = ["OPTRP", "LRURP", "LFURP", "RandomRP" , "FIFORP"]
parameter_list = [
    "simSeconds",
    "simFreq", 
    "simInsts",
    "simOps",
    "system.l2.overallMissRate::cpu.inst",
    "system.l2.overallMissRate::cpu.data",
    "system.l2.overallMissRate::total"
]
filename = "simulate_result.csv"

def main():
    all_results = []

    for testBench in testBench_list:
        results = run_test(testBench)
        all_results.extend(results)

    fields = ["test_bench", "policy"]
    fields.extend(parameter_list)
    with open(filename, 'w', newline='') as csvfile:
        csvwriter = csv.writer(csvfile)
        csvwriter.writerow(fields)
        csvwriter.writerows(all_results)

if __name__ == '__main__':
    main()

