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


def comp_local(file):
    fig, (ax1, ax2) = plt.subplots(2, 1)
    data = build_dataframe(file)
    mask_serial_simple_id = data["name"].str.contains("benchSerialSimpleId")
    mask_copy = data["name"].str.contains("benchCopy")
    mask = data["name"].str.contains("Local")
    nlocal = data[~mask & ~mask_serial_simple_id & ~mask_copy]
    local = data[mask]
    elements = data[mask]["Elements"]
    relative = [j / i for i, j in zip(local["cpu_time"], nlocal["cpu_time"])]
    ax1.plot(elements, nlocal["cpu_time"], label="non local shuffle")
    ax1.plot(elements, local["cpu_time"], label="local shuffle")
    ax2.plot(
        elements, nlocal["cpu_time"] / nlocal["cpu_time"], label="non local shuffle"
    )
    ax2.plot(elements, relative, label="local shuffle")
    ax1.set_yscale("log", base=10)
    ax1.set_xscale("log", base=2)
    ax2.set_xscale("log", base=2)
    ax1.set_xlabel("Elements")
    ax2.set_xlabel("Elements")
    ax1.set_ylabel("cpu_time (ns)")
    ax2.set_ylabel("speedup")
    ax1.legend()
    ax2.legend()
    plt.show()
    return


def comp_cache_local(file1, file2):
    fig, (ax1, ax2) = plt.subplots(2, 1)
    data = build_dataframe(file2)
    data1 = build_dataframe(file1)
    mask_serial_simple_id = data["name"].str.contains("benchSerialSimpleId")
    mask_copy = data["name"].str.contains("benchCopy")
    mask = data["name"].str.contains("Local")
    nlocal = data[~mask & ~mask_serial_simple_id & ~mask_copy]
    local = data[mask]
    elements = data[mask]["Elements"]
    relative_local = [j / i for i, j in zip(local["cpu_time"], data1["cpu_time"])]
    relative_nlocal = [j / i for i, j in zip(nlocal["cpu_time"], data1["cpu_time"])]
    ax1.plot(elements, nlocal["cpu_time"], label="non local shuffle")
    ax1.plot(elements, local["cpu_time"], label="local shuffle")
    ax1.plot(elements, data1["cpu_time"], label="before cache aligned")
    ax2.plot(
        elements, data1["cpu_time"] / data1["cpu_time"], label="before chache aligned"
    )
    ax2.plot(elements, relative_local, label="local shuffle")
    ax2.plot(elements, relative_nlocal, label="non local shuffle")
    ax1.set_yscale("log", base=10)
    ax1.set_xscale("log", base=2)
    ax2.set_xscale("log", base=2)
    ax1.set_xlabel("Elements")
    ax2.set_xlabel("Elements")
    ax1.set_ylabel("cpu_time (ns)")
    ax2.set_ylabel("speedup")
    ax1.legend()
    ax2.legend()
    plt.show()
    return


def usage():
    print("USAGE: {} <file1> [file2]", sys.argv[0])
    return


def main():
    print("Number of arguments:", len(sys.argv) - 1, "arguments")
    print("Argument List:", str(sys.argv[1:]))

    if len(sys.argv) == 2:
        comp_local(sys.argv[1])
    elif len(sys.argv) == 3:
        comp_cache_local(sys.argv[1], sys.argv[2])
    else:
        print("ERROR!")
        usage()


if __name__ == "__main__":
    main()
