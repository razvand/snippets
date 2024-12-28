# Plots

These are plots generated with [Matplotlib](https://matplotlib.org/).

The `so-2024-2025-lecturer-eval.py` script processes the data from `input.csv`.
Run it using:

```console
python so-2024-2025-lecturer-eval.py
```

It prints out a CSV format of processed results and two files:

- `violin.png` is a [violin plot](https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.violinplot.html) with two subplots, one for evaluation and one for relevance

- `scatter.png` is a [scatter plot](https://matplotlib.org/stable/api/_as_gen/matplotlib.axes.Axes.scatter.html) with placement of evaluation + relevance markers on a grid layout

The generated `processed.csv`, `violin.png` and `scatter.png` files are part of the repository.
