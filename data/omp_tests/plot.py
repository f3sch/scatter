#!/bin/python3

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

    frame = {}
    speedup = {}
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2)
    for file in sys.argv[1:]:
        data = build_dataframe(file)
        frame[file.rsplit(".", 1)[0]] = copy.deepcopy(data["real_time"])
        ax1.plot(data["Elements"], data["real_time"], label=file[:-5])
        ax3.plot(
            data["Elements"],
            data["Bytes_processed"] / data["real_time"],
            label=file[:-5],
        )  # time is in ns cancelling the G
        ax4.plot(
            data["Elements"],
            data["GOP"] / data["real_time"],
            label=file[:-5],
        )

    # calculate speedup
    for (k, v) in frame.items():
        speedup[k] = frame["serialBench"] / frame[k]

    # plot speedup
    for (k, v) in speedup.items():
        ax2.plot([2 ** i for i in range(15, 31)], v, label=k)

    ax1.set_yscale("log", base=10)
    ax1.set_xscale("log", base=2)
    ax2.set_xscale("log", base=2)
    ax3.set_xscale("log", base=2)
    ax4.set_xscale("log", base=2)
    ax4.set_yscale("log", base=10)
    ax1.legend()
    ax2.legend()
    ax3.legend()
    ax4.legend()
    ax1.set_xlabel("Elements")
    ax2.set_xlabel("Elements")
    ax3.set_xlabel("Elements")
    ax1.set_ylabel("real_time (ns)")
    ax2.set_ylabel("speedup")
    ax3.set_ylabel("throughput (GB/s)")
    ax4.set_ylabel("GOPS")
    plt.show()


if __name__ == "__main__":
    main()
