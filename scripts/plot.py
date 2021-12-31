#!/bin/python3

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import sys
import json
import re
import os

plt.style.use('ggplot')


def build_dataframe(filename):
    # The benchmark may have been aborted. This is a quickfix/hack.
    fixed_json = ''
    print(f"Opening: {filename}")
    with open(filename, 'r') as reader:
        fixed_json = reader.read()
        if fixed_json.endswith("    }"):
            fixed_json += ']}'
        if fixed_json.endswith("[\n"):
            fixed_json += ']}'
        if "slurmstepd" in fixed_json:
            fixed_json = re.sub(r'slurmstepd.*$', ']}', fixed_json)

    j = json.loads(fixed_json)
    benchmark_json = j["benchmarks"]
    benchmark_json_str = json.dumps(benchmark_json)
    df = pd.read_json(path_or_buf=benchmark_json_str, orient='records')
    return df

def visualize():
    return

def main():
    print ("Number of arguments:", len(sys.argv) - 1, "arguments")
    print ("Argument List:", str(sys.argv[1:]))

    fig, ax = plt.subplots()
    for file in sys.argv[1:]:
        data = build_dataframe(file)
        ax.plot(data["Elements"], data["real_time"], label=file[:-5])

    ax.set_yscale("log", base=10)
    ax.set_xscale("log", base=2)
    plt.legend()
    plt.xlabel("Elements")
    plt.ylabel("real_time (ns)")
    plt.title("RealTime")
    plt.show()



if __name__ == "__main__":
    main()
