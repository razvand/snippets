#!/usr/bin/env python3

import sys
import csv
import re
import matplotlib.pyplot as plt
import numpy

INPUT_FILE = "input.csv"
data = {}


def do_plot():
    plt.style.use('_mpl-gallery')

    eval_data = [data[k]["evaluation"]["values"] for k in data.keys()]
    rel_data = [data[k]["relevance"]["values"] for k in data.keys()]

    # plot
    fig, axs = plt.subplots(nrows=1, ncols=2, figsize=(9,4))
    plt.subplots_adjust(left=0.05, right=0.95, top=0.90, bottom=0.25)

    axs[0].violinplot(eval_data,
                  showmeans=True,
                  showmedians=False)
    axs[0].set_title('Evaluare')

    axs[1].violinplot(rel_data,
                  showmeans=True,
                  showmedians=False)
    axs[1].set_title('Relevanță')

    for ax in axs:
        ax.xaxis.grid(False)
        ax.yaxis.grid(True)
        ax.set_xticks([i for i in range(1,11)])
        ax.set_xticklabels(list(data.keys()), rotation=90, fontsize=6)

    plt.savefig("violin.png", dpi=600)

    fig, ax = plt.subplots()
    plt.subplots_adjust(left=0.15, right=0.90, top=0.90, bottom=0.15)

    rel_means = [data[k]["relevance"]["mean"] for k in data.keys()]
    eval_means = [data[k]["evaluation"]["mean"] for k in data.keys()]
    ax.scatter(rel_means, eval_means, c='limegreen', s=12)

    for i, topic in enumerate(data.keys()):
        ax.annotate(topic, (rel_means[i], eval_means[i]), size=3, ha='center', va='center')

    ax.xaxis.grid(True)
    ax.yaxis.grid(True)
    ax.set_xlabel("Relevanță", fontsize=5)
    ax.set_ylabel("Evaluare", fontsize=5)
    ax.set_xticks([i for i in range(5,11)])
    ax.set_xticklabels([i for i in range(5,11)], fontsize=4)
    ax.set_yticks([i for i in range(5,11)])
    ax.set_yticklabels([i for i in range(5,11)], fontsize=4)
    ax.set_xlim(5,10)
    ax.set_ylim(5,10)

    plt.savefig("scatter.png", dpi=400)


def read_data():
    with open(INPUT_FILE) as csvfile:
        tmp_data = {}
        reader = csv.reader(csvfile, delimiter=',')
        header = next(reader, None)
        for h in header:
            tmp_data[h] = {
                    "values": []
                    }
        for row in reader:
            for h, v in zip(header, row):
                tmp_data[h]["values"].append(v)

    for k in tmp_data.keys():
        name, grade_type = re.split(r"[()]", k)[0:2]
        if not name in data.keys():
            data[name] = {
                    "relevance": {
                        },
                    "evaluation": {
                        }
                    }
        if grade_type == "C":
            data[name]["relevance"]["values"] = tmp_data[k]["values"]
        elif grade_type == "E":
            data[name]["evaluation"]["values"] = tmp_data[k]["values"]


def convert_to_float(x):
    try:
        v = float(x)
        return v
    except ValueError:
        return 0


def process_data():
    for k in data.keys():
        for k2 in data[k].keys():
            l = [float(i) for i in data[k][k2]["values"] if i != ""]
            data[k][k2]["mean"] = numpy.mean(l)
            data[k][k2]["median"] = numpy.median(l)
            data[k][k2]["max"] = max(l)
            data[k][k2]["min"] = min(l)
            data[k][k2]["num"] = len(l)

            l = [convert_to_float(i) for i in data[k][k2]["values"]]
            data[k][k2]["values"] = l

    for k in data.keys():
        data[k]["dot"] = numpy.dot(data[k]["relevance"]["values"], data[k]["evaluation"]["values"])
        data[k]["ratio"] = data[k]["evaluation"]["mean"] / data[k]["relevance"]["mean"]


def print_data():
    print("Topic,GradeType,Num,Mean,Median,Min,Max")
    for k in data.keys():
        print(f"{k},relevance,{data[k]['relevance']['num']}," \
              f"{data[k]['relevance']['mean']:.2f}," \
              f"{data[k]['relevance']['median']}," \
              f"{data[k]['relevance']['min']}," \
              f"{data[k]['relevance']['max']}")
        print(f"{k},evaluation,{data[k]['evaluation']['num']}," \
              f"{data[k]['evaluation']['mean']:.2f}," \
              f"{data[k]['evaluation']['median']}," \
              f"{data[k]['evaluation']['min']}," \
              f"{data[k]['evaluation']['max']}")


def main():
    read_data()
    process_data()
    print_data()
    do_plot()


if __name__ == "__main__":
    sys.exit(main())
