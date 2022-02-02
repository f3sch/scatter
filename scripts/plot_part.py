#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import sys
import json
import re
import os
import copy

plt.style.use("ggplot")


def build_dataframe(filename):
    # The benchmark may have been aborted. This is a quickfix/hack.
    fixed_json = ""
    print(f"Opening: {filename}")
    with open(filename, "r") as reader:
        fixed_json = reader.read()
        if fixed_json.endswith("    }"):
            fixed_json += "]}"
        if fixed_json.endswith("[\n"):
            fixed_json += "]}"
        if "slurmstepd" in fixed_json:
            fixed_json = re.sub(r"slurmstepd.*$", "]}", fixed_json)

    j = json.loads(fixed_json)
    benchmark_json = j["benchmarks"]
    benchmark_json_str = json.dumps(benchmark_json)
    df = pd.read_json(path_or_buf=benchmark_json_str, orient="records")
    return df


def visualize():
    return


def main():
    print("Number of arguments:", len(sys.argv) - 1, "arguments")
    print("Argument List:", str(sys.argv[1:]))

    fig, ax1 = plt.subplots(1, 1)
    for file in sys.argv[1:]:
        data = build_dataframe(file)
        mask = data["name"].str.contains("Local")
        ax1.plot(data[~mask]["Elements"], data[~mask]["cpu_time"], label=file[:-5])

    ax1.set_yscale("log", base=10)
    ax1.set_xscale("log", base=2)
    ax1.legend()
    ax1.set_xlabel("Elements")
    ax1.set_ylabel("cpu_time (ns)")
    plt.show()


if __name__ == "__main__":
    main()
